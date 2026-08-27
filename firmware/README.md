# Firmware

## Structure

| File | For what? |
|---|---|
| `platformio.ini` | Board config (`seeed_xiao_esp32c3`) and libraries |
| `src/main.cpp` | Starts everything, updates the on-screen indicator |
| `src/config.h` / `config.cpp` | Saves text, macros, and LED color to NVS `Preferences` |
| `src/display.h` / `display.cpp` | Drives our OLED display |
| `src/leds.h` / `leds.cpp` | Drives the LEDs |
| `src/keys.h` / `keys.cpp` | Reads the 4 buttons, runs macros over, detects the secret combo of keys ;D |
| `src/game_snake.h` / `game_snake.cpp` | The secret minigame |
| `src/serial_protocol.h` / `serial_protocol.cpp` | USB (serial) protocol that talks to `pc_app/` |

## Flashing (PlatformIO + VS Code)

1. Install [VS Code](https://code.visualstudio.com/) and the **PlatformIO IDE** extension.
2. `File > Open Folder` → select the folder (`firmware/`).
3. Connect the XIAO over USB-C.
4. Click the PlatformIO icon → **Upload** (or `Ctrl+Alt+U`).
5. Open the Serial Monitor (115200 baud) and try sending `PING` — it
   should reply `OK HACKPAD v2`.

## Pairing by Bluetooth

1. With the firmware running, open the Bluetooth settings on your
   PC/phone and look for a device named **"HACK-PAD"**.
2. Pair it like any Bluetooth device.
3. Once paired the top-right corner should be green, if it doesn't try to connect again.
4. The 4 keys send their macros over Bluetooth (it still works for reconfiguring from
   `pc_app/`, in parallel).

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

