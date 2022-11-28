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
#include "ble_qiot_template.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "ble_qiot_export.h"
#include "ble_qiot_common.h"
#include "ble_qiot_param_check.h"
static void ble_property_t_bool_set(uint8_t val)
{
	ble_qiot_log_d("set id t_bool bool value %02x", val);
	return;
}

static uint8_t ble_property_t_bool_get()
{
	uint8_t tmp_bool = 1;
	ble_qiot_log_d("get id t_bool bool value %02x", tmp_bool);
	return tmp_bool;
}

static void ble_property_t_int_set(uint32_t val)
{
	ble_qiot_log_d("set id t_int int value %d", val);
	return;
}

static uint32_t ble_property_t_int_get()
{
	uint32_t tmp_int = 1;
	ble_qiot_log_d("get id t_int int value %d", tmp_int);
	return tmp_int;
}

static void ble_property_t_str_set(const char *val, int len)
{
	ble_qiot_log_d("set id t_str string value %s", val);
	return;
}

static const char *ble_property_t_str_get()
{
	const char *tmp_str = "ticos";
	ble_qiot_log_d("get id t_str string value %s", tmp_str);
	return tmp_str;
}

static void ble_property_t_float_set(float val)
{
	ble_qiot_log_d("set id t_float float value %f", val);
	return;
}

static float ble_property_t_float_get()
{
	float tmp_float = 1.23456;
	ble_qiot_log_d("get id t_float float value %f", tmp_float);
	return tmp_float;
}

static void ble_property_t_enum_set(uint16_t val)
{
	ble_qiot_log_d("set id t_enum int value %d", val);
	return;
}

static uint16_t ble_property_t_enum_get()
{
	uint16_t tmp_enum = 0;
	ble_qiot_log_d("get id t_enum int value %d", tmp_enum);
	return tmp_enum;
}

static void ble_property_t_time_set(uint32_t val)
{
	ble_qiot_log_d("set id t_time time value %d", val);
	return;
}

static uint32_t ble_property_t_time_get()
{
	uint32_t tmp_time = 12345678;
	ble_qiot_log_d("get id t_time time value %d", tmp_time);
	return tmp_time;
}

static void ble_property_t_struct_s_bool_set(uint8_t val)
{
	ble_qiot_log_d("set id s_bool bool value %02x", val);
	return;
}

static uint8_t ble_property_t_struct_s_bool_get()
{
	uint8_t tmp_bool = 1;
	ble_qiot_log_d("get id s_bool bool value %02x", tmp_bool);
	return tmp_bool;
}

static void ble_property_t_struct_s_int_set(uint32_t val)
{
	ble_qiot_log_d("set id s_int int value %d", val);
	return;
}

static uint32_t ble_property_t_struct_s_int_get()
{
	uint32_t tmp_int = 1;
	ble_qiot_log_d("get id s_int int value %d", tmp_int);
	return tmp_int;
}

static void ble_property_t_struct_s_str_set(const char *val, int len)
{
	ble_qiot_log_d("set id s_str string value %s", val);
	return;
}

static const char *ble_property_t_struct_s_str_get()
{
	const char *tmp_str = "ticos";
	ble_qiot_log_d("get id s_str string value %s", tmp_str);
	return tmp_str;
}

static void ble_property_t_struct_s_float_set(float val)
{
	ble_qiot_log_d("set id s_float float value %f", val);
	return;
}

static float ble_property_t_struct_s_float_get()
{
	float tmp_float = 1.23456;
	ble_qiot_log_d("get id s_float float value %f", tmp_float);
	return tmp_float;
}

static void ble_property_t_struct_s_enum_set(uint16_t val)
{
	ble_qiot_log_d("set id s_enum int value %d", val);
	return;
}

static uint16_t ble_property_t_struct_s_enum_get()
{
	uint16_t tmp_enum = 0;
	ble_qiot_log_d("get id s_enum int value %d", tmp_enum);
	return tmp_enum;
}

static void ble_property_t_struct_s_time_set(uint32_t val)
{
	ble_qiot_log_d("set id s_time time value %d", val);
	return;
}

static uint32_t ble_property_t_struct_s_time_get()
{
	uint32_t tmp_time = 12345678;
	ble_qiot_log_d("get id s_time time value %d", tmp_time);
	return tmp_time;
}

static ble_property_t sg_ble_t_struct_property_array[6] = {
	{(property_set_cb)ble_property_t_struct_s_bool_set, (property_get_cb)ble_property_t_struct_s_bool_get, 0, BLE_QIOT_DATA_TYPE_BOOL, 1},
	{(property_set_cb)ble_property_t_struct_s_int_set, (property_get_cb)ble_property_t_struct_s_int_get, 0, BLE_QIOT_DATA_TYPE_INT, 1},
	{(property_set_cb)ble_property_t_struct_s_str_set, (property_get_cb)ble_property_t_struct_s_str_get, 0, BLE_QIOT_DATA_TYPE_STRING, 1},
	{(property_set_cb)ble_property_t_struct_s_float_set, (property_get_cb)ble_property_t_struct_s_float_get, 0, BLE_QIOT_DATA_TYPE_FLOAT, 1},
	{(property_set_cb)ble_property_t_struct_s_enum_set, (property_get_cb)ble_property_t_struct_s_enum_get, 0, BLE_QIOT_DATA_TYPE_ENUM, 1},
	{(property_set_cb)ble_property_t_struct_s_time_set, (property_get_cb)ble_property_t_struct_s_time_get, 0, BLE_QIOT_DATA_TYPE_TIME, 1},
};

static int ble_property_t_struct_set(const char *data, uint16_t len)
{
	return ble_user_property_struct_handle(data, len, sg_ble_t_struct_property_array, 6);
}

static int ble_property_t_struct_get(char *data, uint16_t len)
{
	return ble_user_property_struct_get_data(data, len, sg_ble_t_struct_property_array, 6);
}

static void ble_property_t_struct2_s_bool_set(uint8_t val)
{
	ble_qiot_log_d("set id s_bool bool value %02x", val);
	return;
}

static uint8_t ble_property_t_struct2_s_bool_get()
{
	uint8_t tmp_bool = 1;
	ble_qiot_log_d("get id s_bool bool value %02x", tmp_bool);
	return tmp_bool;
}

static ble_property_t sg_ble_t_struct2_property_array[1] = {
	{(property_set_cb)ble_property_t_struct2_s_bool_set, (property_get_cb)ble_property_t_struct2_s_bool_get, 0, BLE_QIOT_DATA_TYPE_BOOL, 1},
};

static int ble_property_t_struct2_set(const char *data, uint16_t len)
{
	return ble_user_property_struct_handle(data, len, sg_ble_t_struct2_property_array, 1);
}

static int ble_property_t_struct2_get(char *data, uint16_t len)
{
	return ble_user_property_struct_get_data(data, len, sg_ble_t_struct2_property_array, 1);
}

static void ble_property_t_int_array_set(uint32_t val, int index)
{
	ble_qiot_log_d("set id t_int_array int value %d", val);
	return;
}

static uint32_t ble_property_t_int_array_get(int index)
{
	uint32_t tmp_int = 1;
	ble_qiot_log_d("get id t_int_array int value %d", tmp_int);
	return tmp_int;
}

static void ble_property_t_flot_array_set(float val, int index)
{
	ble_qiot_log_d("set id t_flot_array float value %f", val);
	return;
}

static float ble_property_t_flot_array_get(int index)
{
	float tmp_float = 1.23456;
	ble_qiot_log_d("get id t_flot_array float value %f", tmp_float);
	return tmp_float;
}

static void ble_property_t_struct_array_t_bool_set(uint8_t val, int index)
{
	ble_qiot_log_d("set id t_bool bool value %02x", val);
	return;
}

static uint8_t ble_property_t_struct_array_t_bool_get(int index)
{
	uint8_t tmp_bool = 1;
	ble_qiot_log_d("get id t_bool bool value %02x", tmp_bool);
	return tmp_bool;
}

static void ble_property_t_struct_array_t_int_set(uint32_t val, int index)
{
	ble_qiot_log_d("set id t_int int value %d", val);
	return;
}

static uint32_t ble_property_t_struct_array_t_int_get(int index)
{
	uint32_t tmp_int = 1;
	ble_qiot_log_d("get id t_int int value %d", tmp_int);
	return tmp_int;
}

static void ble_property_t_struct_array_t_str_set(const char *val, int len, int index)
{
	ble_qiot_log_d("set id t_str string value %s", val);
	return;
}

static const char *ble_property_t_struct_array_t_str_get(int index)
{
	const char *tmp_str = "ticos";
	ble_qiot_log_d("get id t_str string value %s", tmp_str);
	return tmp_str;
}

static void ble_property_t_struct_array_t_float_set(float val, int index)
{
	ble_qiot_log_d("set id t_float float value %f", val);
	return;
}

static float ble_property_t_struct_array_t_float_get(int index)
{
	float tmp_float = 1.23456;
	ble_qiot_log_d("get id t_float float value %f", tmp_float);
	return tmp_float;
}

static void ble_property_t_struct_array_t_time_set(uint32_t val, int index)
{
	ble_qiot_log_d("set id t_time time value %d", val);
	return;
}

static uint32_t ble_property_t_struct_array_t_time_get(int index)
{
	uint32_t tmp_time = 12345678;
	ble_qiot_log_d("get id t_time time value %d", tmp_time);
	return tmp_time;
}

static void ble_property_t_struct_array_t_enum_set(uint16_t val, int index)
{
	ble_qiot_log_d("set id t_enum int value %d", val);
	return;
}

static uint16_t ble_property_t_struct_array_t_enum_get(int index)
{
	uint16_t tmp_enum = 0;
	ble_qiot_log_d("get id t_enum int value %d", tmp_enum);
	return tmp_enum;
}

static ble_property_t sg_ble_t_struct_array_property_array[6] = {
	{(property_set_cb)ble_property_t_struct_array_t_bool_set, (property_get_cb)ble_property_t_struct_array_t_bool_get, 0, BLE_QIOT_DATA_TYPE_BOOL, 1},
	{(property_set_cb)ble_property_t_struct_array_t_int_set, (property_get_cb)ble_property_t_struct_array_t_int_get, 0, BLE_QIOT_DATA_TYPE_INT, 1},
	{(property_set_cb)ble_property_t_struct_array_t_str_set, (property_get_cb)ble_property_t_struct_array_t_str_get, 0, BLE_QIOT_DATA_TYPE_STRING, 1},
	{(property_set_cb)ble_property_t_struct_array_t_float_set, (property_get_cb)ble_property_t_struct_array_t_float_get, 0, BLE_QIOT_DATA_TYPE_FLOAT, 1},
	{(property_set_cb)ble_property_t_struct_array_t_time_set, (property_get_cb)ble_property_t_struct_array_t_time_get, 0, BLE_QIOT_DATA_TYPE_TIME, 1},
	{(property_set_cb)ble_property_t_struct_array_t_enum_set, (property_get_cb)ble_property_t_struct_array_t_enum_get, 0, BLE_QIOT_DATA_TYPE_ENUM, 1},
};

static int ble_property_t_struct_array_set(const char *data, uint16_t len)
{
	return ble_user_property_struct_array_set(BLE_QIOT_PROPERTY_ID_T_STRUCT_ARRAY, data, len, sg_ble_t_struct_array_property_array, 6);
}

static int ble_property_t_struct_array_get(char *data, uint16_t len)
{
	return ble_user_property_struct_array_get(BLE_QIOT_PROPERTY_ID_T_STRUCT_ARRAY, data, len, sg_ble_t_struct_array_property_array, 6);
}

static void ble_property_t_str_array_set(const char *val, int len, int index)
{
	ble_qiot_log_d("set id t_str_array string value %s", val);
	return;
}

static const char *ble_property_t_str_array_get(int index)
{
	const char *tmp_str = "ticos";
	ble_qiot_log_d("get id t_str_array string value %s", tmp_str);
	return tmp_str;
}

ble_property_t sg_ble_property_array[12] = {
	{ble_property_t_bool_set, ble_property_t_bool_get, 0, BLE_QIOT_DATA_TYPE_BOOL, 1},
	{ble_property_t_int_set, ble_property_t_int_get, 0, BLE_QIOT_DATA_TYPE_INT, 1},
	{ble_property_t_str_set, ble_property_t_str_get, 0, BLE_QIOT_DATA_TYPE_STRING, 1},
	{ble_property_t_float_set, ble_property_t_float_get, 0, BLE_QIOT_DATA_TYPE_FLOAT, 1},
	{ble_property_t_enum_set, ble_property_t_enum_get, 0, BLE_QIOT_DATA_TYPE_ENUM, 1},
	{ble_property_t_time_set, ble_property_t_time_get, 0, BLE_QIOT_DATA_TYPE_TIME, 1},
	{ble_property_t_struct_set, ble_property_t_struct_get, 0, BLE_QIOT_DATA_TYPE_STRUCT, 1},
	{ble_property_t_struct2_set, ble_property_t_struct2_get, 0, BLE_QIOT_DATA_TYPE_STRUCT, 1},
	{(property_set_cb)ble_property_t_int_array_set, (property_get_cb)ble_property_t_int_array_get, 0, BLE_QIOT_DATA_TYPE_ARRAY|BLE_QIOT_ARRAY_INT_BIT_MASK, BLE_QIOT_PROPERTY_T_INT_ARRAY_SIZE_MAX},
	{(property_set_cb)ble_property_t_flot_array_set, (property_get_cb)ble_property_t_flot_array_get, 0, BLE_QIOT_DATA_TYPE_ARRAY|BLE_QIOT_ARRAY_FLOAT_BIT_MASK, BLE_QIOT_PROPERTY_T_FLOT_ARRAY_SIZE_MAX},
	{(property_set_cb)ble_property_t_struct_array_set, (property_get_cb)ble_property_t_struct_array_get, 0, BLE_QIOT_DATA_TYPE_ARRAY|BLE_QIOT_ARRAY_STRUCT_BIT_MASK, BLE_QIOT_PROPERTY_T_STRUCT_ARRAY_SIZE_MAX},
	{(property_set_cb)ble_property_t_str_array_set, (property_get_cb)ble_property_t_str_array_get, 0, BLE_QIOT_DATA_TYPE_ARRAY|BLE_QIOT_ARRAY_STRING_BIT_MASK, BLE_QIOT_PROPERTY_T_STR_ARRAY_SIZE_MAX},
};


static int ble_event_get_t_event_t_bool_get()
{
	uint8_t tmp_bool = 1;
	ble_qiot_log_d("get id t_bool bool value %02x", tmp_bool);
	return tmp_bool;
}

static int ble_event_get_t_event_t_int_get()
{
	uint32_t tmp_int = 1;
	ble_qiot_log_d("get id t_int int value %d", tmp_int);
	return tmp_int;
}

static int ble_event_get_t_event_t_str_get()
{
	const char *tmp_str = "ticos";
	ble_qiot_log_d("get id t_str string value %s", tmp_str);
	return tmp_str;
}

static int ble_event_get_t_event_t_enum_get()
{
	uint16_t tmp_enum = 0;
	ble_qiot_log_d("get id t_enum int value %d", tmp_enum);
	return tmp_enum;
}

static int ble_event_get_t_event_t_float_get()
{
	float tmp_float = 1.23456;
	ble_qiot_log_d("get id t_float float value %f", tmp_float);
	return tmp_float;
}

static int ble_event_get_t_event_t_time_get()
{
	uint32_t tmp_time = 12345678;
	ble_qiot_log_d("get id t_time time value %d", tmp_time);
	return tmp_time;
}

static ble_event_param sg_ble_event_t_event_array[6] = {
	{ble_event_get_t_event_t_bool_get, BLE_QIOT_DATA_TYPE_BOOL},
	{ble_event_get_t_event_t_int_get, BLE_QIOT_DATA_TYPE_INT},
	{ble_event_get_t_event_t_str_get, BLE_QIOT_DATA_TYPE_STRING},
	{ble_event_get_t_event_t_enum_get, BLE_QIOT_DATA_TYPE_ENUM},
	{ble_event_get_t_event_t_float_get, BLE_QIOT_DATA_TYPE_FLOAT},
	{ble_event_get_t_event_t_time_get, BLE_QIOT_DATA_TYPE_TIME},
};

ble_event_t sg_ble_event_array[1] = {
	{sg_ble_event_t_event_array, 6},
};


static int ble_action_handle_t_action_input_cb(e_ble_tlv *input_param_array, uint8_t input_array_size,uint8_t *output_id_array)
{
	int i = 0;
	for(i = 0; i < input_array_size; i++){
		//handle the data of input_param_array[i], set output_id_array value if triggered, the value of the output id obtained follow
	}
	return 0;
}

static int ble_action_handle_t_action_output_cb(uint8_t output_id, char *buf, uint16_t buf_len)
{
	//get value of the output id, return actual length
	return 0;
}

static uint8_t sg_ble_action_t_action_input_type_array[6] = {
	BLE_QIOT_DATA_TYPE_BOOL,
	BLE_QIOT_DATA_TYPE_INT,
	BLE_QIOT_DATA_TYPE_STRING,
	BLE_QIOT_DATA_TYPE_FLOAT,
	BLE_QIOT_DATA_TYPE_ENUM,
	BLE_QIOT_DATA_TYPE_TIME,
};

static uint8_t sg_ble_action_t_action_output_type_array[6] = {
	BLE_QIOT_DATA_TYPE_BOOL,
	BLE_QIOT_DATA_TYPE_INT,
	BLE_QIOT_DATA_TYPE_STRING,
	BLE_QIOT_DATA_TYPE_FLOAT,
	BLE_QIOT_DATA_TYPE_ENUM,
	BLE_QIOT_DATA_TYPE_TIME,
};

ble_action_t sg_ble_action_array[1] = {
	{ble_action_handle_t_action_input_cb, ble_action_handle_t_action_output_cb,sg_ble_action_t_action_input_type_array, sg_ble_action_t_action_output_type_array,6,6},
};

#ifdef __cplusplus
}
#endif
