#pragma once
#include <Arduino.h>

void protocol_init();
void protocol_update();  // llamar en cada loop(), procesa comandos entrantes
