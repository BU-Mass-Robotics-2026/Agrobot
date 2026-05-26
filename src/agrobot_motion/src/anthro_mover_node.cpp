#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.hpp>
#include "agrobot_motion/srv/anthro_go_to.hpp"

#include <cmath>
#include <functional>
#include <memory>
#include <string>
#include <vector>

using MoveGroupInterface = moveit::planning_interface::MoveGroupInterface;
using AnthroGoTo = agrobot_motion::srv::AnthroGoTo;

namespace
{
    constexpr char kPlanningGroup[] = "anthro"; // anthro is J1..J5 -> exactly 5 solution joints
    constexpr std::size_t kNumJoints = 5;
    const std::vector<std::string> kJointNames = {"joint1", "joint2", "joint3", "joint4", "joint5"};
}

class AnthroMoverNode : public rclcpp::Node
{
    public:

        // -------------------------------------------------------------------------------------------------
        // Constructor
        // -------------------------------------------------------------------------------------------------    
        AnthroMoverNode() : rclcpp::Node("anthro_mover")
        {
            // Declare parameters with defaults
            velocity_scaling = this->declare_parameter<double>("anthro_velocity_scaling", 0.2);
            acceleration_scaling = this->declare_parameter<double>("anthro_acceleration_scaling", 0.2);
            planning_time = this->declare_parameter<double>("anthro_planning_time", 5.0);

            RCLCPP_INFO(this->get_logger(), "anthro_mover starting: velocity_scale = %.2f acceleration_scale = %.2f planning_time = %.1fs", velocity_scaling, acceleration_scaling, planning_time);

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
            service = this->create_service<AnthroGoTo>(
                "/anthro_mover/goto",
                std::bind(&AnthroMoverNode::handleGoTo, this, std::placeholders::_1, std::placeholders::_2),
                rclcpp::ServicesQoS(),
                service_callback_group);

            RCLCPP_INFO(this->get_logger(), "Service ready: /anthro_mover/goto");
        }

    private:

        // Configurable parameters with defaults
        double velocity_scaling;
        double acceleration_scaling;
        double planning_time;

        // MoveIt and ROS service members
        rclcpp::CallbackGroup::SharedPtr service_callback_group;
        std::shared_ptr<MoveGroupInterface> move_group;
        rclcpp::Service<AnthroGoTo>::SharedPtr service;

        // -------------------------------------------------------------------------------------------------
        // Service callback
        // -------------------------------------------------------------------------------------------------
        void handleGoTo(const std::shared_ptr<AnthroGoTo::Request> request, const std::shared_ptr<AnthroGoTo::Response> response)
        {
            // --- Validate request length ---
            if (request->joint_positions.size() != kNumJoints)
            {
                response->success = false;
                response->final_positions = currentJointValues();
                response->message = "expected " + std::to_string(kNumJoints) + " joint values [J1..J5], got " + std::to_string(request->joint_positions.size());
                RCLCPP_WARN(this->get_logger(), "Rejected: %s", response->message.c_str());
                return;
            }

            // --- Validate finiteness ---
            for (std::size_t i = 0; i < kNumJoints; ++i)
            {
                if (!std::isfinite(request->joint_positions[i]))
                {
                    response->success = false;
                    response->final_positions = currentJointValues();
                    response->message = "joint value " + std::to_string(i) + " is not finite";
                    RCLCPP_WARN(this->get_logger(), "Rejected: %s", response->message.c_str());
                    return;
                }
            }

            // --- Log the target in a readable form ---
            std::string target;
            for (std::size_t i = 0; i < kNumJoints; ++i)
            {
                target += std::to_string(request->joint_positions[i]);
                if (i + 1 < kNumJoints)
                    target += ", ";
            }
            RCLCPP_INFO(this->get_logger(), "Go to: anthro [J1..J5] -> [%s] rad", target.c_str());

            // --- Per-call velocity scaling ---
            // Request overrides the node default
            // A non-positive request value means "use the node's configured default"
            double scaling = velocity_scaling; // node param default
            if (request->velocity_scaling > 0.0)
            {
                scaling = std::min(request->velocity_scaling, 1.0); // clamp to valid max
            }
            move_group->setMaxVelocityScalingFactor(scaling);
            move_group->setMaxAccelerationScalingFactor(scaling);
            RCLCPP_INFO(this->get_logger(), "Go to: anthro [J1..J5] (vel_scale=%.2f)", scaling);

            // --- Set joint target ---
            move_group->setStartStateToCurrentState();
            std::map<std::string, double> target_map;
            for (std::size_t i = 0; i < kNumJoints; ++i)
            {
                target_map[kJointNames[i]] = request->joint_positions[i];
            }

            if (!move_group->setJointValueTarget(target_map))
            {
                response->success = false;
                response->final_positions = currentJointValues();
                response->message = "setJointValueTarget rejected the target (joint limits exceeded?)";
                RCLCPP_WARN(this->get_logger(), "%s", response->message.c_str());
                return;
            }

            // --- Plan ---
            MoveGroupInterface::Plan plan;
            bool success = (move_group->plan(plan) == moveit::core::MoveItErrorCode::SUCCESS);
            if (!success)
            {
                response->success = false;
                response->final_positions = currentJointValues();
                response->message = "MoveIt Planning failed";
                RCLCPP_WARN(this->get_logger(), "%s", response->message.c_str());
                return;
            }

            // --- Execute ---
            const bool executed = (move_group->execute(plan) == moveit::core::MoveItErrorCode::SUCCESS);
            response->final_positions = currentJointValues();

            if (!executed)
            {
                response->success = false;
                response->message = "MoveIt execution failed";
                RCLCPP_ERROR(this->get_logger(), "%s", response->message.c_str());
                return;
            }

            response->success = true;
            response->message = "Move successful";
            RCLCPP_INFO(this->get_logger(), "%s", response->message.c_str());
        }

        // -------------------------------------------------------------------------------------------------
        // Helper to get current joint values with error handling (returns NaN vector on failure)
        // -------------------------------------------------------------------------------------------------
        std::vector<double> currentJointValues()
        {
            try
            {
                return move_group->getCurrentJointValues();
            }
            catch (const std::exception& e)
            {
                RCLCPP_ERROR(this->get_logger(), "Failed to get current joint values: %s", e.what());
                return std::vector<double>(kNumJoints, std::numeric_limits<double>::quiet_NaN());
            }
        }
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<AnthroMoverNode>();
  rclcpp::executors::MultiThreadedExecutor executor;
  executor.add_node(node);
  node->initMoveGroup();
  executor.spin();
  rclcpp::shutdown();
  return 0;
}