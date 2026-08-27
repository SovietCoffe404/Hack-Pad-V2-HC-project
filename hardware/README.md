# Hardware

| File | What it is |
|---|---|
| `HACK-PAD_V2.kicad_pro` | Project — open this one from KiCad |
| `HACK-PAD_V2.kicad_sch` | Schematic |
| `HACK-PAD_V2.kicad_pcb` | Board layout |
| `HACK-PAD_V2.kicad_prl` | Local project preferences (not critical) |
| `fp-lib-table` | Footprint library table used by the project |
| `3D_HACK-PAD_Assembled.step` | 3D model with all components mounted — for visualizing/rendering the full pad |
| `3D_HACK-PAD_Printing.step` | Simplified 3D model (no electronics) — for 3D-printing the case/enclosure |

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

