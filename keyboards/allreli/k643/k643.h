/*
Copyright 2017 Balz Guenat <balz.guenat@gmail.com>

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
*/

#pragma once

#include "quantum.h"

#define ______ KC_TRNS

/* ,---.   ,---------------. ,---------------. ,---------------. ,-----------.
 * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau|
 * `---'   `---------------' `---------------' `---------------' `-----------'
 * ,-----------------------------------------------------------. ,-----------. ,---------------.
 * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|    Bsp| |Ins|Hom|PgU| |NmL|  /|  *|  -|
 * |-----------------------------------------------------------| |-----------| |---------------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  | |Del|End|PgD| |  7|  8|  9|  +|
 * |-----------------------------------------------------------| `-----------' |-----------|   |
 * |CapsL |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  Return|               |  4|  5|  6|  +|
 * |-----------------------------------------------------------|     ,---.     |---------------|
 * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shift     |     |Up |     |  1|  2|  3|   |
 * |-----------------------------------------------------------| ,-----------. |-----------|   |
 * |Ctl|Gui|Alt|           Space               |Alt|Gui|App|Ctl| |Lef|Dow|Rig| |      0|  .|Ent|
 * `-----------------------------------------------------------' `-----------' `---------------'
 */
#define LAYOUT_ansi( \
    K29,K3A,K3B,K3C,K3D,K3E,K3F,K40,K41,K42,K43,K44,K45,      K46,K47,K48,                   \
    K35,K1E,K1F,K20,K21,K22,K23,K24,K25,K26,K27,K2D,K2E,K2A,  K49,K4A,K4B,  K53,K54,K55,K56, \
    K2B,K14,K1A,K08,K15,K17,K1C,K18,K0C,K12,K13,K2F,K30,K31,  K4C,K4D,K4E,  K5F,K60,K61,     \
    K39,K04,K16,K07,K09,K0A,K0B,K0D,K0E,K0F,K33,K34,    K28,                K5C,K5D,K5E,K57, \
    KE1,K1D,K1B,K06,K19,K05,K11,K10,K36,K37,K38,        KE5,      K52,      K59,K5A,K5B,     \
    KE0,KE3,KE2,        K2C,                KE6,KE7,K65,KE4,  K50,K51,K4F,  K62,    K63,K58  \
) LAYOUT_all( \
                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                                                                \
    K29,          K3A,   K3B,   K3C,   K3D,   K3E,   K3F,   K40,   K41,   K42,   K43,   K44,   K45,             K46,   K47,   K48,      KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO,        \
    K35,   K1E,   K1F,   K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K2D,   K2E,   KC_NO, K2A,      K49,   K4A,   K4B,      K53,   K54,   K55,   K56,      KC_NO, KC_NO, \
    K2B,   K14,   K1A,   K08,   K15,   K17,   K1C,   K18,   K0C,   K12,   K13,   K2F,   K30,          K31,      K4C,   K4D,   K4E,      K5F,   K60,   K61,   K57,      KC_NO, KC_NO, \
    K39,   K04,   K16,   K07,   K09,   K0A,   K0B,   K0D,   K0E,   K0F,   K33,   K34,          KC_NO, K28,                              K5C,   K5D,   K5E,   KC_NO,    KC_NO, KC_NO, \
    KE1,   KC_NO, K1D,   K1B,   K06,   K19,   K05,   K11,   K10,   K36,   K37,   K38,          KC_NO, KE5,             K52,             K59,   K5A,   K5B,   KC_NO,    KC_NO, KC_NO, \
    KE0,   KE3,   KE2,   KC_NO, KC_NO,        K2C,          KC_NO, KC_NO, KC_NO, KE6,   KE7,   K65,   KE4,      K50,   K51,   K4F,      K62,          K63,   K58,      KC_NO, KC_NO  \
)

#define XXXX KC_NO

/* ,---.   ,---------------. ,---------------. ,---------------. ,-----------.
 * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau|
 * `---'   `---------------' `---------------' `---------------' `-----------'
 * ,-----------------------------------------------------------. ,-----------. ,---------------.
 * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|    Bsp| |Ins|Hom|PgU| |NmL|  /|  *|  -|
 * |-----------------------------------------------------------| |-----------| |---------------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]| Retn| |Del|End|PgD| |  7|  8|  9|  +|
 * |------------------------------------------------------`    | `-----------' |-----------|   |
 * |CapsL |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  :|  #|    |               |  4|  5|  6|   |
 * |-----------------------------------------------------------|     ,---.     |---------------|
 * |Shft|  <|  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shift     |     |Up |     |  1|  2|  3|Ent|
 * |-----------------------------------------------------------| ,-----------. |-----------|   |
 * |Ctl|Gui|Alt|           Space               |Alt|Gui|App|Ctl| |Lef|Dow|Rig| |      0|  .|   |
 * `-----------------------------------------------------------' `-----------' `---------------'
 */
#define LAYOUT_iso( \
    K000,       K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K014, K015, K016,                         \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K115, K116, K117, K118, K119, K120, \
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K313, K214, K215, K216, K217, K218, K219, K220, \
    K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K213,                         K317, K318, K319,       \
    K400, K401, K402, K403, K404, K405, K406, K407, K408, K409, K410, K411,       K413,       K415,       K417, K418, K419, K420, \
    K500, K501, K502,                   K503,                   K504, K505, K506, K508, K514, K515, K516,       K518, K519        \
) \
{ \
    {K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, XXXX, K014, K015, K016, XXXX, XXXX, XXXX, XXXX}, \
    {K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K115, K116, K117, K118, K119, K120}, \
    {K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214, K215, K216, K217, K218, K219, K220}, \
    {K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, XXXX, K313, XXXX, XXXX, XXXX, K317, K318, K319, XXXX}, \
    {K400, K401, K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, XXXX, K413, XXXX, K415, XXXX, K417, K418, K419, K420}, \
    {K500, K501, K502, K503, K504, K505, K506, XXXX, K508, XXXX, XXXX, XXXX, XXXX, XXXX, K514, K515, K516, XXXX, K518, K519, XXXX}  \
}

