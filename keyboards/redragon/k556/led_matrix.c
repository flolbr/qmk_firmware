#include <string.h>
#include "rgb.h"
#include "rgb_matrix.h"
#include "rgb_matrix_types.h"
#include "color.h"

/*
    COLS key / led
    PWM PWM00A - PWM21A (PWM15A unused)
    2ty transistors PNP driven high
    base      - GPIO
    collector - LED Col pins
    emitter   - VDD

    VDD     GPIO
    (E)     (B)
     |  PNP  |
     |_______|
         |
         |
        (C)
        LED

    ROWS RGB
    PWM PWM22A - PWM21B (PWM10B unused)
    C 0-15
    j3y transistors NPN driven low
    base      - GPIO
    collector - LED RGB row pins
    emitter   - GND

        LED
        (C)
         |
         |
      _______
     |  NPN  |
     |       |
    (B)     (E)
    GPIO    GND
*/

LED_TYPE led_state[DRIVER_LED_TOTAL];

void init(void) {}

static void flush(void) {}

void set_color(int index, uint8_t r, uint8_t g, uint8_t b) {
    led_state[index].r = r;
    led_state[index].g = g;
    led_state[index].b = b;
}

static void set_color_all(uint8_t r, uint8_t g, uint8_t b) {
    for (int i=0; i<DRIVER_LED_TOTAL; i++)
        set_color(i, r, g, b);
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init          = init,
    .flush         = flush,
    .set_color     = set_color,
    .set_color_all = set_color_all,
};

// byte order: R,B,G
static uint8_t caps_lock_color[3] = { 0x00, 0x00, 0xFF };

void led_set(uint8_t usb_led) {
    // dk63 has only CAPS indicator
    if (usb_led >> USB_LED_CAPS_LOCK & 1) {
        set_color(11, caps_lock_color[0], caps_lock_color[2], caps_lock_color[1]);
    } else {
        set_color(11, 0x00, 0x00, 0x00);
    }
}

const led_matrix_config_t g_led_matrix_config =
{
    {"Keyboard"},
    {ZONE_TYPE_MATRIX},
    {105},
    {
        { 100,  99,  98,  97,  96,  95,  NO_LED,  94,  NO_LED,  93,  92,  91,  90,  89,  88,  87,  86 },
        { 101,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  85 },
        { 102,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  84 },
        { 103,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  NO_LED,  42,  43,  83 },
        { 104,  44,  NO_LED,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  82 },
        { NO_LED,   58,  59,  60,  NO_LED,  NO_LED,  NO_LED,  61,  NO_LED,  NO_LED,  NO_LED,  62,  63,  64,  65,  66,  NO_LED },
        { 67,   68,  69,  70,  71,  72,  NO_LED,  73,  NO_LED,  74,  75,  76,  77,  78,  79,  80,  81 }
    },
    {
        "Key: Escape",         // 0
        "Key: 1",              // 1
        "Key: 2",              // 2
        "Key: 3",              // 3
        "Key: 4",              // 4
        "Key: 5",              // 5
        "Key: 6",              // 6
        "Key: 7",              // 7
        "Key: 8",              // 8
        "Key: 9",              // 9
        "Key: 0",              // 10
        "Key: -",              // 11
        "Key: =",              // 12
        "Key: Backspace",      // 13
        "Key: Delete",         // 14
        "Key: Tab",            // 15
        "Key: Q",              // 16
        "Key: W",              // 17
        "Key: E",              // 18
        "Key: R",              // 19
        "Key: T",              // 20
        "Key: Y",              // 21
        "Key: U",              // 22
        "Key: I",              // 23
        "Key: O",              // 24
        "Key: P",              // 25
        "Key: [",              // 26
        "Key: ]",              // 27
        "Key: /",              // 28
        "Key: Home",           // 29
        "Key: Caps Lock",      // 30
        "Key: A",              // 31
        "Key: S",              // 32
        "Key: D",              // 33
        "Key: F",              // 34
        "Key: G",              // 35
        "Key: H",              // 36
        "Key: J",              // 37
        "Key: K",              // 38
        "Key: L",              // 39
        "Key: ;",              // 40
        "Key: '",              // 41
        "Key: Enter",          // 42
        "Key: Page Up",        // 43
        "Key: Left Shift",     // 44
        "Key: Z",              // 45
        "Key: X",              // 46
        "Key: C",              // 47
        "Key: V",              // 48
        "Key: B",              // 49
        "Key: N",              // 50
        "Key: M",              // 51
        "Key: ,",              // 52
        "Key: .",              // 53
        "Key: /",              // 54
        "Key: Right Shift",    // 55
        "Key: Up Arrow",       // 56
        "Key: Page Down",      // 57
        "Key: Left Control",   // 58
        "Key: Left Windows",   // 59
        "Key: Left Alt",       // 60
        "Key: Space",          // 61
        "Key: Right Alt",      // 62
        "Key: Right Windows",  // 63
        "Key: Left Arrow",     // 64
        "Key: Down Arrow",     // 65
        "Key: Right Arrow",    // 66
        "Lightbar: 0",         // 67
        "Lightbar: 1",         // 68
        "Lightbar: 2",         // 69
        "Lightbar: 3",         // 70
        "Lightbar: 4",         // 71
        "Lightbar: 5",         // 72
        "Lightbar: 6",         // 73
        "Lightbar: 7",         // 74
        "Lightbar: 8",         // 75
        "Lightbar: 9",         // 76
        "Lightbar: 10",        // 77
        "Lightbar: 11",        // 78
        "Lightbar: 12",        // 79
        "Lightbar: 13",        // 80
        "Lightbar: 14",        // 81
        "Lightbar: 15",        // 82
        "Lightbar: 16",        // 83
        "Lightbar: 17",        // 84
        "Lightbar: 18",        // 85
        "Lightbar: 19",        // 86
        "Lightbar: 20",        // 87
        "Lightbar: 21",        // 88
        "Lightbar: 22",        // 89
        "Lightbar: 23",        // 90
        "Lightbar: 24",        // 91
        "Lightbar: 25",        // 92
        "Lightbar: 26",        // 93
        "Lightbar: 27",        // 94
        "Lightbar: 28",        // 95
        "Lightbar: 29",        // 96
        "Lightbar: 30",        // 97
        "Lightbar: 31",        // 98
        "Lightbar: 32",        // 99
        "Lightbar: 33",        // 100
        "Lightbar: 34",        // 101
        "Lightbar: 35",        // 102
        "Lightbar: 36",        // 103
        "Lightbar: 37",        // 104
    },
};