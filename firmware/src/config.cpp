#include "config.h"
#include <Preferences.h>

HackPadConfig cfg;
static Preferences prefs;

void config_load_defaults() {
  memset(&cfg, 0, sizeof(cfg));
  strncpy(cfg.homeText, "HACK-PAD", sizeof(cfg.homeText) - 1);

  strncpy(cfg.macro[0], "@COPY",  sizeof(cfg.macro[0]) - 1);
  strncpy(cfg.macro[1], "@PASTE", sizeof(cfg.macro[1]) - 1);
  strncpy(cfg.macro[2], "@UNDO",  sizeof(cfg.macro[2]) - 1);
  strncpy(cfg.macro[3], "hola!",  sizeof(cfg.macro[3]) - 1);

  cfg.ledColor[0] = 255; cfg.ledColor[1] = 0; cfg.ledColor[2] = 80; // rosa
  cfg.brightness = 80;
}

void config_load() {
  prefs.begin("hackpad", /*readOnly=*/false);
  size_t len = prefs.getBytesLength("cfg");
  if (len == sizeof(HackPadConfig)) {
    prefs.getBytes("cfg", &cfg, sizeof(HackPadConfig));
  } else {
    config_load_defaults();
    config_save();
  }
}

void config_save() {
  prefs.putBytes("cfg", &cfg, sizeof(HackPadConfig));
}
