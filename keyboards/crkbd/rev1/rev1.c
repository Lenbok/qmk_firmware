#include "crkbd.h"


#ifdef AUDIO_ENABLE
    float tone_startup[][2] = SONG(STARTUP_SOUND);
    float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
#endif

#ifdef SSD1306OLED
void led_set_kb(uint8_t usb_led) {
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
    //led_set_user(usb_led);
}
#endif

#ifdef RGB_MATRIX_ENABLE
  const rgb_led g_rgb_leds[DRIVER_LED_TOTAL] = {
	// Left Hand Mapped in order of WS2812 array
  // 25 24 19 18 11 10
  // 26 23 20 17 12 09
  // 27 22 21 16 13 08
  //             15 14 07
  //
	// Right Hand Mapped in order of WS2812 array
  //     10 11 18 19 24 25
  //     09 12 17 20 23 26
  //     08 13 16 21 22 27
  //  07 14 15
  //
  // Columns
  // 0  1  2  3  4  5  6  7  8  9  10 11 12 13
  //
  // 25 24 19 18 11 10       10 11 18 19 24 25
  // 26 23 20 17 12 09       09 12 17 20 23 26
  // 27 22 21 16 13 08       08 13 16 21 22 27
  //             15 14 07 07 14 15

    /* {row | col << 4}
 *    |              {x=0..224, y=0..64}
 *    |                      |        modifier
 *    |                      |   |   */
   { { 0xFF           }, {          0,          0 }, 0 }, // 1
   { { 0xFF           }, {          0,          0 }, 0 }, // 2
   { { 0xFF           }, {          0,          0 }, 0 }, // 3
   { { 0xFF           }, {          0,          0 }, 0 }, // 4
   { { 0xFF           }, {          0,          0 }, 0 }, // 5
   { { 0xFF           }, {          0,          0 }, 0 }, // 6

   { { 3 | ( 6 << 4 ) }, { 17.23 *  6, 21.33 *  3 }, 1 }, // 7
   { { 2 | ( 5 << 4 ) }, { 17.23 *  5, 21.33 *  2 }, 0 }, // 8
   { { 1 | ( 5 << 4 ) }, { 17.23 *  5, 21.33 *  1 }, 0 }, // 9
   { { 0 | ( 5 << 4 ) }, { 17.23 *  5, 21.33 *  0 }, 0 }, //10
   { { 0 | ( 4 << 4 ) }, { 17.23 *  4, 21.33 *  0 }, 0 }, //11
   { { 1 | ( 4 << 4 ) }, { 17.23 *  4, 21.33 *  1 }, 0 }, //12
   { { 2 | ( 4 << 4 ) }, { 17.23 *  4, 21.33 *  2 }, 0 }, //13
   { { 3 | ( 5 << 4 ) }, { 17.23 *  5, 21.33 *  3 }, 1 }, //14
   { { 3 | ( 4 << 4 ) }, { 17.23 *  4, 21.33 *  3 }, 1 }, //15
   { { 2 | ( 3 << 4 ) }, { 17.23 *  3, 21.33 *  2 }, 0 }, //16
   { { 1 | ( 3 << 4 ) }, { 17.23 *  3, 21.33 *  1 }, 0 }, //17
   { { 0 | ( 3 << 4 ) }, { 17.23 *  3, 21.33 *  0 }, 0 }, //18
   { { 0 | ( 2 << 4 ) }, { 17.23 *  2, 21.33 *  0 }, 0 }, //19
   { { 1 | ( 2 << 4 ) }, { 17.23 *  2, 21.33 *  1 }, 0 }, //20
   { { 2 | ( 2 << 4 ) }, { 17.23 *  2, 21.33 *  2 }, 0 }, //21
   { { 2 | ( 1 << 4 ) }, { 17.23 *  1, 21.33 *  2 }, 0 }, //22
   { { 1 | ( 1 << 4 ) }, { 17.23 *  1, 21.33 *  1 }, 0 }, //23
   { { 0 | ( 1 << 4 ) }, { 17.23 *  1, 21.33 *  0 }, 0 }, //24
   { { 0 | ( 0 << 4 ) }, { 17.23 *  0, 21.33 *  0 }, 1 }, //25
   { { 1 | ( 0 << 4 ) }, { 17.23 *  0, 21.33 *  1 }, 1 }, //26
   { { 2 | ( 0 << 4 ) }, { 17.23 *  0, 21.33 *  2 }, 1 }, //27
  };
#endif

void matrix_init_kb(void) {

    #ifdef AUDIO_ENABLE
        _delay_ms(20); // gets rid of tick
        PLAY_SONG(tone_startup);
    #endif

	matrix_init_user();
};

void shutdown_kb(void) {
    #ifdef AUDIO_ENABLE
        PLAY_SONG(tone_goodbye);
      	_delay_ms(150);
      	stop_all_notes();
    #endif
}
