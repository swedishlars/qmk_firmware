#pragma once

#include "quantum.h"

// NOTE colors set to max value 255 will crash controller.
// 150 seem to be max safe value.
#define LED_MAX 150

// LED colors
// First 3 values are Hue, Saturation, Value (value=brightness).
// Last value sets breathing effect. 0 = no breathing. > 0 sets cycle time
#define L_DRED { 0, 255, LED_MAX, 0 }
#define L_MRED { 254, 240, LED_MAX, 0 }
#define L_LRED { 254, 210, LED_MAX, 0 }
#define L_BRED { 0, 255, LED_MAX, 30 }

#define L_DORA { 6, 255, LED_MAX, 0 }
#define L_LORA { 6, 248, LED_MAX, 0 }
#define L_BORA { 6, 255, LED_MAX, 32 }

#define L_DYEL { 30, 255, LED_MAX, 0 }
#define L_LYEL { 41, 255, LED_MAX, 0 }
#define L_BYEL { 30, 255, LED_MAX, 34 }

#define L_DGRE { 85, 255, LED_MAX, 0 }
#define L_LGRE { 60, 255, LED_MAX, 0 }
#define L_BGRE { 85, 255, LED_MAX, 36 }

#define L_DCYA { 95, 255, LED_MAX, 0 }
#define L_BCYA { 95, 255, LED_MAX, 38 }

#define L_DBLU { 169, 255, LED_MAX, 0 }
#define L_LBLU { 158, 255, LED_MAX, 0 }
#define L_BBLU { 169, 255, LED_MAX, 42 }

#define L_DVIO { 180, 255, LED_MAX, 0 }
#define L_BVIO { 180, 255, LED_MAX, 44 }

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

// array of per key led hsv + breathe cycle time
typedef struct PACKED {
    HSVB    hsvb[RGB_MATRIX_LED_COUNT];
} led_color_t;

// array of per layer and key hsv + breathe cycle time
extern const led_color_t PROGMEM ledcolors[];


// rgb to key index conversion. 
// Array index order represents rgb index.
// value represents key index.
extern const uint8_t PROGMEM rgb_matrix_index[]; 

void set_led_color( uint8_t index, HSVB hsvb, bool use_matrix_value); 
void set_caps_led_color(void);
void set_layer_color( uint8_t layer, uint8_t index, uint16_t keycode);
