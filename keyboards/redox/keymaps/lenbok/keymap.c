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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.                                       ,--------+--------+--------+--------+--------+--------.
      KC_GRV ,  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,                                          KC_6  ,  KC_7  ,  KC_8  ,  KC_9  ,  KC_0  , KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------.                     ,--------+--------+--------+--------+--------+--------+--------|
      KC_GRV ,  KC_Q  ,  KC_W  ,  KC_E  ,  KC_R  ,  KC_T  , KC_MINS,                       KC_EQL ,  KC_Y  ,  KC_U  ,  KC_I  ,  KC_O  ,  KC_P  , KC_BSPC,
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
      _______,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 ,  KC_F5 ,                                          KC_F6 ,  KC_F7 ,  KC_F8 ,  KC_F9 , KC_F10 ,  KC_F11,
  //|--------+--------+--------+--------+--------+--------+--------.                     ,--------+--------+--------+--------+--------+--------+--------|
      KC_ESC ,  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  , _______,                       _______,  KC_6  ,  KC_7  ,  KC_8  ,  KC_9  , KC_0   , KC_BSLS,
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
      KC_ESC , KC_EXLM,  KC_AT , KC_HASH, KC_DLR , KC_PERC, KC_WH_U,                       KC_WH_U, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
  //|--------+--------+--------+--------+--------+--------+--------|                     |--------+--------+--------+--------+--------+--------+--------|
      _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, KC_WH_D,                       KC_WH_D, KC_MINS, KC_EQL , KC_LCBR, KC_RCBR, KC_PIPE, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______, _______, _______,     _______, _______, KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS, _______,
  //|--------+--------+--------+--------+---+----+---+----+--------+--------|   |--------+--------+-----+--+-----+--+--------+--------+--------+--------|
      _______, _______, _______, _______,     _______,      KC_SPC , _______,     _______,  KC_ENT,       _______,    KC_MPRV, KC_VOLD, KC_VOLU, KC_MPLY
  //`--------+--------+--------+--------+   +--------+    +--------+--------/   \--------+--------+     +--------+  +--------+--------+--------+--------'
),

  [_ADJUST] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.                                       ,--------+--------+--------+--------+--------+--------.
      _______, _______, _______, _______, _______, _______,                                         _______, _______, _______, _______, _______, _______, \
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
