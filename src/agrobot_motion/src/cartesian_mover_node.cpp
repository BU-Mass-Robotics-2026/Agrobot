#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <moveit/move_group_interface/move_group_interface.hpp>
#include <moveit_msgs/msg/robot_trajectory.hpp>
#include <moveit_msgs/msg/display_trajectory.hpp>
#include <moveit/robot_state/conversions.hpp>

#include "agrobot_motion/srv/cartesian_go_to.hpp"

#include <algorithm>
#include <cmath>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using MoveGroupInterface = moveit::planning_interface::MoveGroupInterface;
using CartesianGoTo = agrobot_motion::srv::CartesianGoTo;

class CartesianMoverNode : public rclcpp::Node
{
    public:

        // -------------------------------------------------------------------------------------------------
        // Constructor
        // -------------------------------------------------------------------------------------------------
        CartesianMoverNode() : rclcpp::Node("cartesian_mover")
        {
            planning_group = this->declare_parameter<std::string>("planning_group", "anthro");
            default_eef_step = this->declare_parameter<double>("eef_step", 0.01);
            default_min_fraction = this->declare_parameter<double>("min_fraction", 0.95);
            velocity_scaling = this->declare_parameter<double>("velocity_scaling", 0.10);
            acceleration_scaling = this->declare_parameter<double>("acceleration_scaling", 0.10);
            planning_time = this->declare_parameter<double>("planning_time", 5.0);
            publish_display = this->declare_parameter<bool>("publish_display", true);
            display_topic = this->declare_parameter<std::string>("display_topic", "/display_planned_path");
            service_callback_group = this->create_callback_group(rclcpp::CallbackGroupType::Reentrant);
            display_pub = this->create_publisher<moveit_msgs::msg::DisplayTrajectory>(display_topic, rclcpp::QoS(10).transient_local());

            RCLCPP_INFO
            (
                this->get_logger(),
                "cartesian_mover starting: group=%s eef_step=%.4f min_fraction=%.2f vel=%.2f accel=%.2f plan_time=%.1f",
                planning_group.c_str(), default_eef_step, default_min_fraction, velocity_scaling, acceleration_scaling, planning_time
            );
        }

        // -------------------------------------------------------------------------------------------------
        // MoveGroup initialization and service setup
        // -------------------------------------------------------------------------------------------------
        void initMoveGroup()
        {
            move_group = std::make_shared<MoveGroupInterface>(shared_from_this(), planning_group);

            move_group->setPlanningTime(planning_time);
            move_group->setMaxVelocityScalingFactor(velocity_scaling);
            move_group->setMaxAccelerationScalingFactor(acceleration_scaling);

            RCLCPP_INFO
            (
                this->get_logger(),
                "MoveGroupInterface ready for group '%s'. Planning frame: '%s'. Default EE link: '%s'",
                planning_group.c_str(), move_group->getPlanningFrame().c_str(), move_group->getEndEffectorLink().c_str()
            );

            service = this->create_service<CartesianGoTo>
            (
                "/cartesian_mover/goto",
                std::bind(&CartesianMoverNode::handleGoTo, this, std::placeholders::_1, std::placeholders::_2),
                rclcpp::ServicesQoS(),
                service_callback_group
            );

            RCLCPP_INFO(this->get_logger(), "Service ready: /cartesian_mover/goto");
        }

    private:

        // -------------------------------------------------------------------------------------------------
        // Private members
        // -------------------------------------------------------------------------------------------------
        // Configurable parameters with defaults
        double default_eef_step;
        double default_min_fraction;
        double velocity_scaling;
        double acceleration_scaling;
        double planning_time;
        bool publish_display;

        std::string planning_group;
        std::string display_topic;

        // MoveIt and ROS service members
        rclcpp::CallbackGroup::SharedPtr service_callback_group;
        rclcpp::Publisher<moveit_msgs::msg::DisplayTrajectory>::SharedPtr display_pub;
        std::shared_ptr<MoveGroupInterface> move_group;
        rclcpp::Service<CartesianGoTo>::SharedPtr service;

        // -------------------------------------------------------------------------------------------------
        // Helper functions
        // -------------------------------------------------------------------------------------------------
        // Check if all components of the pose are finite numbers
        static bool finitePose(const geometry_msgs::msg::Pose & pose)
        {
            return std::isfinite(pose.position.x) &&
                   std::isfinite(pose.position.y) &&
                   std::isfinite(pose.position.z) &&
                   std::isfinite(pose.orientation.x) &&
                   std::isfinite(pose.orientation.y) &&
                   std::isfinite(pose.orientation.z) &&
                   std::isfinite(pose.orientation.w);
        }

        // Compute the norm of the orientation quaternion
        static double quatNorm(const geometry_msgs::msg::Pose & pose)
        {
            return std::sqrt
            (
                pose.orientation.x * pose.orientation.x +
                pose.orientation.y * pose.orientation.y +
                pose.orientation.z * pose.orientation.z +
                pose.orientation.w * pose.orientation.w
            );
        }

        // Format a pose as a string for logging
        static std::string poseString(const geometry_msgs::msg::Pose & pose)
        {
            std::ostringstream oss;
            oss << "position=("
                << pose.position.x << ", "
                << pose.position.y << ", "
                << pose.position.z << ") orientation=("
                << pose.orientation.x << ", "
                << pose.orientation.y << ", "
                << pose.orientation.z << ", "
                << pose.orientation.w << ")";
            return oss.str();
        }

        // Publish a DisplayTrajectory for visualization in RViz
        void publishDisplayTrajectory(const moveit_msgs::msg::RobotTrajectory & trajectory)
        {
            if (!publish_display || !display_pub)
            {
                return;
            }

            moveit_msgs::msg::DisplayTrajectory display_msg;
            display_msg.model_id = "agrobot";

            try
            {
                auto state = move_group->getCurrentState(2.0);
                if (state)
                {
                    moveit::core::robotStateToRobotStateMsg(*state, display_msg.trajectory_start);
                }
            }

            catch (const std::exception & e) 
            {
                RCLCPP_WARN(this->get_logger(), "Could not fill DisplayTrajectory start state: %s", e.what());
            }

            display_msg.trajectory.push_back(trajectory);
            display_pub->publish(display_msg);

            RCLCPP_INFO(this->get_logger(), "Published Cartesian DisplayTrajectory to '%s'", display_topic.c_str());
        }

        // -------------------------------------------------------------------------------------------------
        // Service callback
        // -------------------------------------------------------------------------------------------------
        void handleGoTo(const std::shared_ptr<CartesianGoTo::Request> request, std::shared_ptr<CartesianGoTo::Response> response)
        {
            response->success = false;
            response->fraction = 0.0;

            // --- Validate MoveGroupInterface ---
            if (!move_group)
            {
                response->message = "MoveGroupInterface not initialized";
                RCLCPP_ERROR(this->get_logger(), "%s", response->message.c_str());
                return;
            }

            // --- Validate target pose ---
            if (!finitePose(request->target))
            {
                response->success = false;
                response->message = "Target pose contains non-finite values";
                RCLCPP_ERROR(this->get_logger(), "%s", response->message.c_str());
                return;
            }

            // --- Validate quaternion norm ---
            const double qnorm = quatNorm(request->target);
            if (qnorm < 0.5 || qnorm > 1.5)
            {
                response->success = false;
                response->message = "target orientation quaternion norm is invalid: " + std::to_string(qnorm);
                RCLCPP_ERROR(this->get_logger(), "%s", response->message.c_str());
                return;
            }

            // --- Set MoveGroup parameters based on request or defaults ---
            const double eef_step = (request->eef_step > 0.0) ? request->eef_step : default_eef_step;
            const double min_fraction = (request->min_fraction > 0.0) ? request->min_fraction : default_min_fraction;

            // --- Override MoveGroup velocity and acceleration scaling if specified in request ---
            double velocity = velocity_scaling;
            if (request->velocity_scaling > 0.0)
            {
                velocity = std::clamp(request->velocity_scaling, 0.01, 1.0);
            }

            // --- Override MoveGroup velocity and acceleration scaling if specified in request ---
            double acceleration = acceleration_scaling;
            if (request->acceleration_scaling > 0.0)
            {
                acceleration = std::clamp(request->acceleration_scaling, 0.01, 1.0);
            }

            move_group->setMaxVelocityScalingFactor(velocity);
            move_group->setMaxAccelerationScalingFactor(acceleration);
            move_group->setPlanningTime(planning_time);

            const std::string frame = request->frame_id.empty() ? move_group->getPlanningFrame() : request->frame_id;
            move_group->setPoseReferenceFrame(frame);

            // --- Set end effector link if specified in request ---
            if (!request->end_effector_link.empty())
            {
                try
                {
                    move_group->setEndEffectorLink(request->end_effector_link);
                }
                catch (const std::exception & e)
                {
                    response->success = false;
                    response->message = "Invalid end effector link: " + request->end_effector_link + ". Error: " + e.what();
                    RCLCPP_ERROR(this->get_logger(), "%s", response->message.c_str());
                    return;
                }
            }
            const std::string ee_link = move_group->getEndEffectorLink();

            RCLCPP_INFO
            (
                this->get_logger(),
                "Cartesian request: frame='%s' ee='%s' execute=%s eef_step=%.4f min_fraction=%.2f vel=%.2f accel=%.2f target=%s",
                frame.c_str(), ee_link.c_str(), request->execute ? "true" : "false", eef_step, min_fraction, velocity, acceleration, poseString(request->target).c_str()
            );

            // --- Compute Cartesian path ---
            std::vector<geometry_msgs::msg::Pose> waypoints;
            waypoints.push_back(request->target);
            
            moveit_msgs::msg::RobotTrajectory trajectory;
            const double fraction = move_group->computeCartesianPath(waypoints, eef_step, trajectory, true);
            response->fraction = fraction;

            if (fraction > 0.0)
            {
                publishDisplayTrajectory(trajectory);
            }

            if (fraction < min_fraction)
            {
                response->message = "Cartesian path fraction " + std::to_string(fraction) + " below required " + std::to_string(min_fraction) + "; refusing to execute partial path";
                RCLCPP_WARN(this->get_logger(), "%s", response->message.c_str());
                return;
            }

            if (!request->execute)
            {
                response->success = true;
                response->message = "Cartesian path valid; dry-run only. fraction=" + std::to_string(fraction);
                RCLCPP_INFO(this->get_logger(), "%s", response->message.c_str());
            }

            moveit::planning_interface::MoveGroupInterface::Plan plan;
            plan.trajectory = trajectory;

            const bool executed = (move_group->execute(plan) == moveit::core::MoveItErrorCode::SUCCESS);
            if (!executed) 
            {
                response->success = false;
                response->message = "MoveIt Cartesian execution failed. fraction=" + std::to_string(fraction);
                RCLCPP_ERROR(this->get_logger(), "%s", response->message.c_str());
                return;
            }

            response->success = true;
            response->message = "Cartesian path execution successful. fraction=" + std::to_string(fraction);
            RCLCPP_INFO(this->get_logger(), "%s", response->message.c_str());
        }
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<CartesianMoverNode>();
  rclcpp::executors::MultiThreadedExecutor executor;
  executor.add_node(node);
  node->initMoveGroup();
  executor.spin();
  rclcpp::shutdown();
  return 0;
}