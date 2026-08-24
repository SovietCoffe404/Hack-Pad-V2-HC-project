#pragma once
#include <Arduino.h>
#include <BleKeyboard.h>

extern BleKeyboard bleKeyboard;

void keys_init();
void keys_update();                 // llamar en cada loop()
bool keys_secret_combo_triggered();  // true una vez cuando se detecta el combo secreto
void keys_run_macro(uint8_t index);  // 0-3, manda el macro por BLE HID
