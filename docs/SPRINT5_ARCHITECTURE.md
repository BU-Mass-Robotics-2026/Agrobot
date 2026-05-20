# Sprint 5 — Detector Architecture (Current Best)

**Result:** mAP@0.5 = **0.492** | COCO mAP@[.5:.95] = **0.438** | Precision = **0.87** | ~21 s/frame (NucBox CPU)

This document explains how the tomato detector works from the ground up — what each component does, why it exists, and what problem it solves. No prior knowledge of the code assumed.

---

## The Big Picture

The detector's job is: *given one RGB frame from the RealSense camera, return a list of bounding boxes around tomatoes with a confidence score for each.*

It does this in four sequential stages:

```
RGB image (518 × 518 px)
        │
        ├──────────────────────────────────────────────────┐
        │                                                  │
        ▼                                                  ▼
[Stage 1] SAM2 AMG                              [Stage 2] DINOv2 + SigLIP
Generate ~784 mask proposals                    Score how "tomato-like"
(pixel-precise outlines of                      each proposal is using two
every distinct region)                          independent AI models
        │                                                  │
        └─────────────────────┬────────────────────────────┘
                              │  784 proposals, each with:
                              │  • pixel mask
                              │  • DINOv2 similarity score
                              │  • SigLIP similarity score
                              │  • SAM2 shape quality score
                              ▼
                    [Stage 3] Fusion MLP
                    A tiny neural network
                    combines all scores into
                    one "is this a tomato?" probability
                              │
                              ▼
                    [Stage 4] NMS + cap
                    Remove overlapping duplicates
                    Keep top 30 by probability
                              │
                              ▼
                    Final detections (boxes + scores)
```

---

## Stage 1 — SAM2 AMG: Generating Proposals

### What it does

SAM2 (Segment Anything Model 2, by Meta) runs in **Automatic Mask Generator** mode. It places a uniform 28 × 28 grid of prompt points across the image — 784 points total — and for each one asks: *"what coherent object is at this location?"*

The result is up to 784 **masks** — pixel-precise binary outlines of every distinct region in the image (tomatoes, leaves, stems, trellises, background, etc.). SAM2 does not know which masks are tomatoes; it just segments everything it can find.

```
28 × 28 grid of prompt points
→ SAM2 decoder runs for each point
→ 784 candidate masks, one per point
→ each mask also comes with pred_iou
   (SAM2's own confidence that the mask
    is a coherent object, 0–1)
```

### Key terms

**Mask** — a boolean image the same size as the input (518 × 518) where `True` pixels belong to the detected region and `False` pixels do not. Tomatoes are roughly circular masks.

**pred_iou** — SAM2's self-assessed score for how well-formed its own mask is. 1.0 = perfect closed shape. This is not semantic — SAM2 doesn't know if it's a tomato or a rock, just whether its segmentation boundary looks clean.

**AMG (Automatic Mask Generator)** — the mode where SAM2 runs without being told where to look. The alternative (SAM2ImagePredictor) takes a specific point as input; AMG tries everywhere automatically.

### Why SAM2 proposes (not DINOv2)

The naive alternative is to have DINOv2 propose regions directly from its patch grid. DINOv2 operates on a 14 × 14 pixel patch grid, so its coarsest possible bounding box is 14 px wide. A tomato 50 cm away subtends ~60 px in the image — its DINOv2-grid bounding box overlaps the true tomato at only ~30% (IoU < 0.3). That's too imprecise for mAP@0.5. SAM2 gives us **pixel-level masks** for each region, so the bounding box is tight around the actual tomato contour, not a patch-grid approximation.

---

## Stage 2 — DINOv2: Patch-Level Semantic Scoring

### What it does

DINOv2 (a self-supervised vision transformer by Meta) runs once per frame and produces a grid of **patch tokens** — a 37 × 37 grid of 768-dimensional feature vectors, one per 14 × 14 pixel block of the image.

Think of each feature vector as a learned "fingerprint" of that image region. DINOv2 was trained to make patches of the same object type produce similar fingerprints, so tomato patches cluster together in this 768-dim space, and leaf patches cluster elsewhere.

### Matching proposals to the query

We pre-built four **prototype vectors** (called `query_embedding_k4.pt`) from the training images:

- Prototype 0 → fingegerprint of green/unripe tomatoes
- Prototype 1 → fingerprint of yellow/partially-ripe tomatoes
- Prototype 2 → finrprint of red/fully-ripe tomatoes
- Prototype 3 → fingerprint of partially-occluded tomatoes

For each SAM2 mask proposal, we compute how similar the image patches *inside* the mask are to each prototype, using **cosine similarity** (a measure of direction-match between two vectors, −1 to +1). We take the **max across the four prototypes** — so a green tomato can score high on prototype 0 even if prototypes 1–3 are all about ripe tomatoes.

### Coverage-weighted scoring

Not all patches are fully inside the mask. A round tomato crosses many 14-px grid boundaries, so boundary patches are partially inside and partially outside. We weight each patch's contribution by how much of its 14 × 14 block is actually inside the mask (a float in [0, 1]).

```
For each mask proposal:
  coverage[i] = fraction of patch cell i inside the mask   (0.0 to 1.0)

  tomato_sim = max over 4 prototypes of:
      Σ(coverage[i] × cos(patch[i], prototype_k)) / Σ(coverage[i])
```

### Contrastive negative suppression

Leaves and stems look similar to green tomatoes in DINOv2 space. We also pre-built a **background prototype** (mean fingerprint of non-tomato patches). The final DINOv2 score subtracts the background similarity:

```
dino_sim = tomato_sim − 1.0 × background_sim
```

This penalises any mask whose patches look like leaf/stem even if they also vaguely resemble a tomato.

---

## Stage 2b — SigLIP: Global Semantic Scoring

### What it does

SigLIP (Sigmoid Language-Image Pre-training, by Google) is a completely different model. It was trained to match **entire images** to **text descriptions**. We use it to score each SAM2 mask proposal by cropping the mask's bounding box from the RGB image and comparing it to text prompts.

**Positive prompts** (we want high similarity to these):
- `"a photograph of a ripe red tomato on a vine"`
- `"a photograph of a ripe yellow tomato"`
- `"a green unripe tomato"`

**Negative prompts** (we want low similarity to these):
- `"a green leaf"`
- `"a stem"`
- `"soil"`
- `"a wooden post"`

```
For each mask proposal:
  1. Crop the bounding box from the original RGB image
  2. Run SigLIP image encoder → one 768-dim embedding
  3. Compare to the pre-computed text embeddings (done once at startup)
  siglip_sim = max(positive cosine similarities) − max(negative cosine similarities)
```

### Why both DINOv2 and SigLIP?

They fail on different things:
- **DINOv2** is patch-level and dense — excellent at local texture and shape, but it has never seen the word "tomato". It scores by visual similarity to known tomato patches.
- **SigLIP** is global and text-aligned — it understands "tomato" semantically, but it only sees the cropped box, not the full-image context.

A mask that fools DINOv2 (e.g. a reddish pepper) often doesn't fool SigLIP's text alignment, and vice versa. Combining them is more robust than either alone.

---

## Stage 3 — Fusion MLP: Learning to Combine All Scores

### The problem with fixed weights

A naive approach: `final_score = 0.4 × dino_sim + 0.4 × siglip_sim + 0.2 × pred_iou`. This was tried (Phase 1.3) and actually *hurt* mAP — the fixed weights are wrong because, for example, `pred_iou` matters more for small masks than large ones, and the DINOv2/SigLIP balance differs between ripe and green tomatoes.

### The MLP solution

We trained a tiny neural network (an MLP — Multi-Layer Perceptron) to learn the right combination from data. It takes 7 features per detection as input and outputs a single probability: "is this a true positive detection (IoU ≥ 0.5 vs a real tomato)?"

**The 7 input features:**

| # | Feature | What it measures | Why it helps |
|---|---|---|---|
| 1 | `dino_sim` | DINOv2 patch similarity to tomato prototypes | Semantic identity via dense features |
| 2 | `siglip_sim` | SigLIP image-text similarity | Semantic identity via language alignment |
| 3 | `pred_iou` | SAM2's self-assessed mask shape quality | Filters fragmented/messy masks |
| 4 | `mask_area_norm` | Mask area ÷ image area | Normalises scale; tiny masks are noisier |
| 5 | `circularity` | 4π·area / perimeter² | Tomatoes are round (≈1); leaves are elongated (≪1) |
| 6 | `color_mean_h` | Mean hue (HSV) inside the bbox | Tomato hues cluster at red/orange/green |
| 7 | `color_sat_mean` | Mean saturation inside the bbox | Distinguishes tomatoes from grey background/walls |

**MLP architecture:** 7 → 32 → 16 → 1 (three linear layers with ReLU activations, sigmoid output)

**Training:**
1. Run the detector over all 643 training images with no confidence gate
2. For each detection, check if it actually overlaps a GT tomato (IoU ≥ 0.5) → label: 1 (TP) or 0 (FP)
3. Train the MLP for 30 epochs via Binary Cross-Entropy loss
4. Best validation AP = 0.907 on held-out train data

The MLP is tiny (< 2KB parameters) and runs in microseconds — its latency cost is zero compared to the 21-second per-frame SAM2+DINOv2+SigLIP forward passes.

---

## Stage 4 — NMS and Cap

### Non-Maximum Suppression (NMS)

SAM2 produces many overlapping proposals for the same tomato (one from each grid point near its centre). After the MLP scores everything, we apply NMS: for any two detections whose bounding boxes overlap by more than 40% (IoU ≥ 0.4), keep only the one with the higher MLP probability and discard the other.

```
Two masks both cover the same tomato → IoU = 0.72 → one is suppressed
```

### Detection cap

We keep only the top 30 detections per frame by MLP probability. This is a hard ceiling — in practice, most frames have 2–15 tomatoes, so the cap rarely bites. Setting it higher (60) or lower (10) trades recall for latency (fewer detections to post-process).

---

## Results vs Previous Versions

| Version | What changed | Legacy mAP@0.5 | COCO mAP@[.5:.95] | Precision |
|---|---|---|---|---|
| Sprint 3 best | pts=20, single-mean query | 0.170 | — | — |
| S4.12 | k=4 prototypes, pts=28 | 0.377 | 0.338 | 0.64 |
| P1.1 | Post-filter sweep | 0.396 | 0.323 | 0.74 |
| **P2.2 (current)** | **+ SigLIP + MLP fusion** | **0.492** | **0.438** | **0.87** |

The single biggest jump (+0.115 mAP@0.5) came from the MLP fusion — not from a better backbone, more data, or longer training, but from **learning to combine existing signals optimally**. The MLP's training data is the detector's own outputs on the training set: no extra labels were needed beyond what was already used to build the prototypes.

---

## Key Metric Definitions

**mAP@0.5 (legacy)** — Mean Average Precision at IoU threshold 0.5. A detection "counts" as correct only if its bounding box overlaps the ground-truth box by at least 50%. AP is the area under the precision–recall curve at that threshold. We still report this because all prior sprint results use it.

**COCO mAP@[.5:.95]** — The standard metric in published computer vision papers. It averages AP across 10 IoU thresholds from 0.50 to 0.95 in steps of 0.05. Much harder than mAP@0.5 — a detection must overlap with the GT *very tightly* (95% for the hardest threshold) to count.

**AP_small / AP_medium / AP_large** — COCO AP broken down by object size. Small = area < 32² px, medium = 32²–96² px, large = > 96² px. Our AP_small improved 2.2× (0.054 → 0.117) because the MLP's `mask_area_norm` and `circularity` features help distinguish real small tomatoes from noise blobs.

**Precision** — Of all detections we made, what fraction were correct? 0.87 means 87% of our reported detections are genuine tomatoes.

**Recall** — Of all real tomatoes in the images, what fraction did we find? 0.57 at the production conf threshold, 0.68 at conf=0.

**IoU (Intersection over Union)** — The overlap metric. Two boxes with IoU = 0.5 have half their combined area in common. This is the standard threshold for "close enough to count as a hit."

**NMS (Non-Maximum Suppression)** — The de-duplication step that removes redundant overlapping detections for the same object.

**Cosine similarity** — A measure of how similar two vectors are, ranging from −1 (opposite directions) to +1 (same direction). We use it to compare DINOv2 patch fingerprints to prototype fingerprints.

---

## File Map

| File | Role |
|---|---|
| `perception/agrobot_perception/detectors/sam2_amg_detector.py` | SAM2 AMG + DINOv2 scoring (Stage 1 + Stage 2) |
| `perception/eval/siglip_rescoring.py` | SigLIP wrapper that adds Stage 2b scores |
| `perception/eval/fusion_mlp.py` | MLP definition + `FusionMLPWrapper` (Stage 3) |
| `models/query_embedding_k4.pt` | Pre-built k=4 DINOv2 prototype vectors |
| `models/negative_embedding.pt` | Pre-built DINOv2 background prototype |
| `models/fusion_mlp.pt` | Trained MLP weights (20 KB) |
| `models/sam2/sam2_tomato_finetuned.pt` | SAM2 decoder fine-tuned on tomato polygon GT |
| `perception/eval/run_eval.py` | Orchestrates the full pipeline + computes metrics |
| `perception/eval/metrics_coco.py` | COCO mAP@[.5:.95] / AP_small/medium/large |
