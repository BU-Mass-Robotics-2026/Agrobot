#!/usr/bin/env bash
###############################################################################
# run_rocm.sh — Run the ROCm Docker image with correct GPU device access [EDGE]
#
# Why this script? Ubuntu base images do not define a "render" (or "video")
# group. Using --group-add render fails with "Unable to find group render".
# Device nodes (/dev/kfd, /dev/dri/renderD*) are owned by a host-specific GID
# (e.g. 992). The container process must be in that GID to open the devices.
# This script reads the host GIDs and passes them to docker run so GPU access
# works on any AMD edge machine.
#
# Usage (from repo root on the edge box):
#   ./deployment/docker/run_rocm.sh [command and args...]
# Example:
#   ./deployment/docker/run_rocm.sh
#   ./deployment/docker/run_rocm.sh bash
#   ./deployment/docker/run_rocm.sh ros2 launch agrobot_perception perception.launch.py
###############################################################################

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"
IMAGE="${IMAGE:-agrobot-tom-v2/rocm-gpu:latest}"

# Host GID that owns /dev/kfd (and usually the DRI render node)
KFD_GID=""
if [ -c /dev/kfd ]; then
  KFD_GID=$(stat -c '%g' /dev/kfd 2>/dev/null || true)
fi
# GID that owns /dev/dri/renderD* — replaces --group-add render (name may not exist
# after purging amdgpu-dkms, which is what creates the "render" group on Ubuntu).
RENDER_GID=""
for rnode in /dev/dri/renderD*; do
  [ -e "$rnode" ] && RENDER_GID=$(stat -c '%g' "$rnode" 2>/dev/null || true) && break
done
# Optional: host "video" group for /dev/dri/card*
VIDEO_GID=""
if getent group video &>/dev/null; then
  VIDEO_GID=$(getent group video | cut -d: -f3)
fi

GROUP_ADD_ARGS=()
[ -n "$KFD_GID" ]    && GROUP_ADD_ARGS+=(--group-add "$KFD_GID")
[ -n "$RENDER_GID" ] && [ "$RENDER_GID" != "$KFD_GID" ] && GROUP_ADD_ARGS+=(--group-add "$RENDER_GID")
[ -n "$VIDEO_GID" ]  && [ "$VIDEO_GID"  != "$KFD_GID" ] && [ "$VIDEO_GID" != "$RENDER_GID" ] && GROUP_ADD_ARGS+=(--group-add "$VIDEO_GID")

# USB passthrough for Intel RealSense D456 (optional; no-op if /dev/bus/usb missing)
# Torch hub + HuggingFace caches are mounted from the host so DINOv2/SAM2/SigLIP weights
# survive container restarts. TORCH_HOME and HF_HOME point into /workspace/.cache so the
# --user UID (non-root) can write there without needing access to /root/.
# Pre-create on the host so Docker doesn't create them as root (which would deny writes).
mkdir -p "${HOME}/.cache/torch" "${HOME}/.cache/huggingface"
VOLUME_ARGS=(
  -v "${REPO_ROOT}:/workspace"
  -v "${HOME}/.cache/torch:/workspace/.cache/torch"
  -v "${HOME}/.cache/huggingface:/workspace/.cache/huggingface"
)
if [ -d /dev/bus/usb ]; then
  VOLUME_ARGS+=(-v /dev/bus/usb:/dev/bus/usb)
fi

# RealSense video device passthrough (/dev/video0–N).
# The camera is visible to the host (lsusb shows Intel RealSense) but Docker
# blocks /dev/video* by default. Pass every video node that exists at launch time.
VIDEO_DEVICE_ARGS=()
for dev in /dev/video*; do
  [ -e "$dev" ] && VIDEO_DEVICE_ARGS+=(--device="$dev")
done

docker run --rm -it \
  --network host \
  --ipc host \
  -e ROS_DOMAIN_ID="${ROS_DOMAIN_ID:-0}" \
  -e TORCH_HOME=/workspace/.cache/torch \
  -e HF_HOME=/workspace/.cache/huggingface \
  -e HSA_OVERRIDE_GFX_VERSION="${HSA_OVERRIDE_GFX_VERSION:-11.5.1}" \
  -e HSA_ENABLE_SDMA="${HSA_ENABLE_SDMA:-0}" \
  -e GPU_MAX_HW_QUEUES="${GPU_MAX_HW_QUEUES:-8}" \
  --device=/dev/kfd \
  --device=/dev/dri \
  "${GROUP_ADD_ARGS[@]}" \
  "${VIDEO_DEVICE_ARGS[@]}" \
  "${VOLUME_ARGS[@]}" \
  -w /workspace \
  "$IMAGE" \
  "$@"
