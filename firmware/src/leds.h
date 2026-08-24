#pragma once
#include <Arduino.h>

void leds_init();
void leds_apply_config();                 // pinta según cfg.ledColor/brightness
void leds_set_all(uint8_t r, uint8_t g, uint8_t b);
void leds_show();
void leds_rainbow_step();                 // efecto usado en el minijuego / idle
