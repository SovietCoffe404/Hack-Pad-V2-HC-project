#include <Arduino.h>
#include "config.h"
#include "display.h"
#include "leds.h"
#include "keys.h"
#include "serial_protocol.h"
#include "game_snake.h"

static bool lastBleConnected = false;
static uint32_t lastBleCheck = 0;

void setup() {
  Serial.begin(115200);

  config_load();
  display_init();
  leds_init();
  keys_init();        // also starts the BLE keyboard (bleKeyboard.begin())
  protocol_init();

  leds_apply_config();
  display_show_home();
}

void loop() {
  keys_update();
  protocol_update();

  // Updates the BLE status dot on screen every half second, without
  // repainting the whole home screen constantly.
  uint32_t now = millis();
  if (now - lastBleCheck > 500) {
    lastBleCheck = now;
    bool connected = bleKeyboard.isConnected();
    if (connected != lastBleConnected) {
      lastBleConnected = connected;
      display_set_ble_status(connected);
      display_show_home();
    }
  }

  if (keys_secret_combo_triggered()) {
    snake_run(); // blocking until the player exits with SW4
  }
}
