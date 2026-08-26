#pragma once
#include <Arduino.h>

void leds_init();
void leds_apply_config();                 // paints according to cfg.ledColor/brightness
void leds_set_all(uint8_t r, uint8_t g, uint8_t b);
void leds_show();
void leds_rainbow_step();                 // effect used in the minigame / idle
