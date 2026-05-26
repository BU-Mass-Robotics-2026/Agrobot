#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from moveit_msgs.srv import ApplyPlanningScene
from moveit_msgs.msg import PlanningScene, CollisionObject, ObjectColor
from shape_msgs.msg import SolidPrimitive
from geometry_msgs.msg import Pose
from std_msgs.msg import ColorRGBA

FRAME = 'world_frame'

# Need to get the relative locations of these after it is built at the expo hall

WALL_LENGTH = 2.47 # x = 247 cm long
WALL_WIDTH = 0.1   # y = 10 cm wide
WALL_HEIGHT = 2.47 # z = 247 cm tall

# Top surface is flush with the rail bottom (z = -0.041 m)
TABLE_LENGTH = 2.15  # x = 215 cm long
TABLE_WIDTH = 0.7    # y = 70 cm wide
TABLE_HEIGHT = 0.63  # z = 63 cm tall

BIN_LENGTH = 0.36 # x = 36 cm long
BIN_WIDTH = 0.28  # y = 28 cm wide
BIN_HEIGHT = 0.18 # z = 18 cm tall

# -------------------------------------------------------------------------------------------------
# Scene setup node class
# -------------------------------------------------------------------------------------------------
class SceneSetup(Node):

    def __init__(self):
        super().__init__('scene_setup')
        self._client = self.create_client(ApplyPlanningScene, '/apply_planning_scene')

    def apply(self):
        self.get_logger().info('Waiting for /apply_planning_scene...')
        if not self._client.wait_for_service(timeout_sec=30.0):
            self.get_logger().error('Timed out — is move_group running?')
            return

        req = ApplyPlanningScene.Request()
        req.scene = _build_scene()

        future = self._client.call_async(req)
        rclpy.spin_until_future_complete(self, future)

        if future.result() and future.result().success:
            self.get_logger().info('Scene applied.')
        else:
            self.get_logger().error('Failed to apply scene.')

# -------------------------------------------------------------------------------------------------
# Helper functions
# -------------------------------------------------------------------------------------------------
def _box(obj_id: str, dims: list, xyz: list, wxyz: list = None) -> CollisionObject:
    obj = CollisionObject()
    obj.id = obj_id
    obj.header.frame_id = FRAME
    obj.operation = CollisionObject.ADD

    shape = SolidPrimitive()
    shape.type = SolidPrimitive.BOX
    shape.dimensions = dims  # [x_size, y_size, z_size] in metres
    obj.primitives.append(shape)

    pose = Pose()
    pose.position.x, pose.position.y, pose.position.z = xyz
    w, x, y, z = wxyz if wxyz else [1.0, 0.0, 0.0, 0.0]
    pose.orientation.w, pose.orientation.x = w, x
    pose.orientation.y, pose.orientation.z = y, z
    obj.primitive_poses.append(pose)

    return obj

def _color(obj_id: str, r: float, g: float, b: float, a: float) -> ObjectColor:
    c = ObjectColor()
    c.id = obj_id
    c.color = ColorRGBA(r=r, g=g, b=b, a=a)
    return c

def _build_scene() -> PlanningScene:
    scene = PlanningScene()
    scene.is_diff = True

    # Rail bottom is at z = -0.041 m in world_frame
    # Table top is flush with rail bottom; table bottom defines the ground plane.
    ground_z = -0.041 - TABLE_HEIGHT

    # Wall
    scene.world.collision_objects.append(_box(
        obj_id='wall',
        dims=[WALL_LENGTH, WALL_WIDTH, WALL_HEIGHT],
        xyz=[0.0, 1.5, ground_z + WALL_HEIGHT / 2.0],
    ))
    scene.object_colors.append(_color('wall', r=0.2, g=0.5, b=0.2, a=1.0))  # green

    # Table
    scene.world.collision_objects.append(_box(
        obj_id='table',
        dims=[TABLE_LENGTH, TABLE_WIDTH, TABLE_HEIGHT],
        xyz=[0.0, 0.0, ground_z + TABLE_HEIGHT / 2.0],
    ))
    scene.object_colors.append(_color('table', r = 0.6, g = 0.6, b = 0.6, a = 1.0)) # gray

    # Bin
    """ scene.world.collision_objects.append(_box(
        obj_id='bin',
        dims=[BIN_LENGTH, BIN_WIDTH, BIN_HEIGHT],
        xyz=[-0.5, 0.0, 0.0]
    ))
    scene.object_colors.append(_color('bin', r = 0.7, g = 0.7, b = 0.7, a = 0.7)) """

    

    return scene

# -------------------------------------------------------------------------------------------------
# Main
# -------------------------------------------------------------------------------------------------
def main():
    rclpy.init()
    node = SceneSetup()
    node.apply()
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()