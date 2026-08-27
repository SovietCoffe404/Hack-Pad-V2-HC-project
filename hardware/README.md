# Hardware

## `PCB`

| File | What it is |
|---|---|
| `PCB/HACK-PAD V2.kicad_pro` | Project — open this one on KiCad |
| `PCB/HACK-PAD V2.kicad_sch` | Schematic |
| `PCB/HACK-PAD V2.kicad_pcb` | Board layout |
| `PCB/HACK-PAD V2.kicad_prl` | Local project preferences (not critical) |
| `PCB/fp-lib-table` | Footprint library |
| `PCB/Hack Pad-V2 Gerber.zip` | Manufacturing the PCB |
| `PCB/3D HACK-PAD.step` | 3D model of the assembled PCB |

## `CAD/case_models`

| File | What it is |
|---|---|
| `CAD/case_models/3D_HACK-PAD_Assembled.step` | 3D model with all components mounted — for visualizing/rendering the full pad |
| `CAD/case_models/3D_HACK-PAD_Printing.step` | Simplified 3D model (no electronics) — for 3D-printing the case/enclosure |
| `CAD/case_models/3D HACK-PAD Top.step` | The top of the case, it keeps everything in place |
| `CAD/case_models/3D HACK-PAD Body.step` | Our main case, it stores all the electronics |
| `CAD/case_models/3D HACK-PAD Battery cover.step` | Case for the batteries compartment |

## `CAD/keycap_models`

Individual `.stl` files, ready to 3D-print. :D

## Pinout

| XIAO pin | Connected to |
|---|---|
| D0–D3 | Buttons SW1–SW4 (to GND, with internal pull-up) |
| D4 (SDA) | Data line for the 6 SK6812 LEDs — **all 6 share the same DIN in parallel on purpose**, which is why they always show the same color |
| D5 (SCL) | OLED RST |
| D6 (TX) | OLED DC |
| D8 (SCK) | OLED SCK (hardware SPI) |
| D9 (MISO) | OLED CS |
| D10 (MOSI) | OLED MOSI/DIN (hardware SPI) |
