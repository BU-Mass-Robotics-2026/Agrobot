# models/quarantine/ — val-leaked artifacts

Files moved here were built using val-set ground truth and therefore cannot
be used in any number reported in the paper without invalidating the result.

| File | Origin | Why quarantined |
|------|--------|-----------------|
| `hard_negative_embedding.pt` | `perception/tools/mine_hard_negatives.py` | Mined false positives against `data/val_gt.csv` → embedding encodes val GT structure. |

The replacement is to mine hard negatives on the **train** set (using train
COCO polygons as the "what is background" oracle) or to use self-training
pseudo-labels (Phase 3.2 — strict label-free regime).

If you need a quick negative for legacy comparison runs, use the background-mean
`models/negative_embedding.pt` produced by `build_query_embedding.py
--output-negative` — it is built from train images only.
