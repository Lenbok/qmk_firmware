#ifdef RGB_MATRIX_ENABLE
#include "alt.h"

#include "led_matrix.h"
#include "rgb_matrix.h"
#include "config_led.h"

// This table can be almost-automatically derived from ISSI3733_LED_MAP that is
// defined in config_led.h

// You can calculate the (0-244, 0-64) x/y values from the x/y values defined in
// ISSI3733_LED_MAP with the following formula:
//   uint8_t rgb_x = ((ISSI3733_LED_MAP[i].x - MIN_X) / (MAX_X - MIN_X)) * 224;
//   uint8_t rgb_y = ((ISSI3733_LED_MAP[i].y - MIN_Y) / (MAX_Y - MIN_Y)) * 64;
// Where the min/max vars are the minimum and maximum "bounds" of x/y values
// present in ISSI3733_LED_MAP
//
// The row/col values need to be manually tweaked though, compensating for the
// "empty" cells that are a product of larger keys
//
// There is a quick-and-dirty implementation of this under ledvis.html

const rgb_led g_rgb_leds[DRIVER_LED_TOTAL] = {
  /*  0 */ { { (0)|(0  << 4) }, { 8,   56 }, 0 }, // KC_ESC
  /*  1 */ { { (0)|(1  << 4) }, { 22,  56 }, 0 }, // KC_1
  /*  2 */ { { (0)|(2  << 4) }, { 35,  56 }, 0 }, // KC_2
  /*  3 */ { { (0)|(3  << 4) }, { 49,  56 }, 0 }, // KC_3
  /*  4 */ { { (0)|(4  << 4) }, { 63,  56 }, 0 }, // KC_4
  /*  5 */ { { (0)|(5  << 4) }, { 77,  56 }, 0 }, // KC_5
  /*  6 */ { { (0)|(6  << 4) }, { 91,  56 }, 0 }, // KC_6
  /*  7 */ { { (0)|(7  << 4) }, { 105, 56 }, 0 }, // KC_7
  /*  8 */ { { (0)|(8  << 4) }, { 118, 56 }, 0 }, // KC_8
  /*  9 */ { { (0)|(9  << 4) }, { 132, 56 }, 0 }, // KC_9
  /* 10 */ { { (0)|(10 << 4) }, { 146, 56 }, 0 }, // KC_0
  /* 11 */ { { (0)|(11 << 4) }, { 160, 56 }, 0 }, // KC_MINS
  /* 12 */ { { (0)|(12 << 4) }, { 174, 56 }, 0 }, // KC_EQL
  /* 13 */ { { (0)|(13 << 4) }, { 195, 56 }, 0 }, // KC_BSPC
  /* 14 */ { { (0)|(14 << 4) }, { 215, 56 }, 0 }, // KC_DEL
  /* 15 */ { { (1)|(0  << 4) }, { 11,  44 }, 0 }, // KC_TAB
  /* 16 */ { { (1)|(1  << 4) }, { 28,  44 }, 0 }, // KC_Q
  /* 17 */ { { (1)|(2  << 4) }, { 42,  44 }, 0 }, // KC_W
  /* 18 */ { { (1)|(3  << 4) }, { 56,  44 }, 0 }, // KC_E
  /* 19 */ { { (1)|(4  << 4) }, { 70,  44 }, 0 }, // KC_R
  /* 20 */ { { (1)|(5  << 4) }, { 84,  44 }, 0 }, // KC_T
  /* 21 */ { { (1)|(6  << 4) }, { 98,  44 }, 0 }, // KC_Y
  /* 22 */ { { (1)|(7  << 4) }, { 112, 44 }, 0 }, // KC_U
  /* 23 */ { { (1)|(8  << 4) }, { 125, 44 }, 0 }, // KC_I
  /* 24 */ { { (1)|(9  << 4) }, { 139, 44 }, 0 }, // KC_O
  /* 25 */ { { (1)|(10 << 4) }, { 153, 44 }, 0 }, // KC_P
  /* 26 */ { { (1)|(11 << 4) }, { 167, 44 }, 0 }, // KC_LBRC
  /* 27 */ { { (1)|(12 << 4) }, { 181, 44 }, 0 }, // KC_RBRC
  /* 28 */ { { (1)|(13 << 4) }, { 198, 44 }, 0 }, // KC_BSLS
  /* 29 */ { { (1)|(14 << 4) }, { 215, 44 }, 0 }, // KC_HOME
  /* 30 */ { { (2)|(0  << 4) }, { 13,  32 }, 1 }, // KC_CAPS
  /* 31 */ { { (2)|(1  << 4) }, { 32,  32 }, 0 }, // KC_A
  /* 32 */ { { (2)|(2  << 4) }, { 46,  32 }, 0 }, // KC_S
  /* 33 */ { { (2)|(3  << 4) }, { 60,  32 }, 0 }, // KC_D
  /* 34 */ { { (2)|(4  << 4) }, { 73,  32 }, 0 }, // KC_F
  /* 35 */ { { (2)|(5  << 4) }, { 87,  32 }, 0 }, // KC_G
  /* 36 */ { { (2)|(6  << 4) }, { 101, 32 }, 0 }, // KC_H
  /* 37 */ { { (2)|(7  << 4) }, { 115, 32 }, 0 }, // KC_J
  /* 38 */ { { (2)|(8  << 4) }, { 129, 32 }, 0 }, // KC_K
  /* 39 */ { { (2)|(9  << 4) }, { 143, 32 }, 0 }, // KC_L
  /* 40 */ { { (2)|(10 << 4) }, { 156, 32 }, 0 }, // KC_SCLN
  /* 41 */ { { (2)|(11 << 4) }, { 170, 32 }, 0 }, // KC_QUOT
  /* _________________________________________ */ // ____
  /* 42 */ { { (2)|(13 << 4) }, { 193, 32 }, 0 }, // KC_ENT
  /* 43 */ { { (2)|(14 << 4) }, { 215, 32 }, 0 }, // KC_PGUP
  /* 44 */ { { (3)|(0  << 4) }, { 16,  19 }, 0 }, // KC_LSFT
  /* 45 */ { { (3)|(2  << 4) }, { 39,  19 }, 0 }, // KC_Z
  /* 46 */ { { (3)|(3  << 4) }, { 53,  19 }, 0 }, // KC_X
  /* 47 */ { { (3)|(4  << 4) }, { 67,  19 }, 0 }, // KC_C
  /* 48 */ { { (3)|(5  << 4) }, { 80,  19 }, 0 }, // KC_V
  /* 49 */ { { (3)|(6  << 4) }, { 94,  19 }, 0 }, // KC_B
  /* 50 */ { { (3)|(7  << 4) }, { 108, 19 }, 0 }, // KC_N
  /* 51 */ { { (3)|(8  << 4) }, { 122, 19 }, 0 }, // KC_M
  /* 52 */ { { (3)|(9  << 4) }, { 136, 19 }, 0 }, // KC_COMM
  /* 53 */ { { (3)|(10 << 4) }, { 150, 19 }, 0 }, // KC_DOT
  /* 54 */ { { (3)|(11 << 4) }, { 163, 19 }, 0 }, // KC_SLSH
  /* 55 */ { { (3)|(12 << 4) }, { 182, 19 }, 0 }, // KC_RSFT
  /* _________________________________________ */ // ____
  /* 56 */ { { (3)|(13 << 4) }, { 201, 19 }, 0 }, // KC_UP
  /* 57 */ { { (3)|(14 << 4) }, { 215, 19 }, 0 }, // KC_PGDN
  /* 58 */ { { (4)|(0  << 4) }, { 9,    7 }, 0 }, // KC_LCTL
  /* 59 */ { { (4)|(1  << 4) }, { 27,   7 }, 0 }, // KC_LGUI
  /* 60 */ { { (4)|(2  << 4) }, { 44,   7 }, 0 }, // KC_LALT
  /* _________________________________________ */ // ____
  /* _________________________________________ */ // ____
  /* _________________________________________ */ // ____
  /* 61 */ { { (4)|(6  << 4) }, { 96,   7 }, 0 }, // KC_SPC
  /* _________________________________________ */ // ____
  /* _________________________________________ */ // ____
  /* _________________________________________ */ // ____
  /* 62 */ { { (4)|(10 << 4) }, { 148,  7 }, 0 }, // KC_RALT
  /* 63 */ { { (4)|(11 << 4) }, { 165,  7 }, 0 }, // MO(1)
  /* 64 */ { { (4)|(12 << 4) }, { 188,  7 }, 0 }, // KC_LEFT
  /* 65 */ { { (4)|(13 << 4) }, { 201,  7 }, 0 }, // KC_DOWN
  /* 66 */ { { (4)|(14 << 4) }, { 215,  7 }, 0 }, // KC_RGHT

  // Underglow LEDs
  { { 255 }, { 1,    1 }, 0 },
  { { 255 }, { 15,   0 }, 0 },
  { { 255 }, { 31,   0 }, 0 },
  { { 255 }, { 47,   0 }, 0 },
  { { 255 }, { 63,   0 }, 0 },
  { { 255 }, { 79,   0 }, 0 },
  { { 255 }, { 95,   0 }, 0 },
  { { 255 }, { 112,  0 }, 0 },
  { { 255 }, { 128,  0 }, 0 },
  { { 255 }, { 144,  0 }, 0 },
  { { 255 }, { 160,  0 }, 0 },
  { { 255 }, { 176,  0 }, 0 },
  { { 255 }, { 192,  0 }, 0 },
  { { 255 }, { 208,  0 }, 0 },
  { { 255 }, { 222,  1 }, 0 },
  { { 255 }, { 224, 13 }, 0 },
  { { 255 }, { 224, 25 }, 0 },
  { { 255 }, { 224, 38 }, 0 },
  { { 255 }, { 224, 50 }, 0 },
  { { 255 }, { 222, 62 }, 0 },
  { { 255 }, { 191, 64 }, 0 },
  { { 255 }, { 179, 64 }, 0 },
  { { 255 }, { 167, 64 }, 0 },
  { { 255 }, { 153, 64 }, 0 },
  { { 255 }, { 139, 64 }, 0 },
  { { 255 }, { 125, 64 }, 0 },
  { { 255 }, { 112, 64 }, 0 },
  { { 255 }, { 98,  64 }, 0 },
  { { 255 }, { 84,  64 }, 0 },
  { { 255 }, { 70,  64 }, 0 },
  { { 255 }, { 56,  64 }, 0 },
  { { 255 }, { 42,  64 }, 0 },
  { { 255 }, { 28,  64 }, 0 },
  { { 255 }, { 1,   62 }, 0 },
  { { 255 }, { 0,   50 }, 0 },
  { { 255 }, { 0,   38 }, 0 },
  { { 255 }, { 0,   25 }, 0 },
  { { 255 }, { 0,   13 }, 0 },
};

#ifdef USB_LED_INDICATOR_ENABLE
void rgb_matrix_indicators_kb(void)
{
  led_matrix_indicators();
}
#endif // USB_LED_INDICATOR_ENABLE

#endif
