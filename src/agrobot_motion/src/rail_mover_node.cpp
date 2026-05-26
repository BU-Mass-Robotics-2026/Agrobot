#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.hpp>
#include "agrobot_motion/srv/rail_go_to.hpp"

#include <algorithm>
#include <cmath>
#include <functional>
#include <limits>
#include <memory>
#include <string>
#include <vector>

using MoveGroupInterface = moveit::planning_interface::MoveGroupInterface;
using RailGoTo = agrobot_motion::srv::RailGoTo;

namespace
{
    constexpr double kRailMin = 0.05;
    constexpr double kRailMax = 1.30;
    constexpr char kPlanningGroup[] = "rail";
    constexpr char kRailJointName[] = "joint0";
}

class RailMoverNode : public rclcpp::Node
{
  public:

    // -------------------------------------------------------------------------------------------------
    // Constructor
    // -------------------------------------------------------------------------------------------------  
    RailMoverNode() : rclcpp::Node("rail_mover")
    {
        velocity_scaling = this->declare_parameter<double>("rail_velocity_scaling", 0.1);
        acceleration_scaling = this->declare_parameter<double>("rail_acceleration_scaling", 0.1);
        planning_time = this->declare_parameter<double>("rail_planning_time", 5.0);

        RCLCPP_INFO(this->get_logger(), "rail_mover starting: velocity_scale = %.2f acceleration_scale = %.2f planning_time = %.1fs usable_range = [%.3f, %.3f] m", velocity_scaling, acceleration_scaling, planning_time, kRailMin, kRailMax);

        service_callback_group = this->create_callback_group(rclcpp::CallbackGroupType::Reentrant);
    }

    // -------------------------------------------------------------------------------------------------
    // MoveGroup initialization and service setup
    // -------------------------------------------------------------------------------------------------
    void initMoveGroup()
    {
        move_group = std::make_shared<MoveGroupInterface>(shared_from_this(), kPlanningGroup); // Initialize MoveGroupInterface for the specified planning group

        // Set the default velocity and acceleration scaling factors for the MoveGroupInterface based on the node parameters
        move_group->setMaxVelocityScalingFactor(velocity_scaling);
        move_group->setMaxAccelerationScalingFactor(acceleration_scaling);
        move_group->setPlanningTime(planning_time);

        RCLCPP_INFO(this->get_logger(), "MoveGroupInterface ready for group '%s'. Planning frame: %s", kPlanningGroup, move_group->getPlanningFrame().c_str());

        // Create the service with the appropriate callback and QoS settings
        service = this->create_service<RailGoTo>(
            "/rail_mover/goto",
            std::bind(&RailMoverNode::handleGoTo, this, std::placeholders::_1, std::placeholders::_2),
            rclcpp::ServicesQoS(),
            service_callback_group);

        RCLCPP_INFO(this->get_logger(), "Service '/rail_mover/goto' ready");
    }

  private:

    // -------------------------------------------------------------------------------------------------
    // Private members
    // -------------------------------------------------------------------------------------------------

    // Configurable parameters with defaults
    double velocity_scaling;
    double acceleration_scaling;
    double planning_time;

    // MoveIt and ROS service members
    rclcpp::CallbackGroup::SharedPtr service_callback_group;
    std::shared_ptr<MoveGroupInterface> move_group;
    rclcpp::Service<RailGoTo>::SharedPtr service;

    // -------------------------------------------------------------------------------------------------
    // Service callback
    // -------------------------------------------------------------------------------------------------
    void handleGoTo(const std::shared_ptr<RailGoTo::Request> request, std::shared_ptr<RailGoTo::Response> response)
    {
      const double requested = request->target_position;
      response->requested_position = requested;

      double target = requested;
      bool clamped = false;

      // --- Validate finiteness ---
      if (!std::isfinite(requested))
      {
        response->success = false;
        response->clamped = false;
        response->final_position = currentRailPosition();
        response->message = "Invalid target position: not finite";
        RCLCPP_WARN(this->get_logger(), "%s", response->message.c_str());
        return;
      }

      // --- Clamp to rail limits ---
      if (requested < kRailMin) 
      {
        target = kRailMin;
        clamped = true;
      } 
      else if (requested > kRailMax) 
      {
        target = kRailMax;
        clamped = true;
      }
      response->clamped = clamped;

      if (clamped)
      {
        RCLCPP_WARN(this->get_logger(), "Target %.4f outside [%.3f, %.3f] -> clamped to %.4f (END-OF-RAIL)", requested, kRailMin, kRailMax, target);
      }
      RCLCPP_INFO(this->get_logger(), "Go to: joint0 -> %.4f m%s", target, clamped ? " (clamped)" : "");

      move_group->setStartStateToCurrentState();

      // --- Set joint target ---
      if (!move_group->setJointValueTarget(kRailJointName, target))
      {
        response->success = false;
        response->final_position = currentRailPosition();
        response->message = "setJointValueTarget rejected the (clamped) target";
        RCLCPP_ERROR(this->get_logger(), "%s", response->message.c_str());
        return;
      }

      // --- Plan ---
      MoveGroupInterface::Plan plan;
      if (move_group->plan(plan) != moveit::core::MoveItErrorCode::SUCCESS)
      {
        response->success = false;
        response->final_position = currentRailPosition();
        response->message = "Planning failed";
        RCLCPP_ERROR(this->get_logger(), "%s", response->message.c_str());
        return;
      }

      // --- Execute ---
      const bool executed = (move_group->execute(plan) == moveit::core::MoveItErrorCode::SUCCESS);
      response->final_position = currentRailPosition();

      if (!executed)
      {
        response->success = false;
        response->message = "MoveIt execution failed (final joint0=" + std::to_string(response->final_position) + ")";
        RCLCPP_ERROR(this->get_logger(), "%s", response->message.c_str());
        return;
      }
      response->message = clamped ? "ok (target was clamped to end of rail)" : "ok";
      RCLCPP_INFO(this->get_logger(), "Move complete: joint0 = %.4f m", response->final_position);
    }

    // -------------------------------------------------------------------------------------------------
    // Helper to read current rail position (joint0)
    // -------------------------------------------------------------------------------------------------
    double currentRailPosition()
    {
      try
      {
        const std::vector<double> current_values = move_group->getCurrentJointValues();
        if (!current_values.empty())
        {
          return current_values.front();
        }
      }

      catch (const std::exception& e)
      {
        RCLCPP_WARN(this->get_logger(), "Could not read current joint0: %s", e.what());
      }
      return std::numeric_limits<double>::quiet_NaN();
    }
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<RailMoverNode>();
  rclcpp::executors::MultiThreadedExecutor executor;
  executor.add_node(node);
  node->initMoveGroup();
  executor.spin();
  rclcpp::shutdown();
  return 0;
}