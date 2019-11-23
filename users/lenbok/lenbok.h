/* Copyright 2019 Len Trigg
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once
#include "quantum.h"

// Layers
enum user_layers {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    ADJUST,
    RGBRST,
    RGBISET,
    VRSN,
    MAKE
};

#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_LOWR MO(_LOWER)
#define KC_RASE MO(_RAISE)
#define KC_AJST MO(_ADJUST)
#define KC_GUGR LGUI_T(KC_GRV)
#define KC_GUES LGUI_T(KC_ESC)
#define KC_CTTB CTL_T(KC_TAB)

// Define some commonly used rows
#define ___QWERTY_L1___   KC_GUGR,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define ___QWERTY_L2___   KC_CTTB,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define ___QWERTY_L3___   KC_LSPO,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B
#define ___QWERTY_R1___                                                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC
#define ___QWERTY_R2___                                                           KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT
#define ___QWERTY_R3___                                                           KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSPC

#define ___LOWER_L1___   KC_GUES,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define ___LOWER_L2___   _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define ___LOWER_L3___   _______,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10
#define ___LOWER_R1___                                                            KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______
#define ___LOWER_R2___                                                         KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, _______, _______
#define ___LOWER_R3___                                                         _______, _______, _______, _______, _______, _______

#define ___UPPER_L1___   KC_GUES, KC_EXLM,  KC_AT , KC_HASH, KC_DLR , KC_PERC
#define ___UPPER_L2___   _______, _______, _______, _______, _______, _______
#define ___UPPER_L3___   _______, _______, _______, _______, _______, _______
#define ___UPPER_R1___                                                         KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______
#define ___UPPER_R2___                                                         KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, _______
#define ___UPPER_R3___                                                         KC_UNDS, KC_EQL , KC_LBRC, KC_RBRC, KC_BSLS, _______

#define ___ADJUST_L1___    RESET,  RGBRST, EEP_RST,    VRSN,    MAKE, RGBISET
#define ___ADJUST_L2___  KC_CAPS, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, RGB_MOD
#define ___ADJUST_L3___  KC_LSFT, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, RGB_TOG
#define ___ADJUST_R1___                                                        KC_MUTE, KC_BTN1, KC_BTN3, KC_BTN2, _______,  KC_INS
#define ___ADJUST_R2___                                                        KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, VLK_TOG
#define ___ADJUST_R3___                                                        KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_MPLY, _______


#define ___BASE_6_MOD___                            KC_LALT, KC_ENT,  KC_LOWR, KC_RASE,  KC_SPC, KC_RCTL
#define ___ALT_6_MOD___                             KC_LALT, KC_SPC,  KC_LOWR, KC_RASE,  KC_ENT, KC_RCTL
#define ___TRANS_MOD___                             _______, _______, _______, _______, _______, _______


#define ___NUM_L1___       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define ___FUN_L1___       KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define ___NUM_R1___                                                              KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______
#define ___FUN_R1___                                                             KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, _______
