#include "game_snake.h"
#include "config.h"
#include "display.h"
#include "leds.h"

#define CELL 8
#define GRID (SCREEN_W / CELL)  // 16x16

struct Pt { int8_t x, y; };

// direcciones: 0=arriba,1=derecha,2=abajo,3=izquierda
static Pt snake[GRID * GRID];
static int len;
static int dir;
static Pt food;
static uint32_t lastStep;
static uint16_t stepMs;
static bool paused;
static long score;

static void placeFood() {
  bool ok = false;
  while (!ok) {
    food.x = random(0, GRID);
    food.y = random(0, GRID);
    ok = true;
    for (int i = 0; i < len; i++) {
      if (snake[i].x == food.x && snake[i].y == food.y) { ok = false; break; }
    }
  }
}

static void drawCell(int8_t x, int8_t y, uint16_t color) {
  Adafruit_SSD1351 &t = display_raw();
  t.fillRect(x * CELL, y * CELL, CELL - 1, CELL - 1, color);
}

static void resetGame() {
  len = 3;
  dir = 1;
  snake[0] = {8, 8};
  snake[1] = {7, 8};
  snake[2] = {6, 8};
  score = 0;
  stepMs = 220;
  paused = false;
  placeFood();
  display_raw().fillScreen(0x0000);
  for (int i = 0; i < len; i++) drawCell(snake[i].x, snake[i].y, 0x07E0);
  drawCell(food.x, food.y, 0xF800);
}

static bool readPress(uint8_t pin, bool &lastRaw) {
  bool raw = (digitalRead(pin) == LOW);
  bool pressed = raw && !lastRaw;
  lastRaw = raw;
  return pressed;
}

void snake_run() {
  randomSeed(micros());
  resetGame();
  leds_set_all(0, 0, 0);
  leds_show();

  bool lastL = false, lastR = false, lastPause = false, lastExit = false;
  lastStep = millis();

  while (true) {
    bool exitPressed = readPress(PIN_KEY4, lastExit);
    if (exitPressed) break;

    bool turnLeft  = readPress(PIN_KEY1, lastL);
    bool turnRight = readPress(PIN_KEY2, lastR);
    bool togglePause = readPress(PIN_KEY3, lastPause);

    if (togglePause) paused = !paused;
    if (turnLeft)  dir = (dir + 3) % 4;
    if (turnRight) dir = (dir + 1) % 4;

    if (!paused && millis() - lastStep > stepMs) {
      lastStep = millis();

      Pt head = snake[0];
      switch (dir) {
        case 0: head.y--; break;
        case 1: head.x++; break;
        case 2: head.y++; break;
        case 3: head.x--; break;
      }

      bool dead = (head.x < 0 || head.x >= GRID || head.y < 0 || head.y >= GRID);
      for (int i = 0; i < len && !dead; i++) {
        if (snake[i].x == head.x && snake[i].y == head.y) dead = true;
      }

      if (dead) {
        leds_set_all(255, 0, 0);
        leds_show();
        display_show_text("GAME OVER", 0xF800);
        delay(1500);
        char buf[24];
        snprintf(buf, sizeof(buf), "Score: %ld", score);
        display_show_text(buf, 0x07FF);
        delay(1800);
        break;
      }

      bool ate = (head.x == food.x && head.y == food.y);
      for (int i = len; i > 0; i--) snake[i] = snake[i - 1];
      snake[0] = head;
      if (ate) {
        len++;
        score += 10;
        if (stepMs > 90) stepMs -= 6;
        placeFood();
        drawCell(food.x, food.y, 0xF800);
        leds_rainbow_step();
      } else {
        drawCell(snake[len].x, snake[len].y, 0x0000); // borra la cola
      }
      drawCell(snake[0].x, snake[0].y, 0x07E0);
    }
    delay(5);
  }

  leds_set_all(0, 0, 0);
  leds_show();
  display_show_home();
}
