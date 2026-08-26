#pragma once
#include <Arduino.h>

// ======================================================================
// PINOUT — same as the wired version (SAMD21): the XIAO ESP32-C3 shares
// the footprint AND the same hardware SPI pins with the rest of the
// XIAO family, so the board wiring didn't change.
// ======================================================================
#define PIN_KEY1      0   // SW1
#define PIN_KEY2      1   // SW2
#define PIN_KEY3      2   // SW3
#define PIN_KEY4      3   // SW4

#define PIN_LED_DATA  4   // D4/SDA -> chain of 6x SK6812 (D1..D6 on the PCB)
#define NUM_LEDS      6

#define PIN_OLED_RST  5   // D5/SCL -> OLED RES
#define PIN_OLED_DC   6   // D6/TX  -> OLED DC
#define PIN_OLED_CS   9   // D9/MISO-> OLED CS
// D8 (SCK) and D10 (MOSI) are the XIAO's hardware SPI, used directly.

#define SCREEN_W 128
#define SCREEN_H 128

// ======================================================================
// Persistent config — on the ESP32-C3 this is stored in NVS (flash) via
// the Preferences library, instead of FlashStorage (that one was
// SAMD21-specific). The custom image still isn't persisted (see README):
// the ESP32-C3 has plenty of flash for that, but it was left as a
// possible future improvement instead of adding it now.
// ======================================================================
struct HackPadConfig {
  char homeText[64];
  char macro[4][40];      // literal text, or "@SHORTCUT" (see keys.cpp)
  uint8_t ledColor[3];    // a single color: the 6 LEDs share DIN in
                           // parallel (on purpose), so they always show
                           // the same color.
  uint8_t brightness;     // 0-255
};

extern HackPadConfig cfg;

void config_load_defaults();
void config_load();   // reads from NVS (or loads defaults if nothing is saved)
void config_save();   // writes to NVS
