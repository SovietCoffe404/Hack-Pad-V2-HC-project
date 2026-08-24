#pragma once
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>

void display_init();
void display_show_home();                 // pantalla principal (texto custom)
void display_set_ble_status(bool connected); // punto indicador arriba a la derecha
void display_show_image_rgb565(const uint16_t *pixels); // 128x128 desde la app de PC
void display_show_text(const char *msg, uint16_t color);
Adafruit_SSD1351 &display_raw();           // acceso directo para el minijuego
