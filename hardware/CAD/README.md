# hardware/

KiCad 8 project for the HACK-PAD V2 (4-key macropad with color OLED screen
and RGB LEDs).

| File | What it is |
|---|---|
| `HACK-PAD_V2.kicad_pro` | Project — open this one from KiCad |
| `HACK-PAD_V2.kicad_sch` | Schematic |
| `HACK-PAD_V2.kicad_pcb` | Board layout |
| `HACK-PAD_V2.kicad_prl` | Local project preferences (not critical) |
| `fp-lib-table` | Footprint library table used by the project |
| `3D_HACK-PAD_Assembled.step` | 3D model with all components mounted — for visualizing/rendering the full pad |
| `3D_HACK-PAD_Printing.step` | Simplified 3D model (no electronics) — for 3D-printing the case/enclosure |

## XIAO module: SAMD21 (board) → ESP32-C3 (current firmware)

The schematic/PCB were originally designed around the **Seeed XIAO
SAMD21** footprint. The current firmware (`firmware/`) targets the
**Seeed XIAO ESP32-C3** for Bluetooth.

**No board redesign needed**: the whole XIAO family (SAMD21, ESP32-C3,
ESP32-S3, nRF52840, RP2040...) shares the same 14-pad castellated
footprint (21×17.5mm), and it's confirmed that the hardware SPI pins land
in the same spots (D8=SCK, D9=MISO, D10=MOSI) on both the SAMD21 and the
ESP32-C3 — the module can be swapped on the physical board without
touching the wiring.

The only thing left "untidy" is cosmetic: the schematic symbol still says
`MOUDLE-SEEEDUINO-XIAO` (its original value). If you want the BOM/schematic
to reflect the real chip, in KiCad: `Edit > Change Symbols...` and update
the `Value` to something like `XIAO-ESP32C3`. Not required for the board
to work, just project tidiness.

## Pinout (applies to any XIAO module you use)

| XIAO pin | Connected to |
|---|---|
| D0–D3 | Buttons SW1–SW4 (to GND, with internal pull-up) |
| D4 (SDA) | Data line for the 6 SK6812 LEDs — **all 6 share the same DIN in parallel on purpose**, which is why they always show the same color |
| D5 (SCL) | OLED RST |
| D6 (TX) | OLED DC |
| D8 (SCK) | OLED SCK (hardware SPI) |
| D9 (MISO) | OLED CS |
| D10 (MOSI) | OLED MOSI/DIN (hardware SPI) |

## Notes

- The screen is a Waveshare 1.5" 128x128 RGB OLED (SSD1351 driver).
- Power: 14500 Li-ion battery + TP4056 charge/protection module.
- The `*-backups/` folder KiCad automatically generates on save is
  excluded from the repo (see the root `.gitignore`) — no need to version it.
