#include "leds.h"
#include "config.h"
#include <Adafruit_NeoPixel.h>

static Adafruit_NeoPixel strip(NUM_LEDS, PIN_LED_DATA, NEO_GRB + NEO_KHZ800);
static uint16_t rainbowHue = 0;

void leds_init() {
  strip.begin();
  strip.setBrightness(80);
  strip.show();
}

void leds_apply_config() {
  strip.setBrightness(cfg.brightness);
  // Los 6 LEDs comparten el mismo DIN en paralelo (adrede), así que solo
  // tiene sentido un color "maestro": los 6 van a mostrar lo mismo sin
  // importar qué le mandemos a cada índice individual.
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(cfg.ledColor[0], cfg.ledColor[1], cfg.ledColor[2]));
  }
  strip.show();
}

void leds_set_all(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < NUM_LEDS; i++) strip.setPixelColor(i, strip.Color(r, g, b));
}

void leds_show() {
  strip.show();
}

void leds_rainbow_step() {
  for (int i = 0; i < NUM_LEDS; i++) {
    uint32_t c = strip.gamma32(strip.ColorHSV((rainbowHue + i * 9000) % 65536));
    strip.setPixelColor(i, c);
  }
  strip.show();
  rainbowHue += 400;
}
