# hardware/

Proyecto de KiCad 8 del HACK-PAD V2 (macropad de 4 teclas + pantalla OLED +
LEDs RGB).

| Archivo | Qué es |
|---|---|
| `HACK-PAD_V2.kicad_pro` | Proyecto — abrir este desde KiCad |
| `HACK-PAD_V2.kicad_sch` | Esquemático |
| `HACK-PAD_V2.kicad_pcb` | Layout de la placa |
| `HACK-PAD_V2.kicad_prl` | Preferencias locales del proyecto (no crítico) |
| `fp-lib-table` | Tabla de librerías de footprints usadas |
| `3D_HACK-PAD_Assembled.step` | Modelo 3D con todos los componentes montados — para visualizar/renderizar el pad completo |
| `3D_HACK-PAD_Printing.step` | Modelo 3D simplificado (sin componentes electrónicos) — para imprimir el case/enclosure |

## Módulo XIAO: SAMD21 (placa) → ESP32-C3 (firmware actual)

El esquemático/PCB fueron diseñados originalmente con el footprint del
**Seeed XIAO SAMD21**. El firmware actual (`firmware/`) apunta al **Seeed
XIAO ESP32-C3** para tener Bluetooth.

**No hace falta rediseñar la placa**: toda la familia XIAO (SAMD21,
ESP32-C3, ESP32-S3, nRF52840, RP2040...) comparte el mismo footprint de
14 pads castellados de 21×17.5mm, y confirmado que los pines de SPI de
hardware caen en los mismos lugares (D8=SCK, D9=MISO, D10=MOSI) en el
SAMD21 y en el ESP32-C3 — el módulo se puede reemplazar en la placa física
sin tocar el cableado.

Lo único que queda "desprolijo" es cosmético: el símbolo en el
esquemático todavía dice `MOUDLE-SEEEDUINO-XIAO` (el valor original). Si
querés que el BOM/esquemático reflejen el chip real, en KiCad:
`Edit > Change Symbols...` y actualizá el `Value` a algo como
`XIAO-ESP32C3`. No es necesario para que la placa funcione, es solo
prolijidad del proyecto.

## Pinout (aplica a cualquier módulo XIAO que uses)

| Pin XIAO | Conectado a |
|---|---|
| D0–D3 | Botones SW1–SW4 (a GND, con pull-up interno) |
| D4 (SDA) | Datos de los 6 LEDs SK6812 — **los 6 comparten el mismo DIN en paralelo a propósito**, por eso siempre muestran el mismo color |
| D5 (SCL) | RST de la OLED |
| D6 (TX) | DC de la OLED |
| D8 (SCK) | SCK de la OLED (SPI de hardware) |
| D9 (MISO) | CS de la OLED |
| D10 (MOSI) | MOSI/DIN de la OLED (SPI de hardware) |

## Notas

- La pantalla es una OLED Waveshare 1.5" 128x128 RGB (controlador SSD1351).
- Alimentación: batería Li-ion 14500 + módulo de carga/protección TP4056.
- La carpeta `*-backups/` que genera KiCad automáticamente al guardar está
  excluida del repo (ver `.gitignore` en la raíz) — no hace falta versionarla.
