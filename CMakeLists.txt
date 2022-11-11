set(srcs
        src/core/ble_qiot_llsync_data.c
        src/core/ble_qiot_llsync_device.c
        src/core/ble_qiot_llsync_event.c
        src/core/ble_qiot_llsync_ota.c
        src/core/ble_qiot_llsync_utils.c
        src/core/ble_qiot_service.c
        src/utils/ble_qiot_utils_aes.c
        src/utils/ble_qiot_utils_base64.c
        src/utils/ble_qiot_utils_crc.c
        src/utils/ble_qiot_utils_hmac.c
        src/utils/ble_qiot_utils_log.c
        src/utils/ble_qiot_utils_md5.c
        src/utils/ble_qiot_utils_sha1.c)

list(APPEND srcs
        hal/esp32/ble_qiot_ble_device.c
        hal/esp32/ble_qiot_ble_service.c)

list(APPEND srcs
        data_template/ble_qiot_template.c
        data_template/ble_qiot_template.c)

set(includes inc hal/esp32)
set(priv_includes src/internal_inc data_template)


idf_component_register(SRCS "${srcs}"
        INCLUDE_DIRS "${includes}"
        PRIV_INCLUDE_DIRS "${priv_includes}"
        REQUIRES bt app_update hal_kv_db)
