# copley_bridge

ROS 2 per-joint bridge for Copley Controls Accelnet Plus Micro Module CANopen drives (APV / APZ family). Designed to plug into the same orchestrator (`epos2_arm_controller`) that drives the Maxon EPOS2 joints, so a mixed-vendor arm just works.

## Joint assignment

Per the project's joint+1 node-ID convention:

| Joint | Drive | CAN Node ID | Bridge |
|-------|-------|-------------|--------|
| joint0 | Copley APZ-090-50 | 1 | `copley_joint_bridge` |
| joint1 | Copley APZ-090-50 | 2 | `copley_joint_bridge` |
| joint2 | Maxon EPOS2 70/10 | 3 | `epos2_j3_bridge` (rename pending) |
| joint3 | Maxon EPOS2 70/10 | 4 | `epos2_j3_bridge` (was node 1) |
| joint4 | Maxon EPOS2 70/10 | 5 | `epos2_j3_bridge` (was node 4) |
| joint5 | Maxon EPOS2 70/10 | 6 | `epos2_j3_bridge` (was node 5) |

> **Action item on the EPOS2 side:** the EPOS2 drives currently boot with their old node IDs (J3=1, J1=2, J2=3, J4=4, J5=5, J6=6). The launch files in `epos2_bridge` will need to be updated to match the new scheme, and each EPOS2 needs its node ID re-saved via EPOS Studio. That's an EPOS2-side change, not handled by this package.

## Wire protocol (matches `epos2_bridge`)

Per joint `jN`, the bridge offers:

**Services**
- `/copley/jN/clear_fault` — `std_srvs/Trigger`
- `/copley/jN/arm_ipm` — `std_srvs/Trigger` (full CiA 402 + IPM bring-up)
- `/copley/jN/disarm_ipm` — `std_srvs/Trigger`
- `/copley/jN/move_absolute_timed` — `epos2_bridge_interfaces/MoveAbsoluteTimed`

**Subscriptions**
- `/copley/jN/reduced_traj` — `std_msgs/Float64MultiArray` in `[q, v, dt, q, v, dt, ...]` format (the orchestrator's reduced-trajectory stream)

**Publications**
- `/joint_states` — `sensor_msgs/JointState`
- `/copley/jN/fault` — `std_msgs/Bool`

**Action server**
- `/jointN_position_controller/follow_joint_trajectory` — `control_msgs/FollowJointTrajectory`

## Bring-up

### One-time per drive

1. Configure the drive in CME (motor params, current limits, PID gains, `Desired State = 30` for CANopen-driven position control). Save to flash.
2. Set the drive's CAN node ID via CMO and save to flash. (Node ID 1 for joint0, node ID 2 for joint1.)
3. **Map PDOs.** The drives ship without the PDO layout this bridge expects, so run (with the workspace sourced and a CANopen master node already up on the bus):

   ```bash
   bash "$(ros2 pkg prefix copley_bridge)/share/copley_bridge/scripts/apply_copley_pdo_remap_one.sh" 1   # for joint0
   bash "$(ros2 pkg prefix copley_bridge)/share/copley_bridge/scripts/apply_copley_pdo_remap_one.sh" 2   # for joint1
   ```

   This sets:

   | PDO | Maps |
   |-----|------|
   | RPDO1 | `0x2010` (IP move segment, 64-bit) |
   | RPDO2 | `0x6040` ctrlword + `0x6060` mode |
   | TPDO1 | `0x2012` buffer status + `0x6041` statusword + `0x6061` mode display |
   | TPDO2 | `0x6064` position actual + `0x606C` velocity actual |

   The bridge reads back the four critical mappings on `arm_ipm` and refuses to arm if they don't match.

### Every boot

```bash
ros2 launch copley_bridge copley_j0_bridge.launch.py
ros2 launch copley_bridge copley_j1_bridge.launch.py
```

## Required configuration

The bridge **refuses to start** if these aren't overridden in the YAML:

- `encoder_qc_per_motor_rev` — encoder counts per motor revolution (the drive's quadrature count, not the line count). Get this from CME's "Motor / Feedback" page.
- `gear_ratio_motor_per_joint_rev` — motor revolutions per one joint revolution.

Optional but commonly tuned:

- `sign` — set `-1.0` if positive joint motion produces negative encoder counts.
- `zero_offset_qc` — encoder count at the joint's zero pose (homing offset).
- `ipm_default_segment_ms` — keepalive segment time when armed but idle (default 100 ms).
- `goal_position_tolerance_rad` — convergence threshold for `move_absolute_timed` and trajectory completion (default 0.03 rad).

## How it differs from `epos2_bridge`

The CiA 402 state machine, mode-of-operation codes, position feedback, and start-IPM trigger (controlword bit 4 rising edge) are all identical — both vendors implement DSP-402. The Copley-specific code is confined to:

| Concept | EPOS2 | Copley |
|---------|-------|--------|
| Streaming data record | `0x20C1` (Maxon proprietary) | `0x2010` (Copley alt object) |
| Buffer status | `0x20C4:01` (16-bit) | `0x2012` (32-bit) |
| Buffer clear/enable | SDO write to `0x60C4:6` | RPDO1 command frame (header bit 7=1) |
| PVT segment layout | 8-byte: `[pos32, vel24, time8]` LSB-first | 8-byte: `[header8, time8, pos24, vel24]` LSB-first |
| Velocity feedback units | RPM | counts / sec |
| Velocity command units | RPM (in segment) | 0.1 counts/sec (in segment) |
| Integrity counter | None | 3-bit counter in segment header (drive checks for missed segments) |

Vendor-shared helpers live in `cia402.py` (state-machine constants and predicates) and `raw_socket_can.py` (SocketCAN wrapper, lifted verbatim from `epos2_bridge`).

## Limitations / TODO

- **24-bit position range.** Format-code-0 PVT segments use a signed 24-bit position field, so the absolute encoder position must stay within ±8,388,607 counts. The bridge logs an error and refuses to stream if a trajectory point exceeds this. To support larger ranges, add support for format-code-4 (32-bit absolute preload) followed by format-code-2 (24-bit relative segments). Not implemented yet.
- **No diagnostic / state-engineering topics.** Unlike `epos2_bridge`, this package omits the `state_raw` / `state_engineering` / `state_summary` debug pubs. Add later if useful.
- **No `move_absolute` / `move_delta` services.** Only `move_absolute_timed` (the one the orchestrator actually calls). Add the others if direct manual moves are wanted.
- **PDO mapping isn't auto-saved.** The remap script writes mappings to RAM. To persist to flash, add `cansend can0 600+nodeID#23.10.10.01.73.61.76.65` (SDO write 0x1010:01 = 'save') after the remap, or do a save-all in CME after running it once.
- **Self-test.** No automated bring-up self-check beyond the PDO mapping verification. Consider adding a "verify_copley_drive" tool that reads `0x6502` (supported modes), `0x2300` (desired state), `0x1010:01` (last save state).
