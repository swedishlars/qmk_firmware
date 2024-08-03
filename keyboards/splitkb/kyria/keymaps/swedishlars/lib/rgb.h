/* Copyright 2024 Lars Johansson (github.com/swedishlars)
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include "quantum.h"

// Key to rgb matrix index conversion macro.
// This enables per key rgb colour maps to be declared in the same fashion as keymaps
/*
    L_SW06, L_SW05, L_SW04, L_SW03, L_SW02, L_SW01,                                  R_SW01, R_SW02, R_SW03, R_SW04, R_SW05, R_SW06,
    24                                      19                                       50                                      55
    L_SW12, L_SW11, L_SW10, L_SW09, L_SW08, L_SW07,                                  R_SW07, R_SW08, R_SW09, R_SW10, R_SW11, R_SW12,
    18                                      13                                       44                                      49
    L_SW20, L_SW19, L_SW18, L_SW17, L_SW16, L_SW15, L_SW14, L_SW13,  R_SW13, R_SW14, R_SW15, R_SW16, R_SW17, R_SW18, R_SW19, R_SW20,
    12                                                      5        36                                                      43
                            L_SW25, L_SW24, L_SW23, L_SW22, L_SW21,  R_SW21, R_SW22, R_SW23, R_SW24, R_SW25                           
                            4                               0        31                              35                           
    ---------------------------------------------------------------------------------------------------------------------------------
    L_RGB1,         L_RGB2,         L_RGB3,                                                  R_RGB1,         R_RGB2,         R_RGB3,
    25                              27                                                       59                              61
    L_RGB4,         L_RGB5,         L_RGB6,                                                  R_RGB4,         R_RGB5,         R_RGB6
    28                              30                                                       56                              58

*/

#define RGB_MATRIX_LAYOUT( \
    L_SW06, L_SW05, L_SW04, L_SW03, L_SW02, L_SW01,                                  R_SW01, R_SW02, R_SW03, R_SW04, R_SW05, R_SW06, \
    L_SW12, L_SW11, L_SW10, L_SW09, L_SW08, L_SW07,                                  R_SW07, R_SW08, R_SW09, R_SW10, R_SW11, R_SW12, \
    L_SW20, L_SW19, L_SW18, L_SW17, L_SW16, L_SW15, L_SW14, L_SW13,  R_SW13, R_SW14, R_SW15, R_SW16, R_SW17, R_SW18, R_SW19, R_SW20, \
                            L_SW25, L_SW24, L_SW23, L_SW22, L_SW21,  R_SW21, R_SW22, R_SW23, R_SW24, R_SW25,                          \
    L_RGB1,         L_RGB2,         L_RGB3,                                                  R_RGB1,         R_RGB2,         R_RGB3, \
    L_RGB4,         L_RGB5,         L_RGB6,                                                  R_RGB4,         R_RGB5,         R_RGB6  \
) \
{ \
{L_SW21}, {L_SW22}, {L_SW23}, {L_SW24}, {L_SW25}, {L_SW13}, \
{L_SW14}, {L_SW15}, {L_SW16}, {L_SW17}, {L_SW18}, {L_SW19}, \
{L_SW20}, {L_SW07}, {L_SW08}, {L_SW09}, {L_SW10}, {L_SW11}, \
{L_SW12}, {L_SW01}, {L_SW02}, {L_SW03}, {L_SW04}, {L_SW05}, \
{L_SW06},                                                   \
{L_RGB1}, {L_RGB2}, {L_RGB3}, {L_RGB4}, {L_RGB5}, {L_RGB6}, \
{R_SW21}, {R_SW22}, {R_SW23}, {R_SW24}, {R_SW25}, {R_SW13}, \
{R_SW14}, {R_SW15}, {R_SW16}, {R_SW17}, {R_SW18}, {R_SW19}, \
{R_SW20}, {R_SW07}, {R_SW08}, {R_SW09}, {R_SW10}, {R_SW11}, \
{R_SW12}, {R_SW01}, {R_SW02}, {R_SW03}, {R_SW04}, {R_SW05}, \
{R_SW06},                                                   \
{R_RGB1}, {R_RGB2}, {R_RGB3}, {R_RGB4}, {R_RGB5}, {R_RGB6}  \
}


// TODO rm:
    /* L_RGB1,         L_RGB2,         L_RGB3,                                                  R_RGB1,         R_RGB2,         R_RGB3, \ */
    /* L_RGB4,         L_RGB5,         L_RGB6,                                                  R_RGB4,         R_RGB5,         R_RGB6  \ */

/* {L_RGB1}, {L_RGB2}, {L_RGB3}, {L_RGB4}, {L_RGB5}, {L_RGB6}, \ */
/* {R_RGB1}, {R_RGB2}, {R_RGB3}, {R_RGB4}, {R_RGB5}, {R_RGB6}, \ */


// NOTE colors set to max value 255 will crash controller.
// 150 seem to be max safe value.
#define LED_MAX 150

// LED colors
// First 3 values are Hue, Saturation, Value (value=brightness).
// Last value sets breathing effect. 0 = no breathing. > 0 sets cycle time
#define L_DRED { 0, 255, LED_MAX, 0 }
#define L_BRED { 0, 255, LED_MAX, 30 }

// TODO retire, too close:
#define L_MRED { 254, 240, LED_MAX, 0 }

// TODO use L_DROS instead:
#define L_LRED { 254, 210, LED_MAX, 0 }

#define L_DORA { 6, 255, LED_MAX, 0 }
#define L_BORA { 6, 255, LED_MAX, 32 }
#define L_LORA { 6, 248, LED_MAX, 0 }

#define L_DYEL { 30, 255, LED_MAX, 0 }
#define L_BYEL { 30, 255, LED_MAX, 34 }
#define L_LYEL { 41, 255, LED_MAX, 0 }

#define L_DGRE { 85, 255, LED_MAX, 0 }
#define L_LGRE { 60, 255, LED_MAX, 0 }
#define L_BGRE { 85, 255, LED_MAX, 36 }

// TODO cyan too similar to green
#define L_DCYA { 125, 255, LED_MAX, 0 }
#define L_BCYA { 125, 255, LED_MAX, 38 }

#define L_DAZU { 158, 255, LED_MAX, 0 }
#define L_BAZU { 158, 255, LED_MAX, 40 }

#define L_DBLU { 169, 255, LED_MAX, 0 }
#define L_BBLU { 169, 255, LED_MAX, 42 }
// TODO use L_DAZU instead
#define L_LBLU { 158, 255, LED_MAX, 0 }

#define L_DVIO { 180, 255, LED_MAX, 0 }
#define L_BVIO { 180, 255, LED_MAX, 44 }

// TODO use L_DROS instead of L_DLED:
#define L_DROS { 254, 210, LED_MAX, 0 }
#define L_BROS { 254, 210, LED_MAX, 46 }

#define L__OFF { 0, 0, 0, 0 }


// Use keyboard current brighness when setting LED HSV value.
#define USE_RGB_MATRIX_VALUE_ON true

// Override keyboard current brighness when setting LED HSV value.
#define USE_RGB_MATRIX_VALUE_OFF false

// RGB HSV + breathe cycle time
typedef struct PACKED {
    uint8_t h;
    uint8_t s;
    uint8_t v;
    uint8_t b;
} HSVB;

// Per key led hsv + breathe cycle time
typedef struct PACKED {
    HSVB    hsvb;
} led_color_t;

// array of per layer and key hsv + breathe cycle time
// TODO do I need extern?
extern const led_color_t PROGMEM ledmaps[][RGB_MATRIX_LED_COUNT];

// TODO orig:
/* void set_layer_color( uint8_t layer, uint8_t index, uint16_t keycode); */

// This works fine:
void set_layer_color( uint8_t layer, uint8_t led_min, uint8_t led_max);

void set_led_color( uint8_t index, HSVB hsvb, bool use_matrix_value); 
void set_caps_led_color(void);
