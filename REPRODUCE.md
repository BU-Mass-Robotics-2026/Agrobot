# Reproducibility — Agrobot TOM v2

---

## Live ROS 2 pipeline — NucBox

Five terminal windows. Run in order. Each terminal enters the same running container.

### Terminal 1 — Camera [start new container here]
```bash
./deployment/docker/run_rocm.sh bash

source /opt/ros/jazzy/setup.bash
export ROS_DOMAIN_ID=42

ros2 launch realsense2_camera rs_launch.py \
  align_depth.enable:=true \
  pointcloud.enable:=true \
  rgb_camera.color_profile:=640x480x30 \
  depth_module.depth_profile:=640x480x30
```

Wait for `RealSense Node Is Up!` before continuing.

**Fallback (USB 2 or driver rejects 30 FPS):**
```bash
ros2 launch realsense2_camera rs_launch.py \
  align_depth.enable:=true \
  pointcloud.enable:=true
```

> Higher camera FPS does **not** speed up the detector (~17s/frame on CPU). It only
> makes `/camera/...` topics smoother for debugging.

---

### Terminal 2 — Detector (NODE 1)
```bash
docker exec -it $(docker ps -q) bash
source /opt/ros/jazzy/setup.bash
colcon build --packages-select agrobot_perception --symlink-install
source /workspace/install/setup.bash
export ROS_DOMAIN_ID=42

ros2 launch agrobot_perception perception.launch.py \
  depth_topic:=/camera/camera/depth/image_rect_raw \
  depth_camera_info_topic:=/camera/camera/depth/camera_info
```

Wait for `TomatoDetectorNode initialized`.

> `AGROBOT_FORCE_CPU=1`, `HIP_VISIBLE_DEVICES=-1`, `ROCR_VISIBLE_DEVICES=-1` are baked
> into the launch file — no need to export them manually.
>
> `colcon build` only needed once per session (or after code changes). Do NOT set
> `PYTHONPATH` — it breaks `ros2`.

---

### Terminal 3 — Spatial Node (NODE 2)
```bash
docker exec -it $(docker ps -q) bash
source /opt/ros/jazzy/setup.bash && source /workspace/install/setup.bash
export ROS_DOMAIN_ID=42

ros2 run agrobot_perception tomato_spatial
```

Wait for:
```
[INFO] [tomato_spatial]: Camera intrinsics cached: fx=... fy=... cx=... cy=... res=640×480
```

Then every ~17s when the detector fires:
```
[INFO] [tomato_spatial]: Published 2/2 tomato spatial estimates.
```

---

### Terminal 4 — Tracker (NODE 2b)
```bash
docker exec -it $(docker ps -q) bash
source /opt/ros/jazzy/setup.bash && source /workspace/install/setup.bash
export ROS_DOMAIN_ID=42

ros2 run agrobot_perception tomato_tracker
```

Wait for:
```
[INFO] [tomato_tracker]: TomatoTrackerNode initialized. threshold=8cm max_missed=3 alpha=0.4
```

Then after 3 frames (`age≥3`, `smoothed=True`):
```
[INFO] [tomato_tracker]: Frame 3: 2 active tracks [0, 1] (registry size=2).
```

---

### Terminal 5 — Qwen-VL Pick Selection (NODE 3)

> **First run only:** install deps and pre-download model (~6GB, ~15 min).
> ```bash
> pip install transformers qwen-vl-utils Pillow --break-system-packages
> ```

```bash
docker exec -it $(docker ps -q) bash
source /opt/ros/jazzy/setup.bash && source /workspace/install/setup.bash
export ROS_DOMAIN_ID=42

ros2 run agrobot_perception qwen_vl
```

Model loads in background (~30s). Once ready:
```
[INFO] [qwen_vl]: Qwen2.5-VL loaded. VLM-guided pick selection active.
```

Then when tracker publishes smoothed tracks (age≥3):
```
[INFO] [qwen_vl]: VLM response: 'Tomato 0 is closer and appears ripe.\n0'
[INFO] [qwen_vl]: Published pick_target: persistent_id=0 x=-0.062 y=+0.012 z=0.382m
```

---

### Terminal 6 — Verify
```bash
docker exec -it $(docker ps -q) bash
source /opt/ros/jazzy/setup.bash && source /workspace/install/setup.bash
export ROS_DOMAIN_ID=42

# Camera rate
ros2 topic hz /camera/camera/color/image_raw

# 2D detections (every ~17s)
ros2 topic echo /agrobot/detections

# Arm gate
ros2 topic echo /agrobot/safe_to_pick

# Tracked tomatoes with persistent IDs (pretty-print)
cat > /tmp/show_tracks.py << 'EOF'
import sys, json
raw = sys.stdin.read()
data = json.loads(raw[raw.index('['):raw.rindex(']')+1])
for t in data:
    print(f"\n--- persistent_id={t['persistent_id']} age={t['age']} smoothed={t['smoothed']} ---")
    print(f"  centroid : x={t['centroid']['x']:+.3f}  y={t['centroid']['y']:+.3f}  z={t['centroid']['z']:.3f} m")
    print(f"  radius   : {t['sphere']['radius']*100:.1f} cm")
    print(f"  score    : {t['confidence']:.3f}")
EOF
ros2 topic echo --full-length /agrobot/tomato_tracks --once | python3 /tmp/show_tracks.py

# VLM pick target (geometry_msgs/PoseStamped → Dani's arm planner)
ros2 topic echo /agrobot/pick_target --once

# VLM reasoning text
ros2 topic echo /agrobot/vlm_reasoning --once
```

---

### Expected output — full pipeline (2 tomatoes in scene)
```
# Terminal 3 — spatial
[INFO] [tomato_spatial]: Published 2/2 tomato spatial estimates.

# Terminal 4 — tracker (frame 3+)
[INFO] [tomato_tracker]: Frame 3: 2 active tracks [0, 1] (registry size=2).

# Terminal 5 — qwen_vl
[INFO] [qwen_vl]: VLM response: 'Tomato 0 is closer and appears ripe.\n0'
[INFO] [qwen_vl]: Published pick_target: persistent_id=0 x=-0.062 y=+0.012 z=0.382m

# Terminal 6 — /agrobot/pick_target
header:
  frame_id: camera_color_optical_frame
pose:
  position: {x: -0.062, y: 0.012, z: 0.382}
  orientation: {x: 0.0, y: 0.0, z: 0.0, w: 1.0}
```

---

### Optional — Save JPEG crops + pull to Mac
```bash
# Terminal 7 (NucBox container): save crops every detector cycle
python3 tools/save_spatial_crops.py

# Mac terminal: pull over Tailscale → opens Finder
bash tools/pull_crops.sh
```

---

### Known warnings (all safe to ignore)
| Warning | Cause |
|---|---|
| `xFormers is not available` | Optional attention library, no impact |
| `/opt/amdgpu/share/libdrm/amdgpu.ids: No such file or directory` | ROCm driver gap, CPU fallback active |
| `cannot import name '_C' from 'sam2'` | SAM2 C++ extension skipped, results unaffected |
| `Device connected using a 2.1 port.` | Plug into USB 3 for full 30 FPS |
| `get_xu(ctrl=1) failed!` | IMU issue on USB 2.1, IMU unused |
| `generation flags are not valid` | Harmless transformers version warning |

---

## VLM smoke-test on Mac (no ROS needed)

```bash
# Activate venv and install deps (one time)
python3 -m venv .venv && source .venv/bin/activate
pip install torch torchvision transformers qwen-vl-utils Pillow

# Dry run — instant, no model download
python3 tools/test_qwen_vl.py --dry-run

# Real inference on MPS (~30s after first download)
python3 tools/test_qwen_vl.py
python3 tools/test_qwen_vl.py --policy closest_first
python3 tools/test_qwen_vl.py --policy largest_first
```

---

## Quick start (eval only, no camera)

> **All model weights are already on NucBox** — no re-training needed.
> `transformers` and `sentencepiece` must be installed inside the container
> on first use (one-time, ~15 sec):
> ```bash
> pip install transformers sentencepiece Pillow --break-system-packages
> ```

### Current best — P2.2 SigLIP + MLP fusion

```bash
./deployment/docker/run_rocm.sh bash
pip install transformers sentencepiece Pillow --break-system-packages  # first time only

AGROBOT_FORCE_CPU=1 HIP_VISIBLE_DEVICES="" PYTHONPATH=perception \
  python3 perception/eval/run_eval.py \
  --val-list data/val_list.txt \
  --gt-csv data/val_gt.csv \
  --detector sam2_amg \
  --amg-points 28 \
  --max-detections 30 \
  --confidence 0.0 \
  --mlp-confidence 0.40 \
  --nms-iou 0.40 \
  --dino-weight 0.7 \
  --query-embedding models/query_embedding_k4.pt \
  --negative-embedding models/negative_embedding.pt \
  --negative-weight 1.0 \
  --siglip --fusion-mlp models/fusion_mlp.pt \
  --metric coco \
  --visualize-dir eval_reports/p2_2_mlp
```

> `--confidence 0.0` lets all SAM2 proposals reach the MLP.
> `--mlp-confidence 0.40` then gates on the MLP's own probability (0–1).
> Do **not** pass `--confidence 0.40` alone — that applies the threshold on the
> raw DINOv2 score before the MLP sees anything, producing 0 detections.

**Result:**

| Metric | Value | Δ vs S4.12 |
|---|---|---|
| **Legacy mAP@0.5** | **0.492** | **+0.115** |
| Precision | **0.871** | +0.231 |
| Recall | 0.574 | −0.042 |
| COCO mAP@[.5:.95] | 0.409 | +0.071 |
| COCO AP@0.50 | 0.559 | +0.070 |
| COCO AP@0.75 | 0.439 | +0.088 |
| AP_small | 0.093 | +0.039 |
| AP_medium | 0.571 | +0.082 |
| AP_large | 0.671 | +0.066 |
| Mean latency | ~21 s/frame (CPU) | +2 s vs baseline |

**Alternative — PR-curve config (no confidence gate; use for paper COCO numbers):**

```bash
# Same as above but add:  --confidence 0.0 --max-detections 60
# Result: COCO mAP@[.5:.95]=0.438 (+0.100), AP50=0.621 (+0.132), AP_small=0.117 (2.2×)
```

### Legacy S4.12 baseline (for comparison)

```bash
AGROBOT_FORCE_CPU=1 HIP_VISIBLE_DEVICES="" PYTHONPATH=perception \
  python3 perception/eval/run_eval.py \
  --val-list data/val_list.txt \
  --gt-csv data/val_gt.csv \
  --detector sam2_amg \
  --amg-points 28 \
  --max-detections 30 \
  --confidence 0.35 \
  --nms-iou 0.5 \
  --dino-weight 0.7 \
  --query-embedding models/query_embedding_k4.pt \
  --negative-embedding models/negative_embedding.pt \
  --negative-weight 1.0 \
  --metric coco \
  --visualize-dir eval_reports/s4_final
```

**Result:** Legacy mAP@0.5=0.377 | COCO mAP[.5:.95]=0.338 | AP50=0.489 | ~19 s/frame (CPU)

View report: `cd eval_reports/s4_final && python3 -m http.server 8000` → http://localhost:8000

> **NucBox:** `AGROBOT_FORCE_CPU=1 HIP_VISIBLE_DEVICES=""` required (ROCm blocked on gfx1151).
> See [docs/SPRINT3_ROCM_ISSUE.md](docs/SPRINT3_ROCM_ISSUE.md).

---

## Models

**Tick = already on NucBox at `/home/robotics-club/AgrobotV2/`.**

| Model | Path | On NucBox? | How to (re)build |
|-------|------|---|---|
| DINOv2 ViT-B/14 | `~/.cache/torch/hub/` | auto-dl on first run | — |
| SAM2.1 hiera-small | `models/sam2/sam2.1_hiera_small.pt` | ✅ | [Download](https://dl.fbaipublicfiles.com/segment_anything_2/092824/sam2.1_hiera_small.pt) |
| SAM2 fine-tuned | `models/sam2/sam2_tomato_finetuned.pt` | ✅ | `finetune_sam2_polygon.py --epochs 5` |
| Query embedding (k=4) | `models/query_embedding_k4.pt` | ✅ | `build_query_embedding.py --num-prototypes 4` |
| Negative embedding | `models/negative_embedding.pt` | ✅ | `build_query_embedding.py --output-negative` |
| **Fusion MLP** | **`models/fusion_mlp.pt`** | **✅** | **See P2.2 setup below** |
| SigLIP base-patch16-224 | `~/.cache/huggingface/` | auto-dl on first `--siglip` | `pip install transformers sentencepiece Pillow --break-system-packages` |
| Qwen2.5-VL-3B | `~/.cache/huggingface/` or `models/qwen_vl/` | auto-dl on first `ros2 run` | — |

**Save Qwen-VL locally after first download (avoids re-fetching):**
```bash
python3 -c "
from transformers import Qwen2_5_VLForConditionalGeneration, AutoProcessor
m = Qwen2_5_VLForConditionalGeneration.from_pretrained('Qwen/Qwen2.5-VL-3B-Instruct')
m.save_pretrained('models/qwen_vl/')
AutoProcessor.from_pretrained('Qwen/Qwen2.5-VL-3B-Instruct').save_pretrained('models/qwen_vl/')
print('Saved to models/qwen_vl/')
"
# Then launch with: qwen_model_path:=models/qwen_vl/
```

---

## One-time setup

> **Skip this entire section** if you are on NucBox — all models are already built and present.
> Only run these steps if you are starting from scratch on a new machine.

### Step 1 — SAM2 fine-tune with point prompts (~60–90 min NucBox CPU)

```bash
AGROBOT_FORCE_CPU=1 HIP_VISIBLE_DEVICES="" PYTHONPATH=perception \
  python3 perception/tools/finetune_sam2_polygon.py \
  --coco-json data/Laboro-Tomato/annotations/train.json \
  --train-images data/Laboro-Tomato/train/images \
  --sam2-checkpoint models/sam2/sam2.1_hiera_small.pt \
  --output models/sam2/sam2_tomato_finetuned.pt \
  --epochs 5
```

### Step 2 — k=4 prototype query + background-mean negative (~8 min)

```bash
AGROBOT_FORCE_CPU=1 HIP_VISIBLE_DEVICES="" PYTHONPATH=perception \
  python3 perception/tools/build_query_embedding.py \
  --train-images data/Laboro-Tomato/train/images \
  --train-labels data/Laboro-Tomato/train/labels \
  --output models/query_embedding_k4.pt \
  --num-prototypes 4 \
  --output-negative models/negative_embedding.pt
```

### Step 3 — P2.2 fusion MLP (~3.5 h NucBox CPU total; ~30 sec for the MLP train itself)

```bash
# 3a. Build train_list.txt + train_gt.csv (instant)
python3 -c "
from pathlib import Path
imgs = sorted(Path('data/Laboro-Tomato/train/images').glob('*.jpg'))
Path('data/train_list.txt').write_text('\n'.join(str(p) for p in imgs) + '\n')
print(f'Wrote {len(imgs)} lines')
"
PYTHONPATH=perception python3 perception/tools/build_val_gt_csv.py \
  --val-images data/Laboro-Tomato/train/images \
  --val-labels data/Laboro-Tomato/train/labels \
  --output data/train_gt.csv \
  --val-list data/train_list.txt

# 3b. Install SigLIP deps (once per container)
pip install transformers sentencepiece Pillow --break-system-packages

# 3c. Dump per-detection features from the train set (~3.5 h NucBox CPU)
AGROBOT_FORCE_CPU=1 HIP_VISIBLE_DEVICES="" PYTHONPATH=perception \
  python3 perception/eval/run_eval.py \
    --val-list data/train_list.txt --gt-csv data/train_gt.csv \
    --detector sam2_amg --amg-points 28 --max-detections 60 \
    --confidence 0.0 --nms-iou 0.50 --dino-weight 0.7 \
    --query-embedding models/query_embedding_k4.pt \
    --negative-embedding models/negative_embedding.pt \
    --negative-weight 1.0 \
    --siglip --siglip-w-dino 0.4 --siglip-w-siglip 0.4 --siglip-w-pred-iou 0.2 \
    --fusion-features-out eval_reports/p2_2_train_features.jsonl

# 3d. Train the fusion MLP (~30 sec CPU)
PYTHONPATH=perception python3 perception/tools/train_fusion_mlp.py \
  --features eval_reports/p2_2_train_features.jsonl \
  --image-list data/train_list.txt \
  --gt-csv data/train_gt.csv \
  --output models/fusion_mlp.pt --epochs 30
```

### Sync Mac ↔ NucBox

```bash
bash tools/network/setup/model_sync.sh --pull   # NucBox → Mac
bash tools/network/setup/model_sync.sh --all    # Mac → NucBox
```

### Rebuild val_gt.csv if labels change

```bash
python3 perception/tools/build_val_gt_csv.py \
  --val-images data/Laboro-Tomato/val/images \
  --val-labels data/Laboro-Tomato/val/labels \
  --output data/val_gt.csv --val-list data/val_list.txt
```

---

## Results — Laboro Tomato val (161 images, 1,996 GT)

| Sprint | Config | mAP | prec | rec | Mean ms |
|--------|--------|-----|------|-----|---------|
| S3.4a | sam2_amg pts=8 | 0.022 | 0.19 | 0.13 | 2017 |
| S3.4b | sam2_amg pts=12 | 0.023 | 0.14 | 0.20 | 3665 |
| S3.6 | + contrastive λ=1.0 | 0.060 | 0.35 | 0.19 | ~3990 |
| S3.7 | pts=16 | 0.091 | 0.34 | 0.28 | 6536 |
| S3.8 | + nms=0.5 | 0.112 | 0.42 | 0.28 | 6329 |
| S3.9 | + polygon FT (box prompts) | 0.139 | 0.52 | 0.27 | 7061 |
| S3.10 | pts=20, single-mean query | 0.170 | 0.50 | 0.34 | 9458 |
| S4.1 | k4 + hard-neg λ=1.2 (poisoned) | 0.070 | 0.79 | 0.09 | 9392 |
| S4.2 | E1+E2+E4: k4 query + bg-mean neg λ=1.0, pts=20, max=20 | 0.287 | 0.72 | 0.42 | 9393 |
| S4.3 | k4 + hard-neg λ=0.5 | 0.135 | 0.31 | 0.50 | 9391 |
| S4.4 | pts=24, max=30, k4 + bg-mean λ=1.0 | 0.328 | 0.70 | 0.49 | 13377 |
| S4.5 | sam2_semantic top-k=48 (under-prompted) | 0.083 | 0.41 | 0.22 | 1772 |
| S4.6 | sam2_semantic top-k=128 | 0.114 | 0.36 | 0.34 | 3716 |
| S4.7 | dino_weight=0.7, conf=0.20 | 0.134 | 0.25 | 0.60 | 13225 |
| S4.8 | dino_weight=1.0, conf=0.15 | 0.335 | 0.66 | 0.54 | 14578 |
| S4.9 | dino_weight=0.7, conf=0.35, pts=24 | 0.360 | 0.68 | 0.56 | 13968 |
| S4.10 | dino_weight=0.7, conf=0.30, pts=24 | <0.360 | — | — | — |
| **S4.12** | **dino_weight=0.7, conf=0.35, pts=28, max=30** | **0.377** | **0.64** | **0.62** | **19081** |
| S4.13 | pts=32, max=35 (recall-chasing) | 0.378 | 0.61 | 0.67 | 21883 |
| E6-base | LoRA DINOv2 rank=8, same conf=0.35 | 0.035 | 0.744 | 0.045 | 17887 |
| P1.1 | post-filter sweep: conf=0.40 nms=0.40 max=30 | 0.396 | 0.74 | 0.55 | 19081 |
| P1.2 | P1.1 + horizontal-flip TTA | 0.391 | 0.67 | 0.61 | 37993 |
| P1.3 | P1.1 + SigLIP fixed fusion (0.4/0.4/0.2) | 0.360 | 0.59 | 0.65 | 21023 |
| **P2.2** | **SigLIP + trained MLP fusion (7-dim features)** | †0.089 | †0.14 | †0.68 | 24148 |
| P3.1 | Mask-Cond LoRA (polygon GT, fixed NT-Xent, cross-image batches) | 0.350 | 0.60 | 0.62 | 21382 |

† P2.2 legacy mAP is at `--confidence 0.0` (long low-probability tail); the
COCO 101-point metrics are the meaningful comparison. On COCO P2.2 beats
S4.12 by +0.100 mAP@[.5:.95] and +0.132 AP@0.50 — see the table in `Current
best` above.

### Key insight (S3.4)

DINOv2 proposals snap to a 14px grid → coarse boxes → IoU < 0.5.
Fix: **SAM2 AMG proposes, DINOv2 scores**. Architecture swap alone: mAP 0 → 0.022.

### Progression summary

| Step | Change | Legacy mAP@0.5 |
|------|--------|----------------|
| S3.10 | pts=20, single-mean query | 0.170 |
| S4.12 | k=4 prototypes, pts=28, conf=0.35, nms=0.50 | 0.377 (+122% vs S3) |
| P1.1 | post-filter sweep: conf=0.40, nms=0.40 | 0.396 |
| **P2.2** | **+ SigLIP + trained MLP fusion** | **0.492 (+30% vs S4.12)** |

Architecture deep-dive: [docs/SPRINT4_ARCHITECTURE.md](docs/SPRINT4_ARCHITECTURE.md).
ROCm GPU path: [docs/SPRINT3_ROCM_ISSUE.md](docs/SPRINT3_ROCM_ISSUE.md).
