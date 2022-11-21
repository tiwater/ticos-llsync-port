#include "ble_qiot_import.h"
/* #include "le/ble_api.h" */
#include "vm.h"
#include "le_common.h"
#include "dual_bank_updata_api.h"
#include "dual_bank_updata_api.h"
#include "timer.h"
#include "os/os_api.h"
#include "update_loader_download.h"
#include "app_config.h"

#define PRODUCT_ID "AG8WUO8LEE"
#define DEVICE_NAME "ble_device_03"
#define SECRET_KEY "s4g1CBdbPaaLYU1FLQExAw=="

static u8 d_product_id[32] = {0};
static u8 d_device_name[32] = {0};
static u8 d_secrt_key[64] = {0};

#define LOG_TAG             "[ble_qiot_import]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"

#define ADV_INTERVAL_MIN          (160)

static u8 scan_rsp_data[ADV_RSP_PACKET_MAX];//max is 31
static char d_name[7] = "WATER1";  //"LLMAIN";
static u8 d_name_len = 6; //名字长度，不包含结束符
static u8 ble_work_state = 0;      //ble 状态变化
static u8 adv_ctrl_en;             //广播控制
static u16 protocol_MTU;             //广播控制

static u8 adv_data_len;
static u8 adv_data[ADV_RSP_PACKET_MAX];//max is 31
static u8 scan_rsp_data_len;
static u8 scan_rsp_data[ADV_RSP_PACKET_MAX];//max is 31

int ble_get_product_id(char *product_id)
{
    log_info("ble_get_product_id");
    memcpy(product_id, PRODUCT_ID, strlen(PRODUCT_ID));
    put_buf(product_id, strlen(product_id));
    return 0;
}

int ble_get_device_name(char *device_name)
{
    log_info("ble_get_device_name");
    memcpy(device_name, DEVICE_NAME, strlen(DEVICE_NAME));
    put_buf(device_name, strlen(device_name));
    return strlen(device_name);
}

int ble_get_psk(char *psk)
{
    log_info("ble_get_psk");
    memcpy(psk, SECRET_KEY, strlen(SECRET_KEY));
    put_buf(psk, strlen(psk));
    return 0;
}

extern const u8 *ble_get_mac_addr(void);
int ble_get_mac(char *mac)
{
    log_info("ble_get_mac");
    le_controller_get_mac(mac);
    put_buf(mac, 6);
    return 0;
}

static void (*app_set_adv_data)(u8 *adv_data, u8 adv_len) = NULL;
static void (*app_set_rsp_data)(u8 *rsp_data, u8 rsp_len) = NULL;
void app_set_adv_data_register(void (*handler)(u8 *adv_data, u8 adv_len))
{
    app_set_adv_data = handler;
}
void app_set_rsp_data_register(void (*handler)(u8 *rsp_data, u8 rsp_len))
{
    app_set_rsp_data = handler;
}

static int llsync_set_rsp_data(void)
{
    u8 offset = 0;
    u8 *buf = scan_rsp_data;

    u8 name_len = sizeof(d_name);
    u8 vaild_len = ADV_RSP_PACKET_MAX - (offset + 2);
    if (name_len > vaild_len) {
        name_len = vaild_len;
    }
    offset += make_eir_packet_data(&buf[offset], offset, HCI_EIR_DATATYPE_COMPLETE_LOCAL_NAME, (void *)d_name, d_name_len);

    if (offset > ADV_RSP_PACKET_MAX) {
        printf("***rsp_data overflow!!!!!!\n");
        return -1;
    }

    //printf("rsp_data(%d):", offset);
    //printf_buf(buf, offset);
    scan_rsp_data_len = offset;
    if (app_set_rsp_data) {
        app_set_rsp_data(scan_rsp_data, scan_rsp_data_len);
    }
    ble_op_set_rsp_data(offset, buf);
    return 0;
}

static int llsync_set_adv_data(adv_info_s *adv)
{
    u8 offset = 0;
    u8 *buf = adv_data;
    u8 manufacturer_buf[20];

    memcpy(&manufacturer_buf[0], &adv->manufacturer_info.company_identifier, 2);
    memcpy(&manufacturer_buf[2], adv->manufacturer_info.adv_data, adv->manufacturer_info.adv_data_len);
    printf("manufacturer_buf\n");
    put_buf(manufacturer_buf, adv->manufacturer_info.adv_data_len + 2);

    offset += make_eir_packet_val(&buf[offset], offset, HCI_EIR_DATATYPE_FLAGS, 0x06, 1);
    offset += make_eir_packet_val(&buf[offset], offset, HCI_EIR_DATATYPE_COMPLETE_16BIT_SERVICE_UUIDS, IOT_BLE_UUID_SERVICE, 2);
    offset += make_eir_packet_data(&buf[offset], offset, HCI_EIR_DATATYPE_MANUFACTURER_SPECIFIC_DATA, manufacturer_buf, adv->manufacturer_info.adv_data_len + 2);

    if (offset > ADV_RSP_PACKET_MAX) {
        puts("***adv_data overflow!!!!!!\n");
        printf("offset = %d, limite is %d\n", offset, ADV_RSP_PACKET_MAX);
        return -1;
    }

    //log_info("adv_data(%d):", offset);
    //log_info_hexdump(buf, offset);
    adv_data_len = offset;
    if (app_set_adv_data) {
        app_set_adv_data(adv_data, adv_data_len);
    }
    ble_op_set_adv_data(offset, buf);
    return 0;
}

static void (*llsync_ble_module_enable)(u8 en) = NULL;
ble_qiot_ret_status_t ble_advertising_start(adv_info_s *adv)
{
    log_info("ble_advertising_start\n");
    //log_info_hexdump(adv->manufacturer_info.adv_data, adv->manufacturer_info.adv_data_len);

    llsync_set_adv_data(adv);
    llsync_set_rsp_data();

    if (llsync_ble_module_enable) {
        llsync_ble_module_enable(1);
    }
    return 0;
}

void llsync_ble_module_enable_register(void (*handler)(u8 en))
{
    llsync_ble_module_enable = handler;
}

ble_qiot_ret_status_t ble_advertising_stop(void)
{
    log_info("ble_advertising_stop\n");
    if (llsync_ble_module_enable) {
        llsync_ble_module_enable(0);
    }
    return 0;
}

static int (*llsync_send_data)(void *priv, u8 *data, u16 len) = NULL;
void llsync_send_data_register(int (*handler)(void *priv, void *buf, u16 len))
{
    llsync_send_data = handler;
}

ble_qiot_ret_status_t ble_send_notify(uint8_t *buf, uint8_t len)
{
    if (llsync_send_data) {
        llsync_send_data(NULL, buf, len);
    } else {
        log_info("llsync_send_data no register");
    }
    return 0;
}

uint16_t ble_get_user_data_mtu_size(e_system type)
{
    return BLE_QIOT_PACKAGE_LENGTH + 6;
}


static OS_SEM      sg_ota_sem;
static void ble_ota_reboot_timer(void *priv)
{
    cpu_reset();
}

static int ble_ota_write_boot_info_callback(int err)
{
    if (err == 0) {
        sys_timeout_add(NULL, ble_ota_reboot_timer, 500);
    }
}

void ble_ota_start_cb(void)
{
    os_sem_create(&sg_ota_sem, 0);
}

void ble_ota_stop_cb(uint8_t result)
{
    if (BLE_QIOT_OTA_ERR_TIMEOUT == result){
        ble_ota_stop();
        dual_bank_passive_update_exit(NULL);
    }else if (BLE_QIOT_OTA_SUCCESS == result){
        dual_bank_update_burn_boot_info(ble_ota_write_boot_info_callback);
    }

}

ble_qiot_ret_status_t ble_ota_valid_file_cb(uint32_t file_size, char *file_version)
{
    dual_bank_update_burn_boot_info(ble_ota_write_boot_info_callback);
}

void ble_ota_read_flash(uint32_t flash_addr, char * read_buf, uint16_t read_len)
{
    dual_bank_update_read_data(flash_addr, read_buf, read_len);
}

uint8_t ble_ota_is_enable(const char *version, u32 file_size, u32 file_crc)
{
    log_info("ota version: %s, enable ota", version);
    if (dual_bank_passive_update_init(file_crc, file_size, BLE_QIOT_OTA_BUF_SIZE, NULL) == 0) {
        if (dual_bank_update_allow_check(file_size) == 0) {
            return BLE_OTA_ENABLE;
        }
    }
    dual_bank_passive_update_exit(NULL);
    return 0;
}

uint32_t ble_ota_get_download_addr(void)
{
    return 0;
}

static int ble_ota_write_end_callback(void *priv)
{
    os_sem_post(&sg_ota_sem);
    return 0;
}

int ble_ota_write_flash(uint32_t flash_addr, const char *write_buf, uint16_t write_len)
{
    dual_bank_update_write((const char *)write_buf, write_len, ble_ota_write_end_callback);
    os_sem_pend(&sg_ota_sem, 0);
}

typedef struct ble_esp32_timer_id_ {
    uint8_t       type;
    ble_timer_cb  handle;
    int timer;
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
    sys_timer_add(NULL, p_timer->handle, period);

    return BLE_QIOT_RS_OK;
}

ble_qiot_ret_status_t ble_timer_stop(ble_timer_t timer_id)
{
    ble_esp32_timer_id *p_timer = (ble_esp32_timer_id *)timer_id;
    //xTimerStop(p_timer->timer, portMAX_DELAY);

    return BLE_QIOT_RS_OK;
}

ble_qiot_ret_status_t ble_timer_delete(ble_timer_t timer_id)
{
    ble_esp32_timer_id *p_timer = (ble_esp32_timer_id *)timer_id;
    sys_timer_del(p_timer->timer);
    free(p_timer);

    return BLE_QIOT_RS_OK;
}
void ble_qiot_dev_start(void)
{

}
void ble_services_add(const qiot_service_init_s *p_service)
{
    // do nothing
    return;
}

extern s32 vm_open(u16 index);
extern s32 vm_read(vm_hdl hdl, u8 *data_buf, u16 len);
extern s32 vm_write(vm_hdl hdl, u8 *data_buf, u16 len);

int ble_read_flash(uint32_t flash_addr, char *read_buf, uint16_t read_len)
{
    int ret;
    s32 hdl = vm_open(flash_addr);

    ret = vm_read(hdl, read_buf, read_len);
    if (ret < 0) {
        log_info("\n\nread flash error:%d", ret);
    }
    return read_len;
}

int ble_write_flash(uint32_t flash_addr, const char *write_buf, uint16_t write_len)
{
    int ret;
    s32 hdl = vm_open(flash_addr);

    ret = vm_write(hdl, write_buf, write_len);
    if (ret < 0) {
        log_info("\n\nwrite flash error:%d", ret);
    }
    return write_len;
}

