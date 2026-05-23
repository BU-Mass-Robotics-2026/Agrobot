// rail_mover_node.cpp
// ---------------------------------------------------------------------------
// Service node that moves the rail joint (joint0, prismatic) to an absolute
// coordinate using MoveIt's "rail" planning group.
//
// Exposes:  /rail_mover/goto   (agrobot_motion/srv/RailGoto)
//
// Usable rail range [0.05, 1.30] m, inset from URDF limits [0.0, 1.35] by a
// 5 cm end-stop margin. Out-of-range targets are CLAMPED, not rejected, and
// the response sets clamped=true (the supervisor uses that as END-OF-RAIL).
// Velocity/accel scaling are ROS params (default 0.1).
//
// Uses a MultiThreadedExecutor + reentrant callback group: a service node
// also running MoveGroupInterface deadlocks on a SingleThreadedExecutor.
// ---------------------------------------------------------------------------

#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.hpp>
#include "agrobot_motion/srv/rail_goto.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <memory>
#include <string>
#include <vector>

namespace
{
constexpr double kRailMin = 0.05;
constexpr double kRailMax = 1.30;
constexpr char kPlanningGroup[] = "rail";
constexpr char kRailJointName[] = "joint0";
}  // namespace

class RailMoverNode : public rclcpp::Node
{
public:
  RailMoverNode()
  : rclcpp::Node("rail_mover")
  {
    velocity_scaling_ =
      this->declare_parameter<double>("rail_velocity_scaling", 0.1);
    accel_scaling_ =
      this->declare_parameter<double>("rail_acceleration_scaling", 0.1);
    planning_time_ =
      this->declare_parameter<double>("rail_planning_time", 5.0);

    RCLCPP_INFO(
      this->get_logger(),
      "rail_mover starting: vel_scale=%.2f accel_scale=%.2f plan_time=%.1fs "
      "usable_range=[%.3f, %.3f] m",
      velocity_scaling_, accel_scaling_, planning_time_, kRailMin, kRailMax);

    service_cb_group_ =
      this->create_callback_group(rclcpp::CallbackGroupType::Reentrant);
  }

  void initMoveGroup()
  {
    move_group_ = std::make_shared<moveit::planning_interface::MoveGroupInterface>(
      shared_from_this(), kPlanningGroup);

    move_group_->setMaxVelocityScalingFactor(velocity_scaling_);
    move_group_->setMaxAccelerationScalingFactor(accel_scaling_);
    move_group_->setPlanningTime(planning_time_);

    RCLCPP_INFO(
      this->get_logger(),
      "MoveGroupInterface ready for group '%s'. Planning frame: %s",
      kPlanningGroup, move_group_->getPlanningFrame().c_str());

    service_ = this->create_service<agrobot_motion::srv::RailGoto>(
      "/rail_mover/goto",
      std::bind(&RailMoverNode::handleGoto, this,
                std::placeholders::_1, std::placeholders::_2),
      rclcpp::ServicesQoS(),
      service_cb_group_);

    RCLCPP_INFO(this->get_logger(), "Service ready: /rail_mover/goto");
  }

private:
  void handleGoto(
    const std::shared_ptr<agrobot_motion::srv::RailGoto::Request> req,
    std::shared_ptr<agrobot_motion::srv::RailGoto::Response> res)
  {
    const double requested = req->target_position;
    res->requested_position = requested;

    double target = requested;
    bool clamped = false;

    if (!std::isfinite(requested)) {
      res->success = false;
      res->clamped = false;
      res->final_position = currentRailPosition();
      res->message = "target is not a finite number";
      RCLCPP_WARN(this->get_logger(), "%s", res->message.c_str());
      return;
    }

    if (requested < kRailMin) {
      target = kRailMin;
      clamped = true;
    } else if (requested > kRailMax) {
      target = kRailMax;
      clamped = true;
    }
    res->clamped = clamped;

    if (clamped) {
      RCLCPP_WARN(
        this->get_logger(),
        "Target %.4f outside [%.3f, %.3f] -> clamped to %.4f (END-OF-RAIL)",
        requested, kRailMin, kRailMax, target);
    }
    RCLCPP_INFO(this->get_logger(),
                "Goto: joint0 -> %.4f m%s",
                target, clamped ? " (clamped)" : "");

    move_group_->setStartStateToCurrentState();

    if (!move_group_->setJointValueTarget(kRailJointName, target)) {
      res->success = false;
      res->final_position = currentRailPosition();
      res->message = "setJointValueTarget rejected the (clamped) target";
      RCLCPP_ERROR(this->get_logger(), "%s", res->message.c_str());
      return;
    }

    moveit::planning_interface::MoveGroupInterface::Plan plan;
    if (move_group_->plan(plan) != moveit::core::MoveItErrorCode::SUCCESS) {
      res->success = false;
      res->final_position = currentRailPosition();
      res->message = "MoveIt planning failed";
      RCLCPP_ERROR(this->get_logger(), "%s", res->message.c_str());
      return;
    }

    const bool executed =
      (move_group_->execute(plan) == moveit::core::MoveItErrorCode::SUCCESS);
    res->final_position = currentRailPosition();

    if (!executed) {
      res->success = false;
      res->message = "MoveIt execution failed (final joint0=" +
                     std::to_string(res->final_position) + ")";
      RCLCPP_ERROR(this->get_logger(), "%s", res->message.c_str());
      return;
    }

    res->success = true;
    res->message = clamped ? "ok (target was clamped to end of rail)" : "ok";
    RCLCPP_INFO(this->get_logger(),
                "Move complete: joint0 = %.4f m", res->final_position);
  }

  double currentRailPosition()
  {
    try {
      const std::vector<double> vals = move_group_->getCurrentJointValues();
      if (!vals.empty()) {
        return vals.front();
      }
    } catch (const std::exception & e) {
      RCLCPP_WARN(this->get_logger(),
                  "Could not read current joint0: %s", e.what());
    }
    return std::numeric_limits<double>::quiet_NaN();
  }

  double velocity_scaling_;
  double accel_scaling_;
  double planning_time_;

  rclcpp::CallbackGroup::SharedPtr service_cb_group_;
  std::shared_ptr<moveit::planning_interface::MoveGroupInterface> move_group_;
  rclcpp::Service<agrobot_motion::srv::RailGoto>::SharedPtr service_;
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
