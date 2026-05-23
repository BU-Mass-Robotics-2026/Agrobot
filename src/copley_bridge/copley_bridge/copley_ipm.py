"""Copley-specific IPM (Interpolated Position Mode) helpers.

Implements the Copley "alternative objects" path described in
CANopen Programmer's Manual section 11.2 -- specifically:

  0x2010  IP Move Segment Command       (UNSIGNED64, write-only, 8-byte single PDO)
  0x2011  Trajectory Buffer Free Count  (UNSIGNED16, read-only)
  0x2012  Trajectory Buffer Status      (UNSIGNED32, read-only, PDO-mappable)
  0x2013  Next Trajectory Segment ID    (UNSIGNED16, read-only)

This is the Copley equivalent of EPOS2's 0x20C1 / 0x20C4 pair. The same
idea -- one 8-byte CAN frame per trajectory segment, with an integrity
counter so the drive can detect dropped frames -- but the byte layout is
completely different and Copley adds an explicit format-code field that
selects between several supported segment encodings.

We use FORMAT_CODE_PVT_ABS (0): 1B time(ms) + 3B abs position(counts) +
3B velocity(0.1 counts/sec). That matches the EPOS2 PVT semantics most
closely (time + position + velocity per segment, single CAN frame).
"""

from __future__ import annotations

from dataclasses import dataclass


# --- Copley alternative-objects OD indices ------------------------------------

IDX_IP_MOVE_SEGMENT = 0x2010
IDX_TRAJ_BUFFER_FREE_COUNT = 0x2011
IDX_TRAJ_BUFFER_STATUS = 0x2012
IDX_NEXT_TRAJ_SEGMENT_ID = 0x2013


# --- 0x2010 header byte: bits 0-2 integrity, bits 3-6 format code, bit 7 type -

HEADER_TYPE_DATA = 0x00         # bit 7 = 0: segment is PVT/linear data
HEADER_TYPE_COMMAND = 0x80      # bit 7 = 1: segment is a buffer-control command

# Format codes (bits 3-6 of header byte, when bit 7 = 0)
FORMAT_CODE_PVT_ABS = 0         # 1B time + 3B abs pos + 3B vel(0.1 ct/s)
FORMAT_CODE_PVT_ABS_10 = 1      # same as 0 but velocity in 10 ct/s
FORMAT_CODE_PVT_REL = 2         # 1B time + 3B rel pos + 3B vel(0.1 ct/s)
FORMAT_CODE_PVT_REL_10 = 3      # same as 2 but velocity in 10 ct/s
FORMAT_CODE_ABS_POS_PRELOAD = 4  # 4B abs pos only (used at start of move)
FORMAT_CODE_LINEAR_ABS = 5      # 1B time + 4B abs pos (linear, no velocity)
FORMAT_CODE_LINEAR_REL = 6      # 1B time + 4B rel pos (linear, no velocity)

# Buffer command codes (bits 0-6 of header byte, when bit 7 = 1)
BUFFER_CMD_CLEAR_AND_ABORT = 0
BUFFER_CMD_POP = 1              # next byte = N segments to pop
BUFFER_CMD_CLEAR_ERRORS = 2     # next byte = error mask
BUFFER_CMD_RESET_SEGMENT_ID = 3
BUFFER_CMD_NOOP = 4             # EtherCAT only


# --- 0x2012 trajectory buffer status bit layout -------------------------------

BUFSTAT_NEXT_SEG_ID_MASK = 0x0000FFFF       # bits 0-15
BUFSTAT_FREE_COUNT_MASK = 0x00FF0000        # bits 16-23
BUFSTAT_FREE_COUNT_SHIFT = 16
BUFSTAT_BIT_SEQ_ERROR = 24
BUFSTAT_BIT_OVERFLOW = 25
BUFSTAT_BIT_UNDERFLOW = 26
BUFSTAT_BIT_EMPTY = 31


@dataclass
class PVTPoint:
    """A single trajectory waypoint in motor-native units."""
    time_ms: int          # 1..255; 0 is reserved as the end-of-move sentinel
    velocity_ct_s10: int  # signed 24-bit, units of 0.1 counts/sec
    position_qc: int      # signed 24-bit position in encoder counts (absolute)


class IntegrityCounter:
    """3-bit integrity counter that wraps 0..7.

    Copley checks that successive segments arrive with monotonically
    incrementing counter values mod 8. If a gap is detected, the drive
    flags BUFSTAT_BIT_SEQ_ERROR and stops accepting segments until the
    error is cleared.
    """

    def __init__(self) -> None:
        self._value = 0

    @property
    def value(self) -> int:
        return self._value

    def next(self) -> int:
        v = self._value
        self._value = (self._value + 1) & 0x07
        return v

    def reset(self) -> None:
        self._value = 0


def _to_unsigned_24(v: int) -> int:
    if v < 0:
        v = (1 << 24) + v
    return v & 0xFFFFFF


def sign_extend_24(v: int) -> int:
    v &= 0xFFFFFF
    if v & 0x800000:
        return v - (1 << 24)
    return v


def to_signed_32(v: int) -> int:
    v &= 0xFFFFFFFF
    if v & 0x80000000:
        return v - (1 << 32)
    return v


def pack_pvt_segment(point: PVTPoint, integrity: int) -> bytes:
    """Pack a PVT segment into the 8-byte 0x2010 frame, format code 0.

    Layout (LSB first on the wire, as all CANopen multi-byte values):
        byte 0 : header  -- bit7=0 (data), bits3-6=format code 0, bits0-2=integrity
        byte 1 : time_ms (uint8)
        bytes 2-4: position (signed24, counts, absolute)
        bytes 5-7: velocity (signed24, 0.1 counts/sec)
    """
    if not (1 <= point.time_ms <= 255):
        raise ValueError(f"time_ms out of range [1,255]: {point.time_ms}")
    if not (0 <= integrity <= 7):
        raise ValueError(f"integrity counter out of range [0,7]: {integrity}")

    pos_u24 = _to_unsigned_24(point.position_qc)
    vel_u24 = _to_unsigned_24(point.velocity_ct_s10)

    header = HEADER_TYPE_DATA | (FORMAT_CODE_PVT_ABS << 3) | (integrity & 0x07)

    return bytes([
        header,
        point.time_ms & 0xFF,
        pos_u24 & 0xFF,
        (pos_u24 >> 8) & 0xFF,
        (pos_u24 >> 16) & 0xFF,
        vel_u24 & 0xFF,
        (vel_u24 >> 8) & 0xFF,
        (vel_u24 >> 16) & 0xFF,
    ])


def pack_end_of_move(integrity: int, position_qc: int = 0) -> bytes:
    """A PVT segment with time=0 signals 'end of move' to the drive.

    IMPORTANT: this Copley drive uses the position field of the time=0
    segment as the final commanded position and executes a snap to it,
    regardless of time_ms=0. Always pass position_qc = the last
    commanded position of the trajectory. The default of 0 is left for
    backwards compat but is almost certainly wrong for real use --
    passing position_qc=0 will snap the motor to absolute encoder
    counts = 0.
    """
    if not (0 <= integrity <= 7):
        raise ValueError(f"integrity counter out of range [0,7]: {integrity}")
    pos_u24 = _to_unsigned_24(position_qc)
    header = HEADER_TYPE_DATA | (FORMAT_CODE_PVT_ABS << 3) | (integrity & 0x07)
    return bytes([
        header,
        0x00,
        pos_u24 & 0xFF,
        (pos_u24 >> 8) & 0xFF,
        (pos_u24 >> 16) & 0xFF,
        0, 0, 0,
    ])


def pack_buffer_command_clear_abort() -> bytes:
    """Clear the buffer and abort any move in progress.

    Use at startup before staging hold points, and during disarm.
    """
    return bytes([HEADER_TYPE_COMMAND | BUFFER_CMD_CLEAR_AND_ABORT,
                  0, 0, 0, 0, 0, 0, 0])


def pack_buffer_command_clear_errors(error_mask: int = 0xFF) -> bytes:
    """Clear buffer error bits per the bit mask.

    Pass 0xFF to clear all errors. Error bit positions match the top
    byte of the 0x2012 status word (BUFSTAT_BIT_SEQ_ERROR / OVERFLOW /
    UNDERFLOW), shifted into the low byte.
    """
    return bytes([HEADER_TYPE_COMMAND | BUFFER_CMD_CLEAR_ERRORS,
                  error_mask & 0xFF, 0, 0, 0, 0, 0, 0])


def pack_buffer_command_reset_segment_id() -> bytes:
    """Reset the drive's expected-segment-ID counter back to zero.

    Should be paired with resetting the master's IntegrityCounter.
    """
    return bytes([HEADER_TYPE_COMMAND | BUFFER_CMD_RESET_SEGMENT_ID,
                  0, 0, 0, 0, 0, 0, 0])


# --- 0x2012 status decoding ---------------------------------------------------

@dataclass
class TrajectoryBufferStatus:
    next_segment_id: int     # bits 0-15 (16-bit, full segment ID)
    free_count: int          # bits 16-23 (number of free buffer slots)
    sequence_error: bool     # bit 24
    overflow: bool           # bit 25
    underflow: bool          # bit 26
    empty: bool              # bit 31

    @property
    def has_error(self) -> bool:
        return self.sequence_error or self.overflow or self.underflow


def decode_buffer_status(status: int) -> TrajectoryBufferStatus:
    return TrajectoryBufferStatus(
        next_segment_id=status & BUFSTAT_NEXT_SEG_ID_MASK,
        free_count=(status & BUFSTAT_FREE_COUNT_MASK) >> BUFSTAT_FREE_COUNT_SHIFT,
        sequence_error=bool((status >> BUFSTAT_BIT_SEQ_ERROR) & 0x1),
        overflow=bool((status >> BUFSTAT_BIT_OVERFLOW) & 0x1),
        underflow=bool((status >> BUFSTAT_BIT_UNDERFLOW) & 0x1),
        empty=bool((status >> BUFSTAT_BIT_EMPTY) & 0x1),
    )
