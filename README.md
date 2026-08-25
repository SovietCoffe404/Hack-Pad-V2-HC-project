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

# HACK-PAD V2 — Bill of Materials (BOM)

## Electrónica principal

| Ref.    | Componente                               | Descripción / Especificación                                                                                                 | Cant. | Precio unit. est. (USD) | Subtotal (USD) | Proveedor sugerido | Enlace                                                              |
| ------- | ---------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------- | ----: | ----------------------: | -------------: | ------------------ | ------------------------------------------------------------------- |
| U1      | Seeed XIAO ESP32-C3                      | MCU BLE, footprint XIAO 14 pads castellados 21×17.5 mm. . |     1 |                   ~$3–5 |          ~$3–5 | AliExpress | [AliExpress](https://www.aliexpress.com/item/1005004723068527.html) |
| U2      | OLED 1.5" 128×128 SPI, SSD1351           | Waveshare OLED 1.5inch Module B, 7 pines 2.54 mm, color RGB, controlador SSD1351.                                            |     1 |                 ~$12–16 |        ~$12–16 | AliExpress         | [AliExpress](https://www.aliexpress.com/item/4000136106619.html)    |
| D7-D12  | LED SK6812 (5050 PLCC4 SMD)              | LED RGB direccionable, footprint SMD 5.0×5.0 mm. 6 unidades, todas comparten el mismo DIN (van en paralelo, mismo color).    |     6 |             ~$0.05–0.15 |    ~$0.30–0.90 | AliExpress         | [AliExpress](https://www.aliexpress.com/item/32623583544.html)      |
| SW1-SW4 | Switch mecánico tipo Cherry MX (1u, THT) | Footprint `SW_Cherry_MX_1.00u_PCB` — cualquier switch mecánico compatible Cherry MX (lineal/táctil/clicky, a gusto).         |     4 |             ~$0.20–0.50 |    ~$0.80–2.00 | AliExpress         | [AliExpress](https://es.aliexpress.com/item/1005005751466152.html)  |

## Alimentación / batería

| Ref. | Componente                            | Descripción / Especificación                                                          | Cant. | Precio unit. est. (USD) | Subtotal (USD) | Proveedor sugerido | Enlace                                                                                                   |
| ---- | ------------------------------------- | ------------------------------------------------------------------------------------- | ----: | ----------------------: | -------------: | ------------------ | -------------------------------------------------------------------------------------------------------- |
| BAT1 | Batería Li-ion 14500 3.7V             | Formato AA (14.5×50 mm), recomendable con protección integrada (PCB) y ~800-1000 mAh. |     1 |                   ~$2–4 |          ~$2–4 | AliExpress         | [AliExpress](https://www.aliexpress.com/wholesale?SearchText=14500+3.7V+800mAh+protected+Li-ion+battery) |
| U4   | Módulo cargador TP4056 con protección | Carga Li-ion vía USB-C, incluye protección de sobrecarga/sobredescarga (DW01A + FET). |     1 |             ~$0.30–1.00 |    ~$0.30–1.00 | AliExpress         | [AliExpress](https://www.aliexpress.com/wholesale?SearchText=TP4056+USB+C+protection+module)             |

## Componentes pasivos (SMD 1206)

| Ref. | Componente               | Descripción / Especificación                                                                                                                                | Cant. | Precio unit. est. (USD) | Subtotal (USD) | Proveedor sugerido | Enlace                                                                               |
| ---- | ------------------------ | ----------------------------------------------------------------------------------------------------------------------------------------------------------- | ----: | ----------------------: | -------------: | ------------------ | ------------------------------------------------------------------------------------ |
| R1   | Resistor 330 Ω, SMD 1206 | Ver esquemático — línea de datos de los SK6812 (limitador de corriente).                                                                                    |     1 |             ~$0.01–0.03 |    ~$0.01–0.03 | AliExpress         | [AliExpress](https://www.aliexpress.com/wholesale?SearchText=330R+1206+SMD+resistor) |
| C1   | Capacitor, SMD 1206      | El esquemático indica 500 µF — valor inusualmente alto para un 1206 cerámico; revisar en KiCad si corresponde a un electrolítico/tantalio antes de comprar. |     1 |                       — |              — | AliExpress         | [AliExpress](https://www.aliexpress.com/wholesale?SearchText=500uF+SMD+capacitor)    |

## Estructura y consumibles

| Ref. | Componente                              | Descripción / Especificación                                         |  Cant. | Precio unit. est. (USD) | Subtotal (USD) | Proveedor sugerido | Enlace                                                                                 |
| ---- | --------------------------------------- | -------------------------------------------------------------------- | -----: | ----------------------: | -------------: | ------------------ | -------------------------------------------------------------------------------------- |
| —    | PCB fabricada (`HACK-PAD_V2.kicad_pcb`) | 2 capas, Gerbers exportados desde KiCad. Pedir 5-10 unidades.        | 1 lote |                  ~$2–10 |         ~$2–10 | JLCPCB             | [JLCPCB](https://jlcpcb.com/)                                                          |
| —    | Case impreso en 3D                      | Usar `3D_HACK-PAD_Printing.step`. PLA o PETG, ~30-50 g de filamento. |      1 |                  ~$1.50 |         ~$1.50 | Impresión propia   | —                                                                                      |
| —    | Cable USB-C                             | Para programar y usar la app de PC (protocolo serial).               |      1 |             ~$0.80–2.00 |    ~$0.80–2.00 | AliExpress         | [AliExpress](https://www.aliexpress.com/wholesale?SearchText=USB+C+data+cable)         |
| —    | Tornillos M2 (kit)                      | Para cerrar el case impreso, según diseño final del enclosure.       |  1 kit |                   ~$1–3 |          ~$1–3 | AliExpress         | [AliExpress](https://www.aliexpress.com/wholesale?SearchText=M2+screw+kit+electronics) |
| —    | Keycaps genéricas (opcional)            | 4 keycaps compatibles Cherry MX, perfil bajo u OEM según el case.    |      4 |             ~$0.20–0.50 |    ~$0.80–2.00 | AliExpress         | [AliExpress](https://www.aliexpress.com/wholesale?SearchText=Cherry+MX+keycaps)        |

---

## 💰 Total

**TOTAL aproximado de componentes: ~$23–48 USD**

## Licencia

MIT — ver [`LICENSE`](LICENSE). Usa, modifica y comparte el proyecto
libremente, con o sin crédito.
