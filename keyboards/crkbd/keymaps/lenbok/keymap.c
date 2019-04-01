#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif
#include "lenbok.h"

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

#define LAYOUT_crkbd_wrapper(...)      LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_crkbd_wrapper(
  //,-----------------------------------------.                ,-----------------------------------------.
                 ___QWERTY_L1___             ,                               ___QWERTY_R1___             ,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
                 ___QWERTY_L2___             ,                               ___QWERTY_R2___             ,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
                 ___QWERTY_L3___             ,                               ___QWERTY_R3___             ,
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                               ___BASE_6_MOD___
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_crkbd_wrapper(
  //,-----------------------------------------.                ,-----------------------------------------.
                  ___LOWER_L1___              ,                               ___LOWER_R1___             ,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
                  ___LOWER_L2___              ,                               ___LOWER_R2___             ,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
                  ___LOWER_L3___              ,                               ___LOWER_R3___             ,
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                               ___ALT_6_MOD___
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_crkbd_wrapper(
  //,-----------------------------------------.                ,-----------------------------------------.
                  ___UPPER_L1___              ,                               ___UPPER_R1___             ,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
                  ___UPPER_L2___              ,                               ___UPPER_R2___             ,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
                  ___UPPER_L3___              ,                               ___UPPER_R3___             ,
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                               ___ALT_6_MOD___
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_crkbd_wrapper(
  //,-----------------------------------------.                ,-----------------------------------------.
                 ___ADJUST_L1___              ,                              ___ADJUST_R1___             ,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
                 ___ADJUST_L2___              ,                              ___ADJUST_R2___             ,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
                 ___ADJUST_L3___              ,                              ___ADJUST_R3___             ,
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                               ___ALT_6_MOD___
                              //`--------------------'  `--------------------'
  )
};


void matrix_init_user(void) {
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

char layer_state_str[24];
const char* read_layer_state(void) {
    switch (biton32(layer_state)) {
    case _QWERTY:
        snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Qwerty ");
        break;
    case _RAISE:
        snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Raise  ");
        break;
    case _LOWER:
        snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Lower  ");
        break;
    case _ADJUST:
        snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Adjust ");
        break;
    default:
        snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%ld", layer_state);
        break;
    }
    return layer_state_str;
}


void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}

