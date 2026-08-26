# HACK-PAD V2

Hiii, well this is my second version of the Hack Pad since the other one was kinda lame though, so I added new functions to it so it's more fun and useful. You can check out the functions down here :D

## What it does

- 🖥️ **Custom screen** — your own text or image, set from the PC app.
- ⌨️ **4 keys with editable macros** — shortcuts (copy/paste/undo/etc.) or free text, sent over **Bluetooth LE** as if it were a real keyboard.
- 🌈 **RGB LEDs with configurable color** — the 6 SK6812s all show the same color (they share data in parallel, by design).
- 🎮 **Secret minigame** — Snake hidden inside the pad itself, triggered by holding all 4 keys down.
- 🕹️ **Extra minigames on the PC** — Snake and Simon Says, run from the desktop app.
- 🔌 **USB cable** — only used to configure the pad from the PC app (text, macros, colors, image); normal macros go over BLE.
- 🔋 Battery-powered (14500 Li-ion + TP4056 charging).

## Repo structure

```
HACK-PAD/
├── firmware/     C++ firmware (PlatformIO) flashed onto the XIAO ESP32-C3
├── pc_app/       Desktop app in Python to configure the pad
└── hardware/     KiCad project (schematic, PCB, 3D models)
```

Each folder has its own README with the details — this one is just the map.

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

## License

MIT — see [`LICENSE`](LICENSE). Use, modify, and share the project
freely, with or without credit.
