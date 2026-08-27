# HACK-PAD V2

Hiii, well this is my second version of the Hack Pad since the other one was kinda lame though, so I added new functions to it so it's more fun and useful. You can check out the functions down here :D

## What it does

- 🖥️ **Custom screen** — Showing anything u want, text or image. Upload it by the PC app!
- ⌨️ **4 keys with editable macros** — Customizable key macros (copy, paste, undo, etc.)
- 🌈 **RGB LEDs with configurable color** — Also custom! choose the color u want in the app.
- 🎮 **Secret minigame** — Snake hidden inside the pad itself

  `Hint`: Press all keys down at the same time

- 🕹️ **Extra minigames on the PC** — Snake and Simon Says, run from the desktop app.
- 🔌 **USB cable** — only used to configure the pad from the PC app (text, macros, colors, image); normal macros go over BLE.
- 🔋 Battery-powered (14500 Li-ion + TP4056 charging).

## Repo structure

```
HACK-PAD/
├── firmware/     C++ firmware (PlatformIO) flashed onto the XIAO ESP32-C3
├── pc_app/       Desktop app in Python to configure the pad
├── hardware/     KiCad project (schematic, PCB, 3D models)
└── production/   Files for manufacturing the project (Gerber and .STEP files)
```

Each folder has its own README with the details

## Getting started

1. **Build/solder the board** — see `hardware/` for the schematic,
   layout, and the 3D model for printing the case. The module to solder
   is a **Seeed XIAO ESP32-C3** (see the compatibility note in
   `hardware/README.md`).
2. **Flash the firmware** — see `firmware/README.md` (PlatformIO + VS Code).
3. **Pair over Bluetooth** — look for "HACK-PAD" in your PC/phone's
   Bluetooth settings (details in `firmware/README.md`).
4. **Install the PC app** — see `pc_app/README.md` (`pip install -r
   requirements.txt` and you're set) — connects over the USB cable.

## Pinout (Seeed XIAO ESP32-C3)

Traced directly from the original PCB's netlist, not a generic
pinout — and confirmed to match the XIAO ESP32-C3 (same family, same
hardware SPI pins):

| XIAO pin | Connected to |
|---|---|
| D0–D3 | Buttons SW1–SW4 |
| D4 (SDA) | Data line for the 6 SK6812 LEDs (in parallel, all the same color) |
| D5 (SCL) | OLED RST |
| D6 (TX) | OLED DC |
| D8 (SCK) | OLED SCK |
| D9 (MISO) | OLED CS |
| D10 (MOSI) | OLED MOSI/DIN |

## Communication protocol (firmware ↔ PC app, over the cable)

Plain text over USB, 115200 baud — full command reference in
`firmware/README.md`. Summary:

```
PING · SET_TEXT · SET_MACRO · SET_COLOR · SET_BRIGHTNESS · SAVE · GET_CONFIG · IMG_START
```
# Bill of Materials — HACK-PAD V2

## On-board (populated on the HACK-PAD PCB)

| RefDes | Description | Manufacturer / Part | Qty | Unit Price | Line Total | Supplier |
|---|---|---|---|---|---|---|
| U1 | XIAO ESP32-C3 module (RISC-V, WiFi+BLE) | [Seeed Studio XIAO ESP32C3](https://www.seeedstudio.com/Seeed-XIAO-ESP32C3-p-5431.html) | 1 | $4.99 | $4.99 | Seeed Studio |
| U2 (SCREEN) | 1.5" 128x128 RGB OLED, SPI (SSD1351) | [Waveshare 1.5inch RGB OLED Module](https://www.waveshare.com/1.5inch-rgb-oled-module.htm) | 1 | $20.99 | $20.99 | Waveshare |
| SW1–SW4 | Cherry MX mechanical switch, PCB mount | Cherry MX (any linear/tactile variant) | 4 | $0.35 | $1.40 | [MechanicalKeyboards.com](https://mechanicalkeyboards.com/collections/cherry-switches) |
| D1–D6 | Addressable RGB LED, PLCC4 5x5mm | [OPSCO SK6812](https://www.lcsc.com/product-detail/RGB-LEDs-Built-in-IC_OPSCO-Optoelectronics-SK6812_C5378720.html) | 6 | $0.07 | $0.42 | LCSC |
| R1 | Resistor, 330Ω, 1206 SMD | Generic 1206 | 1 | $0.02 | $0.02 | LCSC |
| C1 | Capacitor, 1206 SMD (schematic value: 500µF*) | Generic 1206 | 1 | $0.10 | $0.10 | LCSC |
| J1 (VIN) | 2-pin header, 1.00mm pitch | Generic | 1 | $0.15 | $0.15 | LCSC / Amazon |
| — | Custom 2-layer PCB | Fabricated from `hardware/*.kicad_pcb` | 1 | $5.00 | $5.00 | [JLCPCB](https://jlcpcb.com/) |

\* 500µF is an unusually large value for a 1206 ceramic package — that's
the value as labeled in the schematic. Double-check it against the
physical part (could be a tantalum/polymer cap, or a typo) before ordering.

## Off-board (wired in via the VIN header, not soldered to this PCB)

| Description | Manufacturer / Part | Qty | Unit Price | Line Total | Supplier |
|---|---|---|---|---|---|
| TP4056 protected Li-ion charging module (USB-C) | Generic, with protection | 1 | $1.99 | $1.99 | [Amazon](https://www.amazon.com/TP4056/s?k=TP4056) |
| 14500 Li-ion rechargeable cell, 3.7V | Generic protected cell | 1 | $6.99 | $6.99 | [Amazon](https://www.amazon.com/14500-battery-3-7v-li-ion-rechargeable/s?k=14500+battery+3.7v+li-ion+rechargeable) |
| Hookup wire (22–24 AWG, short length) | Generic | 1 | $0.50 | $0.50 | Amazon / any electronics shop |

## Enclosure (not included in the subtotal)

| Description | Source | Cost |
|---|---|---|
| 3D-printed case (`hardware/3D_HACK-PAD_Printing.step`) | Print it yourself, or a service like JLC3DP / Craftcloud | Varies by filament/service |

## Subtotal

**On-board + off-board parts: ≈ $42.55** (excludes shipping, taxes, and the printed case)

## License

MIT — see [`LICENSE`](LICENSE). Use, modify, and share the project
freely, with or without credit.
