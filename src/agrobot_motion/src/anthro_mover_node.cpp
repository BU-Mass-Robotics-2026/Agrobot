// anthro_mover_node.cpp
// ---------------------------------------------------------------------------
// Service node that moves the anthro group (arm joints J1-J5) to an absolute
// joint-space target using MoveIt's "anthro" planning group.
//
// Exposes:  /anthro_mover/goto   (agrobot_motion/srv/AnthroGoto)
//
// This is the arm-side sibling of rail_mover. The request carries 5 joint
// values in RADIANS, ordered [J1, J2, J3, J4, J5] -- joint-space goal, no IK
// required. Used by the celebration emote now; intended as the motion
// primitive for the future arm-pick service too.
//
// CONCURRENCY (same rationale as rail_mover):
//  - MultiThreadedExecutor + a Reentrant callback group. A service node that
//    also drives a MoveGroupInterface MUST NOT use a SingleThreadedExecutor:
//    the callback blocks inside MoveIt while MoveIt needs the executor to
//    spin -> deadlock.
//
// DEPENDENCY:
//  - The "anthro" group must be defined in the SRDF AND have an entry in
//    kinematics.yaml, or move_group reports "No active joints or end
//    effectors found for group 'anthro'".
// ---------------------------------------------------------------------------

#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.hpp>
#include "agrobot_motion/srv/anthro_goto.hpp"

#include <cmath>
#include <memory>
#include <string>
#include <vector>

namespace
{
constexpr char kPlanningGroup[] = "anthro";
// anthro is J1..J5 -> exactly 5 solution joints.
constexpr std::size_t kNumJoints = 5;
// Joint order the service contract promises. MoveGroupInterface returns joint
// values in the group's internal order; for a simple chain this is J1..J5.
const std::vector<std::string> kJointNames = {
  "joint1", "joint2", "joint3", "joint4", "joint5"};
}  // namespace

class AnthroMoverNode : public rclcpp::Node
{
public:
  AnthroMoverNode()
  : rclcpp::Node("anthro_mover")
  {
    velocity_scaling_ =
      this->declare_parameter<double>("anthro_velocity_scaling", 0.2);
    accel_scaling_ =
      this->declare_parameter<double>("anthro_acceleration_scaling", 0.2);
    planning_time_ =
      this->declare_parameter<double>("anthro_planning_time", 5.0);

    RCLCPP_INFO(
      this->get_logger(),
      "anthro_mover starting: vel_scale=%.2f accel_scale=%.2f plan_time=%.1fs",
      velocity_scaling_, accel_scaling_, planning_time_);

    service_cb_group_ =
      this->create_callback_group(rclcpp::CallbackGroupType::Reentrant);
  }

  // MoveGroupInterface needs shared_from_this(): call after the node is held
  // by a shared_ptr (from main(), not the constructor).
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

    service_ = this->create_service<agrobot_motion::srv::AnthroGoto>(
      "/anthro_mover/goto",
      std::bind(&AnthroMoverNode::handleGoto, this,
                std::placeholders::_1, std::placeholders::_2),
      rclcpp::ServicesQoS(),
      service_cb_group_);

    RCLCPP_INFO(this->get_logger(), "Service ready: /anthro_mover/goto");
  }

private:
  void handleGoto(
    const std::shared_ptr<agrobot_motion::srv::AnthroGoto::Request> req,
    std::shared_ptr<agrobot_motion::srv::AnthroGoto::Response> res)
  {
    // --- Validate request length ---
    if (req->joint_positions.size() != kNumJoints) {
      res->success = false;
      res->final_positions = currentJointValues();
      res->message =
        "expected " + std::to_string(kNumJoints) +
        " joint values [J1..J5], got " +
        std::to_string(req->joint_positions.size());
      RCLCPP_WARN(this->get_logger(), "Rejected: %s", res->message.c_str());
      return;
    }

    // --- Validate finiteness ---
    for (std::size_t i = 0; i < kNumJoints; ++i) {
      if (!std::isfinite(req->joint_positions[i])) {
        res->success = false;
        res->final_positions = currentJointValues();
        res->message = "joint value " + std::to_string(i) +
                       " is not finite";
        RCLCPP_WARN(this->get_logger(), "Rejected: %s", res->message.c_str());
        return;
      }
    }

    {
      // Log the target in a readable form.
      std::string tgt;
      for (std::size_t i = 0; i < kNumJoints; ++i) {
        tgt += std::to_string(req->joint_positions[i]);
        if (i + 1 < kNumJoints) tgt += ", ";
      }
      RCLCPP_INFO(this->get_logger(),
                  "Goto: anthro [J1..J5] -> [%s] rad", tgt.c_str());
    }
    
    // Per-call velocity scaling: request overrides the node default.
    // A non-positive request value means "use the node's configured default".
    double scaling = velocity_scaling_;          // node param default
    if (req->velocity_scaling > 0.0) {
      scaling = std::min(req->velocity_scaling, 1.0);   // clamp to valid max
    }
    move_group_->setMaxVelocityScalingFactor(scaling);
    move_group_->setMaxAccelerationScalingFactor(scaling);
    RCLCPP_INFO(this->get_logger(),
                "Goto: anthro [J1..J5] (vel_scale=%.2f)", scaling);
    
    // --- Set joint target ---
    // Build an explicit name->value map so we do not depend on the group's
    // internal joint ordering matching our [J1..J5] assumption.
    move_group_->setStartStateToCurrentState();
    std::map<std::string, double> target;
    for (std::size_t i = 0; i < kNumJoints; ++i) {
      target[kJointNames[i]] = req->joint_positions[i];
    }
    if (!move_group_->setJointValueTarget(target)) {
      res->success = false;
      res->final_positions = currentJointValues();
      res->message = "setJointValueTarget rejected the target "
                     "(joint limits exceeded?)";
      RCLCPP_WARN(this->get_logger(), "%s", res->message.c_str());
      return;
    }

    // --- Plan ---
    moveit::planning_interface::MoveGroupInterface::Plan plan;
    if (move_group_->plan(plan) != moveit::core::MoveItErrorCode::SUCCESS) {
      res->success = false;
      res->final_positions = currentJointValues();
      res->message = "MoveIt planning failed";
      RCLCPP_ERROR(this->get_logger(), "%s", res->message.c_str());
      return;
    }

    // --- Execute ---
    const bool executed =
      (move_group_->execute(plan) == moveit::core::MoveItErrorCode::SUCCESS);
    res->final_positions = currentJointValues();

    if (!executed) {
      res->success = false;
      res->message = "MoveIt execution failed";
      RCLCPP_ERROR(this->get_logger(), "%s", res->message.c_str());
      return;
    }

    res->success = true;
    res->message = "ok";
    RCLCPP_INFO(this->get_logger(), "Move complete.");
  }

  // Current J1..J5 values from MoveIt's state (group order).
  std::vector<double> currentJointValues()
  {
    try {
      return move_group_->getCurrentJointValues();
    } catch (const std::exception & e) {
      RCLCPP_WARN(this->get_logger(),
                  "Could not read current joint values: %s", e.what());
      return std::vector<double>(kNumJoints,
                                 std::numeric_limits<double>::quiet_NaN());
    }
  }

  double velocity_scaling_;
  double accel_scaling_;
  double planning_time_;

  rclcpp::CallbackGroup::SharedPtr service_cb_group_;
  std::shared_ptr<moveit::planning_interface::MoveGroupInterface> move_group_;
  rclcpp::Service<agrobot_motion::srv::AnthroGoto>::SharedPtr service_;
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
