# pc_app

Desktop app in Python to configure the HACK-PAD over USB.

## Structure

| File | For what? |
|---|---|
| `hackpad_app.py` | Main app — Screen / Macros / LEDs / Extra games |
| `serial_link.py` | USB communication with the pad (protocol from `firmware/`) |
| `image_convert.py` | Converts any image to 128x128 RGB565 |
| `games/snake_game.py` | Extra Snake, played with the PC keyboard |
| `games/memory_game.py` | Themed Simon Says, played with the mouse |
| `requirements.txt` | Dependencies |

## Usage

```bash
cd pc_app
pip install -r requirements.txt
python hackpad_app.py
```

1. Connect the pad over USB, pick the port in the app (it's the same one
   you used to flash the firmware) and click **Connect**.
2. **Screen**: custom text, or upload an image (auto-cropped and scaled
   to 128x128).
3. **Macros**: what each of the 4 keys does — preset shortcuts or free text.
4. **LEDs**: a single color (all 6 LEDs move together, by hardware design)
   + brightness.
5. **Extra games**: launches Snake or Memory, both run on the PC (separate
   from the secret minigame that lives inside the pad itself).

**Important**: "Save to pad" is what makes text/macros/color survive
without the PC connected. Without that step they're lost on disconnect
(the image is never saved on the pad, see `firmware/README.md`).
