# HACK-PAD V2

Hola! Este es un rediseño de mi anterior Hack Pad. Esta nueva version incluye mas y mejores funciones, incluso puedes encontrar un pequeño easter-egg en forma de un minijuego :D

## Qué hace

- 🖥️ **Pantalla personalizable** — texto o imagen propia, controlado desde la app de PC.
- ⌨️ **4 teclas con macros editables** — atajos (copiar/pegar/deshacer/etc.) o texto libre, se mandan por **Bluetooth LE** como si fuera un teclado real.
- 🌈 **LEDs RGB con color configurable** — los 6 SK6812 van todos del mismo color (comparten datos en paralelo, por diseño).
- 🎮 **Minijuego secreto** — Snake escondido en el propio pad, se activa manteniendo las 4 teclas apretadas (anda sin BLE conectado también).
- 🕹️ **Minijuegos extra en la PC** — Snake y Simon Says, corren en la app de escritorio.
- 🔌 **Cable USB** — solo para configurar desde la app de PC (texto, macros, colores, imagen); las macros normales van por BLE.
- 🔋 A batería (Li-ion 14500 + carga TP4056).

## Estructura del repo

```
HACK-PAD/
├── firmware/     Firmware en C++ (PlatformIO) que se sube al XIAO ESP32-C3
├── pc_app/       App de escritorio en Python para configurar el pad
└── hardware/     Proyecto de KiCad (esquemático, PCB, modelos 3D)
```

Cada carpeta tiene su propio README con el detalle — este es solo el mapa
general.

## Empezando

1. **Armar/soldar la placa** — ver `hardware/` para el esquemático, layout
   y el modelo 3D para imprimir el case. El módulo a soldar es un
   **Seeed XIAO ESP32-C3** (ver nota de compatibilidad en `hardware/README.md`).
2. **Subir el firmware** — ver `firmware/README.md` (PlatformIO + VS Code).
3. **Emparejar por Bluetooth** — buscá "HACK-PAD" en la configuración de
   Bluetooth de tu PC/teléfono (detalle en `firmware/README.md`).
4. **Instalar la app de PC** — ver `pc_app/README.md` (`pip install -r
   requirements.txt` y listo) — se conecta por el cable USB.

## Pinout (Seeed XIAO ESP32-C3)

Trazado directo del netlist del PCB original, no es un pinout genérico —
y confirmado que coincide con el del XIAO ESP32-C3 (misma familia,
mismos pines de SPI de hardware):

| Pin XIAO | Conectado a |
|---|---|
| D0–D3 | Botones SW1–SW4 |
| D4 (SDA) | Datos de los 6 LEDs SK6812 (en paralelo, todos el mismo color) |
| D5 (SCL) | RST de la OLED |
| D6 (TX) | DC de la OLED |
| D8 (SCK) | SCK de la OLED |
| D9 (MISO) | CS de la OLED |
| D10 (MOSI) | MOSI/DIN de la OLED |

## Cable vs Bluetooth — quién hace qué

| | Cable USB | Bluetooth LE |
|---|---|---|
| Configurar texto/macros/colores/imagen (`pc_app/`) | ✅ | ❌ (no implementado) |
| Mandar las macros de las 4 teclas | ❌ (el ESP32-C3 no tiene USB HID) | ✅ |
| Minijuego secreto (Snake en el pad) | funciona igual, no depende de ninguno de los dos | |

## Protocolo de comunicación (firmware ↔ app de PC, por cable)

Texto plano por USB, 115200 baud — el detalle completo de comandos está
en `firmware/README.md`. Resumen:

```
PING · SET_TEXT · SET_MACRO · SET_COLOR · SET_BRIGHTNESS · SAVE · GET_CONFIG · IMG_START
```

## Licencia

MIT — ver [`LICENSE`](LICENSE). Usá, modificá y compartí el proyecto
libremente, con o sin crédito.
