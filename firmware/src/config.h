#pragma once
#include <Arduino.h>

// ======================================================================
// PINOUT — obtenido rastreando el netlist real de HACK-PAD_V2.kicad_pcb
// (no es un pinout genérico, es el de tu PCB específico).
// Si algo no prende/lee bien, revisa primero esto contra tu placa.
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
// Configuración persistente (se guarda en flash interna con FlashStorage)
// La mantenemos chica a propósito: la flash interna del SAMD21 no tiene
// mucho espacio libre y no queremos arriesgar corromper el firmware.
// La imagen custom NO se guarda aquí (ver README) — se re-envía desde
// la app de PC cada sesión.
// ======================================================================
#define CONFIG_MAGIC 0xA5C7

struct HackPadConfig {
  uint16_t magic;
  char homeText[64];
  char macro[4][40];      // texto o "@ATAJO" (ver keys.cpp)
  uint8_t ledColor[3];    // un solo color: los 6 LEDs comparten DIN en
                           // paralelo (a propósito), así que siempre
                           // muestran el mismo color, no son direccionables
                           // individualmente.
  uint8_t brightness;     // 0-255
};

extern HackPadConfig cfg;

void config_load_defaults();
void config_load();   // lee de flash (o carga defaults si no hay nada válido)
void config_save();   // escribe a flash
