#include "display.h"
#include "config.h"
#include <SPI.h>

static Adafruit_SSD1351 tft(SCREEN_W, SCREEN_H, &SPI, PIN_OLED_CS, PIN_OLED_DC, PIN_OLED_RST);

Adafruit_SSD1351 &display_raw() { return tft; }

void display_init() {
  tft.begin();
  tft.fillScreen(0x0000);
}

// Envuelve texto simple en líneas para que quepa en 128px de ancho
// (fuente por defecto: 6px de ancho por caracter a tamaño 1, 12px a tamaño 2)
static void printWrapped(const char *msg, uint8_t textSize) {
  tft.setTextSize(textSize);
  uint8_t charW = 6 * textSize;
  uint8_t maxChars = SCREEN_W / charW;
  uint16_t y = 10;
  uint16_t lineH = 8 * textSize + 4;

  char buf[65];
  strncpy(buf, msg, sizeof(buf) - 1);
  buf[sizeof(buf) - 1] = 0;

  char *word = strtok(buf, " ");
  char line[32] = "";
  while (word) {
    char tryLine[40];
    if (strlen(line) == 0) snprintf(tryLine, sizeof(tryLine), "%s", word);
    else snprintf(tryLine, sizeof(tryLine), "%s %s", line, word);

    if (strlen(tryLine) > maxChars) {
      tft.setCursor(4, y);
      tft.setTextColor(0x07FF);
      tft.print(line);
      y += lineH;
      strncpy(line, word, sizeof(line) - 1);
    } else {
      strncpy(line, tryLine, sizeof(line) - 1);
    }
    word = strtok(NULL, " ");
  }
  if (strlen(line) > 0) {
    tft.setCursor(4, y);
    tft.setTextColor(0x07FF);
    tft.print(line);
  }
}

void display_show_home() {
  tft.fillScreen(0x0000);
  printWrapped(cfg.homeText, 2);
}

void display_show_text(const char *msg, uint16_t color) {
  tft.fillScreen(0x0000);
  tft.setTextColor(color);
  printWrapped(msg, 2);
}

void display_show_image_rgb565(const uint16_t *pixels) {
  tft.drawRGBBitmap(0, 0, (uint16_t *)pixels, SCREEN_W, SCREEN_H);
}
