# HACK-PAD V2

Hola! Este es un rediseño de mi anterior Hack Pad. Esta nueva version incluye mas y mejores funciones, incluso puedes encontrar un pequeño easter-egg en forma de un minijuego :D

## Qué hace

- 🖥️ **Pantalla personalizable** — texto o imagen propia, controlado desde la app de PC.
- ⌨️ **4 teclas con macros editables** — atajos (copiar/pegar/deshacer/etc.) o texto libre, se mandan por **Bluetooth LE** como si fuera un teclado real.
- 🌈 **LEDs RGB con color configurable** — los 6 SK6812 van todos del mismo color (comparten datos en paralelo, por diseño).
- 🎮 **Minijuego secreto** — Snake escondido en el propio pad, se activa manteniendo las 4 teclas apretadas (anda sin BLE conectado también).
- 🕹️ **Minijuegos extra en la PC** — Snake y Simon Says, corren en la app de escritorio.
- 🔌 **Cable USB** — solo para configurar desde la app de PC (texto, macros, colores, imagen); las macros normales van por BLE.
- 🔋 **Bateria intercambiable** (Li-ion 14500 + carga TP4056).

## Estructura del repo

```
HACK-PAD/
├── firmware/     Firmware en C++ (PlatformIO) que se sube al XIAO ESP32-C3
├── pc_app/       App de escritorio en Python para configurar el pad
└── hardware/     Proyecto de KiCad (esquemático, PCB, modelos 3D)
```

Cada carpeta tiene su propio README con el detalle — este es solo el mapa
general.

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

## Protocolo de comunicación (firmware ↔ app de PC, por cable)

Texto plano por USB, 115200 baud — el detalle completo de comandos está
en `firmware/README.md`. Resumen:

```
PING · SET_TEXT · SET_MACRO · SET_COLOR · SET_BRIGHTNESS · SAVE · GET_CONFIG · IMG_START
```
## Screen Shots del proyecto 

<img width="392" height="266" alt="Screenshot 2026-08-23 134833" src="https://github.com/user-attachments/assets/fdafd54b-7331-4a69-8acb-91fbe255be91" />

<img width="623" height="305" alt="Screenshot 2026-08-07 132914" src="https://github.com/user-attachments/assets/3f805d54-b381-4061-98b6-7c45c9c34c3c" />

<img width="269" height="350" alt="Screenshot 2026-08-25 124445" src="https://github.com/user-attachments/assets/02c9b169-3304-421c-acd9-4ff05f4cdaec" />

## BOM

|HACK-PAD V2 � Bill of Materials (BOM)                                   |FIELD2                                  |FIELD3                                                                                                                                                        |FIELD4|FIELD5                      |FIELD6        |FIELD7                              |FIELD8                                                                            |
|------------------------------------------------------------------------|----------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------|------|----------------------------|--------------|------------------------------------|----------------------------------------------------------------------------------|
|                                                                        |                                        |                                                                                                                                                              |      |                            |              |                                    |                                                                                  |
|Ref.                                                                    |Componente                              |Descripci�n / Especificaci�n                                                                                                                                  |Cant. |Precio unit. est. (USD)     |Subtotal (USD)|Proveedor sugerido                  |Enlace                                                                            |
|Electr�nica principal                                                   |                                        |                                                                                                                                                              |      |                            |              |                                    |                                                                                  |
|U1                                                                      |Seeed XIAO ESP32-C3                     |MCU BLE, footprint XIAO 14 pads castellados 21x17.5mm. Reemplaza al XIAO SAMD21 original del esquem�tico (mismo footprint).                                   |1     |$5.50                       |$5.50         |AliExpress (Seeedstudio Store)      |https://www.aliexpress.com/item/1005004723068527.html                             |
|U2                                                                      |OLED 1.5" 128x128 SPI, SSD1351          |Waveshare OLED 1.5inch Module B, 7 pines 2.54mm, color RGB, controlador SSD1351.                                                                              |1     |$13.00                      |$13.00        |AliExpress                          |https://www.aliexpress.com/item/4000136106619.html                                |
|D7-D12                                                                  |LED SK6812 (5050 PLCC4 SMD)             |LED RGB direccionable, footprint SMD 5.0x5.0mm. 6 unidades, todas comparten el mismo DIN (van en paralelo, mismo color).                                      |6     |$0.18                       |$1.08         |AliExpress (comprar por 10-20u)     |https://www.aliexpress.com/item/32623583544.html                                  |
|SW1-SW4                                                                 |Switch mec�nico tipo Cherry MX (1u, THT)|Footprint SW_Cherry_MX_1.00u_PCB � cualquier switch mec�nico compatible Cherry MX (lineal/t�ctil/clicky, a gusto).                                            |4     |$0.45                       |$1.80         |AliExpress                          |https://es.aliexpress.com/item/1005005751466152.html                              |
|Alimentaci�n / bater�a                                                  |                                        |                                                                                                                                                              |      |                            |              |                                    |                                                                                  |
|BAT1                                                                    |Bater�a Li-ion 14500 3.7V               |Formato AA (14.5x50mm), recomendable con protecci�n integrada (PCB) y ~800-1000mAh.                                                                           |1     |$4.50                       |$4.50         |AliExpress                          |https://es.aliexpress.com/w/wholesale-14500-li-ion-rechargeable-battery-3.7-v.html|
|U4                                                                      |M�dulo cargador TP4056 con protecci�n   |Carga Li-ion v�a Micro-USB/USB-C, incluye protecci�n de sobrecarga/sobredescarga (DW01A + FET).                                                               |1     |$0.80                       |$0.80         |AliExpress                          |https://www.aliexpress.com/item/32467578996.html                                  |
|Componentes pasivos (SMD 1206)                                          |                                        |                                                                                                                                                              |      |                            |              |                                    |                                                                                  |
|R1                                                                      |Resistor 330?, SMD 1206                 |Ver esquem�tico � l�nea de datos de los SK6812 (limitador de corriente).                                                                                      |1     |$0.02                       |$0.02         |AliExpress (kit de resistores 1206) |https://www.aliexpress.com/w/wholesale-resistor-kit-1206.html                     |
|C1                                                                      |Capacitor, SMD 1206                     |El esquem�tico indica 500uF � valor inusualmente alto para un 1206 cer�mico; revisar en KiCad si corresponde a un electrol�tico/tantalio THT antes de comprar.|1     |$0.05                       |$0.05         |AliExpress (kit de capacitores 1206)|https://www.aliexpress.com/w/wholesale-capacitor-kit-1206.html                    |
|Estructura y consumibles (no est�n en el esquem�tico, pero se necesitan)|                                        |                                                                                                                                                              |      |                            |              |                                    |                                                                                  |
|�                                                                       |PCB fabricada (HACK-PAD_V2.kicad_pcb)   |2 capas, gerbers exportados desde KiCad. Pedir 5-10 unidades (precio no baja mucho por menos).                                                                |1     |$5.00                       |$5.00         |JLCPCB / PCBWay (no AliExpress)     |https://jlcpcb.com/                                                               |
|�                                                                       |Case impreso en 3D                      |Usar 3D_HACK-PAD_Printing.step. PLA o PETG, ~30-50g de filamento.                                                                                             |1     |$1.50                       |$1.50         |Impresi�n propia / servicio local   |                                                                                  |
|�                                                                       |Cable USB-C                             |Para programar y usar la app de PC (protocolo serial).                                                                                                        |1     |$2.00                       |$2.00         |AliExpress                          |https://www.aliexpress.com/w/wholesale-usb-c-cable.html                           |
|�                                                                       |Tornillos M2 (kit)                      |Para cerrar el case impreso, seg�n dise�o final del enclosure.                                                                                                |1     |$1.50                       |$1.50         |AliExpress                          |https://www.aliexpress.com/w/wholesale-m2-screw-kit.html                          |
|�                                                                       |Keycaps gen�ricas (opcional)            |4 keycaps compatibles Cherry MX, perfil bajo o OEM seg�n el case.                                                                                             |4     |$0.30                       |$1.20         |AliExpress                          |https://www.aliexpress.com/w/wholesale-keycaps-cherry-mx.html                     |
|                                                                        |                                        |                                                                                                                                                              |      |                            |              |                                    |                                                                                  |
|                                                                        |                                        |                                                                                                                                                              |      |TOTAL (sin env�o/PCB extra):|$37.95        |                                    |                                                                                  |
|                                                                        |                                        |                                                                                                                                                              |      |                            |              |                                    |                                                                                  |
|                                                                        |                                        |                                                                                                                                                              |      |                            |              |                                    |                                                                                  |
|                                                                        |                                        |                                                                                                                                                              |      |                            |              |                                    |                                                                                  |
|                                                                        |                                        |                                                                                                                                                              |      |                            |              |                                    |                                                                                  |
|                                                                        |                                        |                                                                                                                                                              |      |                            |              |                                    |                                                                                  |
|                                                                        |                                        |                                                                                                                                                              |      |                            |              |                                    |                                                                                  |
|                                                                        |                                        |                                                                                                                                                              |      |                            |              |                                    |                                                                                  |
|                                                                        |                                        |                                                                                                                                                              |      |                            |              |                                    |                                                                                  |
|                                                                        |                                        |                                                                                                                                                              |      |                            |              |                                    |                                                                                  |

## Licencia

MIT — ver [`LICENSE`](LICENSE). Usa, modifica y comparte el proyecto
libremente, con o sin crédito.
