#include "keys.h"
#include "config.h"

// El pad se presenta como teclado Bluetooth LE (no hay USB HID nativo en
// el ESP32-C3, solo un puerto serie por USB — ver serial_protocol.cpp).
BleKeyboard bleKeyboard("HACK-PAD", "Santi", 100);

static const uint8_t PINS[4] = {PIN_KEY1, PIN_KEY2, PIN_KEY3, PIN_KEY4};

static bool lastState[4]      = {false, false, false, false};
static uint32_t lastChange[4] = {0, 0, 0, 0};
static const uint32_t DEBOUNCE_MS = 25;

// --- combo secreto: mantener las 4 teclas juntas HOLD_MS ---
static const uint32_t HOLD_MS = 1200;
static uint32_t allHeldSince = 0;
static bool comboFired = false;

void keys_init() {
  for (int i = 0; i < 4; i++) pinMode(PINS[i], INPUT_PULLUP);
  bleKeyboard.begin();
}

// Presiona una combinación de modificadores + tecla y suelta.
// Mismos nombres de constante que Arduino Keyboard.h (BleKeyboard los
// define compatibles a propósito), así que esta lógica es casi idéntica
// a la versión con cable.
static void sendCombo(uint8_t modifier, uint8_t key) {
  if (!bleKeyboard.isConnected()) return;
  if (modifier) bleKeyboard.press(modifier);
  bleKeyboard.press(key);
  delay(15);
  bleKeyboard.releaseAll();
}

// Traduce atajos con prefijo "@" a combinaciones reales de teclado.
// Si no matchea ninguno, se escribe el texto literal tal cual.
static void executeMacroString(const char *m) {
  if (!bleKeyboard.isConnected()) return; // sin conexión BLE no hay a quién mandarle nada

  if (m[0] != '@') {
    bleKeyboard.print(m);
    return;
  }
  if (!strcmp(m, "@COPY"))        sendCombo(KEY_LEFT_CTRL, 'c');
  else if (!strcmp(m, "@PASTE"))  sendCombo(KEY_LEFT_CTRL, 'v');
  else if (!strcmp(m, "@CUT"))    sendCombo(KEY_LEFT_CTRL, 'x');
  else if (!strcmp(m, "@UNDO"))   sendCombo(KEY_LEFT_CTRL, 'z');
  else if (!strcmp(m, "@REDO"))   sendCombo(KEY_LEFT_CTRL, 'y');
  else if (!strcmp(m, "@SAVE"))   sendCombo(KEY_LEFT_CTRL, 's');
  else if (!strcmp(m, "@SELECTALL")) sendCombo(KEY_LEFT_CTRL, 'a');
  else if (!strcmp(m, "@ALTTAB")) sendCombo(KEY_LEFT_ALT, KEY_TAB);
  else if (!strcmp(m, "@ENTER"))  sendCombo(0, KEY_RETURN);
  else if (!strcmp(m, "@ESC"))    sendCombo(0, KEY_ESC);
  else if (!strcmp(m, "@TAB"))    sendCombo(0, KEY_TAB);
  else {
    // atajo desconocido -> lo escribe tal cual para que el usuario lo note
    bleKeyboard.print(m);
  }
}

void keys_run_macro(uint8_t index) {
  if (index > 3) return;
  executeMacroString(cfg.macro[index]);
}

bool keys_secret_combo_triggered() {
  bool result = comboFired;
  comboFired = false;
  return result;
}

void keys_update() {
  uint32_t now = millis();
  bool current[4];
  for (int i = 0; i < 4; i++) {
    bool raw = (digitalRead(PINS[i]) == LOW); // pull-up: LOW = presionado
    if (raw != lastState[i] && (now - lastChange[i]) > DEBOUNCE_MS) {
      lastChange[i] = now;
      lastState[i] = raw;
      if (raw) {
        // flanco de bajada -> presionado: si NO están las 4 abajo, es un macro normal
        bool allDown = true;
        for (int j = 0; j < 4; j++) {
          bool s = (j == i) ? true : (digitalRead(PINS[j]) == LOW);
          if (!s) { allDown = false; break; }
        }
        if (!allDown) keys_run_macro(i);
      }
    }
    current[i] = raw;
  }

  bool allHeld = current[0] && current[1] && current[2] && current[3];
  if (allHeld) {
    if (allHeldSince == 0) allHeldSince = now;
    else if (!comboFired && (now - allHeldSince) > HOLD_MS) {
      comboFired = true;
    }
  } else {
    allHeldSince = 0;
  }
}
