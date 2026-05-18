// Copyright 2024 Lars Johansson (github.com/swedishlars)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"


// Key to rgb matrix index conversion macro.
// This enables per key rgb colour maps to be declared in the same fashion as keymaps
#define RGB_MATRIX_LAYOUT( \
    L_SW28, L_SW21, L_SW20, L_SW11, L_SW10, L_SW00,                          R_SW00, R_SW10, R_SW11, R_SW20, R_SW21, R_SW28, \
    L_SW27, L_SW22, L_SW19, L_SW12, L_SW09, L_SW01,                          R_SW01, R_SW09, R_SW12, R_SW19, R_SW22, R_SW27, \
    L_SW26, L_SW23, L_SW18, L_SW13, L_SW08, L_SW02,                          R_SW02, R_SW08, R_SW13, R_SW18, R_SW23, R_SW26, \
    L_SW25, L_SW24, L_SW17, L_SW14, L_SW07, L_SW03,                          R_SW03, R_SW07, R_SW14, R_SW17, R_SW24, R_SW25, \
                    L_SW16, L_SW15, L_SW06, L_SW05, L_SW04,          R_SW04, R_SW05, R_SW06, R_SW15, R_SW16                  \
) \
{ \
{L_SW00}, {L_SW01}, {L_SW02}, {L_SW03}, {L_SW04}, {L_SW05}, \
{L_SW06}, {L_SW07}, {L_SW08}, {L_SW09}, {L_SW10}, {L_SW11}, \
{L_SW12}, {L_SW13}, {L_SW14}, {L_SW15}, {L_SW16}, {L_SW17}, \
{L_SW18}, {L_SW19}, {L_SW20}, {L_SW21}, {L_SW22}, {L_SW23}, \
{L_SW24}, {L_SW25}, {L_SW26}, {L_SW27}, {L_SW28},           \
{R_SW00}, {R_SW01}, {R_SW02}, {R_SW03}, {R_SW04}, {R_SW05}, \
{R_SW06}, {R_SW07}, {R_SW08}, {R_SW09}, {R_SW10}, {R_SW11}, \
{R_SW12}, {R_SW13}, {R_SW14}, {R_SW15}, {R_SW16}, {R_SW17}, \
{R_SW18}, {R_SW19}, {R_SW20}, {R_SW21}, {R_SW22}, {R_SW23}, \
{R_SW24}, {R_SW25}, {R_SW26}, {R_SW27}, {R_SW28}            \
}

// caps lock led index
#define CAPS_LED_INDEX 26

// caps word led index
#define LSHIFT_LED_INDEX 25
#define RSHIFT_LED_INDEX 52

// NOTE colors set to max value 255 will crash controller.
// 150 seem to be max safe value.
#define LED_MAX 150

// LED colors - prefix S_ means solid, B_ means blinking
// First 3 values are Hue, Saturation, Value (value=brightness).
// Last value sets breathing effect. 0 = no breathing. > 0 sets cycle time
// red - default
#define S__RED { 0, 255, LED_MAX, 0 }
#define B__RED { 0, 255, LED_MAX, 30 }

// orange
#define S_ORAN { 7, 248, LED_MAX, 0 }
#define B_ORAN { 7, 248, LED_MAX, 32 }

// yellow
#define S_YELL { 30, 255, LED_MAX, 0 }
#define B_YELL { 30, 255, LED_MAX, 34 }

// lime - light green
#define S_LIME { 65, 255, LED_MAX, 0 }
#define B_LIME { 65, 255, LED_MAX, 35 }

// green
#define S_GREN { 85, 255, LED_MAX, 0 }
#define B_GREN { 85, 255, LED_MAX, 36 }

// cyan
#define S_CYAN { 124, 255, LED_MAX, 0 }
#define B_CYAN { 124, 255, LED_MAX, 38 }

// sky blue
#define S_SKYB { 156, 245, LED_MAX, 0 }
#define B_SKYB { 156, 245, LED_MAX, 40 }

// blue
#define S_BLUE { 169, 255, LED_MAX, 0 }
#define B_BLUE { 169, 255, LED_MAX, 42 }

// violet
#define S_VIOL { 180, 255, LED_MAX, 0 }
#define B_VIOL { 180, 255, LED_MAX, 44 }

// rose
#define S_ROSE { 240, 210, LED_MAX, 0 }
#define B_ROSE { 240, 210, LED_MAX, 46 }

#define S_WHIT { 0, 0, LED_MAX, 0 }
#define B_WHIT { 0, 0, LED_MAX, 50 }

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

void set_led_color( uint8_t index, HSVB hsvb, bool use_matrix_value);
void set_layer_color(uint8_t layer, uint8_t led_min, uint8_t led_max);

void set_caps_led(void);
void set_caps_word_led(void);
