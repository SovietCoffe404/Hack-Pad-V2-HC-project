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
  keys_init();        // también arranca el BLE keyboard (bleKeyboard.begin())
  protocol_init();

  leds_apply_config();
  display_show_home();
}

void loop() {
  keys_update();
  protocol_update();

  // Actualiza el puntito de estado BLE en la pantalla cada medio segundo,
  // sin repintar todo el home screen a cada rato.
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
    snake_run(); // bloqueante hasta que el jugador sale con SW4
  }
}
