#include "jorne_ble.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_power.h"
#include "nrfx_power.h"
#include "nrfx_pwm.h"
#include "nrf.h"
#include "app_ble_func.h"

// adafruit bootloader, send "dfu" to debug serial port
#define DFU_MAGIC_UF2_RESET             0x57
void bootloader_jump(void) {
  sd_power_gpregret_set(0, DFU_MAGIC_UF2_RESET);
  NVIC_SystemReset();
}

bool has_usb(void) {
  return (nrfx_power_usbstatus_get() == NRFX_POWER_USB_STATE_CONNECTED
    || nrfx_power_usbstatus_get() == NRFX_POWER_USB_STATE_READY);
}

void nrfmicro_power_enable(bool enable) {
  if (has_usb()) enable = true;
#ifdef USE_GND_POWER_PIN
  nrf_gpio_pin_write(POWER_PIN, enable ? 1 : 0);
#endif
#ifdef USE_VCC_POWER_PIN
  nrf_gpio_pin_write(POWER_PIN, enable ? 0 : 1);
#endif
}

void nrfmicro_blink(int times, int delay) {
  for (int i=0; i<times*2; i++) {
    nrf_gpio_pin_write(LED_PIN, i%2==0 ? 1 : 0);
    nrf_delay_ms(delay);
  }
}

void check_ble_switch(bool init) {
#ifdef USE_SWITCH_PIN
  static bool ble_flag = false;
  uint8_t value = nrf_gpio_pin_read(SWITCH_PIN);
  if (init || ble_flag != value) {
    ble_flag = value;
    // mind that it doesn't disable BLE completely, it only disables send
    set_usb_enabled(!ble_flag);
    set_ble_enabled(ble_flag);
    nrf_gpio_pin_clear(LED_PIN);
    // blink on ble enabled
    if (ble_flag) nrmicro_blink(2, 100);
  }
#else
  // just use BT for now
  bool ble_flag = true;
  (void)ble_flag; // may be unused on slave
  set_usb_enabled(!ble_flag);
  set_ble_enabled(ble_flag);
#endif
}

void nrfmicro_init(void) {
  nrf_gpio_cfg_output(LED_PIN);

#if defined USE_GND_POWER_PIN_GND || defined USE_VCC_POWER_PIN
  nrf_gpio_cfg_output(POWER_PIN);
#endif

#ifdef USE_SWITCH_PIN
  nrf_gpio_cfg_input(SWITCH_PIN, NRF_GPIO_PIN_PULLDOWN);
#endif

#ifdef USE_INTERNAL_LDO
  // set internal LDO to 3.3V (power mosfet can't close at 1.8V)
  if (NRF_UICR->REGOUT0 != UICR_REGOUT0_VOUT_3V3) {
    NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos;
    NRF_UICR->REGOUT0 = UICR_REGOUT0_VOUT_3V3;
    NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos;
  }
#endif

#ifdef USE_MCP73811_CTRL
  // tested with KSB7 marking and nRFMicro 1.2, doesn't comply with the specs
  nrf_gpio_cfg_output(STAT_PIN); nrf_gpio_cfg_output(PROG_PIN);
//nrf_gpio_pin_write(STAT_PIN, 1); nrf_gpio_pin_write(PROG_PIN, 1); // 0V BAT
//nrf_gpio_pin_write(STAT_PIN, 0); nrf_gpio_pin_write(PROG_PIN, 1); // 0V BAT
//nrf_gpio_pin_write(STAT_PIN, 1); nrf_gpio_pin_write(PROG_PIN, 0); // 4.2V BAT, 1.2V STAT
  nrf_gpio_pin_write(STAT_PIN, 0); nrf_gpio_pin_write(PROG_PIN, 0); // 4.2V BAT, 0V STAT
#endif

#ifdef USE_MCP73831_CTRL
  //nrf_gpio_cfg_input(PROG_PIN, NRF_GPIO_PIN_NOPULL); // disabled
  nrf_gpio_cfg_input(PROG_PIN, NRF_GPIO_PIN_PULLDOWN); // enabled, Rprog = 13K, ~78 mA current
#endif

#ifdef USE_TP4054_CTRL
  //nrf_gpio_cfg_input(PROG_PIN, NRF_GPIO_PIN_NOPULL); // disabled
  //nrf_gpio_cfg_output(PROG_PIN); nrf_gpio_pin_write(PROG_PIN, 0); // enabled
#endif

  nrfmicro_power_enable(true);

  check_ble_switch(true);

  // blink on start
  nrfmicro_blink(2, 100);
}

// called every matrix_scan_user
void nrfmicro_update(void) {
  check_ble_switch(false);
}

