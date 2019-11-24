#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#include "lenbok.h"

extern keymap_config_t keymap_config;

#if defined(RGB_MATRIX_ENABLE)
extern rgb_config_t rgb_matrix_config;
#elif defined(RGBLIGHT_ENABLE)
extern rgblight_config_t rgblight_config;
#endif
#if defined(RGB_IDLE)
extern uint8_t rgb_idle_mode;
#endif

extern uint8_t is_master;

#if defined(RGB_IDLE)
extern uint8_t rgb_idle_mode;
#endif

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


#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_master) {
        return OLED_ROTATION_270;
    } else {
        return rotation;
    }
}

void render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

char keylog_str_pos[6] = {};
char keylog_str_code[6] = {};
uint16_t log_timer = 0;
const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ';', '\'', ' ', ',', '.', '/', ' ', ' ', ' '};
void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
  if (keycode < 60) {
    name = code_to_name[keycode];
  }
  snprintf(keylog_str_pos, sizeof(keylog_str_pos), "%dx%d",
           record->event.key.row, record->event.key.col);
  snprintf(keylog_str_code, sizeof(keylog_str_code), "%2d %c",
           keycode, name);
}


#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
char rgb_info_str[6];
void render_rgb_info(void) {
#if defined(RGBLIGHT_ENABLE)
    bool enabled = rgblight_config.enable;
    uint8_t mode = rgblight_config.mode;
    oled_write_P(PSTR("RGBl:"), false);
#elif defined(RGB_MATRIX_ENABLE)
    bool enabled = rgb_matrix_config.enable;
    uint8_t mode = rgb_matrix_get_mode();
    oled_write_P(PSTR("RGBm:"), false);
#endif
    if (enabled) {
        snprintf(rgb_info_str, sizeof(rgb_info_str), "On %2d", mode);
    } else {
        snprintf(rgb_info_str, sizeof(rgb_info_str), "   %2d", mode);
    }
    oled_write(rgb_info_str, false);
#if defined(RGB_IDLE)
    snprintf(rgb_info_str, sizeof(rgb_info_str), "Id %2d", rgb_idle_mode);
    oled_write_ln(rgb_info_str, false);
#endif
}
#endif

// If cond is true, render data (possibly inverted), else clear the line
void render_line_P(bool cond, const char* data, bool invert) {
    if (cond) {
        oled_write_P(data, invert);
    } else {
        oled_advance_page(true);
    }
}
void render_status(void) {
    switch (biton32(layer_state)) {
        case 0:
            oled_advance_page(true);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjst"), false);
            break;
        default:
            oled_write_P(PSTR("Unkn "), false);
            break;
    }

    uint8_t modifiers = get_mods();
    uint8_t one_shot = get_oneshot_mods();
    render_line_P(modifiers & MOD_MASK_SHIFT || one_shot & MOD_MASK_SHIFT, PSTR(" SFT "), false);
    render_line_P(modifiers & MOD_MASK_CTRL  || one_shot & MOD_MASK_CTRL,  PSTR(" CTL "), false);
    render_line_P(modifiers & MOD_MASK_ALT   || one_shot & MOD_MASK_ALT,   PSTR(" ALT "), false);
    render_line_P(modifiers & MOD_MASK_GUI   || one_shot & MOD_MASK_GUI,   PSTR(" GUI "), false);

    uint8_t led_usb_state = host_keyboard_leds();
    render_line_P(led_usb_state & (1<<USB_LED_NUM_LOCK),    PSTR(" NUM "), true);
    render_line_P(led_usb_state & (1<<USB_LED_CAPS_LOCK),   PSTR(" CAPS"), true);
    render_line_P(led_usb_state & (1<<USB_LED_SCROLL_LOCK), PSTR(" SCRL"), true);

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    render_rgb_info();
#endif

    oled_write_ln(keylog_str_pos, false);
    oled_write(keylog_str_code, false);
}

void oled_task_user(void) {
    if (is_master) {
        render_status();     // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_logo();
        //oled_scroll_left();  // Turns on scrolling
    }
}
#endif//OLED

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
        set_keylog(keycode, record);
#endif
    }
    return true;
}
