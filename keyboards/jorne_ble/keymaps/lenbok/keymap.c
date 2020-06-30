#include QMK_KEYBOARD_H
#include "app_ble_func.h"
#include "peer_manager.h"
#include "matrix.h"

#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif


const uint8_t is_master = IS_LEFT_HAND;

#define MODS_SHIFT_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

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
    HID_TOG,              /* Swap BLE vs USB HID sending          */
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
    B_ID1,                /* Advertise to or delete bonding (if shifted) for PeerID 1  */
    B_ID2,                /* Advertise to or delete bonding (if shifted) for PeerID 2  */
    B_ID3,                /* Advertise to or delete bonding (if shifted) for PeerID 3  */
    B_ID4,                /* Advertise to or delete bonding (if shifted) for PeerID 4  */
    B_ALL,                /* Advertise without whitelist, or (if shifted) delete all bondings */
    ENT_DFU,              /* Start bootloader                     */
    ENT_SLP,              /* Deep sleep mode                      */
    RST_DFU,              /* Reset or (if shifted) enter DFU */
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
#define KC_HTOG  HID_TOG
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
#define KC_B_ALL B_ALL
#define KC_B_ID1 B_ID1
#define KC_B_ID2 B_ID2
#define KC_B_ID3 B_ID3
#define KC_B_ID4 B_ID4
#define KC_GUGR  LGUI_T(KC_GRV)
#define KC_GUES  LGUI_T(KC_ESC)
#define KC_CTLTB CTL_T(KC_TAB)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
_______, KC_GUGR,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,  KC_BSPC, _______,\
        KC_CTLTB,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                      KC_H,     KC_J,     KC_K,     KC_L,  KC_SCLN,  KC_QUOT,\
         KC_LSPO,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                      KC_N,     KC_M,  KC_COMM,   KC_DOT,  KC_SLSH,  KC_RSPC,\
                                                   KC_LALT, KC_ENT,  LOWER,    RAISE,  KC_SPC,  KC_RCTL \
  ),

  [_LOWER] = LAYOUT( \
_______, KC_GUES,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,  KC_TRNS, _______,\
         KC_TRNS,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,                   KC_LEFT,  KC_DOWN,    KC_UP,  KC_RGHT,  KC_TRNS,  KC_TRNS,\
         KC_TRNS,    KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,                   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,\
                                                   KC_LALT,  RAISE,  LOWER,    RAISE,   LOWER,  KC_RCTL \
  ),

  [_RAISE] = LAYOUT( \
_______, KC_GUES,  KC_EXLM,    KC_AT,  KC_HASH,   KC_DLR,  KC_PERC,                   KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,   KC_DEL, _______,\
         KC_TRNS,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                   KC_MINS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_PIPE,  KC_TRNS,\
         KC_TRNS,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                   KC_UNDS,   KC_EQL,  KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_TRNS,\
                                                   KC_LALT,  RAISE,  LOWER,    RAISE,   LOWER,  KC_RCTL \
  ),

  [_ADJUST] = LAYOUT( \
_______, RST_DFU,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                   KC_MUTE,  KC_BTN1,  KC_BTN3,  KC_BTN2,  XXXXXXX,   KC_INS, _______,\
         KC_CAPS, KC_B_ID1, KC_B_ID2, KC_B_ID3, KC_B_ID4, KC_B_ALL,                   KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R,  XXXXXXX,  XXXXXXX,\
         KC_TRNS,  KC_HTOG,  KC_BDIS,  XXXXXXX,  XXXXXXX,  XXXXXXX,                   KC_MPRV,  KC_VOLD,  KC_VOLU,  KC_MNXT,  KC_MPLY,  KC_TRNS,\
                                                   KC_LALT,  RAISE,  LOWER,    RAISE,   LOWER,  KC_RCTL \
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

bool has_usb(void);

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
  pm_peer_id_t current_peer = ble_connected_peer_id();
#if defined IS_LEFT_HAND  &&  IS_LEFT_HAND == true
  snprintf(hid_state_str, sizeof(hid_state_str), "Hid: %s %s %c",
           get_usb_enabled() ? (has_usb() ? "USB" : "usb") : "   ",
           get_ble_enabled() ? (ble_connected() ? "BLE" : "ble") : "   ",
           get_ble_enabled() && ble_connected() && (current_peer < BLE_GAP_WHITELIST_ADDR_MAX_COUNT) ? ((current_peer & 0xFF) + '0') : ' ');
#else
  snprintf(hid_state_str, sizeof(hid_state_str), "Slave: %s %c",
           ble_connected() ? "BLE" : "ble",
           ble_connected() && (current_peer < BLE_GAP_WHITELIST_ADDR_MAX_COUNT) ? ((current_peer & 0xFF) + '0') : '?');
#endif
  return hid_state_str;
}


//#define BATTERY_PCT

#ifdef BATTERY_PCT
#define MAX_BATT_MV 3300
#define MIN_BATT_MV 2000
#define BATT_RANGE (MAX_BATT_MV-MIN_BATT_MV)
#define batt_pct(x) (100*((x)-MIN_BATT_MV)/BATT_RANGE)
#endif

char bat_state_str[24];
void set_bat_state(void) {
#ifdef BATTERY_PCT
  uint16_t curr = get_vcc();
  curr = curr < MAX_BATT_MV ? curr : MAX_BATT_MV;
  curr = curr > MIN_BATT_MV ? curr : MIN_BATT_MV;
  curr = batt_pct(curr);
  snprintf(bat_state_str, sizeof(bat_state_str), "Batt: %3d%%", curr);
#else
  snprintf(bat_state_str, sizeof(bat_state_str), "Batt: %3dmV", get_vcc());
#endif
}
const char *read_bat_state(void) {
  return bat_state_str;
}

void matrix_init_user(void) {
  // Default to USB
  set_ble_enabled(false);
  set_usb_enabled(true);
}

void matrix_scan_user(void) {
  if (!is_master && matrix_is_modified()) {
    // Update slave side battery just when it is in use
    // (slave side doesn't see process_record_user)
    set_bat_state();
#ifdef SSD1306OLED
    iota_gfx_flush(); // wake up screen
#endif
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  char str[16];
  uint8_t id;
  uint8_t current_mods;

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
    case DEL_ID4:
      delete_bond_id(4);
      return false;
    case B_ALL:
      current_mods = get_mods();
      if (current_mods & MODS_SHIFT_MASK) {
        delete_bonds();
      } else {
        restart_advertising_wo_whitelist();
      }
      return false;
    case B_ID1:
    case B_ID2:
    case B_ID3:
    case B_ID4:
      current_mods = get_mods();
      if (current_mods & MODS_SHIFT_MASK) {
        id = keycode - B_ID1 + 1;
        delete_bond_id(id);
      } else {
        id = keycode - B_ID1 + 1;
        restart_advertising_id(id);
      }
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
    case HID_TOG:
      set_ble_enabled(!get_ble_enabled());
      set_usb_enabled(!get_ble_enabled());
      return false;
    case BLE_DIS:
      ble_disconnect();
      return false;
    case BATT_LV:
      sprintf(str, "%4dmV", get_vcc());
      send_string(str);
      return false;
    case RST_DFU:
      current_mods = get_mods();
      if (current_mods & MODS_SHIFT_MASK) {
        bootloader_jump();
      } else {
        reset_keyboard();
      }
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
    matrix_write_ln(matrix, read_hid_state());
    matrix_write_ln(matrix, read_bat_state());
    //matrix_write_ln(matrix, read_host_led_state());
    matrix_write(matrix, read_keylog());
    //matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
  } else {
    matrix_write_ln(matrix, read_hid_state());
    matrix_write_ln(matrix, read_bat_state());
  /*   matrix_write_ln(matrix, read_layer_state()); // somehow removes the dead pixel */
  /*   matrix_write(matrix, read_logo()); */
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}

#endif
