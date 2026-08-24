# firmware/

Firmware del HACK-PAD, para Seeeduino XIAO (SAMD21). Proyecto de
**PlatformIO** (no Arduino IDE clásico, aunque se puede adaptar — ver abajo).

## Estructura

| Archivo | Qué hace |
|---|---|
| `platformio.ini` | Config de placa (`seeed_xiao`) y librerías — se instalan solas |
| `src/main.cpp` | Arranca todo |
| `src/config.h` / `config.cpp` | Guarda texto, macros y color de LEDs en flash interna, sobreviven a un reinicio |
| `src/display.h` / `display.cpp` | Controla la OLED (texto e imágenes) |
| `src/leds.h` / `leds.cpp` | Controla los 6 SK6812 |
| `src/keys.h` / `keys.cpp` | Lee los 4 botones, ejecuta macros por USB HID, detecta el combo secreto |
| `src/game_snake.h` / `game_snake.cpp` | Minijuego secreto: Snake en la OLED |
| `src/serial_protocol.h` / `serial_protocol.cpp` | Protocolo USB que habla con `pc_app/` |

## Compilar y subir (PlatformIO + VS Code)

1. Instalá [VS Code](https://code.visualstudio.com/) y la extensión **PlatformIO IDE**.
2. `File > Open Folder` → elegí esta carpeta (`firmware/`).
3. Conectá el XIAO por USB. Si es la primera vez y no aparece el puerto,
   hacé doble-click rápido al botón RESET de la placa para forzar el modo
   bootloader (aparece como drive `XIAO-BOOT`).
4. Click en el ícono de PlatformIO → **Upload** (o `Ctrl+Alt+U`).
5. Abrí el Monitor Serie (115200 baud) y probá mandar `PING` — debería
   responder `OK HACKPAD v1`.

### Alternativa: Arduino IDE clásico

Agregá el URL de placas de Seeed en Preferencias:
`https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json`,
instalá "Seeed SAMD Boards" desde el Boards Manager, elegí "Seeeduino XIAO",
e instalá a mano estas librerías desde el Library Manager:

- Adafruit GFX Library
- Adafruit SSD1351 library
- Adafruit NeoPixel
- FlashStorage

Después copiá los `.h`/`.cpp` de `src/` a una carpeta con el mismo nombre
que tu `.ino`.

## Activar el minijuego secreto

Mantené las 4 teclas apretadas juntas ~1.2 segundos. Controles:
SW1/SW2 giran a izquierda/derecha, SW3 pausa, SW4 sale.

## Protocolo serial (USB CDC, 115200 baud, texto plano `\n`)

```
PING
SET_TEXT <texto>
SET_MACRO <1-4> <texto o @ATAJO>
SET_COLOR <RRGGBB>
SET_BRIGHTNESS <0-255>
SAVE
GET_CONFIG
IMG_START            (después manda 128*128*2 bytes crudos RGB565, sin \n)
```

Atajos predefinidos (`@ATAJO`): `@COPY @PASTE @CUT @UNDO @REDO @SAVE
@SELECTALL @ALTTAB @ENTER @ESC @TAB`. Cualquier otro texto se tipea literal.

## Limitaciones de memoria (SAMD21: 32KB RAM / 256KB flash)

- Texto, macros y color de LEDs **sí** persisten (comando `SAVE`).
- La imagen custom de la pantalla **no** se guarda en flash — se dibuja al
  toque (streaming directo, sin usar RAM extra) pero si el pad se queda sin
  batería hay que reenviarla desde `pc_app/`. Guardar 32KB de imagen en la
  flash interna es posible en teoría pero arriesga corromper el firmware.
