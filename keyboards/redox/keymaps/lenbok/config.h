/*
Copyright 2017 Danny Nguyen <danny@hexwire.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* Use I2C or Serial, not both */

//#define USE_SERIAL
#define USE_I2C

/* Select hand configuration */

// #define MASTER_LEFT
// #define MASTER_RIGHT
 #define EE_HANDS

#undef RGB_DI_PIN
#define RGB_DI_PIN F4

#undef RGBLED_NUM
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 14
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8

#define MOUSEKEY_DELAY             0
#define MOUSEKEY_INTERVAL          80
//#define MOUSEKEY_MAX_SPEED         5
//#define MOUSEKEY_TIME_TO_MAX       0
#define MOUSEKEY_WHEEL_MAX_SPEED   1
#define MOUSEKEY_WHEEL_TIME_TO_MAX 0

// How long before a tap becomes a hold
#define TAPPING_TERM 200
// Treat mod tap key as a hold even if it hasn't hit TAPPING_TERM
#define PERMISSIVE_HOLD
// Treat a hold following a tap as a hold rather than key repeat
#define TAPPING_FORCE_HOLD
// Make it possible to do rolling combos with keys that convert to other keys on hold
//#define IGNORE_MOD_TAP_INTERRUPT
// If a mod tap key is pressed for TAPPING_TERM with no other key pressed, issue a tap rather than treating as a (no-op) mod.
//#define RETRO_TAPPING

#define DISABLE_SPACE_CADET_ROLLOVER
