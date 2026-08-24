#pragma once
#include <Arduino.h>

// ======================================================================
// PINOUT — mismo que la versión con cable (SAMD21): el XIAO ESP32-C3
// comparte footprint Y mismos pines de SPI de hardware con el resto de
// la familia XIAO, así que el cableado de la placa no cambió.
// ======================================================================
#define PIN_KEY1      0   // SW1
#define PIN_KEY2      1   // SW2
#define PIN_KEY3      2   // SW3
#define PIN_KEY4      3   // SW4

#define PIN_LED_DATA  4   // D4/SDA -> cadena de 6x SK6812 (D1..D6 en el PCB)
#define NUM_LEDS      6

#define PIN_OLED_RST  5   // D5/SCL -> RES de la OLED
#define PIN_OLED_DC   6   // D6/TX  -> DC de la OLED
#define PIN_OLED_CS   9   // D9/MISO-> CS de la OLED
// D8 (SCK) y D10 (MOSI) son el SPI de hardware del XIAO, se usan directo.

#define SCREEN_W 128
#define SCREEN_H 128

// ======================================================================
// Configuración persistente — en el ESP32-C3 se guarda en NVS (flash)
// vía la librería Preferences, en vez de FlashStorage (esa era específica
// del SAMD21). La imagen custom sigue sin guardarse (ver README): el
// ESP32-C3 tiene flash de sobra para eso, pero se dejó para una mejora
// futura en vez de meterlo ahora.
// ======================================================================
struct HackPadConfig {
  char homeText[64];
  char macro[4][40];      // texto o "@ATAJO" (ver keys.cpp)
  uint8_t ledColor[3];    // un solo color: los 6 LEDs comparten DIN en
                           // paralelo (a propósito), así que siempre
                           // muestran el mismo color.
  uint8_t brightness;     // 0-255
};

extern HackPadConfig cfg;

void config_load_defaults();
void config_load();   // lee de NVS (o carga defaults si no hay nada guardado)
void config_save();   // escribe a NVS
