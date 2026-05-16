#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.hpp>
#include <robot_interfaces/msg/joint_command.hpp>
#include <robot_interfaces/msg/pose_command.hpp>
#include <robot_interfaces/msg/position_command.hpp>
#include <geometry_msgs/msg/pose_array.hpp>
#include <std_msgs/msg/bool.hpp>
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2/LinearMath/Quaternion.h>

using MoveGroupInterface = moveit::planning_interface::MoveGroupInterface;
using PoseCommand = robot_interfaces::msg::PoseCommand;
using JointCommand = robot_interfaces::msg::JointCommand;
using PositionCommand = robot_interfaces::msg::PositionCommand;
using PoseArray = geometry_msgs::msg::PoseArray;
using Pose = geometry_msgs::msg::Pose;
using Bool = std_msgs::msg::Bool;
using namespace std::placeholders;

static constexpr int POSES_PER_TOMATO = 3; // approach, grasp, retract

class Commander
{
    public:

        // --------------------------------------- Constructor ---------------------------------------

        // Constructor for the Commander class, which takes a shared pointer to a ROS 2 node as an argument
        Commander(std::shared_ptr<rclcpp::Node> node)
        {
            node_ = node; // Store the node in a member variable

            arm_ = std::make_shared<MoveGroupInterface>(node_, "arm"); // Create a MoveGroupInterface for the "arm" group
            arm_->setMaxVelocityScalingFactor(1.0);                    // Set the maximum velocity scaling factor
            arm_->setMaxAccelerationScalingFactor(1.0);                // Set the maximum acceleration scaling factor
            arm_->setEndEffectorLink("link6");                         // Set the end effector link

            // Create subscriptions for receiving command messages and bind them to their respective callback functions
            named_pose_cmd_sub_ = node_->create_subscription<PoseCommand>("/agrobot/named_pose_cmd", 10, std::bind(&Commander::namedPoseCmdCallback, this, _1));
            joint_cmd_sub_ = node_->create_subscription<JointCommand>("/agrobot/joint_cmd", 10, std::bind(&Commander::jointCmdCallback, this, _1));
            position_cmd_sub_ = node_->create_subscription<PositionCommand>("/agrobot/position_cmd", 10, std::bind(&Commander::positionCmdCallback, this, _1));

            // Create subscriptions for receiving pick target poses and safe to pick signals, and bind them to their respective callback functions
            pick_target_sub_ = node_->create_subscription<PoseArray>("/agrobot/pick_targets", 10, std::bind(&Commander::pickTargetCallback, this, _1));
            safe_to_pick_pub_ = node_->create_publisher<Bool>("/agrobot/safe_to_pick", 10);

            RCLCPP_INFO(node_->get_logger(), "Commander node initialized and ready to receive commands."); // Log that the commander node has been initialized
        }

        // ------------------------------------- Public methods -------------------------------------

        // Method to move the arm to a named pose target
        void goToNamedTarget(const std::string &name)
        {
            arm_->setStartStateToCurrentState(); // Set the start state to the current state
            arm_->setNamedTarget(name);          // Set the named target
            planAndExecute(arm_);                // Plan and execute the motion to the named target
        }

        // Method to move the arm to a joint target specified by a vector of joint values
        void goToJointTarget(const std::vector<double> &joints)
        {
            arm_->setStartStateToCurrentState(); // Set the start state to the current state
            arm_->setJointValueTarget(joints);   // Set the joint target
            planAndExecute(arm_);                // Plan and execute the motion to the joint target
        }

        // Method to move the arm to a position target specified by position (x, y, z) and orientation (roll, pitch, yaw) values, with an option to use Cartesian path planning
        void goToPositionTarget(double x, double y, double z, double roll, double pitch, double yaw, bool cartesian_path = false)
        {
            tf2::Quaternion q;          // Create a quaternion to represent the orientation
            q.setRPY(roll, pitch, yaw); // Set the roll, pitch, and yaw of the quaternion
            q = q.normalize();          // Normalize the quaternion

            geometry_msgs::msg::PoseStamped target_pose; // Create a Pose message to hold the target pose
            target_pose.header.frame_id = "world_frame"; // Set the frame of reference for the target pose
            target_pose.pose.position.x = x;             // Set the x position of the target pose
            target_pose.pose.position.y = y;             // Set the y position of the target pose
            target_pose.pose.position.z = z;             // Set the z position of the target pose
            target_pose.pose.orientation.x = q.getX();   // Set the x orientation of the target pose
            target_pose.pose.orientation.y = q.getY();   // Set the y orientation of the target pose
            target_pose.pose.orientation.z = q.getZ();   // Set the z orientation of the target pose
            target_pose.pose.orientation.w = q.getW();   // Set the w orientation of the target pose

            // If cartesian_path is false, plan and execute a motion to the pose target
            if (!cartesian_path)
            {
                arm_->setPoseTarget(target_pose);    // Set the pose target
                planAndExecute(arm_);                // Plan and execute the motion to the pose target
            }

            // If cartesian_path is true, plan and execute a Cartesian path to the pose target
            else
            {
                std::vector<geometry_msgs::msg::Pose> waypoints; // Create a vector to hold the waypoints for the Cartesian path
                waypoints.push_back(target_pose.pose);           // Add the target pose to the waypoints
                moveit_msgs::msg::RobotTrajectory trajectory;    // Create a RobotTrajectory message to hold the trajectory of the Cartesian path

                double fraction = arm_->computeCartesianPath(waypoints, 0.01, trajectory); // Try to plan a Cartesian path through the waypoints with a step size of 1 cm, returning the fraction of the path that was successfully planned
                
                if (fraction == 1)  // Check if the entire path was planned successfully
                {
                    arm_->execute(trajectory); // Execute the planned trajectory if it was successful
                }
            }
        }

        void goToPoseTarget(const Pose &pose)
        {
            geometry_msgs::msg::PoseStamped stamped;
            stamped.header.frame_id = "linear_rail_link";
            stamped.header.stamp = node_->get_clock()->now();
            stamped.pose = pose;
            arm_->setStartStateToCurrentState();
            arm_->setPoseTarget(stamped);
            planAndExecute(arm_);
        }

    private:

        // ------------------------------------- Private members -------------------------------------

        std::shared_ptr<rclcpp::Node> node_;      // Member variable to hold the shared pointer to the ROS 2 node
        std::shared_ptr<MoveGroupInterface> arm_; // Member variable to hold the MoveGroupInterface for controlling the robot's arm

        rclcpp::Subscription<PoseCommand>::SharedPtr named_pose_cmd_sub_;         // Subscription for receiving named target command messages
        rclcpp::Subscription<JointCommand>::SharedPtr joint_cmd_sub_;       // Subscription for receiving joint command messages
        rclcpp::Subscription<PositionCommand>::SharedPtr position_cmd_sub_; // Subscription for receiving position command messages

        rclcpp::Subscription<PoseArray>::SharedPtr pick_target_sub_; // Subscription for receiving pick target poses
        rclcpp::Publisher<Bool>::SharedPtr safe_to_pick_pub_;    // Publisher for sending safe to pick signals

        bool is_picking_ = false; // Flag to indicate whether the robot is currently in the process of picking an object

        // ------------------------------------- Helper functions -------------------------------------
        
        // Helper function to plan and execute a motion using the MoveGroupInterface
        void planAndExecute(const std::shared_ptr<MoveGroupInterface> &interface)
        {
            MoveGroupInterface::Plan plan; // Create a plan object

            bool success = (interface->plan(plan) == moveit::core::MoveItErrorCode::SUCCESS); // Plan to the named target and check if it was successful
            if (success)
            {
                interface->execute(plan); // Execute the plan if it was successful
            }
            else
            {
                RCLCPP_ERROR(node_->get_logger(), "Failed to plan a motion to the target."); // Log an error message if planning failed
            }
        }

        // Callback function to handle incoming named target command messages
        void namedPoseCmdCallback(const PoseCommand::SharedPtr msg)
        {
            std::string target_name(msg->pose_name); // Get the target name from the message

            if (target_name == "crouch" || target_name == "attention" || target_name == "vertical" || target_name == "bin") // Check if the target name is one of the valid named targets
            {
                goToNamedTarget(target_name); // Plan and execute a motion to the named target
            }
        }

        // Callback function to handle incoming joint command messages
        void jointCmdCallback(const JointCommand::SharedPtr msg)
        {
            std::vector<double> joints = {msg->j0, msg->j1, msg->j2, msg->j3, msg->j4, msg->j5, msg->j6};
            goToJointTarget(joints);
        }

        // Callback function to handle incoming position command messages
        void positionCmdCallback(const PositionCommand::SharedPtr msg)
        {
            goToPositionTarget(msg->x, msg->y, msg->z, msg->roll, msg->pitch, msg->yaw, msg->cartesian_path); // Plan and execute a motion to the position target specified in the message
        }

        // Pick target callback function to handle incoming pick target poses
        void pickTargetCallback(const PoseArray::SharedPtr msg)
        {
            // --- Error handling ----
            if (is_picking_) // If the robot is already in the process of picking, ignore new pick targets
            {
                RCLCPP_WARN(node_->get_logger(), "Received new pick targets while already picking. Ignoring new targets."); // Log a warning message
                return;
            }

            if (msg->poses.size() % POSES_PER_TOMATO != 0) // Check if the number of poses in the message is a multiple of the expected number of poses per tomato
            {
                RCLCPP_ERROR(node_->get_logger(), "Received pick targets with an invalid number of poses. Expected a multiple of %d, but got %zu. Ignoring targets.", POSES_PER_TOMATO, msg->poses.size()); // Log an error message
                return;
            }

            setSafeToPick(false); // Set the safe to pick flag to false to indicate that the robot is not yet safe to pick
            is_picking_ = true;   // Set the picking flag to true to indicate that the robot is now in the process of picking

            const size_t num_tomatoes = msg->poses.size() / POSES_PER_TOMATO; // Calculate the number of tomatoes based on the number of poses in the message
            RCLCPP_INFO(node_->get_logger(), "Received pick targets for %zu tomatoes.", num_tomatoes); // Log the number of tomatoes for which pick targets were received

            // Loop through each tomato and execute the pick sequence for each one
            for (size_t i = 0; i < msg->poses.size(); i += POSES_PER_TOMATO)
            {
                const Pose & approach = msg->poses[i];    // Get the approach pose for the current tomato
                const Pose & grasp = msg->poses[i + 1];   // Get the grasp pose for the current tomato
                const Pose & retract = msg->poses[i + 2]; // Get the retract pose for the current tomato

                size_t tomato_idx = (i / POSES_PER_TOMATO) + 1; // Calculate the tomato number for logging purposes

                // ----- Motion sequence -----
                // Execute motion to crouch pose before any picking is done
                RCLCPP_INFO(node_->get_logger(), "Moving to crouch pose.");
                goToNamedTarget("crouch");

                // Execute the approach, grasp, and retract motions to the positions in sequence for the current tomato
                RCLCPP_INFO(node_->get_logger(), "Picking tomato %zu / %zu", tomato_idx, num_tomatoes);

                RCLCPP_INFO(node_->get_logger(), "Planning & executing approach for tomato %zu / %zu", tomato_idx, num_tomatoes);
                goToPoseTarget(approach);

                RCLCPP_INFO(node_->get_logger(), "Planning & executing grasp for tomato %zu / %zu", tomato_idx, num_tomatoes);
                goToPoseTarget(grasp);

                RCLCPP_INFO(node_->get_logger(), "Planning & executing retract for tomato %zu / %zu", tomato_idx, num_tomatoes);
                goToPoseTarget(retract);
                
                // Execute motion to bin pose after picking each tomato
                RCLCPP_INFO(node_->get_logger(), "Planning & executing to bin pose for tomato %zu / %zu", tomato_idx, num_tomatoes);
                goToNamedTarget("bin");
            }

            RCLCPP_INFO(node_->get_logger(), "Finished executing pick targets for all tomatoes."); // Log that the pick sequence has been completed for all tomatoes
            setSafeToPick(true); // Set the safe to pick flag to true to indicate that the robot is now safe to pick again
            is_picking_ = false; // Set the picking flag to false to indicate that the robot is no longer in the process of picking
        }

        void setSafeToPick(bool safe)
        {
            std_msgs::msg::Bool msg; // Create a Bool message to hold the safe to pick status
            msg.data = safe; // Set the data field of the message to the value of the safe parameter
            safe_to_pick_pub_->publish(msg); // Publish the safe to pick status message
        }
};


int main(int argc, char** argv)
{
    // --- Setup ---

    rclcpp::init(argc, argv); // Initialize ROS 2

    auto node = std::make_shared<rclcpp::Node>("commander"); // Create a commander node
    auto commander = std::make_shared<Commander>(node);      // Create an instance of the Commander class, passing the node as an argument

    rclcpp::spin(node); // Spin the node to keep it alive and responsive to callbacks

    // --- Shutdown ---

    rclcpp::shutdown(); // Shutdown ROS 2
    return 0; // Exit the program
}