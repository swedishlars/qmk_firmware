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

// TODO remove AZU, too similar to BLU
#define L_DAZU { 150, 255, LED_MAX, 0 }
#define L_BAZU { 150, 255, LED_MAX, 40 }

#define L_DBLU { 169, 255, LED_MAX, 0 }
#define L_LBLU { 158, 255, LED_MAX, 0 }
#define L_BBLU { 169, 255, LED_MAX, 42 }

#define L_DVIO { 180, 255, LED_MAX, 0 }
#define L_BVIO { 180, 255, LED_MAX, 44 }

// TODO remove MAG, too similar to RED
#define L_DMAG { 201, 255, LED_MAX, 0 }
#define L_BMAG { 201, 255, LED_MAX, 46 }

// TODO remove ROS, too similar to RED
#define L_DROS { 253, 255, LED_MAX, 0 }
#define L_BROS { 222, 255, LED_MAX, 48 }
#define L__OFF { 0, 0, 0, 0 }

// TODO maybe define common color rows for my led maps, similar to this:
/* #define NUM_KEYS {KC_0, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9} */

// Use keyboard current brighness when setting LED HSV value.
#define USE_RGB_MATRIX_VALUE_ON true

// Override keyboard current brighness when setting LED HSV value.
#define USE_RGB_MATRIX_VALUE_OFF false

// RGB HSV + breathe cycle time
/* typedef struct _HSVB HSVB; */
/* typedef struct PACKED HSVB; */
typedef struct PACKED {
    uint8_t h;
    uint8_t s;
    uint8_t v;
    uint8_t b;
} HSVB;

// TODO use RGB_MATRIX_MAX_LED_COUNT
// TODO can I define array index order in struct?
/* typedef struct PACKED led_color_t; */
typedef struct PACKED {
    HSVB    hsvb[58];
} led_color_t;

extern const led_color_t PROGMEM ledcolors[];

extern const uint8_t PROGMEM rgb_matrix_index[]; 

void set_led_color( uint8_t index, HSVB hsvb, bool use_matrix_value); 
void set_caps_led_color(void);
void set_layer_color( uint8_t layer, uint8_t index, uint16_t keycode);
