#pragma once
#include <Arduino.h>
#include <BleKeyboard.h>

extern BleKeyboard bleKeyboard;

void keys_init();
void keys_update();                 // call every loop()
bool keys_secret_combo_triggered();  // true once when the secret combo is detected
void keys_run_macro(uint8_t index);  // 0-3, sends the macro over BLE HID
