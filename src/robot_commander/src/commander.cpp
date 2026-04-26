#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.hpp>
#include <example_interfaces/msg/float64_multi_array.hpp> // !!! Create custom interface package later and replace this with the custom message type !!!
#include <example_interfaces/msg/string.hpp>              // !!! Create custom interface package later and replace this with the custom message type !!!

using MoveGroupInterface = moveit::planning_interface::MoveGroupInterface;
using FloatArray = example_interfaces::msg::Float64MultiArray;
using String = example_interfaces::msg::String;
using namespace std::placeholders;

class Commander
{
    public:

        // Constructor for the Commander class, which takes a shared pointer to a ROS 2 node as an argument
        Commander(std::shared_ptr<rclcpp::Node> node)
        {
            node_ = node; // Store the node in a member variable

            arm_ = std::make_shared<MoveGroupInterface>(node_, "arm"); // Create a MoveGroupInterface for the "arm" group
            arm_->setMaxVelocityScalingFactor(1.0);                    // Set the maximum velocity scaling factor
            arm_->setMaxAccelerationScalingFactor(1.0);                // Set the maximum acceleration scaling factor

            // Create a subscription to the "named_goal" topic with a queue size of 10, and bind the callback function to handle incoming messages
            // This functions the same as the buttons in the RViz GUI that send named pose commands to the robot
            named_command_subscriber_ = node_->create_subscription<String>("named_goal_command", 10, std::bind(&Commander::namedGoalCallback, this, _1));

            // Create a subscription to the "joint_command" topic with a queue size of 10, and bind the callback function to handle incoming messages
            joint_command_subscriber_ = node_->create_subscription<FloatArray>("joint_goal_command", 10, std::bind(&Commander::jointCommandCallback, this, _1));
        }

        // ------------------------------------- Public methods to control the arm using MoveGroupInterface -------------------------------------

        // Method to move the arm to a named target
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

        // Method to move the arm to a pose target specified by position (x, y, z) and orientation (roll, pitch, yaw) values, with an option to use Cartesian path planning
        void goToPoseTarget(double x, double y, double z, double roll, double pitch, double yaw, bool cartesian_path = false)
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
                if (fraction == 1) // Check if the entire path was planned successfully
                {
                    arm_->execute(trajectory); // Execute the planned trajectory if it was successful
                }
            }
        }

    private:

        std::shared_ptr<rclcpp::Node> node_;      // Member variable to hold the shared pointer to the ROS 2 node
        std::shared_ptr<MoveGroupInterface> arm_; // Member variable to hold the MoveGroupInterface for controlling the robot's arm

        rclcpp::Subscription<String>::SharedPtr named_command_subscriber_;  // Subscriber for receiving named target commands as String messages
        rclcpp::Subscription<FloatArray>::SharedPtr joint_command_subscriber_;  // Subscriber for receiving joint commands as Float64MultiArray messages

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
        void namedGoalCallback(const String::SharedPtr msg)
        {
            std::string target_name(msg->data); // Convert the incoming String message to a string representing the named target

            if (target_name == "home" || target_name == "zero") // Check if the target name is "home" or "zero"
            {
                goToNamedTarget(target_name); // Plan and execute a motion to the named target
            }
        }

        // Callback function to handle incoming joint command messages
        void jointCommandCallback(const FloatArray::SharedPtr msg)
        {
            auto joints = msg->data; // Get the joint values from the message
            
            if (joints.size() == 7) // Check if the correct number of joint values were received
            {
                goToJointTarget(joints); // Plan and execute a motion to the joint target
            }
        }
};


int main(int argc, char** argv)
{
    // --- Setup ---

    rclcpp::init(argc, argv); // Initialize ROS 2

    auto node = std::make_shared<rclcpp::Node>("commander_node"); // Create a commander node
    auto commander = std::make_shared<Commander>(node);           // Create an instance of the Commander class, passing the node as an argument

    rclcpp::spin(node); // Spin the node to keep it alive and responsive to callbacks

    // --- Shutdown ---

    rclcpp::shutdown(); // Shutdown ROS 2
    return 0; // Exit the program
}