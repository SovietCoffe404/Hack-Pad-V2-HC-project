# firmware/

Firmware for the HACK-PAD, targeting a **Seeed XIAO ESP32-C3** — wireless
over Bluetooth LE. A **PlatformIO** project.

> This project used to run on a XIAO SAMD21 over a USB cable. The
> wireless version swaps the module for a XIAO ESP32-C3 (same footprint,
> no board redesign needed) and the keyboard now sends keystrokes over
> Bluetooth LE instead of USB HID — the ESP32-C3 has no USB HID
> controller, only a USB serial port, which is still used to configure
> the pad from `pc_app/`.

## Structure

| File | What it does |
|---|---|
| `platformio.ini` | Board config (`seeed_xiao_esp32c3`) and libraries — installed automatically |
| `src/main.cpp` | Starts everything, updates the on-screen BLE indicator |
| `src/config.h` / `config.cpp` | Saves text, macros, and LED color to NVS (flash) via `Preferences` |
| `src/display.h` / `display.cpp` | Drives the OLED (text, images, BLE status dot) |
| `src/leds.h` / `leds.cpp` | Drives the 6 SK6812 LEDs |
| `src/keys.h` / `keys.cpp` | Reads the 4 buttons, runs macros over **BLE HID** (`BleKeyboard`), detects the secret combo |
| `src/game_snake.h` / `game_snake.cpp` | The secret minigame: Snake on the OLED |
| `src/serial_protocol.h` / `serial_protocol.cpp` | USB (serial) protocol that talks to `pc_app/` |

## Build and flash (PlatformIO + VS Code)

1. Install [VS Code](https://code.visualstudio.com/) and the **PlatformIO IDE** extension.
2. `File > Open Folder` → select this folder (`firmware/`).
3. Connect the XIAO ESP32-C3 over USB-C.
4. Click the PlatformIO icon → **Upload** (or `Ctrl+Alt+U`). If it doesn't
   drop into bootloader mode on its own, hold BOOT, tap RESET, then
   release BOOT (typical for ESP32 boards).
5. Open the Serial Monitor (115200 baud) and try sending `PING` — it
   should reply `OK HACKPAD v1`.

## Pairing over Bluetooth

1. With the firmware running, open the Bluetooth settings on your
   PC/phone and look for a device named **"HACK-PAD"**.
2. Pair it like any Bluetooth keyboard (usually no PIN required).
3. The dot in the top-right corner of the screen turns **green** when
   there's an active BLE connection, and gray when there isn't.
4. Once paired, the 4 keys send their macros over Bluetooth — the cable
   is no longer required (it still works for reconfiguring from
   `pc_app/`, in parallel).

## Activating the secret minigame

Hold all 4 keys down together for ~1.2 seconds. Controls: SW1/SW2 turn
left/right, SW3 pauses, SW4 exits. (Works the same whether or not BLE is
connected — it's entirely local.)

## Serial protocol (USB, 115200 baud, plain text `\n`)

```
PING
SET_TEXT <text>
SET_MACRO <1-4> <text or @SHORTCUT>
SET_COLOR <RRGGBB>
SET_BRIGHTNESS <0-255>
SAVE
GET_CONFIG           (now includes a BLE CONNECTED|DISCONNECTED line)
IMG_START            (then send 128*128*2 raw RGB565 bytes, no \n)
```

Preset shortcuts (`@SHORTCUT`): `@COPY @PASTE @CUT @UNDO @REDO @SAVE
@SELECTALL @ALTTAB @ENTER @ESC @TAB`. Any other text is typed out literally.

## Technical notes

- **Why BLE and not WiFi**: for a battery-powered device that only needs
  to send keystrokes, BLE uses much less power — with WiFi the 14500
  battery would last noticeably less.
- **Why the cable still works**: the ESP32-C3 has a USB-serial port built
  into the chip itself (not HID), so `Serial` still works exactly like
  before for talking to `pc_app/`.
- **Memory**: the ESP32-C3 has 320KB of RAM and 4MB of flash — much more
  than the original SAMD21. The custom screen image still isn't persisted
  (it's sent fresh each session from the app), but there's now plenty of
  flash headroom to add that later if wanted (e.g. with LittleFS) — not
  implemented yet.
