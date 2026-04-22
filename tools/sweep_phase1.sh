#!/usr/bin/env bash
###############################################################################
# sweep_phase1.sh — Phase 1.1: confidence + max-detections sweep on S4.12.
#
# Runs the heavy detector ONCE with no post-filter (conf=0, nms=0, max=1000) and
# dumps all raw detections to JSONL. Then replays a Cartesian sweep over
# (confidence, nms_iou, max_detections) cheaply via sweep_post_filter.py.
#
# Total time on NucBox CPU:
#   - Heavy dump: ~50 min (one full eval pass; mAP/latency printed for sanity)
#   - Sweep:      ~30 sec
#
# Run on NucBox (inside the ROCm container):
#   bash tools/sweep_phase1.sh
#
# Override defaults (rare):
#   AMG_POINTS=32 bash tools/sweep_phase1.sh
###############################################################################
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$REPO_ROOT"

OUT_DIR="${OUT_DIR:-eval_reports/sweep_p1_1}"
RAW_JSONL="${OUT_DIR}/raw_detections.jsonl"
SWEEP_CSV="${OUT_DIR}/sweep_results.csv"

AMG_POINTS="${AMG_POINTS:-28}"
DINO_WEIGHT="${DINO_WEIGHT:-0.7}"
NEG_WEIGHT="${NEG_WEIGHT:-1.0}"
QUERY_EMB="${QUERY_EMB:-models/query_embedding_k4.pt}"
NEG_EMB="${NEG_EMB:-models/negative_embedding.pt}"

mkdir -p "$OUT_DIR"

# ── Step 1: heavy dump ──────────────────────────────────────────────────────
# conf=0, nms=0, max=1000 → no in-detector filtering. We replay filters in post.
if [[ -f "$RAW_JSONL" && "${REUSE:-1}" == "1" ]]; then
    echo "[skip] Reusing existing raw dump: $RAW_JSONL"
    echo "       Set REUSE=0 to force re-run."
else
    echo "[run] Heavy dump (~50 min on NucBox CPU)..."
    AGROBOT_FORCE_CPU=1 HIP_VISIBLE_DEVICES="" PYTHONPATH=perception \
      python3 perception/eval/run_eval.py \
        --val-list data/val_list.txt \
        --gt-csv data/val_gt.csv \
        --detector sam2_amg \
        --amg-points "$AMG_POINTS" \
        --confidence 0.0 \
        --nms-iou 0.0 \
        --max-detections 1000 \
        --dino-weight "$DINO_WEIGHT" \
        --query-embedding "$QUERY_EMB" \
        --negative-embedding "$NEG_EMB" \
        --negative-weight "$NEG_WEIGHT" \
        --detections-jsonl "$RAW_JSONL"
fi

# ── Step 2: cheap post-filter sweep ─────────────────────────────────────────
echo
echo "[run] Post-filter sweep..."
PYTHONPATH=perception python3 perception/eval/sweep_post_filter.py \
    --detections-jsonl "$RAW_JSONL" \
    --gt-csv data/val_gt.csv \
    --confidence 0.15 0.20 0.25 0.30 0.35 0.40 \
    --nms-iou 0.4 0.5 0.6 \
    --max-detections 30 45 60 \
    --output-csv "$SWEEP_CSV"

echo
echo "[done] Results: $SWEEP_CSV"
echo "       Use the best row to update the S4.12 command line in REPRODUCE.md."
