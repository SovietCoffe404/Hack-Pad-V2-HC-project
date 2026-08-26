#include "keys.h"
#include "config.h"

// The pad presents itself as a Bluetooth LE keyboard (there's no native
// USB HID on the ESP32-C3, only a USB serial port — see serial_protocol.cpp).
BleKeyboard bleKeyboard("HACK-PAD", "Santi", 100);

static const uint8_t PINS[4] = {PIN_KEY1, PIN_KEY2, PIN_KEY3, PIN_KEY4};

static bool lastState[4]      = {false, false, false, false};
static uint32_t lastChange[4] = {0, 0, 0, 0};
static const uint32_t DEBOUNCE_MS = 25;

// --- secret combo: hold all 4 keys together for HOLD_MS ---
static const uint32_t HOLD_MS = 1200;
static uint32_t allHeldSince = 0;
static bool comboFired = false;

void keys_init() {
  for (int i = 0; i < 4; i++) pinMode(PINS[i], INPUT_PULLUP);
  bleKeyboard.begin();
}

// Presses a modifier + key combo and releases it.
// Same constant names as Arduino's Keyboard.h (BleKeyboard defines
// compatible ones on purpose), so this logic is nearly identical to the
// wired version.
static void sendCombo(uint8_t modifier, uint8_t key) {
  if (!bleKeyboard.isConnected()) return;
  if (modifier) bleKeyboard.press(modifier);
  bleKeyboard.press(key);
  delay(15);
  bleKeyboard.releaseAll();
}

// Translates "@"-prefixed shortcuts into real key combos.
// If nothing matches, the literal text is typed as-is.
static void executeMacroString(const char *m) {
  if (!bleKeyboard.isConnected()) return; // no BLE connection, nothing to send to

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
    // unknown shortcut -> type it literally so the user notices
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
    bool raw = (digitalRead(PINS[i]) == LOW); // pull-up: LOW = pressed
    if (raw != lastState[i] && (now - lastChange[i]) > DEBOUNCE_MS) {
      lastChange[i] = now;
      lastState[i] = raw;
      if (raw) {
        // falling edge -> pressed: if NOT all 4 are down, it's a normal macro
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
