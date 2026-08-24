# HACK-PAD V2

Macropad de 4 teclas mecánicas con pantalla OLED a color, LEDs RGB y
minijuego secreto, basado en un Seeeduino XIAO (SAMD21). Diseño de PCB
propio (KiCad) + firmware + app de PC para configurarlo.

## Qué hace

- 🖥️ **Pantalla personalizable** — texto o imagen propia, controlado desde la app de PC.
- ⌨️ **4 teclas con macros editables** — atajos (copiar/pegar/deshacer/etc.) o texto libre, se manda por USB como teclado real.
- 🌈 **LEDs RGB con color configurable** — los 6 SK6812 van todos del mismo color (comparten datos en paralelo, por diseño).
- 🎮 **Minijuego secreto** — Snake escondido en el propio pad, se activa manteniendo las 4 teclas apretadas.
- 🕹️ **Minijuegos extra en la PC** — Snake y Simon Says, corren en la app de escritorio.
- 🔋 A batería (Li-ion 14500 + carga TP4056).

## Estructura del repo

```
HACK-PAD/
├── firmware/     Firmware en C++ (PlatformIO) que se sube al XIAO
├── pc_app/       App de escritorio en Python para configurar el pad
└── hardware/     Proyecto de KiCad (esquemático, PCB, modelos 3D)
```

Cada carpeta tiene su propio README con el detalle — este es solo el mapa
general.

## Empezando

1. **Armar/soldar la placa** — ver `hardware/` para el esquemático, layout
   y el modelo 3D para imprimir el case.
2. **Subir el firmware** — ver `firmware/README.md` (PlatformIO + VS Code).
3. **Instalar la app de PC** — ver `pc_app/README.md` (`pip install -r
   requirements.txt` y listo).

## Pinout (Seeeduino XIAO)

Trazado directo del netlist del PCB, no es un pinout genérico:

| Pin XIAO | Conectado a |
|---|---|
| D0–D3 | Botones SW1–SW4 |
| D4 (SDA) | Datos de los 6 LEDs SK6812 (en paralelo, todos el mismo color) |
| D5 (SCL) | RST de la OLED |
| D6 (TX) | DC de la OLED |
| D8 (SCK) | SCK de la OLED |
| D9 (MISO) | CS de la OLED |
| D10 (MOSI) | MOSI/DIN de la OLED |

## Protocolo de comunicación (firmware ↔ app de PC)

Texto plano por USB CDC, 115200 baud — el detalle completo de comandos
está en `firmware/README.md`. Resumen:

```
PING · SET_TEXT · SET_MACRO · SET_COLOR · SET_BRIGHTNESS · SAVE · GET_CONFIG · IMG_START
```

## Licencia

MIT — ver [`LICENSE`](LICENSE). Usá, modificá y compartí el proyecto
libremente, con o sin crédito.
