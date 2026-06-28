/* Copyright 2024 Lars Johansson (github.com/swedishlars)
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "rgb.h"
// include to use layer enums
#include "swedishlars.h"

// LIB USED FOR  LED INDICATOR BREATHING EFFECT
#include "lib/lib8tion/lib8tion.h"


// Per layer, per key rgb maps
const uint8_t PROGMEM ledmaps[][RGB_MATRIX_LED_COUNT][4] = {
[_BASE] = {
    //  ESC       1         2         3         4         5         6         7         8         9         0         -         =         BCKSPC    DEL     0-14 = 15 leds
        S_YELL,   S_ORAN,   S_ORAN,   S_ORAN,   S_ORAN,   S_ORAN,   S_ORAN,   S_ORAN,   S_ORAN,   S_ORAN,   S_ORAN,   S_ORAN,   S_ORAN,   S_YELL,   S_YELL,
    //  TAB       Q         W         E         R         T         Y         U         I         O         P         [         ]         ENTER     INSERT  15-29 = 15 leds
        S_ORAN,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S_YELL,
    //  CAPS      A         S         D         F         G         H         J         K         L         ;         '         #                   PG UP   30-43 = 14 leds
        S_ORAN,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,             S_YELL,
    //  SHIFT     \         Z         X         C         V         B         N         M         ,         .         ?         SHIFT     UP        PG DOWN 44-58 = 15 leds
        S_ORAN,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S_YELL,   S_YELL,
    //  CTRL      FN        ALT                                     SPACE                         ALTGR     FN                  LEFT      DOWN      RIGHT   59-67 = 9 leds
        S_GREN,   S_GREN,   S_GREN,                                 S__RED,                       S_GREN,   S_GREN,             S_YELL,   S_YELL,   S_YELL,
    //  UGLW69              UGLW68                        UGLW67              UGLW66                        UGLW65              UGLW64                      68-73 = 6 leds underglow
        L__OFF,             L__OFF,                       L__OFF,             L__OFF,                       L__OFF,             L__OFF
//),
},

    // FN LAYER
//[_FUNC] = RGB_MATRIX_LAYOUT(
[_FUNC] = {
    //  ESC       1         2         3         4         5         6         7         8         9         0         -         =         BCKSPC    DEL
        B__RED,   S_ORAN,   S_ORAN,   S_ORAN,   S_ORAN,   S__RED,   S__RED,   S__RED,   S__RED,   S_ORAN,   S_ORAN,   S_ORAN,   S_ORAN,   L__OFF,   L__OFF,
    //  TAB       Q         W         E         R         T         Y         U         I         O         P         [         ]         ENTER     INSERT
        L__OFF,   S_VIOL,   L__OFF,   L__OFF,   L__OFF,   S_GREN,   L__OFF,   S_VIOL,   L__OFF,   L__OFF,   S_CYAN,   L__OFF,   L__OFF,   L__OFF,   S_ORAN,
    //  CAPS      A         S         D         F         G         H         J         K         L         ;         '         #                   PG UP
        L__OFF,   L__OFF,   S_CYAN,   S_GREN,   S_VIOL,   L__OFF,   S_ROSE,   S_ROSE,   S_ROSE,   S_ROSE,   L__OFF,   L__OFF,   L__OFF,             L__OFF,
    //  SHIFT     \         Z         X         C         V         B         N         M         ,         .         ?         SHIFT     UP        PG DOWN
        L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   S__RED,   S_VIOL,   S_CYAN,   S_CYAN,   S_CYAN,   L__OFF,   L__OFF,   S_CYAN,   L__OFF,
    //  CTRL      FN        ALT                                     SPACE                         ALTGR     FN                  LEFT      DOWN      RIGHT
        L__OFF,   B__RED,   S_GREN,                                 S__RED,                       L__OFF,   L__OFF,             S_CYAN,   S_CYAN,   S_CYAN,
    //  UGLW69              UGLW68                        UGLW67              UGLW66                        UGLW65              UGLW64
        B__RED,             B__RED,                       B__RED,             B__RED,                       B__RED,             B__RED
},

[_MACRO] = {
    //  ESC       1         2         3         4         5         6         7         8         9         0         -         =         BCKSPC    DEL
        B_BLUE,   B__RED,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   B_CYAN,   B_CYAN,   L__OFF,   L__OFF,
    //  TAB       Q         W         E         R         T         Y         U         I         O         P         [         ]         ENTER     INSERT
        L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   B_BLUE,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,
    //  CAPS      A         S         D         F         G         H         J         K         L         ;         '         #                   PG UP
        L__OFF,   L__OFF,   B_VIOL,   L__OFF,   L__OFF,   L__OFF,   B_VIOL,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,             L__OFF,
    //  SHIFT     \         Z         X         C         V         B         N         M         ,         .         ?         SHIFT     UP        PG DOWN
        L__OFF,   L__OFF,   L__OFF,   B_VIOL,   L__OFF,   L__OFF,   L__OFF,   B_VIOL,   B_BLUE,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   B_SKYB,   L__OFF,
    //  CTRL      FN        ALT                                     SPACE                         ALTGR     FN                  LEFT      DOWN      RIGHT
        L__OFF,   L__OFF,   L__OFF,                                 L__OFF,                       L__OFF,   L__OFF,             B_BLUE,   B_SKYB,   B_BLUE,
    //  UGLW69              UGLW68                        UGLW67              UGLW66                        UGLW65              UGLW64
        B_BLUE,             B_BLUE,                       B_BLUE,             B_BLUE,                       B_BLUE,             B_BLUE
},

[_CONF] = {
    //  ESC       1         2         3         4         5         6         7         8         9         0         -         =         BCKSPC    DEL
        B_YELL,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,
    //  TAB       Q         W         E         R         T         Y         U         I         O         P         [         ]         ENTER     INSERT
        L__OFF,   L__OFF,   L__OFF,   L__OFF,   B_BLUE,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,
    //  CAPS28    A         S         D         F         G         H         J         K         L         ;         '         #                   PG UP
        L__OFF,   L__OFF,   L__OFF,   B_VIOL,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,             L__OFF,
    //  SHIFT     \         Z         X         C         V         B         N         M         ,         .         ?         SHIFT     UP        PG DOWN
        L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   B_BLUE,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,
    //  CTRL      FN        ALT                                     SPACE                         ALTGR     FN                  LEFT      DOWN      RIGHT
        L__OFF,   L__OFF,   L__OFF,                                 L__OFF,                       L__OFF,   L__OFF,             L__OFF,   L__OFF,   L__OFF,
    //  UGLW69              UGLW68                        UGLW67              UGLW66                        UGLW65              UGLW64
        B_YELL,             B_YELL,                       B_YELL,             B_YELL,                       B_YELL,             B_YELL
}
};

// Set LED for caps word
// NOTE caps word state is not synced to slave side, so setting led index on
// slave side will not work
void set_caps_word_led(void) {
    if (is_caps_word_on()) {
        HSVB hsvb = B_GREN;
        set_led_color(LSHIFT_LED_INDEX, hsvb, USE_RGB_MATRIX_VALUE_ON);
        // NOTE so this will not work:
        set_led_color(RSHIFT_LED_INDEX, hsvb, USE_RGB_MATRIX_VALUE_ON);
    }
}


// Set LED for Caps Lock
void set_caps_led(void) {
    if (host_keyboard_led_state().caps_lock) {
        HSVB hsvb = B__RED;
        set_led_color(CAPS_LED_INDEX, hsvb, USE_RGB_MATRIX_VALUE_ON);
    }
}


// SET INDIVIDUAL LED RGB
void set_led_color( uint8_t index, HSVB hsvb, bool use_matrix_value) {
    uint8_t val = hsvb.v;

    // if the brightness of the led is set to 0 in the map, the value is not overriden by matrix effect,
    // allowing the led to appear turned off. Else, set brightness to current rgb matrix value.
    if (val != 0 && use_matrix_value) {
         val = rgb_matrix_get_val();
    }

    // If breathe, set val based on time cycle
    if (hsvb.b > 0) {
        uint16_t time = scale16by8(g_rgb_timer, hsvb.b);
        uint8_t hsv_breathe_val = abs8(sin8(time) - 128) * 2;
        val = scale8(hsv_breathe_val, val);
    }
    
    HSV _hsv = { .h=hsvb.h, .s=hsvb.s, .v = val};
    RGB rgb = hsv_to_rgb( _hsv );
    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
}


// SET LED RGB & BREATHING CYCLE BASED ON LAYER AND KEYCODES
void set_layer_color( uint8_t layer) {
    // By default, use global LED brightness set by user
    bool use_curr_brightness = USE_RGB_MATRIX_VALUE_ON;

    for (uint8_t index = 0; index < RGB_MATRIX_LED_COUNT; index++) {
        HSVB hsvb = {
            .h = pgm_read_byte(&ledmaps[layer][index][0]),
            .s = pgm_read_byte(&ledmaps[layer][index][1]),
            .v = pgm_read_byte(&ledmaps[layer][index][2]),
            .b = pgm_read_byte(&ledmaps[layer][index][3])
        };

        set_led_color(index, hsvb, use_curr_brightness);
    }
}

