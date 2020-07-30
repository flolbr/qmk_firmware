/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Ported to QMK by Stephen Peery <https://github.com/smp4488/>
*/

#include <stdint.h>
#include <stdbool.h>
#include <SN32F240B.h>
#include "ch.h"
#include "hal.h"
#include "CT16.h"

#include "wait.h"
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "quantum.h"

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
static const pin_t led_row_pins[LED_MATRIX_ROWS] = LED_MATRIX_ROW_PINS;

matrix_row_t raw_matrix[MATRIX_ROWS]; //raw values
matrix_row_t last_matrix[MATRIX_ROWS] = {0};  // raw values
matrix_row_t matrix[MATRIX_ROWS]; //debounced values

static bool matrix_changed = false;
static uint8_t current_row = 0;

extern volatile LED_TYPE led_state[DRIVER_LED_TOTAL];

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

inline matrix_row_t matrix_get_row(uint8_t row) { return matrix[row]; }

void matrix_print(void) {}

static void init_pins(void) {

    //  Unselect ROWs
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        setPinInput(row_pins[x]);
        writePinHigh(row_pins[x]);
    }

    // Unselect COLs
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        setPinOutput(col_pins[x]);
        writePinHigh(col_pins[x]);
    }

   for (uint8_t x = 0; x < LED_MATRIX_ROWS; x++) {
        setPinOutput(led_row_pins[x]);
        writePinHigh(led_row_pins[x]);
   }
}

void matrix_init(void) {
    // initialize key pins
    init_pins();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i]     = 0;
    }

    debounce_init(MATRIX_ROWS);

    matrix_init_quantum();

    // Enable Timer Clock
    SN_SYS1->AHBCLKEN_b.CT16B1CLKEN = 1;

    // PFPA - Map all PWM outputs to their PWM A pins
    SN_PFPA->CT16B1 = 0x00000000;

    // Enable PWM function, IOs and select the PWM modes
    // Enable PWM0-PWM3, PWM8-PWM20 function (except PWM10)
    SN_CT16B1->PWMENB   =   (mskCT16_PWM0EN_EN  \
                            |mskCT16_PWM1EN_EN  \
                            |mskCT16_PWM2EN_EN  \
                            |mskCT16_PWM3EN_EN  \
                            |mskCT16_PWM4EN_EN  \
                            |mskCT16_PWM5EN_EN  \
                            |mskCT16_PWM6EN_EN  \
                            |mskCT16_PWM7EN_EN  \
                            |mskCT16_PWM8EN_EN  \
                            |mskCT16_PWM9EN_EN  \
                            |mskCT16_PWM10EN_EN \
                            |mskCT16_PWM11EN_EN \
                            |mskCT16_PWM12EN_EN \
                            |mskCT16_PWM13EN_EN \
                            |mskCT16_PWM14EN_EN \
                            |mskCT16_PWM16EN_EN \
                            |mskCT16_PWM17EN_EN \
                            |mskCT16_PWM18EN_EN \
                            |mskCT16_PWM19EN_EN \
                            |mskCT16_PWM20EN_EN \
                            |mskCT16_PWM21EN_EN);

    // Enable PWM0-PWM3, PWM8-PWM20 IO (except PWM10)
    SN_CT16B1->PWMIOENB =   (mskCT16_PWM0EN_EN  \
                            |mskCT16_PWM1EN_EN  \
                            |mskCT16_PWM2EN_EN  \
                            |mskCT16_PWM3EN_EN  \
                            |mskCT16_PWM4EN_EN  \
                            |mskCT16_PWM5EN_EN  \
                            |mskCT16_PWM6EN_EN  \
                            |mskCT16_PWM7EN_EN  \
                            |mskCT16_PWM8EN_EN  \
                            |mskCT16_PWM9EN_EN  \
                            |mskCT16_PWM10EN_EN \
                            |mskCT16_PWM11EN_EN \
                            |mskCT16_PWM12EN_EN \
                            |mskCT16_PWM13EN_EN \
                            |mskCT16_PWM14EN_EN \
                            |mskCT16_PWM16EN_EN \
                            |mskCT16_PWM17EN_EN \
                            |mskCT16_PWM18EN_EN \
                            |mskCT16_PWM19EN_EN \
                            |mskCT16_PWM20EN_EN \
                            |mskCT16_PWM21EN_EN);

    // Select as PWM mode 2 PWM0-PWM3 PWM8-PWM20 (except PWM10)
    SN_CT16B1->PWMCTRL =    (mskCT16_PWM0EN_EN  \
                            |mskCT16_PWM1EN_EN  \
                            |mskCT16_PWM2EN_EN  \
                            |mskCT16_PWM3EN_EN  \
                            |mskCT16_PWM4EN_EN  \
                            |mskCT16_PWM5EN_EN  \
                            |mskCT16_PWM6EN_EN  \
                            |mskCT16_PWM7EN_EN  \
                            |mskCT16_PWM8EN_EN  \
                            |mskCT16_PWM9EN_EN  \
                            |mskCT16_PWM10EN_EN \
                            |mskCT16_PWM11EN_EN \
                            |mskCT16_PWM12EN_EN \
                            |mskCT16_PWM13EN_EN \
                            |mskCT16_PWM14EN_EN);

    SN_CT16B1->PWMCTRL2 =   (mskCT16_PWM16EN_EN \
                            |mskCT16_PWM17EN_EN \
                            |mskCT16_PWM18EN_EN \
                            |mskCT16_PWM19EN_EN \
                            |mskCT16_PWM20EN_EN \
                            |mskCT16_PWM21EN_EN);

    // Set match interrupts and TC rest
    SN_CT16B1->MCTRL3 = (mskCT16_MR22IE_EN);
    SN_CT16B1->MCTRL3_b.MR22RST = 1;

    // COL match register
    SN_CT16B1->MR22 = 0xFF;

    // Set prescale value
    SN_CT16B1->PRE = 0x24;

    //Set CT16B1 as the up-counting mode.
	SN_CT16B1->TMRCTRL = (mskCT16_CRST);

    // Wait until timer reset done.
    while (SN_CT16B1->TMRCTRL & mskCT16_CRST);

    // Let TC start counting.
    SN_CT16B1->TMRCTRL |= mskCT16_CEN_EN;

    NVIC_ClearPendingIRQ(CT16B1_IRQn);
    nvicEnableVector(CT16B1_IRQn, 4);
}

uint8_t matrix_scan(void) {
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
            // Determine if the matrix changed state
            if ((last_matrix[row_index] != raw_matrix[row_index])) {
                matrix_changed         = true;
                last_matrix[row_index] = raw_matrix[row_index];
            }
        }
    }

    debounce(raw_matrix, matrix, MATRIX_ROWS, matrix_changed);

    matrix_scan_quantum();

    return matrix_changed;
}

/**
 * @brief   MR1 interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(Vector80) {

    OSAL_IRQ_PROLOGUE();

    SN_CT16B1->IC = mskCT16_MR22IC; // Clear match interrupt status

//    // Read the key matrix
//    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
//        // Check row pin state
//        if (readPin(row_pins[row_index]) == 0) {
//            // Pin LO, set col bit
//            raw_matrix[row_index] |= (MATRIX_ROW_SHIFTER << current_col);
//        } else {
//            // Pin HI, clear col bit
//            raw_matrix[row_index] &= ~(MATRIX_ROW_SHIFTER << current_col);
//        }
//    }

    // Turn the selected row off and turn the next row on
    writePinLow(led_row_pins[current_row]);
    current_row = (current_row + 1) % LED_MATRIX_ROWS;
    writePinHigh(led_row_pins[current_row]);

    SN_CT16B1->MR0  = 255;//led_state[(0 * MATRIX_COLS) + current_col].r;
    SN_CT16B1->MR1  = 255;//led_state[(0 * MATRIX_COLS) + current_col].b;
    SN_CT16B1->MR2  = 255;//led_state[(0 * MATRIX_COLS) + current_col].g;
    SN_CT16B1->MR3  = 255;//led_state[(0 * MATRIX_COLS) + current_col].r;
    SN_CT16B1->MR4  = 255;//led_state[(0 * MATRIX_COLS) + current_col].b;
    SN_CT16B1->MR5  = 255;//led_state[(0 * MATRIX_COLS) + current_col].g;
    SN_CT16B1->MR6  = 255;//led_state[(0 * MATRIX_COLS) + current_col].r;
    SN_CT16B1->MR7  = 255;//led_state[(0 * MATRIX_COLS) + current_col].b;
    SN_CT16B1->MR8  = 255;//led_state[(0 * MATRIX_COLS) + current_col].g;
    SN_CT16B1->MR9  = 255;//led_state[(0 * MATRIX_COLS) + current_col].r;
    SN_CT16B1->MR10 = 255;//led_state[(0 * MATRIX_COLS) + current_col].b;
    SN_CT16B1->MR11 = 255;//led_state[(0 * MATRIX_COLS) + current_col].g;
    SN_CT16B1->MR12 = 255;//led_state[(0 * MATRIX_COLS) + current_col].r;
    SN_CT16B1->MR13 = 255;//led_state[(0 * MATRIX_COLS) + current_col].b;
    SN_CT16B1->MR14 = 255;//led_state[(0 * MATRIX_COLS) + current_col].g;
    SN_CT16B1->MR16 = 255;//led_state[(0 * MATRIX_COLS) + current_col].r;
    SN_CT16B1->MR17 = 255;//led_state[(0 * MATRIX_COLS) + current_col].b;
    SN_CT16B1->MR18 = 255;//led_state[(0 * MATRIX_COLS) + current_col].g;
    SN_CT16B1->MR19 = 255;
    SN_CT16B1->MR20 = 255;
    SN_CT16B1->MR21 = 255;

    SN_CT16B1->IC = SN_CT16B1->RIS;  // Clear all for now

    OSAL_IRQ_EPILOGUE();
}
