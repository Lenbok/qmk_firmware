/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

//#define USE_MATRIX_I2C

/* Select hand configuration */

// #define MASTER_LEFT
// #define MASTER_RIGHT
#define EE_HANDS

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"

#define USE_SERIAL_PD2

#define RGBLIGHT_LIMIT_VAL 120

//#define DISABLE_RGB_MATRIX_ALPHAS_MODS
//#define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
//#define DISABLE_RGB_MATRIX_BREATHING
#define DISABLE_RGB_MATRIX_CYCLE_ALL
//#define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
//#define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define DISABLE_RGB_MATRIX_DUAL_BEACON
//#define DISABLE_RGB_MATRIX_RAINBOW_BEACON
//#define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
//#define DISABLE_RGB_MATRIX_RAINDROPS
#define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
//#define DISABLE_RGB_MATRIX_DIGITAL_RAIN
//#define DISABLE_RGB_MATRIX_SOLID_REACTIVE
//#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
//#define DISABLE_RGB_MATRIX_SPLASH
//#define DISABLE_RGB_MATRIX_MULTISPLASH
//#define DISABLE_RGB_MATRIX_SOLID_SPLASH
//#define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
