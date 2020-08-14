#include QMK_KEYBOARD_H

enum tapdance_keycodes {
    TD_KEY_1,
    TD_KEY_2,
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_KEY_1] = ACTION_TAP_DANCE_DOUBLE(KC_VOLU, KC_MNXT),
    [TD_KEY_2] = ACTION_TAP_DANCE_DOUBLE(KC_VOLD, KC_MPRV),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        TD(TD_KEY_1),
        TD(TD_KEY_2)
    ),
};
