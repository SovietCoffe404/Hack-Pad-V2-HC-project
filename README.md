# HACK-PAD V2

Hiii, well this is my second version of the Hack Pad since the other one was kinda lame though, so I added new functions to it so it's more fun and useful. You can check out the functions down here :D

# Based on:
**https://hackpad.hackclub.com**

## What it does

- 🖥️ **Custom screen** — Showing anything u want, text or image. Upload it by the PC app!
- ⌨️ **4 keys with editable macros** — Customizable key macros (copy, paste, undo, etc.)
- 🌈 **RGB LEDs with configurable color** — Also custom! choose the color u want in the app.
- 🎮 **Secret minigame** — Snake hidden inside the pad

  `Hint`: Press all keys down at the same time

- 🕹️ **Extra minigames on the PC** — U can add more minigames!
- 🔌 **USB cable** — Only used to configure the pad from the PC app.
- 🔋 **Battery** (14500 Li-ion + TP4056 charging) you can replace it whenever is needed.

## Repo structure

```
HACK-PAD/
├── firmware/     C++ firmware (PlatformIO) flashed onto the XIAO
├── pc_app/       Desktop app in Python to configure the pad
├── hardware/     KiCAD and Fusion project (schematic, PCB, 3D models)
| ├── PCB/        KiCAD project
| └── CAD/        3D models
└── production/   Files for manufacturing (Gerber and .STEP files)
```

Each folder has its own README with the details, such like the PINOUT and clarifications about some things you may have doubts on :) 

## Pinout (Seeed XIAO ESP32-C3)

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
# BOM — HACK-PAD V2

## On-board (populated on the HACK-PAD PCB)

| RefDes | Description | Manufacturer / Part | Qty | Unit Price | Line Total | Supplier |
|---|---|---|---|---|---|---|
| U1 | XIAO ESP32-C3 module (RISC-V, WiFi+BLE) | [Seeed Studio XIAO ESP32C3](https://www.seeedstudio.com/Seeed-XIAO-ESP32C3-p-5431.html) | 1 | $4.99 | $4.99 | Seeed Studio |
| U2 (SCREEN) | 1.5" 128x128 RGB OLED, SPI (SSD1351) | [Waveshare 1.5inch RGB OLED Module](https://www.waveshare.com/1.5inch-rgb-oled-module.htm) | 1 | $20.99 | $20.99 | Waveshare |
| SW1–SW4 | Cherry MX mechanical switch, PCB mount | Cherry MX (any linear/tactile variant) | 4 | $0.35 | $1.40 | [MechanicalKeyboards.com](https://mechanicalkeyboards.com/collections/cherry-switches) |
| D1–D6 | Addressable RGB LED, PLCC4 5x5mm | [OPSCO SK6812](https://www.lcsc.com/product-detail/RGB-LEDs-Built-in-IC_OPSCO-Optoelectronics-SK6812_C5378720.html) | 6 | $0.07 | $0.42 | LCSC |
| R1 | Resistor, 330Ω, 1206 SMD | Generic 1206 | 1 | $0.02 | $0.02 | LCSC |
| C1 | Capacitor, 1206 SMD (schematic value: 100nF) | Generic 1206 | 1 | $0.10 | $0.10 | LCSC |
| J1 (VIN) | 2-pin header, 1.00mm pitch | Generic | 1 | $0.15 | $0.15 | LCSC / Amazon |
| — | Custom 2-layer PCB | Fabricated from `hardware/*.kicad_pcb` | 1 | $5.00 | $5.00 | [JLCPCB](https://jlcpcb.com/) |

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

## Screen Shots!

<img width="269" height="350" alt="Screenshot 2026-08-25 124445" src="https://github.com/user-attachments/assets/57dff823-78fc-4db9-b97f-e2bf9d4f8c6a" />

<img width="392" height="266" alt="Screenshot 2026-08-23 134833" src="https://github.com/user-attachments/assets/a5ac759a-d925-4f4e-998b-c7fa6ee18c80" />

<img width="461" height="299" alt="Screenshot 2026-08-26 154640" src="https://github.com/user-attachments/assets/6fef6c26-5d16-42cc-927a-d03d297d1b54" />

<img width="566" height="286" alt="Screenshot 2026-08-27 131850" src="https://github.com/user-attachments/assets/7ec89ceb-b461-4cf8-9bda-0ab4a03d65e4" />

<img width="15247" height="4320" alt="3D HACK-PAD" src="https://github.com/user-attachments/assets/7c5693a5-3ada-4bca-98b4-d1e0525cddf6" />

<img width="15247" height="4320" alt="jhjhghcvfgc  " src="https://github.com/user-attachments/assets/8466db94-a98a-4b03-ab76-d6f569df8152" />

<img width="3840" height="2160" alt="3D_HACK-PAD_2026-Aug-27_08-37-06PM-000_CustomizedView8673833641" src="https://github.com/user-attachments/assets/7b36a1b4-f58e-4fc3-8dcf-19d46a5b6b6a" />

## License

MIT — see [`LICENSE`](LICENSE). Use, modify, and share the project
freely, with or without credit.

## ★ Special thanks to:
`https://www.printables.com/@wireva` for the keycaps 3d model! :D

`hackclub.com` for the DIY guide and funding! <3
