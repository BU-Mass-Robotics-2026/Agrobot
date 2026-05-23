#!/usr/bin/env bash
# Configure the four PDOs needed by copley_joint_bridge on a Copley APV/APZ
# CANopen drive. Mirrors scripts/apply_ipm_pdo_remap_one.sh in epos2_bridge,
# with the following swaps (Maxon -> Copley standard):
#
#   RPDO1 maps 0x20100040  (Copley IP move segment, 64-bit)
#                                   instead of 0x20C10040 (Maxon record)
#   TPDO1 maps 0x20120020 + 0x60410010 + 0x60610008
#                                   instead of 0x20C40110 + ...
#
# Prerequisites:
#   - ROS 2 (Jazzy) sourced; ros2_canopen master node running and exposing
#     /node_${NODE_ID}/sdo_write
#   - can-utils installed (for cansend NMT control)
#   - The drive is on the bus and at the expected NODE_ID
#
# Usage: ./apply_copley_pdo_remap_one.sh NODE_ID

set -eo pipefail

NODE_ID="${1:?usage: $0 NODE_ID}"
CAN_IFACE="${CAN_IFACE:-can0}"

write() {
  local idx="$1"
  local sub="$2"
  local data="$3"
  ros2 service call "/node_${NODE_ID}/sdo_write" canopen_interfaces/srv/COWrite \
       "{index: ${idx}, subindex: ${sub}, data: ${data}}"
}

RPDO1=$((0x200 + NODE_ID))
RPDO2=$((0x300 + NODE_ID))
TPDO1=$((0x180 + NODE_ID))
TPDO2=$((0x280 + NODE_ID))

RPDO1_DISABLE=$((0x80000000 + RPDO1))
RPDO2_DISABLE=$((0x80000000 + RPDO2))
TPDO1_DISABLE=$((0xC0000000 + TPDO1))
TPDO2_DISABLE=$((0xC0000000 + TPDO2))

echo "Node ${NODE_ID}: entering Pre-Operational"
cansend "${CAN_IFACE}" 000#80$(printf "%02X" ${NODE_ID})

echo "Node ${NODE_ID}: disabling PDOs"
write 5120 1 "${RPDO1_DISABLE}"      # 0x1400
write 5121 1 "${RPDO2_DISABLE}"      # 0x1401
write 6144 1 "${TPDO1_DISABLE}"      # 0x1800
write 6145 1 "${TPDO2_DISABLE}"      # 0x1801

echo "Node ${NODE_ID}: mapping RPDO1 = 0x2010 (Copley IP move segment, 64-bit)"
write 5632 0 0                       # 0x1600 sub0 = 0 (disable mapping)
write 5632 1 537919552               # 0x20100040
write 5632 0 1                       # one mapped object

echo "Node ${NODE_ID}: mapping RPDO2 = 0x6040 + 0x6060"
write 5633 0 0                       # 0x1601
write 5633 1 1614807056              # 0x60400010 (controlword, 16)
write 5633 2 1616904200              # 0x60600008 (mode of operation, 8)
write 5633 0 2

echo "Node ${NODE_ID}: mapping TPDO1 = 0x2012 + 0x6041 + 0x6061"
write 6656 0 0                       # 0x1A00
write 6656 1 538050592               # 0x20120020 (buffer status, 32)
write 6656 2 1614872592              # 0x60410010 (statusword, 16)
write 6656 3 1616969736              # 0x60610008 (mode display, 8)
write 6656 0 3

echo "Node ${NODE_ID}: mapping TPDO2 = 0x6064 + 0x606C"
write 6657 0 0                       # 0x1A01
write 6657 1 1617166368              # 0x60640020 (position actual, 32)
write 6657 2 1617690656              # 0x606C0020 (velocity actual, 32, counts/sec on Copley)
write 6657 0 2

echo "Node ${NODE_ID}: re-enabling PDOs"
write 5120 1 "${RPDO1}"
write 5120 2 255                     # asynchronous (event-driven)
write 5121 1 "${RPDO2}"
write 5121 2 255
write 6144 1 $((0x40000000 + TPDO1))
write 6144 2 255
write 6145 1 $((0x40000000 + TPDO2))
write 6145 2 255

echo "Node ${NODE_ID}: back to Operational"
cansend "${CAN_IFACE}" 000#01$(printf "%02X" ${NODE_ID})

echo "Node ${NODE_ID}: done"
