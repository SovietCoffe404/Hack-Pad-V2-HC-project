#include <Arduino.h>
#include "config.h"
#include "display.h"
#include "leds.h"
#include "keys.h"
#include "serial_protocol.h"
#include "game_snake.h"

void setup() {
  Serial.begin(115200);

  config_load();
  display_init();
  leds_init();
  keys_init();
  protocol_init();

  leds_apply_config();
  display_show_home();
}

void loop() {
  keys_update();
  protocol_update();

  if (keys_secret_combo_triggered()) {
    snake_run(); // bloqueante hasta que el jugador sale con SW4
  }
}
