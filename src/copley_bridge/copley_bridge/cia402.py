"""CiA 402 (DSP-402) state machine constants and helpers.

These are vendor-agnostic — both EPOS2 and Copley implement DSP-402, so the
controlword bit layout, statusword bit layout, and standard mode-of-operation
codes are identical across both bridges. Only the manufacturer-specific OD
indices (e.g. 0x20C1 vs 0x2010 for the IPM data record) differ.

Spec: CiA 402 Part 1 (general definitions) + Part 2 (operation modes).
"""

from __future__ import annotations


# --- Standard CiA 402 object indices ------------------------------------------

IDX_CONTROLWORD = 0x6040            # u16 RW
IDX_STATUSWORD = 0x6041             # u16 RO
IDX_MODES_OF_OPERATION = 0x6060     # i8  RW
IDX_MODES_OF_OPERATION_DISPLAY = 0x6061  # i8 RO
IDX_POSITION_ACTUAL = 0x6064        # i32 RO (counts)
IDX_VELOCITY_ACTUAL = 0x606C        # i32 RO (counts/sec on Copley, RPM on EPOS2)
IDX_TARGET_POSITION = 0x607A        # i32 RW (counts)
IDX_INTERPOLATION_SUBMODE = 0x60C0  # i16 RW (0 / -1 / -2 / -3 on Copley)
IDX_INTERPOLATION_DATA_RECORD = 0x60C1  # array RW (CiA standard IPM data record)
IDX_INTERPOLATION_DATA_CONFIG = 0x60C4   # record RW (buffer config)


# --- Mode of operation codes (0x6060) -----------------------------------------

MODE_PROFILE_POSITION = 1
MODE_PROFILE_VELOCITY = 3
MODE_PROFILE_TORQUE = 4
MODE_HOMING = 6
MODE_INTERPOLATED_POSITION = 7
MODE_CYCLIC_SYNC_POSITION = 8
MODE_CYCLIC_SYNC_VELOCITY = 9
MODE_CYCLIC_SYNC_TORQUE = 10


# --- Controlword bit positions (0x6040) ---------------------------------------

CW_BIT_SWITCH_ON = 0
CW_BIT_ENABLE_VOLTAGE = 1
CW_BIT_QUICK_STOP = 2          # active LOW
CW_BIT_ENABLE_OPERATION = 3
CW_BIT_NEW_SETPOINT = 4        # 0->1 starts an IPM move (mode 7)
CW_BIT_RESET_FAULT = 7         # 0->1 clears latched fault
CW_BIT_HALT = 8


# --- Controlword command words ------------------------------------------------
# Constructed from the bits above; these are the values you actually write
# during the bring-up sequence.

CW_SHUTDOWN = 0x06              # bits 1,2 set            -> Ready to Switch On
CW_SWITCH_ON = 0x07             # bits 0,1,2 set          -> Switched On
CW_ENABLE_OPERATION = 0x0F      # bits 0,1,2,3 set        -> Operation Enable
CW_DISABLE_VOLTAGE = 0x00
CW_QUICK_STOP = 0x02            # bit 1 set, bit 2 clear
CW_FAULT_RESET = 0x80           # bit 7 rising edge clears fault
CW_START_IPM_MOVE = 0x1F        # bits 0,1,2,3,4 set      -> begin IPM execution


# --- Statusword bit positions (0x6041) ----------------------------------------

SW_BIT_READY_TO_SWITCH_ON = 0
SW_BIT_SWITCHED_ON = 1
SW_BIT_OPERATION_ENABLED = 2
SW_BIT_FAULT = 3
SW_BIT_VOLTAGE_ENABLED = 4
SW_BIT_QUICK_STOP = 5
SW_BIT_SWITCH_ON_DISABLED = 6
SW_BIT_WARNING = 7
SW_BIT_REMOTE = 9
SW_BIT_TARGET_REACHED = 10
SW_BIT_INTERNAL_LIMIT = 11
SW_BIT_IPM_ACTIVE = 12          # in IPM mode, "interpolated position mode active"


def sw_faulted(statusword: int) -> bool:
    return bool((statusword >> SW_BIT_FAULT) & 0x1)


def sw_operation_enabled(statusword: int) -> bool:
    return bool((statusword >> SW_BIT_OPERATION_ENABLED) & 0x1)


def sw_ipm_active(statusword: int) -> bool:
    return bool((statusword >> SW_BIT_IPM_ACTIVE) & 0x1)


def sw_target_reached(statusword: int) -> bool:
    return bool((statusword >> SW_BIT_TARGET_REACHED) & 0x1)
