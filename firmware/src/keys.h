#pragma once
#include <Arduino.h>

void keys_init();
void keys_update();               // llamar en cada loop()
bool keys_secret_combo_triggered(); // true una vez cuando se detecta el combo secreto
void keys_run_macro(uint8_t index); // 0-3, escribe el macro por USB HID
