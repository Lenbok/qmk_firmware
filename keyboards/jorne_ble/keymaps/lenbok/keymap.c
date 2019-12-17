#include QMK_KEYBOARD_H
#include "app_ble_func.h"

#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif


const uint8_t is_master = IS_LEFT_HAND;

// Layers
enum user_layers {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
    AD_WO_L = SAFE_RANGE, /* Start advertising without whitelist  */
    BLE_TOG,              /* Toggle BLE HID sending               */
    BLE_DIS,              /* Disable BLE HID sending              */
    BLE_EN,               /* Enable BLE HID sending               */
    USB_TOG,              /* Toggle USB HID sending               */
    USB_DIS,              /* Disable USB HID sending              */
    USB_EN,               /* Enable USB HID sending               */
    DELBNDS,              /* Delete all bonding                   */
    ADV_ID1,              /* Start advertising to PeerID 1        */
    ADV_ID2,              /* Start advertising to PeerID 2        */
    ADV_ID3,              /* Start advertising to PeerID 3        */
    ADV_ID4,              /* Start advertising to PeerID 4        */
    BATT_LV,              /* Display battery level in milli volts */
    DEL_ID1,              /* Delete bonding of PeerID 1           */
    DEL_ID2,              /* Delete bonding of PeerID 2           */
    DEL_ID3,              /* Delete bonding of PeerID 3           */
    DEL_ID4,              /* Delete bonding of PeerID 4           */
    ENT_DFU,              /* Start bootloader                     */
    ENT_SLP,              /* Deep sleep mode                      */
    QWERTY,
    LOWER,
    RAISE,
    ADJUST,
    BACKLIT,
    RGBRST
};


extern keymap_config_t keymap_config;

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_RST   RESET
#define KC_DFU   ENT_DFU
#define KC_BATT  BATT_LV
#define KC_UEN   USB_EN
#define KC_UDIS  USB_DIS
#define KC_UTOG  USB_TOG
#define KC_BEN   BLE_EN
#define KC_BDIS  BLE_DIS
#define KC_BTOG  BLE_TOG
#define KC_A_ALL AD_WO_L
#define KC_D_ALL DELBNDS
#define KC_A_ID1 ADV_ID1
#define KC_A_ID2 ADV_ID2
#define KC_A_ID3 ADV_ID3
#define KC_A_ID4 ADV_ID4
#define KC_D_ID1 DEL_ID1
#define KC_D_ID2 DEL_ID2
#define KC_D_ID3 DEL_ID3
#define KC_D_ID4 DEL_ID4
#define KC_GUGR  LGUI_T(KC_GRV)
#define KC_GUES  LGUI_T(KC_ESC)
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_GUIEI GUI_T(KC_LANG2)
#define KC_ALTKN ALT_T(KC_LANG1)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
       GUGR,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLTB,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,  QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSPO,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH,  RSPC,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LALT, ENT,  LOWER,     RAISE,  SPC,  RCTL \
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
       GUES,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0,  TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       TRNS,    F1,    F2,    F3,    F4,    F5,                   LEFT,  DOWN,    UP,  RGHT,  TRNS,  TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       TRNS,    F6,    F7,    F8,    F9,   F10,                   TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LALT, SPC,  LOWER,     RAISE,  ENT,  RCTL \
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
       GUES,  EXLM,    AT,  HASH,   DLR,  PERC,                   CIRC,  AMPR,  ASTR,  LPRN,  RPRN,  TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       TRNS, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                   MINS,  PLUS,  LCBR,  RCBR,  PIPE,  TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       TRNS, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                   UNDS,   EQL,  LBRC,  RBRC,  BSLS,  TRNS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LALT, SPC,  LOWER,     RAISE,  ENT,  RCTL \
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        RST, D_ID1, D_ID2, D_ID3, D_ID4, D_ALL,                   MUTE, XXXXX, XXXXX, XXXXX, XXXXX,   INS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       CAPS, A_ID1, A_ID2, A_ID3, A_ID4, A_ALL,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       TRNS,  UTOG,  BTOG, XXXXX, XXXXX, XXXXX,                   MPRV,  VOLD,  VOLU,  MNXT,  MPLY,  TRNS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LALT, SPC,  LOWER,     RAISE,  ENT,  RCTL \
                              //`--------------------'  `--------------------'
  )
};

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

char host_led_state_str[24];
const char *read_host_led_state(void) {
    uint8_t leds = host_keyboard_leds();
    snprintf(host_led_state_str, sizeof(host_led_state_str), "%s %s %s",
             (leds & (1 << USB_LED_CAPS_LOCK))   ? "CAPS" : "    ",
             (leds & (1 << USB_LED_NUM_LOCK))    ? "NUML" : "    ",
             (leds & (1 << USB_LED_SCROLL_LOCK)) ? "SCRL" : "    ");
    return host_led_state_str;
}

char hid_state_str[24];
const char *read_hid_state(void) {
#if defined IS_LEFT_HAND  &&  IS_LEFT_HAND == true
  snprintf(hid_state_str, sizeof(hid_state_str), "Hid: %s %s",
           (get_usb_enabled()) ? "USB" : "   ",
           (get_ble_enabled()) ? "BLE" : "   ");
#endif
  return hid_state_str;
}

char bat_state_str[24];
void set_bat_state(void) {
  snprintf(bat_state_str, sizeof(bat_state_str), "Batt: %4dmV",
           get_vcc());
}
const char *read_bat_state(void) {
  return bat_state_str;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  char str[16];

  //NRF_LOG_INFO("process_record_user, keycode: %d, pressed: %s", keycode, record->event.pressed ? "true" : "false");
#ifdef SSD1306OLED
  iota_gfx_flush(); // wake up screen
#endif

  if (record->event.pressed) {
    set_bat_state();
    set_keylog(keycode, record);
  }

  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
  }
  if (record->event.pressed) {
    switch (keycode) {
    case DELBNDS:
      delete_bonds();
      return false;
    case AD_WO_L:
      restart_advertising_wo_whitelist();
      return false;
    case ADV_ID1:
      restart_advertising_id(1);
      return false;
    case ADV_ID2:
      restart_advertising_id(2);
      return false;
    case ADV_ID3:
      restart_advertising_id(3);
      return false;
    case ADV_ID4:
      restart_advertising_id(4);
      return false;
    case DEL_ID1:
      delete_bond_id(1);
      return false;
    case DEL_ID2:
      delete_bond_id(2);
      return false;
    case DEL_ID3:
      delete_bond_id(3);
      return false;
    case BLE_TOG:
      set_ble_enabled(!get_ble_enabled());
      return false;
    case USB_TOG:
      set_usb_enabled(!get_usb_enabled());
      return false;
    case BLE_EN:
      set_ble_enabled(true);
      set_usb_enabled(false);
      return false;
    case USB_EN:
      set_ble_enabled(false);
      set_usb_enabled(true);
      return false;
    case BATT_LV:
      sprintf(str, "%4dmV", get_vcc());
      send_string(str);
      return false;
    case ENT_DFU:
      bootloader_jump();
      return false;
    }
  }
  else if (!record->event.pressed) {
    switch (keycode) {
    case ENT_SLP:
      sleep_mode_enter();
      return false;
    }
  }
  return true;
}


#ifdef SSD1306OLED

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_bat_state());
    matrix_write_ln(matrix, read_hid_state());
    //matrix_write_ln(matrix, read_host_led_state());
    matrix_write(matrix, read_keylog());
    //matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
  } else {
    matrix_write_ln(matrix, read_layer_state()); // somehow removes the dead pixel
    matrix_write(matrix, read_logo());
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}

#endif
