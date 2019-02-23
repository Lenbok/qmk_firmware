#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

// Shortcut to make keymap more readable
#define KC_LOWR MO(_LOWER)
#define KC_RASE MO(_RAISE)
#define KC_AJST MO(_ADJUST)
#define LOWR_SP LT(_LOWER,KC_SPC)
#define RASE_EN LT(_RAISE,KC_ENT)
#define LOWR_EN LT(_LOWER,KC_ENT)
#define RASE_SP LT(_RAISE,KC_SPC)
#define KC_CTTB CTL_T(KC_TAB)
#define KC_GUGR LGUI_T(KC_GRV)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.                                       ,--------+--------+--------+--------+--------+--------.
      KC_GRV ,  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,                                          KC_6  ,  KC_7  ,  KC_8  ,  KC_9  ,  KC_0  , KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------.                     ,--------+--------+--------+--------+--------+--------+--------|
      KC_GUGR,  KC_Q  ,  KC_W  ,  KC_E  ,  KC_R  ,  KC_T  , KC_MINS,                       KC_EQL ,  KC_Y  ,  KC_U  ,  KC_I  ,  KC_O  ,  KC_P  , KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|                     |--------+--------+--------+--------+--------+--------+--------|
      KC_CTTB,  KC_A  ,  KC_S  ,  KC_D  ,  KC_F  ,  KC_G  , KC_LBRC,                       KC_RBRC,  KC_H  ,  KC_J  ,  KC_K  ,  KC_L  , KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------+--------+--------|
      KC_LSPO,  KC_Z  ,  KC_X  ,  KC_C  ,  KC_V  ,  KC_B  , KC_PGUP, KC_PGDN,     KC_INS , KC_DEL ,  KC_N  ,  KC_M  , KC_COMM, KC_DOT , KC_SLSH, KC_RSPC,
  //|--------+--------+--------+--------+---+----+---+----+--------+--------|   |--------+--------+-----+--+-----+--+--------+--------+--------+--------|
      RGB_TOG, RGB_MOD, KC_LGUI, KC_RGUI,     KC_LALT     , KC_ENT , KC_LOWR,     KC_RASE, KC_SPC ,       KC_RCTL,    KC_LEFT, KC_DOWN,  KC_UP , KC_RGHT
  //`--------+--------+--------+--------+   +--------+    +--------+--------/   \--------+--------+     +--------+  +--------+--------+--------+--------'
  ),

  [_LOWER] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.                                       ,--------+--------+--------+--------+--------+--------.
      _______,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 ,  KC_F5 ,                                          KC_F6 ,  KC_F7 ,  KC_F8 ,  KC_F9 , KC_F10 , _______,
  //|--------+--------+--------+--------+--------+--------+--------.                     ,--------+--------+--------+--------+--------+--------+--------|
      KC_ESC ,  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  , _______,                       _______,  KC_6  ,  KC_7  ,  KC_8  ,  KC_9  , KC_0   , _______,
  //|--------+--------+--------+--------+--------+--------+--------|                     |--------+--------+--------+--------+--------+--------+--------|
      _______,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 ,  KC_F5 , _______,                       _______,  KC_F6 ,  KC_F7 ,  KC_F8 ,  KC_F9 , KC_F10 , _______,
  //|--------+--------+--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+---+----+---+----+--------+--------|   |--------+--------+-----+--+-----+--+--------+--------+--------+--------|
      _______, _______, _______, _______,     _______,      KC_SPC , _______,     _______, KC_ENT ,       _______,    KC_MPRV, KC_VOLD, KC_VOLU, KC_MPLY
  //`--------+--------+--------+--------+   +--------+    +--------+--------/   \--------+--------+     +--------+  +--------+--------+--------+--------'
  ),

  [_RAISE] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.                                       ,--------+--------+--------+--------+--------+--------.
      _______,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 ,  KC_F5 ,                                          KC_F6 ,  KC_F7 ,  KC_F8 ,  KC_F9 , KC_F10 ,  KC_F11,
  //|--------+--------+--------+--------+--------+--------+--------.                     ,--------+--------+--------+--------+--------+--------+--------|
      KC_ESC , KC_EXLM,  KC_AT , KC_HASH, KC_DLR , KC_PERC, KC_WH_U,                       KC_WH_U, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  //|--------+--------+--------+--------+--------+--------+--------|                     |--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______, KC_WH_D,                       KC_WH_D, KC_MINS, KC_EQL , KC_LCBR, KC_RCBR, KC_PIPE, _______,
  //|--------+--------+--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______, _______, _______,     _______, _______, KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS, _______,
  //|--------+--------+--------+--------+---+----+---+----+--------+--------|   |--------+--------+-----+--+-----+--+--------+--------+--------+--------|
      _______, _______, _______, _______,     _______,      KC_SPC , _______,     _______,  KC_ENT,       _______,    KC_MPRV, KC_VOLD, KC_VOLU, KC_MPLY
  //`--------+--------+--------+--------+   +--------+    +--------+--------/   \--------+--------+     +--------+  +--------+--------+--------+--------'
),

  [_ADJUST] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.                                       ,--------+--------+--------+--------+--------+--------.
      DEBUG, _______, _______, _______, _______, _______,                                         _______, _______, _______, _______, _______, _______, \
  //|--------+--------+--------+--------+--------+--------+--------.                     ,--------+--------+--------+--------+--------+--------+--------|
      RESET  , _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, _______,                       _______, _______, KC_HOME, KC_UP  , KC_END , _______,  KC_INS, \
  //|--------+--------+--------+--------+--------+--------+--------|                     |--------+--------+--------+--------+--------+--------+--------|
      KC_CAPS, RGB_HUI, RGB_SAI, RGB_VAI, RGB_TOG, KC_VOLU, _______,                       _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, \
  //|--------+--------+--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------+--------+--------|
      _______, RGB_HUD, RGB_SAD, RGB_VAD, RGB_MOD, KC_VOLD, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, \
  //|--------+--------+--------+--------+---+----+---+----+--------+--------|   |--------+--------+-----+--+-----+--+--------+--------+--------+--------|
      _______, _______, _______, _______,     _______,      _______, _______,     _______, _______,       _______,    _______, _______, _______, _______ \
  //`--------+--------+--------+--------+   +--------+    +--------+--------/   \--------+--------+     +--------+  +--------+--------+--------+--------'
  )

};

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

#ifdef RGBLIGHT_ENABLE
#define IDLE_TIMEOUT 600000   // Blank underglow after 600 secs of inactivity
extern rgblight_config_t rgblight_config;
static uint32_t idle_timer;
static bool idle_timeout_enabled;
void keyboard_post_init_user(void) {
    idle_timer = timer_read32();
    idle_timeout_enabled = rgblight_config.enable ? true : false;
    xprintf("idle_timeout init: idle_timeout_enabled = %u\n", idle_timeout_enabled);
}
void matrix_scan_user(void) {
    if (idle_timeout_enabled) {
        bool shouldenable = timer_elapsed32(idle_timer) < IDLE_TIMEOUT ? true : false;
        if (shouldenable != rgblight_config.enable) {
            xprintf("idle_timeout override: toggling\n");
            // Toggle the underglow. Unfortunately for split keyboards we need
            // to use the eeprom version in order to have it propagate across halves
#ifdef SPLIT_KEYBOARD
            rgblight_toggle();
            RGB_DIRTY = true;
#else
            rgblight_toggle_noeeprom();
#endif
        }
    }
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        idle_timer = timer_read32();
    }
    switch (keycode) {
    case RGB_TOG: // Monitor for change in global status
        // Split keyboards need to trigger on key-up for edge-case issue
        // See corresponding case in quantum.c
#ifndef SPLIT_KEYBOARD
        if (record->event.pressed) {
#else
        if (!record->event.pressed) {
#endif
            // First restore rgblight enabled status to original
            rgblight_config.enable = idle_timeout_enabled;
            idle_timeout_enabled = idle_timeout_enabled ? false : true;
            xprintf("idle_timeout enable: idle_timeout_enabled = %u, rgblight_config.enabled = %u\n", idle_timeout_enabled, rgblight_config.enable);
        }
        return true; // Let main quantum code handle the actual toggling
    }
    return true;
}
#endif
