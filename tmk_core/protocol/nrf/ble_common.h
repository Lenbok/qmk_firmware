#ifndef TMK_CORE_PROTOCOL_NRF_BLE_COMMON_H_
#define TMK_CORE_PROTOCOL_NRF_BLE_COMMON_H_

#include "adc.h"
#include "peer_id.h"

void logger_init();
void advertising_start();
void peer_list_get(pm_peer_id_t * p_peers, uint32_t * p_size);
void sleep_mode_enter(void);

#endif /* TMK_CORE_PROTOCOL_NRF_BLE_COMMON_H_ */
