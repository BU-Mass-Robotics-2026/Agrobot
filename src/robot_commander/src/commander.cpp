#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <moveit/move_group_interface/move_group_interface.hpp>
#include <robot_interfaces/msg/joint_command.hpp>
#include <robot_interfaces/msg/named_command.hpp>
#include <robot_interfaces/msg/pose_command.hpp>
#include <robot_interfaces/action/pick_sequence.hpp>
#include <geometry_msgs/msg/pose_array.hpp>
#include <std_msgs/msg/bool.hpp>
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2/LinearMath/Quaternion.h>

using MoveGroupInterface = moveit::planning_interface::MoveGroupInterface;
using JointCommand = robot_interfaces::msg::JointCommand;
using NamedCommand = robot_interfaces::msg::NamedCommand;
using PoseCommand = robot_interfaces::msg::PoseCommand;
using PickSequence = robot_interfaces::action::PickSequence;
using GoalHandlePickSeq = rclcpp_action::ServerGoalHandle<PickSequence>;
using PoseArray = geometry_msgs::msg::PoseArray;
using Pose = geometry_msgs::msg::Pose;
using Bool = std_msgs::msg::Bool;
using namespace std::placeholders;

static constexpr int POSES_PER_TOMATO = 3; // approach, grasp, retract

class Commander
{
    public:

        // -------------------------------------------------------------------------------------------------
        // Constructor
        // -------------------------------------------------------------------------------------------------

        // Constructor for the Commander class, which takes a shared pointer to a ROS 2 node as an argument
        Commander(std::shared_ptr<rclcpp::Node> node)
        {
            node_ = node; // Store the node in a member variable

            arm_ = std::make_shared<MoveGroupInterface>(node_, "arm"); // Create a MoveGroupInterface for the "arm" group
            arm_->setMaxVelocityScalingFactor(1.0);                    // Set the maximum velocity scaling factor
            arm_->setMaxAccelerationScalingFactor(1.0);                // Set the maximum acceleration scaling factor
            arm_->setEndEffectorLink("link6");                         // Set the end effector link

            // Create subscriptions for receiving motion command messages and bind them to their respective callback functions
            joint_cmd_sub_ = node_->create_subscription<JointCommand>("/agrobot/joint_cmd", 10, std::bind(&Commander::jointCmdCallback, this, _1));
            named_cmd_sub_ = node_->create_subscription<NamedCommand>("/agrobot/named_cmd", 10, std::bind(&Commander::namedCmdCallback, this, _1));
            pose_cmd_sub_ = node_->create_subscription<PoseCommand>("/agrobot/pose_cmd", 10, std::bind(&Commander::poseCmdCallback, this, _1));

            // Create a subscription for receiving proceed signals and bind it to the proceed callback function
            proceed_sub_ = node_->create_subscription<Bool>("/agrobot/proceed", 10, std::bind(&Commander::proceedCallback, this, _1));

            // Create an action server for handling pick sequence goals and bind it to the goal, cancel, and accepted callback functions
            action_server_ = rclcpp_action::create_server<PickSequence>(
                node_, 
                "/agrobot/pick_sequence", 
                std::bind(&Commander::handleGoal, this, _1, _2), 
                std::bind(&Commander::handleCancel, this, _1), 
                std::bind(&Commander::handleAccepted, this, _1)
            );

            RCLCPP_INFO(node_->get_logger(), "Commander node initialized and ready to receive commands."); // Log that the commander node has been initialized
        }

        // -------------------------------------------------------------------------------------------------
        // Motion helpers
        // -------------------------------------------------------------------------------------------------

        // Method to move the arm to a joint target specified by a vector of joint values
        void goToJointTarget(const std::vector<double> &joints)
        {
            arm_->setStartStateToCurrentState(); // Set the start state to the current state
            arm_->setJointValueTarget(joints);   // Set the joint target
            planAndExecute(arm_);                // Plan and execute the motion to the joint target
        }

        // Method to move the arm to a named pose target
        void goToNamedTarget(const std::string &name)
        {
            arm_->setStartStateToCurrentState(); // Set the start state to the current state
            arm_->setNamedTarget(name);          // Set the named target
            planAndExecute(arm_);                // Plan and execute the motion to the named target
        }

        // Method to move the arm to a pose target specified by a geometry_msgs::msg::Pose message (which has position)
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

        // -------------------------------------------------------------------------------------------------
        // Private members
        // -------------------------------------------------------------------------------------------------

        std::shared_ptr<rclcpp::Node> node_;      // Member variable to hold the shared pointer to the ROS 2 node
        std::shared_ptr<MoveGroupInterface> arm_; // Member variable to hold the MoveGroupInterface for controlling the robot's arm

        rclcpp::Subscription<JointCommand>::SharedPtr joint_cmd_sub_;  // Subscription for receiving joint command messages
        rclcpp::Subscription<NamedCommand>::SharedPtr named_cmd_sub_;  // Subscription for receiving named target command messages
        rclcpp::Subscription<PoseCommand>::SharedPtr pose_cmd_sub_;    // Subscription for receiving pose command messages
        rclcpp::Subscription<Bool>::SharedPtr proceed_sub_;            // Subscription for receiving proceed signals

        rclcpp_action::Server<PickSequence>::SharedPtr action_server_; // Action server for handling pick sequence goals

        std::mutex proceed_mutex_;           // Mutex for synchronizing access to the proceed flag
        std::condition_variable proceed_cv_; // Condition variable for waiting on proceed signals
        bool proceed_flag_ = false;          // Flag to indicate whether a proceed signal has been received
        
        // -------------------------------------------------------------------------------------------------
        // Topic callbacks
        // -------------------------------------------------------------------------------------------------

        // Callback function to handle incoming joint command messages
        void jointCmdCallback(const JointCommand::SharedPtr msg)
        {
            std::vector<double> joints = {msg->j0, msg->j1, msg->j2, msg->j3, msg->j4, msg->j5, msg->j6};
            goToJointTarget(joints);
        }

        // Callback function to handle incoming named pose command messages
        void namedCmdCallback(const NamedCommand::SharedPtr msg)
        {
            std::string target_name(msg->pose_name); // Get the target name from the message

            if (target_name == "crouch" || target_name == "attention" || target_name == "vertical" || target_name == "bin") // Check if the target name is one of the valid named targets
            {
                goToNamedTarget(target_name); // Plan and execute a motion to the named target
            }
        }

        // Callback function to handle incoming pose command messages, which converts the roll, pitch, and yaw angles from the message into a quaternion, constructs a Pose message, and plans and executes a motion to the target pose
        void poseCmdCallback(const PoseCommand::SharedPtr msg)
        {
            tf2::Quaternion q;
            q.setRPY(msg->roll, msg->pitch, msg->yaw); // Convert the roll, pitch, and yaw angles from the message into a quaternion
            q = q.normalize(); // Normalize the quaternion to ensure it represents a valid rotation

            Pose pose; // Create a Pose message to hold the target pose
            pose.position.x = msg->x;   // Set the x position from the message
            pose.position.y = msg->y;   // Set the y position from the message
            pose.position.z = msg->z;   // Set the z position from the message
            pose.orientation.x = q.x(); // Set the x component of the orientation from the quaternion
            pose.orientation.y = q.y(); // Set the y component of the orientation from the quaternion
            pose.orientation.z = q.z(); // Set the z component of the orientation from the quaternion
            pose.orientation.w = q.w(); // Set the w component of the orientation from the quaternion

            goToPoseTarget(pose); // Plan and execute a motion to the target pose
        }

        // Callback function to handle incoming proceed signals, which sets the proceed flag and notifies any waiting threads to continue with the pick sequence execution
        void proceedCallback(const Bool::SharedPtr msg)
        {
            if (!msg->data)                                 // If the proceed signal is false, ignore it
                return;

            std::lock_guard<std::mutex> lk(proceed_mutex_); // Lock the mutex to safely update the proceed flag
            proceed_flag_ = true;                           // Set the proceed flag to true to indicate that a proceed signal has been received
            proceed_cv_.notify_all();                       // Notify any waiting threads that a proceed signal has been received
        }

        // -------------------------------------------------------------------------------------------------
        // Action server callbacks
        // -------------------------------------------------------------------------------------------------

        // Callback function to handle incoming pick sequence goals
        rclcpp_action::GoalResponse handleGoal(const rclcpp_action::GoalUUID &uuid, std::shared_ptr<const PickSequence::Goal> goal)
        {
            (void)uuid;
            if (goal->targets.poses.size() % POSES_PER_TOMATO != 0) // Check if the number of poses in the goal is a multiple of the number of poses per tomato
            {
                RCLCPP_ERROR(node_->get_logger(), "Rejecting goal: pose count %zu not a multiple of %d", goal->targets.poses.size(), POSES_PER_TOMATO);
                return rclcpp_action::GoalResponse::REJECT; // Reject the goal if the pose count is not valid
            }

            return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE; // Accept and execute the goal if the pose count is valid
        }

        // Callback function to handle cancel requests for pick sequence goals
        rclcpp_action::CancelResponse handleCancel(const std::shared_ptr<GoalHandlePickSeq> goal_handle)
        {
            (void)goal_handle;
            RCLCPP_INFO(node_->get_logger(), "Cancel requested");

            arm_->stop();             // Interrupt any motion currently executing
            proceed_cv_.notify_all(); // Notify any waiting threads to unblock and check for cancellation
            return rclcpp_action::CancelResponse::ACCEPT;
        }

        // Callback function to handle accepted pick sequence goals, which starts the execution of the pick sequence in a detached thread
        void handleAccepted(const std::shared_ptr<GoalHandlePickSeq> goal_handle)
        {
            std::thread{[this, goal_handle]() { executeSequence(goal_handle); }}.detach();
        }

        // -------------------------------------------------------------------------------------------------
        // Pick sequence helper functions
        // -------------------------------------------------------------------------------------------------

        // Helper function to publish feedback about the current step of the pick sequence to the action client
        void publishStep(const std::shared_ptr<GoalHandlePickSeq> &goal_handle, std::shared_ptr<PickSequence::Feedback> &feedback, const std::string &step, bool awaiting)
        {
            feedback->step = step;                   // Update the feedback message with the current step
            feedback->awaiting_confirm = awaiting;   // Update the feedback message to indicate whether we are awaiting confirmation to proceed
            goal_handle->publish_feedback(feedback); // Publish the feedback message to the action client
        }

        // Helper function to wait for a proceed signal from the action client before continuing to the next step of the pick sequence, while also checking for cancel requests
        void waitForProceed(const std::shared_ptr<GoalHandlePickSeq> &goal_handle, std::shared_ptr<PickSequence::Feedback> &feedback)
        {
            {
                std::lock_guard<std::mutex> lk(proceed_mutex_); // Lock the mutex to safely update the proceed flag
                proceed_flag_ = false;                          // Reset the proceed flag to false before waiting for the next proceed signal
            }

            publishStep(goal_handle, feedback, feedback->step, true);                                            // Publish feedback indicating that we are awaiting confirmation to proceed
            std::unique_lock<std::mutex> lk(proceed_mutex_);                                                     // Lock the mutex to wait for a proceed signal or a cancel request
            proceed_cv_.wait(lk, [this, &goal_handle] { return proceed_flag_ || goal_handle->is_canceling(); }); // Wait until either a proceed signal is received or a cancel request is made
        }

        // Returns false if the step was interrupted by a cancel request
        bool executeStep(const std::shared_ptr<GoalHandlePickSeq> &goal_handle, std::shared_ptr<PickSequence::Feedback> &feedback, const Pose &pose_target, const std::string &step, const size_t log_idx, const size_t n)
        {
            if (goal_handle->is_canceling()) return false;                                      // Check for cancel request before starting the step

            RCLCPP_INFO(node_->get_logger(), "Tomato %zu/%zu: %s", log_idx, n, step.c_str());
            publishStep(goal_handle, feedback, step, false);                                    // Publish feedback about the current step to the action client
            goToPoseTarget(pose_target);                                                        // Plan and execute a motion to the target pose
            return !goal_handle->is_canceling();                                                // Check for cancel request after completing the step and return false if a cancel request was made during the step
        }

        // Returns false if the step was interrupted by a cancel request
        bool executeStep(const std::shared_ptr<GoalHandlePickSeq> &goal_handle, std::shared_ptr<PickSequence::Feedback> &feedback, const std::string &named_target, const std::string &step, const size_t log_idx, const size_t n)
        {
            if (goal_handle->is_canceling()) return false;                                      // Check for cancel request before starting the step

            RCLCPP_INFO(node_->get_logger(), "Tomato %zu/%zu: %s", log_idx, n, step.c_str());
            publishStep(goal_handle, feedback, step, false);                                    // Publish feedback about the current step to the action client
            goToNamedTarget(named_target);                                                      // Plan and execute a motion to the target pose
            return !goal_handle->is_canceling();                                                // Check for cancel request after completing the step and return false if a cancel request was made during the step
        }

        // -------------------------------------------------------------------------------------------------
        // Pick sequence execution (runs in detached thread)
        // -------------------------------------------------------------------------------------------------

        void executeSequence(const std::shared_ptr<GoalHandlePickSeq> goal_handle)
        {
            auto feedback = std::make_shared<PickSequence::Feedback>(); // Create a shared pointer to a Feedback message to send feedback to the action client during the execution of the pick sequence
            auto result   = std::make_shared<PickSequence::Result>();   // Create a shared pointer to a Result message to send the final result to the action client at the end of the pick sequence

            const auto &poses = goal_handle->get_goal()->targets.poses; // Get the target poses from the goal message
            const size_t n = poses.size() / POSES_PER_TOMATO;           // Calculate the number of tomatoes to process based on the number of poses and the number of poses per tomato
            feedback->total_tomatoes = static_cast<uint32_t>(n);        // Set the total number of tomatoes in the feedback message so it can be included in feedback updates during the sequence execution

            RCLCPP_INFO(node_->get_logger(), "Starting pick sequence for %zu tomatoes", n);

            // Sequence loop
            for (size_t i = 0; i < poses.size() && !goal_handle->is_canceling(); i += POSES_PER_TOMATO)
            {
                const size_t log_idx = i / POSES_PER_TOMATO + 1;         // Calculate the current tomato index for logging and feedback purposes (1-based index)
                feedback->tomato_index = static_cast<uint32_t>(log_idx); // Update the current tomato index in the feedback message so it can be included in feedback updates during the sequence execution

                if (!executeStep(goal_handle, feedback, "attention", "resetting", log_idx, n)) break; // Move to the attention pose before processing each tomato
                if (!executeStep(goal_handle, feedback, "crouch", "crouching", log_idx, n)) break;    // Move to crouch pose before processing each tomato
                if (!executeStep(goal_handle, feedback, poses[i], "approaching", log_idx, n)) break;  // Move to the approach pose for the current tomato
                if (!executeStep(goal_handle, feedback, poses[i+1], "grasping", log_idx, n)) break;   // Move to the grasp pose for the current tomato
                if (!executeStep(goal_handle, feedback, poses[i+2], "retracting", log_idx, n)) break; // Move to the retract pose for the current tomato
                if (!executeStep(goal_handle, feedback, "bin", "binning", log_idx, n)) break;         // Move to the bin pose to drop the current tomato
                if (!executeStep(goal_handle, feedback, "crouch", "crouching", log_idx, n)) break;    // Move back to crouch pose after dropping each tomato
            }

            // Check if the sequence was completed successfully or if it was canceled, and send the appropriate result to the action client
            if (goal_handle->is_canceling())
            {
                result->success = false;
                result->message = "Sequence was canceled.";
                goal_handle->canceled(result);
                RCLCPP_INFO(node_->get_logger(), "Sequence canceled.");
            }
            else
            {
                result->success = true;
                result->message = "All tomatoes successfully processed!";
                goal_handle->succeed(result);
                RCLCPP_INFO(node_->get_logger(), "Sequence completed successfully.");
            }
        }

        // -------------------------------------------------------------------------------------------------
        // Plan and execute helper function
        // -------------------------------------------------------------------------------------------------

        void planAndExecute(const std::shared_ptr<MoveGroupInterface> &interface)
        {
            MoveGroupInterface::Plan plan; // Create a Plan object to hold the planned trajectory
            bool success = (interface->plan(plan) == moveit::core::MoveItErrorCode::SUCCESS); // Attempt to plan a motion using the provided MoveGroupInterface and check if it was successful

            if (success)
            {
                interface->execute(plan); // If planning was successful, execute the planned trajectory
            }
            else
            {
                RCLCPP_ERROR(node_->get_logger(), "Planning failed"); // Log an error message if planning failed
            }
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