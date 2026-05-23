import rclpy
from rclpy.node import Node
from tf2_ros import Buffer, TransformListener, LookupException
from scipy.spatial.transform import Rotation as R

rclpy.init()
node = Node('pose_reader')
buf = Buffer()
TransformListener(buf, node)

while rclpy.ok():
    rclpy.spin_once(node, timeout_sec=0.1)
    try:
        t = buf.lookup_transform('linear_rail_link', 'link6', rclpy.time.Time())
        p = t.transform.translation
        q = t.transform.rotation
        roll, pitch, yaw = R.from_quat([q.x, q.y, q.z, q.w]).as_euler('xyz')
        print(f"\rx={p.x:.4f} y={p.y:.4f} z={p.z:.4f}  roll={roll:.4f} pitch={pitch:.4f} yaw={yaw:.4f}", end='', flush=True)
    except LookupException:
        pass
