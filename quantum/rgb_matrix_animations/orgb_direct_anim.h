#ifdef ORGB_ENABLE
RGB_MATRIX_EFFECT(ORGB_DIRECT)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool ORGB_DIRECT(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, g_orgb_direct_mode_colors[i].r, g_orgb_direct_mode_colors[i].g, g_orgb_direct_mode_colors[i].b);
    }
    return led_max < DRIVER_LED_TOTAL;
}
#    endif
#endif
