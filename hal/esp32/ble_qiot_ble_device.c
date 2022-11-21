/*
 * Copyright (C) 2019 THL A29 Limited, a Tencent company. All rights reserved.
 * Licensed under the MIT License (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://opensource.org/licenses/MIT
 * Unless required by applicable law or agreed to in writing, software distributed under the License is
 * distributed on an "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "ble_qiot_export.h"
#include "ble_qiot_service.h"
#include "ble_qiot_import.h"

// add std head file here
#include <stdint.h>

// add ble qiot head file here
#include "ble_qiot_config.h"
#include "ble_qiot_log.h"

#include "esp_bt_device.h"
#include "esp_spi_flash.h"
#include "esp_ota_ops.h"

#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"

// divece info which defined in explorer platform

#define PRODUCT_ID  "IQ6QIFREU1"
#define DEVICE_NAME "0000000007"

int ble_get_device_name(char *device_name)
{
    memcpy(device_name, DEVICE_NAME, strlen(DEVICE_NAME));

    return strlen(DEVICE_NAME);
}

int ble_get_product_id(char *product_id)
{
    memcpy(product_id, PRODUCT_ID, strlen(PRODUCT_ID));

    return 0;
}

int ble_get_mac(char *mac)
{
    char *address = (char *)esp_bt_dev_get_address();
    memcpy(mac, address, 6);

    return 0;
}

// return ATT MTU
uint16_t ble_get_user_data_mtu_size(e_system type)
{
    return 128;
}

void ble_qiot_dev_start(void)
{

}

#if BLE_QIOT_LLSYNC_STANDARD

#if BLE_QIOT_DYNREG_ENABLE
static uint8_t sg_device_secret[24] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
#else
static uint8_t sg_device_secret[24];
#endif

#define PROUDCT_SECRET  "+JtTQ9gjsYVuGcwHxn7SSg=="

int ble_get_product_key(char *product_secret)
{
    memcpy(product_secret, PROUDCT_SECRET, sizeof(PROUDCT_SECRET) - 1);
    return 0;
}

int ble_set_psk(const char *psk, uint8_t len)
{
    memcpy(sg_device_secret, psk, sizeof(sg_device_secret));
    return 0;
}

int ble_get_psk(char *psk)
{
    memcpy(psk, sg_device_secret, sizeof(sg_device_secret));

    return 0;
}

int ble_write_flash(uint32_t flash_addr, const char *write_buf, uint16_t write_len)
{
    int ret = spi_flash_erase_range(flash_addr, BLE_QIOT_RECORD_FLASH_PAGESIZE);
    ret     = spi_flash_write(flash_addr, write_buf, write_len);

    return ret == ESP_OK ? write_len : ret;
}

int ble_read_flash(uint32_t flash_addr, char *read_buf, uint16_t read_len)
{
    int ret = spi_flash_read(flash_addr, read_buf, read_len);

    return ret == ESP_OK ? read_len : ret;
}

typedef struct ble_esp32_timer_id_ {
    uint8_t       type;
    ble_timer_cb  handle;
    TimerHandle_t timer;
} ble_esp32_timer_id;

ble_timer_t ble_timer_create(uint8_t type, ble_timer_cb timeout_handle)
{
    ble_esp32_timer_id *p_timer = malloc(sizeof(ble_esp32_timer_id));
    if (NULL == p_timer) {
        return NULL;
    }

    p_timer->type   = type;
    p_timer->handle = timeout_handle;
    p_timer->timer  = NULL;

    return (ble_timer_t)p_timer;
}

ble_qiot_ret_status_t ble_timer_start(ble_timer_t timer_id, uint32_t period)
{
    ble_esp32_timer_id *p_timer = (ble_esp32_timer_id *)timer_id;

    if (NULL == p_timer->timer) {
        p_timer->timer =
            (ble_timer_t)xTimerCreate("ota_timer", period / portTICK_PERIOD_MS,
                                      p_timer->type == BLE_TIMER_PERIOD_TYPE ? pdTRUE : pdFALSE, NULL, p_timer->handle);
    }
    xTimerReset(p_timer->timer, portMAX_DELAY);

    return BLE_QIOT_RS_OK;
}

ble_qiot_ret_status_t ble_timer_stop(ble_timer_t timer_id)
{
    ble_esp32_timer_id *p_timer = (ble_esp32_timer_id *)timer_id;
    xTimerStop(p_timer->timer, portMAX_DELAY);

    return BLE_QIOT_RS_OK;
}

ble_qiot_ret_status_t ble_timer_delete(ble_timer_t timer_id)
{
    ble_esp32_timer_id *p_timer = (ble_esp32_timer_id *)timer_id;
    xTimerDelete(p_timer->timer, portMAX_DELAY);
    free(p_timer);

    return BLE_QIOT_RS_OK;
}

uint8_t ble_ota_is_enable(const char *version)
{
    ble_qiot_log_e("ota version: %s, enable ota", version);
    return BLE_OTA_ENABLE;
}

uint32_t ble_ota_get_download_addr(void)
{
    esp_partition_t *partition = esp_ota_get_next_update_partition(NULL);
    ble_qiot_log_i("otafile download address: %d", partition->address);
    return partition->address;
}

int ble_ota_write_flash(uint32_t flash_addr, const char *write_buf, uint16_t write_len)
{
    assert(flash_addr % BLE_QIOT_RECORD_FLASH_PAGESIZE == 0);
    int ret = spi_flash_erase_range(flash_addr, BLE_QIOT_RECORD_FLASH_PAGESIZE);
    ret     = spi_flash_write(flash_addr, write_buf, write_len);

    return ret == ESP_OK ? write_len : ret;
}

#endif

#if BLE_QIOT_LLSYNC_CONFIG_NET
#include "esp_wifi.h"
#include "esp_log.h"
#include "hal_kv_db.h"

#define TAG     "netconfig"

void ble_report_wificonn_state(BLE_WIFI_STATE state)
{
    wifi_config_t cfg;
    esp_wifi_get_config(WIFI_IF_STA, &cfg);
    ble_event_report_wifi_connect(BLE_WIFI_MODE_STA, state,
                                  (uint8_t)strlen((const char *)cfg.sta.ssid),
                                  (const char *)cfg.sta.ssid);
}

ble_qiot_ret_status_t ble_combo_wifi_mode_set(BLE_WIFI_MODE mode)
{
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    return ble_event_report_wifi_mode(0);
}

ble_qiot_ret_status_t ble_combo_wifi_info_set(const char *ssid, uint8_t ssid_len, const char *passwd, uint8_t passwd_len)
{
    wifi_config_t wifi_config = {
        .sta = {
            .threshold.authmode = WIFI_AUTH_WPA2_PSK,
            .pmf_cfg = {
                .capable = true,
                .required = false
            },
        },
    };
    uint8_t str_len = 0;

    ESP_LOGI(TAG, "wifi info set");
    memset(wifi_config.sta.ssid, 0, sizeof(wifi_config.sta.ssid));
    memset(wifi_config.sta.password, 0, sizeof(wifi_config.sta.password));
    memcpy(wifi_config.sta.ssid, ssid, ssid_len);
    memcpy(wifi_config.sta.password, passwd, passwd_len);
    ESP_LOGI(TAG, "wifi info %s, %s", wifi_config.sta.ssid,wifi_config.sta.password);
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));

    return ble_event_report_wifi_info(0);
}

ble_qiot_ret_status_t ble_combo_wifi_connect()
{
    ESP_LOGI(TAG, "wifi connect");
    ESP_ERROR_CHECK(esp_wifi_connect());
    return 0;
}

#define LLSYNC_TOKEN        "llsync_token"
ble_qiot_ret_status_t ble_combo_wifi_token_set(const char *token, uint16_t token_len)
{
    ESP_LOGI(TAG, "get token: %s", token);
    hal_kv_set(LLSYNC_TOKEN, token, token_len);
    ble_event_report_wifi_token(0);
    return 0;
}

int llsync_token_get(char *buf, int len)
{
    return hal_kv_get(LLSYNC_TOKEN, buf, len);
}

int llsync_token_clear(void)
{
    return hal_kv_del(LLSYNC_TOKEN);
}

ble_qiot_ret_status_t ble_combo_wifi_log_get(void)
{
    return 0;
}

#endif

#ifdef __cplusplus
}
#endif
