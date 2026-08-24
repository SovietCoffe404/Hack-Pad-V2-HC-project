# hardware/

Proyecto de KiCad 8 del HACK-PAD V2 (macropad de 4 teclas + pantalla OLED +
LEDs RGB, basado en un Seeeduino XIAO).

| Archivo | Qué es |
|---|---|
| `HACK-PAD_V2.kicad_pro` | Proyecto — abrir este desde KiCad |
| `HACK-PAD_V2.kicad_sch` | Esquemático |
| `HACK-PAD_V2.kicad_pcb` | Layout de la placa |
| `HACK-PAD_V2.kicad_prl` | Preferencias locales del proyecto (no crítico) |
| `fp-lib-table` | Tabla de librerías de footprints usadas |
| `3D_HACK-PAD_Assembled.step` | Modelo 3D con todos los componentes montados — para visualizar/renderizar el pad completo |
| `3D_HACK-PAD_Printing.step` | Modelo 3D simplificado (sin componentes electrónicos) — para imprimir el case/enclosure en una impresora 3D o mandar a cortar |

## Pinout (Seeeduino XIAO)

Esto es lo que usa el firmware — si modificás el layout y cambiás algún pin,
hay que actualizar `firmware/src/config.h` a mano.

| Pin XIAO | Conectado a |
|---|---|
| D0–D3 | Botones SW1–SW4 (a GND, con pull-up interno) |
| D4 (SDA) | Datos de los 6 LEDs SK6812 — **los 6 comparten el mismo DIN en paralelo a propósito**, por eso siempre muestran el mismo color; no son direccionables individualmente |
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
