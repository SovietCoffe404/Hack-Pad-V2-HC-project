# App

A Python app I've crated to configure our HACK-PAD over USB cable. ◝(ᵔᗜᵔ)◜

## Structure

| File | For what? |
|---|---|
| `hackpad_app.py` | hackpad_app.py — The main app, handles the screen, macros, LEDs and extra games |
| `serial_link.py` | serial_link.py — Handles the USB connection with the pad |
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

1. Connect the pad over USB, select the port you used for flashing, and click **Connect**.
2. **Screen**: custom text, or upload an image (auto-cropped and scaled
   to 128x128).
3. **Macros**: change what each of the 4 keys does, either with shortcuts or your own text.
4. **LEDs**: a single color (all 6 LEDs move together, by hardware design) + brightness.
5. **Extra games**: launches Snake or Memory, both run on the PC (separate
   from the secret minigame that lives inside the pad itself).

**Important**: You need to press "Save to pad" if you want the text, macros and color to stay after disconnecting the PC.
