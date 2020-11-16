/* Copyright 2020 Kasper
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

enum orgb_command_id 
{ 
    ORGB_EOM,
    ORGB_SUCCESS,
    ORGB_FAILURE,

    ORGB_SET_SINGLE_LED,
    ORGB_SET_LEDS,

    ORGB_SET_MODE,
    ORGB_SET_MODE_AND_SPEED,
    ORGB_SET_COLOR_MODE_AND_SPEED,

    ORGB_GET_QMK_VERSION,
    ORGB_GET_DEVICE_NAME,
    ORGB_GET_ZONES_COUNT,
    ORGB_GET_ZONE_NAME,
    ORGB_GET_ZONE_TYPE,
    ORGB_GET_ZONE_SIZE,
    ORGB_GET_LED_NAME,
    ORGB_GET_LED_MATRIX_COLUMNS,
    ORGB_GET_LED_MATRIX_ROWS,
    ORGB_GET_LED_VALUE_IN_MATRIX,
    ORGB_GET_LED_COLOR,
    ORGB_GET_HSV
};
enum orgb_eeprom_commands
{
    ORGB_EEPROM_SAVE,
    ORGB_EEPROM_DONT_SAVE
};

enum zone_types 
{
    ZONE_TYPE_SINGLE, 
    ZONE_TYPE_LINEAR, 
    ZONE_TYPE_MATRIX 
};

typedef struct PACKED 
{
    char    zone_names[ORGB_ZONES_COUNT][64];
    uint8_t zone_types[ORGB_ZONES_COUNT];
    uint8_t zone_sizes[ORGB_ZONES_COUNT];
    uint8_t led_matrix_map[ORGB_MATRIX_COLUMNS][ORGB_MATRIX_ROWS];
    char    led_names[DRIVER_LED_TOTAL][64];
} orgb_config_t;

extern orgb_config_t g_orgb_config;
extern RGB g_orgb_direct_mode_colors[DRIVER_LED_TOTAL];

// Controls RGB
void orgb_set_single_led(uint8_t *data);
void orgb_set_leds(uint8_t *data);
void orgb_set_mode(uint8_t *data);
void orgb_set_mode_and_speed(uint8_t *data);
void orgb_set_color_mode_and_speed(uint8_t *data);

// Send info to OpenRGB
void orgb_get_qmk_version(void);
void orgb_get_device_name(void);
void orgb_get_zones_count(void);
void orgb_get_zone_name(uint8_t *data);
void orgb_get_zone_type(uint8_t *data);
void orgb_get_zone_size(uint8_t *data);
void orgb_get_led_name(uint8_t *data);
void orgb_get_led_matrix_columns(void);
void orgb_get_led_matrix_rows(void);
void orgb_get_led_value_in_matrix(uint8_t *data);
void orgb_get_led_color(uint8_t *data);
void orgb_get_hsv(void);