#include "serial_protocol.h"
#include "config.h"
#include "leds.h"
#include "display.h"
#include "keys.h"

// ============================================================================
// Protocolo por Serial (USB CDC), texto plano terminado en '\n':
//
//   PING                          -> "OK HACKPAD v1"
//   SET_TEXT <texto>              -> cambia el texto de la pantalla principal
//   SET_MACRO <1-4> <texto|@ATAJO>-> asigna macro a una tecla
//   SET_COLOR <RRGGBB>            -> color de los 6 LEDs (comparten DIN en
//                                    paralelo a propósito, así que siempre
//                                    van todos iguales; hex sin '#')
//   SET_BRIGHTNESS <0-255>
//   SAVE                          -> persiste todo a NVS (flash)
//   GET_CONFIG                    -> vuelca la config actual (incluye estado BLE)
//   IMG_START                     -> el firmware espera EXACTAMENTE 128*128*2
//                                    bytes crudos RGB565 (big-endian) a
//                                    continuación, sin saltos de línea.
//                                    La imagen se dibuja directo (streaming,
//                                    no se guarda en flash — ver README).
// ============================================================================

static char lineBuf[96];
static uint8_t lineLen = 0;

static void trimTrailing(char *s) {
  size_t l = strlen(s);
  while (l && (s[l - 1] == '\r' || s[l - 1] == ' ')) s[--l] = 0;
}

static uint8_t hexNibble(char c) {
  if (c >= '0' && c <= '9') return c - '0';
  if (c >= 'A' && c <= 'F') return c - 'A' + 10;
  if (c >= 'a' && c <= 'f') return c - 'a' + 10;
  return 0;
}

static void parseHexColor(const char *hex, uint8_t *r, uint8_t *g, uint8_t *b) {
  *r = (hexNibble(hex[0]) << 4) | hexNibble(hex[1]);
  *g = (hexNibble(hex[2]) << 4) | hexNibble(hex[3]);
  *b = (hexNibble(hex[4]) << 4) | hexNibble(hex[5]);
}

static void sendConfigDump() {
  Serial.print("TEXT "); Serial.println(cfg.homeText);
  for (int i = 0; i < 4; i++) {
    Serial.print("MACRO "); Serial.print(i + 1); Serial.print(" "); Serial.println(cfg.macro[i]);
  }
  {
    char buf[8];
    snprintf(buf, sizeof(buf), "%02X%02X%02X", cfg.ledColor[0], cfg.ledColor[1], cfg.ledColor[2]);
    Serial.print("COLOR "); Serial.println(buf);
  }
  Serial.print("BRIGHTNESS "); Serial.println(cfg.brightness);
  Serial.print("BLE "); Serial.println(bleKeyboard.isConnected() ? "CONNECTED" : "DISCONNECTED");
  Serial.println("OK");
}

// Recibe 128*128 px RGB565 (big-endian) y los pinta directo en la pantalla,
// SIN guardarlos en un buffer completo: el SAMD21 solo tiene 32KB de RAM
// y guardar los 32KB de la imagen se comería toda la memoria.
static void handleImageTransfer() {
  const uint32_t totalBytes = (uint32_t)SCREEN_W * SCREEN_H * 2;
  Adafruit_SSD1351 &t = display_raw();

  t.startWrite();
  t.setAddrWindow(0, 0, SCREEN_W, SCREEN_H);

  uint32_t received = 0;
  uint32_t lastByteAt = millis();
  bool haveHighByte = false;
  uint8_t highByte = 0;

  while (received < totalBytes) {
    if (Serial.available()) {
      uint8_t b = (uint8_t)Serial.read();
      lastByteAt = millis();
      if (!haveHighByte) {
        highByte = b;
        haveHighByte = true;
      } else {
        uint16_t color = ((uint16_t)highByte << 8) | b;
        t.writePixel(color);
        haveHighByte = false;
        received += 2;
      }
    } else if (millis() - lastByteAt > 3000) {
      break; // timeout: la app de PC se cortó o tardó demasiado
    }
  }
  t.endWrite();
  Serial.println(received == totalBytes ? "OK IMG" : "ERR IMG_TIMEOUT");
}

static void handleLine(char *line) {
  trimTrailing(line);

  if (!strcmp(line, "PING")) {
    Serial.println("OK HACKPAD v1");

  } else if (!strncmp(line, "SET_TEXT ", 9)) {
    strncpy(cfg.homeText, line + 9, sizeof(cfg.homeText) - 1);
    cfg.homeText[sizeof(cfg.homeText) - 1] = 0;
    display_show_home();
    Serial.println("OK");

  } else if (!strncmp(line, "SET_MACRO ", 10)) {
    int idx = atoi(line + 10) - 1;
    char *sp = strchr(line + 10, ' ');
    if (idx >= 0 && idx < 4 && sp) {
      strncpy(cfg.macro[idx], sp + 1, sizeof(cfg.macro[idx]) - 1);
      cfg.macro[idx][sizeof(cfg.macro[idx]) - 1] = 0;
      Serial.println("OK");
    } else {
      Serial.println("ERR SET_MACRO");
    }

  } else if (!strncmp(line, "SET_COLOR ", 10)) {
    char hex[8];
    if (sscanf(line + 10, "%7s", hex) == 1 && strlen(hex) >= 6) {
      uint8_t r, g, b;
      parseHexColor(hex, &r, &g, &b);
      cfg.ledColor[0] = r; cfg.ledColor[1] = g; cfg.ledColor[2] = b;
      leds_apply_config();
      Serial.println("OK");
    } else {
      Serial.println("ERR SET_COLOR");
    }

  } else if (!strncmp(line, "SET_BRIGHTNESS ", 15)) {
    int v = atoi(line + 15);
    cfg.brightness = (uint8_t)constrain(v, 0, 255);
    leds_apply_config();
    Serial.println("OK");

  } else if (!strcmp(line, "SAVE")) {
    config_save();
    Serial.println("OK");

  } else if (!strcmp(line, "GET_CONFIG")) {
    sendConfigDump();

  } else if (!strcmp(line, "IMG_START")) {
    handleImageTransfer();

  } else if (strlen(line) > 0) {
    Serial.println("ERR UNKNOWN_CMD");
  }
}

void protocol_init() {
  lineLen = 0;
}

void protocol_update() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      lineBuf[lineLen] = 0;
      handleLine(lineBuf);
      lineLen = 0;
    } else if (c != '\r') {
      if (lineLen < sizeof(lineBuf) - 1) lineBuf[lineLen++] = c;
    }
  }
}
