# Production!

Every file ready for manufacturing!

## Files

| File | Tipe | What for? |
|---|---|---|
| `Hack_Pad-V2_Gerber.zip` | Gerber (PCB) | PCB manufacturing |
| `3D_HACK-PAD_Body.step` | STEP | 3D print / Body of the Pad |
| `3D_HACK-PAD_Top.step` | STEP | 3D print / Top case for the pad and mount of the switchs |
| `3D_HACK-PAD_Battery_cover.step` | STEP | 3D print / Case for the battery compartment |

## PCB — `Hack_Pad-V2_Gerber.zip`

**From**: KiCad (Pcbnew 10.0.2)

| Parameters | Value |
|---|---|
| Dimensions | 60.05 mm × 91.05 mm |
| Layers | 2 (F.Cu / B.Cu) |
| Thickness | 1.6 mm |
| Surface finish | No especificado |
| Pad-to-pad / Pad-to-track / Track-to-track | 0.2 mm |
| Minimum track width | 0.2 mm |

**Zip content:**
- `*-F_Cu.gbr` / `*-B_Cu.gbr` — copper top/bottom
- `*-F_Mask.gbr` / `*-B_Mask.gbr` — solder mask
- `*-F_Paste.gbr` / `*-B_Paste.gbr` — solder paste
- `*-F_Silkscreen.gbr` / `*-B_Silkscreen.gbr` — serigraphy
- `*-Edge_Cuts.gbr` — edge borders of the board
- `*-PTH.drl` / `*-NPTH.drl` — holes and drill job 
- `*-job.gbrjob` — metadata

## Case — STEP files

STEP (AP214), modifiable in every CAD (FreeCAD, Fusion 360, SolidWorks, etc.)

| Part | File | Notes |
|---|---|---|
| Body | `3D_HACK-PAD_Body.step` | Stores the PCB and is the main case of the project |
| Top case | `3D_HACK-PAD_Top.step` | Closes everything and keeps things on it's place |
| Battery cover | `3D_HACK-PAD_Battery_cover.step` | Stops batteries from falling |
