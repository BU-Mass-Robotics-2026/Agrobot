#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.hpp>

#include <robot_interfaces/msg/joint_command.hpp>
#include <robot_interfaces/msg/pose_command.hpp>
#include <robot_interfaces/msg/position_command.hpp>

using MoveGroupInterface = moveit::planning_interface::MoveGroupInterface;
using PoseCommand = robot_interfaces::msg::PoseCommand;
using JointCommand = robot_interfaces::msg::JointCommand;
using PositionCommand = robot_interfaces::msg::PositionCommand;
using namespace std::placeholders;


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

            // Create a subscription to the "pose_command" topic with a queue size of 10, and bind the callback function to handle incoming messages
            // This functions the same as the buttons in the RViz GUI that send pose commands to the robot
            pose_cmd_sub_ = node_->create_subscription<PoseCommand>("pose_cmd", 10, std::bind(&Commander::poseCmdCallback, this, _1));

            // Create a subscription to the "joint_command" topic with a queue size of 10, and bind the callback function to handle incoming messages
            joint_cmd_sub_ = node_->create_subscription<JointCommand>("joint_cmd", 10, std::bind(&Commander::jointCmdCallback, this, _1));

            // Create a subscription to the "position_command" topic with a queue size of 10, and bind the callback function to handle incoming messages
            position_cmd_sub_ = node_->create_subscription<PositionCommand>("position_cmd", 10, std::bind(&Commander::positionCmdCallback, this, _1));
        }

        // ------------------------------------- Public methods -------------------------------------

        // Method to move the arm to a named pose target
        void goToPoseTarget(const std::string &name)
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

    private:

        // ------------------------------------- Private members -------------------------------------

        std::shared_ptr<rclcpp::Node> node_;      // Member variable to hold the shared pointer to the ROS 2 node
        std::shared_ptr<MoveGroupInterface> arm_; // Member variable to hold the MoveGroupInterface for controlling the robot's arm

        rclcpp::Subscription<PoseCommand>::SharedPtr pose_cmd_sub_;         // Subscription for receiving named target command messages
        rclcpp::Subscription<JointCommand>::SharedPtr joint_cmd_sub_;       // Subscription for receiving joint command messages
        rclcpp::Subscription<PositionCommand>::SharedPtr position_cmd_sub_; // Subscription for receiving position command messages

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
        }

        // Callback function to handle incoming named target command messages
        void poseCmdCallback(const PoseCommand::SharedPtr msg)
        {
            std::string target_name(msg->pose_name); // Get the target name from the message

            if (target_name == "home" || target_name == "zero") // Check if the target name is "home" or "zero"
            {
                goToPoseTarget(target_name); // Plan and execute a motion to the named target
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