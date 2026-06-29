// Copyright 2024 Lars Johansson (github.com/swedishlars)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"


// caps lock led index
#define CAPS_LED_INDEX 30

// caps word led index
#define LSHIFT_LED_INDEX 44
#define RSHIFT_LED_INDEX 56

// NOTE colors set to max value 255 will crash controller.
// 150 seem to be max safe value.
#define LED_MAX 10

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

void set_led_color( uint8_t index, HSVB hsvb, bool use_matrix_value);
void set_layer_color( uint8_t layer);

void set_caps_led(void);
void set_caps_word_led(void);
