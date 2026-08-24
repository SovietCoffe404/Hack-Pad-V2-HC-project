# firmware/

Firmware del HACK-PAD, para **Seeed XIAO ESP32-C3** — inalámbrico por
Bluetooth LE. Proyecto de **PlatformIO**.

> Este proyecto usaba antes un XIAO SAMD21 con cable USB. La versión
> inalámbrica cambia el módulo por un XIAO ESP32-C3 (mismo footprint, no
> hace falta rediseñar la placa) y el teclado ahora manda las teclas por
> Bluetooth LE en vez de por USB HID — el ESP32-C3 no tiene controlador
> USB para HID, solo un puerto serie por USB, que se sigue usando para
> configurar el pad desde `pc_app/`.

## Estructura

| Archivo | Qué hace |
|---|---|
| `platformio.ini` | Config de placa (`seeed_xiao_esp32c3`) y librerías — se instalan solas |
| `src/main.cpp` | Arranca todo, actualiza el indicador de BLE en pantalla |
| `src/config.h` / `config.cpp` | Guarda texto, macros y color de LEDs en NVS (flash), vía `Preferences` |
| `src/display.h` / `display.cpp` | Controla la OLED (texto, imágenes, punto de estado BLE) |
| `src/leds.h` / `leds.cpp` | Controla los 6 SK6812 |
| `src/keys.h` / `keys.cpp` | Lee los 4 botones, ejecuta macros por **BLE HID** (`BleKeyboard`), detecta el combo secreto |
| `src/game_snake.h` / `game_snake.cpp` | Minijuego secreto: Snake en la OLED |
| `src/serial_protocol.h` / `serial_protocol.cpp` | Protocolo por USB (serie) que habla con `pc_app/` |

## Compilar y subir (PlatformIO + VS Code)

1. Instalá [VS Code](https://code.visualstudio.com/) y la extensión **PlatformIO IDE**.
2. `File > Open Folder` → elegí esta carpeta (`firmware/`).
3. Conectá el XIAO ESP32-C3 por USB-C.
4. Click en el ícono de PlatformIO → **Upload** (o `Ctrl+Alt+U`). Si no
   entra solo en modo bootloader, mantené apretado el botón BOOT, tocá
   RESET, y soltá BOOT (típico de placas ESP32).
5. Abrí el Monitor Serie (115200 baud) y probá mandar `PING` — debería
   responder `OK HACKPAD v1`.

## Emparejar por Bluetooth

1. Con el firmware corriendo, andá a la configuración de Bluetooth de tu
   PC/teléfono y buscá un dispositivo llamado **"HACK-PAD"**.
2. Emparejalo como cualquier teclado Bluetooth (sin PIN, normalmente).
3. El puntito arriba a la derecha de la pantalla se pone **verde** cuando
   hay conexión BLE activa, y gris cuando no.
4. Una vez emparejado, las 4 teclas mandan sus macros por Bluetooth — ya
   no hace falta el cable (el cable sigue sirviendo para reconfigurar
   desde `pc_app/`, en paralelo).

## Activar el minijuego secreto

Mantené las 4 teclas apretadas juntas ~1.2 segundos. Controles:
SW1/SW2 giran a izquierda/derecha, SW3 pausa, SW4 sale.
(El minijuego funciona igual con o sin BLE conectado, es 100% local.)

## Protocolo serial (USB, 115200 baud, texto plano `\n`)

```
PING
SET_TEXT <texto>
SET_MACRO <1-4> <texto o @ATAJO>
SET_COLOR <RRGGBB>
SET_BRIGHTNESS <0-255>
SAVE
GET_CONFIG           (ahora incluye una línea BLE CONNECTED|DISCONNECTED)
IMG_START            (después manda 128*128*2 bytes crudos RGB565, sin \n)
```

Atajos predefinidos (`@ATAJO`): `@COPY @PASTE @CUT @UNDO @REDO @SAVE
@SELECTALL @ALTTAB @ENTER @ESC @TAB`. Cualquier otro texto se tipea literal.

## Notas técnicas

- **Por qué BLE y no WiFi**: para un dispositivo a batería que solo
  necesita mandar teclas, BLE consume mucho menos — con WiFi la batería
  14500 duraría bastante menos.
- **Por qué sigue andando el cable**: el ESP32-C3 tiene un puerto
  serie-por-USB integrado en el chip (no es HID), así que `Serial` sigue
  funcionando exactamente igual que antes para hablar con `pc_app/`.
- **Memoria**: el ESP32-C3 tiene 320KB de RAM y 4MB de flash — mucho más
  que el SAMD21 original. La imagen custom de la pantalla sigue sin
  guardarse de forma persistente (se manda cada sesión desde la app), pero
  ahora hay flash de sobra como para agregar eso más adelante si se
  quiere (por ejemplo con LittleFS) — no se implementó todavía.
