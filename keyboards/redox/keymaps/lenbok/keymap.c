#include QMK_KEYBOARD_H
#include "lenbok.h"

extern keymap_config_t keymap_config;

#define LAYOUT_redox_wrapper(...)      LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_redox_wrapper(
  //,--------+--------+--------+--------+--------+--------.                                       ,--------+--------+--------+--------+--------+--------.
      KC_ESC ,  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,                                          KC_6  ,  KC_7  ,  KC_8  ,  KC_9  ,  KC_0  , KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------.                     ,--------+--------+--------+--------+--------+--------+--------|
                        ___QWERTY_L1___                   , KC_MINS,                       KC_EQL ,                   ___QWERTY_R1___                   ,
  //|--------+--------+--------+--------+--------+--------+--------|                     |--------+--------+--------+--------+--------+--------+--------|
                        ___QWERTY_L2___                   , KC_LBRC,                       KC_RBRC,                   ___QWERTY_R2___                   ,
  //|--------+--------+--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------+--------+--------|
                        ___QWERTY_L3___                   , KC_PGUP, KC_PGDN,     KC_INS , KC_DEL ,                   ___QWERTY_R3___                   ,
  //|--------+--------+--------+--------+---+----+---+----+--------+--------|   |--------+--------+-----+--+-----+--+--------+--------+--------+--------|
      RGB_TOG, RGB_MOD, KC_LGUI, KC_RGUI,                              ___BASE_6_MOD___                          ,    KC_LEFT, KC_DOWN,  KC_UP , KC_RGHT
  //`--------+--------+--------+--------+   +--------+    +--------+--------/   \--------+--------+     +--------+  +--------+--------+--------+--------'
  ),

  [_LOWER] = LAYOUT_redox_wrapper(
  //,--------+--------+--------+--------+--------+--------.                                       ,--------+--------+--------+--------+--------+--------.
                         ___FUN_L1___                     ,                                                             ___FUN_R1___                    ,
  //|--------+--------+--------+--------+--------+--------+--------.                     ,--------+--------+--------+--------+--------+--------+--------|
                        ___LOWER_L1___                    , _______,                       _______,                    ___LOWER_R1___                   ,
  //|--------+--------+--------+--------+--------+--------+--------|                     |--------+--------+--------+--------+--------+--------+--------|
                        ___LOWER_L2___                    , _______,                       _______,                    ___LOWER_R2___                   ,
  //|--------+--------+--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------+--------+--------|
                        ___LOWER_L3___                    , _______, _______,     _______, _______,                    ___LOWER_R3___                   ,
  //|--------+--------+--------+--------+---+----+---+----+--------+--------|   |--------+--------+-----+--+-----+--+--------+--------+--------+--------|
      _______, _______, _______, _______,                              ___ALT_6_MOD___                           ,    KC_MPRV, KC_VOLD, KC_VOLU, KC_MPLY
  //`--------+--------+--------+--------+   +--------+    +--------+--------/   \--------+--------+     +--------+  +--------+--------+--------+--------'
  ),

  [_RAISE] = LAYOUT_redox_wrapper(
  //,--------+--------+--------+--------+--------+--------.                                       ,--------+--------+--------+--------+--------+--------.
                         ___FUN_L1___                     ,                                                             ___FUN_R1___                    ,
  //|--------+--------+--------+--------+--------+--------+--------.                     ,--------+--------+--------+--------+--------+--------+--------|
                        ___UPPER_L1___                    , KC_WH_U,                       KC_WH_U,                    ___UPPER_R1___                   ,
  //|--------+--------+--------+--------+--------+--------+--------|                     |--------+--------+--------+--------+--------+--------+--------|
                        ___UPPER_L2___                    , KC_WH_D,                       KC_WH_D,                    ___UPPER_R2___                   ,
  //|--------+--------+--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------+--------+--------|
                        ___UPPER_L2___                    , _______, _______,     _______, _______,                    ___UPPER_R3___                   ,
  //|--------+--------+--------+--------+---+----+---+----+--------+--------|   |--------+--------+-----+--+-----+--+--------+--------+--------+--------|
      _______, _______, _______, _______,                              ___ALT_6_MOD___                           ,    KC_MPRV, KC_VOLD, KC_VOLU, KC_MPLY
  //`--------+--------+--------+--------+   +--------+    +--------+--------/   \--------+--------+     +--------+  +--------+--------+--------+--------'
),

  [_ADJUST] = LAYOUT_redox_wrapper(
  //,--------+--------+--------+--------+--------+--------.                                       ,--------+--------+--------+--------+--------+--------.
      _______, _______, _______, _______, _______, _______,                                         _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------.                     ,--------+--------+--------+--------+--------+--------+--------|
                        ___ADJUST_L1___                   , _______,                       _______,                   ___ADJUST_R1___                   ,
  //|--------+--------+--------+--------+--------+--------+--------|                     |--------+--------+--------+--------+--------+--------+--------|
                        ___ADJUST_L2___                   , _______,                       _______,                   ___ADJUST_R2___                   ,
  //|--------+--------+--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------+--------+--------|
                        ___ADJUST_L3___                   , _______, _______,     _______, _______,                   ___ADJUST_R3___                   ,
  //|--------+--------+--------+--------+---+----+---+----+--------+--------|   |--------+--------+-----+--+-----+--+--------+--------+--------+--------|
      _______, _______, _______, _______,     _______,      _______, _______,     _______, _______,       _______,    _______, _______, _______, _______
  //`--------+--------+--------+--------+   +--------+    +--------+--------/   \--------+--------+     +--------+  +--------+--------+--------+--------'
  )
};



#ifdef RGBLIGHT_ENABLE
#define IDLE_TIMEOUT 600000   // Blank underglow after 600 secs of inactivity
extern rgblight_config_t rgblight_config;
static uint32_t rgb_idle_timer;
static bool rgb_idle_timeout = false;
void keyboard_post_init_user(void) {
  rgb_idle_timer = timer_read32();
}
void matrix_scan_user(void) {
  if (!rgb_idle_timeout && rgblight_config.enable) {
    bool shouldblank = timer_elapsed32(rgb_idle_timer) < IDLE_TIMEOUT ? false : true;
    if (shouldblank) {
      xprintf("rgb_idle_timeout: disabling\n");
      rgblight_disable_noeeprom();
      rgb_idle_timeout = true;
    }
  }
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    if (rgb_idle_timeout) {
      xprintf("rgb_idle_timeout: enabling\n");
      rgblight_enable_noeeprom();
      rgb_idle_timeout = false;
    }
    rgb_idle_timer = timer_read32();
  }
  return true;
}
#endif
