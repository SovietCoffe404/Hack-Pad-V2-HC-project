#pragma once
#include <Arduino.h>

void protocol_init();
void protocol_update();  // call every loop(), processes incoming commands
