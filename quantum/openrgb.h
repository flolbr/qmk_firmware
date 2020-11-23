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

enum openrgb_command_id {
    OPENRGB_EOM,
    OPENRGB_SUCCESS,
    OPENRGB_FAILURE,

    OPENRGB_SET_SINGLE_LED,
    OPENRGB_SET_LEDS,

    OPENRGB_SET_MODE,
    OPENRGB_SET_MODE_AND_SPEED,
    OPENRGB_SET_COLOR_MODE_AND_SPEED,

    OPENRGB_GET_QMK_VERSION,
    OPENRGB_GET_DEVICE_NAME,
    OPENRGB_GET_ZONES_COUNT,
    OPENRGB_GET_ZONE_NAME,
    OPENRGB_GET_ZONE_TYPE,
    OPENRGB_GET_ZONE_SIZE,
    OPENRGB_GET_LED_NAME,
    OPENRGB_GET_LED_MATRIX_COLUMNS,
    OPENRGB_GET_LED_MATRIX_ROWS,
    OPENRGB_GET_LED_VALUE_IN_MATRIX,
    OPENRGB_GET_LED_COLOR,
    OPENRGB_GET_HSV
};

enum openrgb_zone_types { OPENRGB_ZONE_TYPE_SINGLE, OPENRGB_ZONE_TYPE_LINEAR, OPENRGB_ZONE_TYPE_MATRIX };

typedef struct PACKED {
    char    zone_names[OPENRGB_ZONES_COUNT][64];
    uint8_t zone_types[OPENRGB_ZONES_COUNT];
    uint8_t zone_sizes[OPENRGB_ZONES_COUNT];
    uint8_t led_matrix_map[OPENRGB_MATRIX_ROWS][OPENRGB_MATRIX_COLUMNS];
    char    led_names[DRIVER_LED_TOTAL][64];
    bool should_save_to_eeprom;
} openrgb_config_t;

extern const openrgb_config_t g_openrgb_config;
extern RGB              g_openrgb_direct_mode_colors[DRIVER_LED_TOTAL];

// Controls RGB
void openrgb_set_single_led(uint8_t *data);
void openrgb_set_leds(uint8_t *data);
void openrgb_set_mode(uint8_t *data);
void openrgb_set_mode_and_speed(uint8_t *data);
void openrgb_set_color_mode_and_speed(uint8_t *data);

// Send info to OpenRGB
void openrgb_get_qmk_version(void);
void openrgb_get_device_name(void);
void openrgb_get_zones_count(void);
void openrgb_get_zone_name(uint8_t *data);
void openrgb_get_zone_type(uint8_t *data);
void openrgb_get_zone_size(uint8_t *data);
void openrgb_get_led_name(uint8_t *data);
void openrgb_get_led_matrix_columns(void);
void openrgb_get_led_matrix_rows(void);
void openrgb_get_led_value_in_matrix(uint8_t *data);
void openrgb_get_led_color(uint8_t *data);
void openrgb_get_hsv(void);
