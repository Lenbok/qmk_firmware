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

#include "lenbok.h"
#include "version.h"


#ifdef RGBLIGHT_ENABLE
extern rgblight_config_t rgblight_config;
#endif
#ifdef RGB_MATRIX_ENABLE
extern rgb_config_t rgb_matrix_config;
#endif

#ifdef RGB_IDLE
#define IDLE_TIMEOUT 600000   // Blank underglow after 600 secs of inactivity
static uint32_t rgb_idle_timer;
static bool rgb_idle_timeout = false;
#endif


__attribute__((weak))
void keyboard_post_init_keymap(void){ }

void keyboard_post_init_user(void) {
#ifdef RGB_IDLE
    rgb_idle_timer = timer_read32();
#endif
    keyboard_post_init_keymap();
}

#ifdef RGB_IDLE
#ifdef RGBLIGHT_ENABLE
void rgb_idle_activate(void) {
    rgblight_disable_noeeprom();
}
void rgb_idle_restore(void) {
    rgblight_enable_noeeprom();
}
#endif
#ifdef RGB_MATRIX_ENABLE
static uint8_t rgb_matrix_prev = 0;
void rgb_idle_activate(void) {
    rgb_matrix_prev = rgb_matrix_get_mode();
    rgb_matrix_mode(RGB_MATRIX_DIGITAL_RAIN);
}
void rgb_idle_restore(void) {
    rgb_matrix_mode(rgb_matrix_prev);
}
#endif
#endif

__attribute__ ((weak))
void matrix_scan_keymap(void) {}

void matrix_scan_user(void) {
#ifdef RGB_IDLE
    if (!rgb_idle_timeout
#ifdef RGBLIGHT_ENABLE
        && rgblight_config.enable
#endif
#ifdef RGB_MATRIX_ENABLE
        && rgb_matrix_config.enable
#endif
        ) {
        bool shouldblank = timer_elapsed32(rgb_idle_timer) < IDLE_TIMEOUT ? false : true;
        if (shouldblank) {
            xprintf("rgb_idle_timeout: activating\n");
            rgb_idle_activate();
            rgb_idle_timeout = true;
        }
    }
#endif
    matrix_scan_keymap();
}


__attribute__ ((weak))
uint32_t layer_state_set_keymap(uint32_t state) {
    return state;
}

uint32_t layer_state_set_user(uint32_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    return layer_state_set_keymap(state);
}


__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef RGB_IDLE
    if (record->event.pressed) {
        if (rgb_idle_timeout) {
            xprintf("rgb_idle_timeout: restoring\n");
            rgb_idle_restore();
            rgb_idle_timeout = false;
        }
        rgb_idle_timer = timer_read32();
    }
#endif
    switch (keycode) {
    case MAKE:
        if (!record->event.pressed) {
            uint8_t mods = get_mods();
            clear_mods();
            SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP);
            if (mods & MOD_MASK_SHIFT) {
#if defined(__arm__)
                SEND_STRING(":dfu-util");
#elif  (defined(BOOTLOADER_DFU) || defined(BOOTLOADER_LUFA_DFU) || defined(BOOTLOADER_QMK_DFU))
                SEND_STRING(":dfu");
#elif defined(BOOTLOADER_HALFKAY)
                SEND_STRING(":teensy");
#elif defined(BOOTLOADER_CATERINA)
                SEND_STRING(":avrdude");
#endif
            }
            set_mods(mods);
        }
        return false;
        break;
    case VRSN: // Prints firmware version
        if (record->event.pressed) {
            //send_string_with_delay_P(PSTR(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE), MACRO_TIMER);
            SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " version " QMK_VERSION " built on " QMK_BUILDDATE);
        }
        return false;
        break;
    case RGBRST:
#ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
            eeconfig_update_rgblight_default();
            rgblight_enable();
        }
#endif
        return false;
        break;
    }
    return process_record_keymap(keycode, record);
}
