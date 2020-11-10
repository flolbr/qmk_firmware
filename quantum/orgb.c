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

#ifndef RAW_ENABLE
#    error "RAW_ENABLE is not enabled"
#endif

#include "quantum.h"

#include "orgb.h"

#include "raw_hid.h"
#include "version.h"
#include "string.h"
#include <color.h>

uint8_t raw_hid_buffer[RAW_EPSIZE];

void raw_hid_receive(uint8_t *data, uint8_t length)
{
    // Clear the HID buffer
    memset(raw_hid_buffer, 0, RAW_EPSIZE);

    switch (*data) 
    {
        case ORGB_SET_SINGLE_LED:
            orgb_set_single_led(data);
            break;
        case ORGB_SET_LEDS:
            orgb_set_leds(data);
            break;
        case ORGB_SET_MODE:
            orgb_set_mode(data);
            break;
        case ORGB_SET_MODE_AND_SPEED:
            orgb_set_mode_and_speed(data);
            break;
        case ORGB_SET_COLOR_MODE_AND_SPEED:
            orgb_set_color_mode_and_speed(data);
            break;
        case ORGB_GET_QMK_VERSION:
            orgb_get_qmk_version();
            break;
        case ORGB_GET_DEVICE_NAME:
            orgb_get_device_name();
            break;
        case ORGB_GET_ZONES_COUNT:
            orgb_get_zones_count();
            break;
        case ORGB_GET_ZONE_NAME:
            orgb_get_zone_name(data);
            break;
        case ORGB_GET_ZONE_TYPE:
            orgb_get_zone_type(data);
            break;
        case ORGB_GET_ZONE_SIZE:
            orgb_get_zone_size(data);
            break;
        case ORGB_GET_LED_NAME:
            orgb_get_led_name(data);
            break;
        case ORGB_GET_LED_MATRIX_COLUMNS:
            orgb_get_led_matrix_columns();
            break;
        case ORGB_GET_LED_MATRIX_ROWS:
            orgb_get_led_matrix_rows();
            break;
        case ORGB_GET_LED_VALUE_IN_MATRIX:
            orgb_get_led_value_in_matrix(data);
            break;
        case ORGB_GET_LED_COLOR:
            orgb_get_led_color(data);
            break;
        case ORGB_GET_HSV:
            orgb_get_hsv();
            break;
    }

    raw_hid_send(raw_hid_buffer, RAW_EPSIZE);
}

// Controls RGB
void orgb_set_single_led(uint8_t *data)
{
    const uint8_t led = data[1];
    const uint8_t r = data[2];
    const uint8_t g = data[3];
    const uint8_t b = data[4];

    if(led >= DRIVER_LED_TOTAL || r > 255 || g > 255 || b > 255)
    {
        raw_hid_buffer[1] = ORGB_FAILURE;
        raw_hid_buffer[2] = ORGB_EOM;
        return;
    }

    g_rgb_matrix_hid_direct_mode_colors[led].r = r;
    g_rgb_matrix_hid_direct_mode_colors[led].g = g;
    g_rgb_matrix_hid_direct_mode_colors[led].b = b;
    
    raw_hid_buffer[1] = ORGB_SUCCESS;
    raw_hid_buffer[2] = ORGB_EOM;
}
void orgb_set_leds(uint8_t *data)
{
    const uint8_t first_led = data[1];
    const uint8_t number_leds = data[2];

    if(first_led + number_leds > DRIVER_LED_TOTAL)
    {
        raw_hid_buffer[1] = ORGB_FAILURE;
        raw_hid_buffer[2] = ORGB_EOM;
        return;
    }
 
    uint8_t i = 0;
    while (i < number_leds && first_led + i < DRIVER_LED_TOTAL && i * 3 + 5 < RAW_EPSIZE) 
    {
        const uint8_t r = data[3 + i * 3 + 0];
        const uint8_t g = data[3 + i * 3 + 1];
        const uint8_t b = data[3 + i * 3 + 2];

        if(r > 255 || g > 255 || b > 255)
        {
            raw_hid_buffer[1] = ORGB_FAILURE;
            raw_hid_buffer[2] = ORGB_EOM;
            continue;
        }

        g_rgb_matrix_hid_direct_mode_colors[first_led + i].r = r;
        g_rgb_matrix_hid_direct_mode_colors[first_led + i].g = g;
        g_rgb_matrix_hid_direct_mode_colors[first_led + i].b = b;
        i++;
    }

    raw_hid_buffer[1] = ORGB_SUCCESS;
    raw_hid_buffer[2] = ORGB_EOM;
}

void orgb_set_mode(uint8_t *data)
{
    const bool should_save_to_eeprom = data[1] == RAW_HID_EEPROM_SAVE;
    const uint8_t mode = data[2];
    if (mode >= RGB_MATRIX_EFFECT_MAX) 
    {
        raw_hid_buffer[1] = ORGB_FAILURE;
        raw_hid_buffer[2] = ORGB_EOM;
        return;
    }

    if(should_save_to_eeprom) rgb_matrix_mode(mode);
    else rgb_matrix_mode_noeeprom(mode);

    raw_hid_buffer[1] = ORGB_SUCCESS;
    raw_hid_buffer[2] = ORGB_EOM;
}
void orgb_set_mode_and_speed(uint8_t *data)
{
    const bool should_save_to_eeprom = data[1] == RAW_HID_EEPROM_SAVE;
    const uint8_t mode = data[2];
    const uint8_t speed = data[3];

    if (mode > RGB_MATRIX_EFFECT_MAX || speed > 255) 
    {
        raw_hid_buffer[1] = ORGB_FAILURE;
        raw_hid_buffer[2] = ORGB_EOM;
        return;
    }

    if(should_save_to_eeprom) 
    {
        rgb_matrix_mode(mode);
        //rgb_matrix_set_speed(speed);
    }
    else 
    {        
        rgb_matrix_mode_noeeprom(mode);
        //rgb_matrix_set_speed_noeeprom(speed);
    }

    raw_hid_buffer[1] = ORGB_SUCCESS;
    raw_hid_buffer[2] = ORGB_EOM;
}
void orgb_set_color_mode_and_speed(uint8_t *data)
{
    const bool should_save_to_eeprom = data[1] == RAW_HID_EEPROM_SAVE;
    const uint8_t h = data[2];
    const uint8_t s = data[3];
    const uint8_t v = data[4];
    const uint8_t mode = data[5];
    const uint8_t speed = data[6];

    if (h > 255 || s > 255 || v > 255 || mode > RGB_MATRIX_EFFECT_MAX || speed > 255) 
    {
        raw_hid_buffer[1] = ORGB_FAILURE;
        raw_hid_buffer[2] = ORGB_EOM;
        return;
    }

    if(should_save_to_eeprom) 
    {
        rgb_matrix_sethsv(h, s, v);
        rgb_matrix_mode(mode);
        //rgb_matrix_set_speed(speed);
    }
    else 
    {
        rgb_matrix_sethsv_noeeprom(h, s, v);
        rgb_matrix_mode_noeeprom(mode);
        //rgb_matrix_set_speed_noeeprom(speed);
    }

    raw_hid_buffer[1] = ORGB_SUCCESS;
    raw_hid_buffer[2] = ORGB_EOM;
}

// Send info to OpenRGB
void orgb_get_qmk_version(void)
{
    const char *qmk_version = QMK_VERSION;
    uint8_t i = 0;
    while (qmk_version[i] != 0 && i + 2 < RAW_EPSIZE) 
    {
        raw_hid_buffer[i + 1] = qmk_version[i];
        i++;
    }
    raw_hid_buffer[i + 1] = ORGB_EOM;
}
void orgb_get_device_name(void)
{
    memcpy(&raw_hid_buffer[1], MANUFACTURER, strlen(MANUFACTURER));
    memcpy(&raw_hid_buffer[1 + strlen(MANUFACTURER)], " ", 1);
    memcpy(&raw_hid_buffer[2 + strlen(MANUFACTURER)], PRODUCT, strlen(PRODUCT));
    raw_hid_buffer[2 + strlen(MANUFACTURER) + strlen(PRODUCT)] = ORGB_EOM;
}
void orgb_get_zones_count(void)
{
    raw_hid_buffer[1] = ZONES_COUNT;
    raw_hid_buffer[2] = ORGB_EOM;
}
void orgb_get_zone_name(uint8_t *data)
{  
    const uint8_t zone = data[1];

    if(zone >= ZONES_COUNT)
    {
        raw_hid_buffer[1] = ORGB_FAILURE;
        raw_hid_buffer[2] = ORGB_EOM;
        return;
    }
    
    const char *zone_name = g_led_matrix_config.zone_names[zone];
    uint8_t i = 0;
    while (zone_name[i] != 0 && i + 2 < RAW_EPSIZE) 
    {
        raw_hid_buffer[i + 1] = zone_name[i];
        i++;
    }
    raw_hid_buffer[i + 1] = ORGB_EOM;
}
void orgb_get_zone_type(uint8_t *data)
{
    const uint8_t zone = data[1];

    if(zone >= ZONES_COUNT)
    {
        raw_hid_buffer[1] = ORGB_FAILURE;
        raw_hid_buffer[2] = ORGB_EOM;
        return;
    }

    raw_hid_buffer[1] = g_led_matrix_config.zone_types[zone];
    raw_hid_buffer[2] = ORGB_EOM;
}
void orgb_get_zone_size(uint8_t *data)
{
    const uint8_t zone = data[1];

    if(zone >= ZONES_COUNT)
    {
        raw_hid_buffer[1] = ORGB_FAILURE;
        raw_hid_buffer[2] = ORGB_EOM;
        return;
    }

    raw_hid_buffer[1] = g_led_matrix_config.zone_sizes[zone];
    raw_hid_buffer[2] = ORGB_EOM;
}
void orgb_get_led_name(uint8_t *data)
{  
    const uint8_t led = data[1];

    if(led >= DRIVER_LED_TOTAL)
    {
        raw_hid_buffer[1] = ORGB_FAILURE;
        raw_hid_buffer[2] = ORGB_EOM;
        return;
    }

    const char *led_name = g_led_matrix_config.led_names[led];
    uint8_t i = 0;
    while (led_name[i] != 0 && i + 2 < RAW_EPSIZE) 
    {
        raw_hid_buffer[i + 1] = led_name[i];
        i++;
    }
    raw_hid_buffer[i + 1] = ORGB_EOM;
}
void orgb_get_led_matrix_columns(void)
{
    raw_hid_buffer[1] = LED_MATRIX_COLUMNS;
    raw_hid_buffer[2] = ORGB_EOM;
}
void orgb_get_led_matrix_rows(void)
{
    raw_hid_buffer[1] = LED_MATRIX_ROWS;
    raw_hid_buffer[2] = ORGB_EOM;
}
void orgb_get_led_value_in_matrix(uint8_t *data)
{
    const uint8_t column = data[1];
    const uint8_t row = data[2];

    if(column >= LED_MATRIX_COLUMNS || row >= LED_MATRIX_ROWS)
    {
        raw_hid_buffer[1] = ORGB_FAILURE;
        raw_hid_buffer[2] = ORGB_EOM;
        return;
    }

    raw_hid_buffer[1] = g_led_matrix_config.led_matrix_map[column][row];
    raw_hid_buffer[2] = ORGB_EOM;
}
void orgb_get_led_color(uint8_t *data)
{
    const uint8_t led = data[1];

    if(led >= DRIVER_LED_TOTAL)
    {
        raw_hid_buffer[1] = ORGB_FAILURE;
        raw_hid_buffer[2] = ORGB_EOM;
        return;
    }

    raw_hid_buffer[1] = g_rgb_matrix_hid_direct_mode_colors[led].r;
    raw_hid_buffer[2] = g_rgb_matrix_hid_direct_mode_colors[led].g;
    raw_hid_buffer[3] = g_rgb_matrix_hid_direct_mode_colors[led].b;
    raw_hid_buffer[4] = ORGB_EOM;
}
void orgb_get_hsv(void)
{
    //HSV hsv_color = rgb_matrix_get_hsv();
    //raw_hid_buffer[1] = hsv_color.h;
    //raw_hid_buffer[2] = hsv_color.s;
    //raw_hid_buffer[3] = hsv_color.v;
    raw_hid_buffer[4] = ORGB_EOM;
}