/* Copyright 2024 Lars Johansson (github.com/swedishlars)
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "rgb.h"
// include to use layer enums
#include "swedishlars.h"

// LIB USED FOR  LED INDICATOR BREATHING EFFECT
#include "lib/lib8tion/lib8tion.h"


// Per layer, per key rgb maps
const led_color_t PROGMEM ledmaps[][RGB_MATRIX_LED_COUNT] = {
[_BASE] = RGB_MATRIX_LAYOUT( 
     // .-----------------------------------------------------------.                                              ,-----------------------------------------------------------.
     // |esc      |    Q    |    W    |    E    |    R    |    T    |                                              |    Y    |    U    |    I    |    O    |    P    |backspace|
         S__RED,   S__RED,   S__RED,   S__RED,   S__RED,  S__RED,                                                   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,
     // |---------+---------+---------+---------|---------+---------|                                              |---------+---------|---------|---------|---------+---------|
     // | tab     |    A    |    S    |    D    |    F    |   G     |                                              |    H    |    J    |    K    |    L    |    ;    |   '     |
         S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,                                                  S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,
     // |---------+---------+---------+---------+---------+---------+-------------------.      .-------------------|---------+---------+---------+---------+---------+---------|
     // | lshift  |    Z    |    X    |    C    |    V    |    B    |    [    |    `    |      |    #    |    ]    |    N    |    M    | , and < | . and>  | / and ? | rshift  |
         S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,          S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,
     // .---------+-------------------------------------------------|-------------------|      |---------+---------|-------------------------------------------------+---------'
     //                               | \ and | |left ctl |left alt | lower   | space   |      | enter   |  raise  |right alt| - and _ | = and + |
                                       S__RED,   S__RED,   S__RED,   S__RED,   S__RED,          S__RED,   S__RED,   S__RED,   S__RED,   S__RED,
     // ______________________________|_________|_________|_________|_________|_________|      |_________|_________|_________|_________|_________|______________________________
     //                                underglow                                                                                        underglow 
         L__OFF,                       L__OFF,                       L__OFF,                              L__OFF,                       L__OFF,                       L__OFF,
         L__OFF,                       L__OFF,                       L__OFF,                              L__OFF,                       L__OFF,                       L__OFF
),

[_GAME] = RGB_MATRIX_LAYOUT( 
     // .-----------------------------------------------------------.                                              ,-----------------------------------------------------------.
     // |         |         |    E    |    W    |         |         |                                              |         |         |         |         |         |         |
         S__RED,   S__RED,   S_GREN,   B_ORAN,   S__RED,  S__RED,                                                   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,
     // |---------+---------+---------+---------|---------+---------|                                              |---------+---------|---------|---------|---------+---------|
     // |         |    F    |    A    |    S    |    D    |         |                                              |         |         |         |         |         |         |
         S__RED,   S_ROSE,   B_ORAN,   B_ORAN,   B_ORAN,   S__RED,                                                  S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,
     // |---------+---------+---------+---------+---------+---------+-------------------.      .-------------------|---------+---------+---------+---------+---------+---------|
     // |         |         |         |         |         |         |         |         |      |         |         |         |         |         |         |         |         |
         S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,          S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,
     // .---------+-------------------------------------------------|-------------------|      |---------+---------|-------------------------------------------------+---------'
     //                               |         |         |         |         |         |      |         |         |         |         |         |
                                       S__RED,   S__RED,   S__RED,   S__RED,   S__RED,          S__RED,   S__RED,   S__RED,   S__RED,   S__RED,
     // ______________________________|_________|_________|_________|_________|_________|      |_________|_________|_________|_________|_________|______________________________
     //                                underglow                                                                                        underglow 
         L__OFF,                       L__OFF,                       L__OFF,                              L__OFF,                       L__OFF,                       L__OFF,
         L__OFF,                       L__OFF,                       L__OFF,                              L__OFF,                       L__OFF,                       L__OFF
),

[_LOWER] = RGB_MATRIX_LAYOUT( 
     // .-----------------------------------------------------------.                                              ,------------------------------------------------ ----------.
     // |= equal  |/ div    |7        |8        |9        |backspace|                                              |         |         |         |         |         |insert   |
         S_ROSE,   S_GREN,   S_ORAN,   S_ORAN,   S_ORAN,   S_BLUE,                                                  S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S_BLUE,
     // |---------+---------+---------+---------|---------+---------|                                              |---------+---------|---------|---------|---------+---------|
     // |delete   |* mult   |4        |5        |6        |- minus  |                                              |         |         |         |         |         |         |
         S_BLUE,   S_GREN,   S_ORAN,   S_ORAN,   S_ORAN,   S_GREN,                                                  S_SKYB,   B_CYAN,   B_CYAN,   B_CYAN,   B_CYAN,   S__RED,
     // |---------+---------+---------+---------+---------+---------+-------------------.      .-------------------|---------+---------+---------+---------+---------+---------|
     // |. dot    |0        |1        |2        |3        |- plus   |         |         |      |         |         |         |         |         |         |         |         |
         S_ROSE,   S_ORAN,   S_ORAN,   S_ORAN,   S_ORAN,   S_GREN,   S__RED,   S__RED,          S_CYAN,   S_CYAN,   S_SKYB,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,
     // .---------+-------------------------------------------------|-------------------|      |---------+---------|-------------------------------------------------+---------'
     //                               |         |         |enter    |         |         |      |         |         |         |         |         |
                                       S__RED,   S__RED,   S_BLUE,   B__RED,   S__RED,          S_CYAN,   S__RED,   S__RED,   S__RED,   S__RED,
     // ______________________________|_________|_________|_________|_________|_________|      |_________|_________|_________|_________|_________|______________________________
     //                                underglow                                                                                        underglow 
         L__OFF,                       L__OFF,                       L__OFF,                              L__OFF,                       L__OFF,                       L__OFF,
         L__OFF,                       L__OFF,                       L__OFF,                              L__OFF,                       L__OFF,                       L__OFF
),

[_RAISE] = RGB_MATRIX_LAYOUT( 
     // .-----------------------------------------------------------.                                              ,------------------------------------------------ ----------.
     // |         |    !    |    "    |    £    |    $    |    %    |                                              |    ^    |    &    |    *    |    (    |    )    |del      |
         S__RED,   S_ORAN,   S_ORAN,   S_ORAN,   S_ORAN,   S_ORAN,                                                  S_ORAN,   S_ORAN,   S_ORAN,   S_ORAN,   S_ORAN,   S_ROSE,
     // |---------+---------+---------+---------|---------+---------|                                              |---------+---------|---------|---------|---------+---------|
     // |         |home     |page down|page up  |end      |         |                                              |left     |down     |up       |right    |    :    |         |
         S__RED,   S_CYAN,   S_CYAN,   S_CYAN,   S_CYAN,   S__RED,                                                  S_SKYB,   S_SKYB,   S_SKYB,   S_SKYB,   S_ROSE,   S__RED,
     // |---------+---------+---------+---------+---------+---------+-------------------.      .-------------------|---------+---------+---------+---------+---------+---------|
     // |         |         |         |         |         |         |         |         |      |         |         |alt+left |alt+down |alt+up   |alt+right|         |         |
         S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S__RED,          S__RED,   S__RED,   S_BLUE,   S_BLUE,   S_BLUE,   S_BLUE,   S__RED,   S__RED,
     // .---------+-------------------------------------------------|-------------------|      |---------+---------|-------------------------------------------------+---------'
     //                               |         |         |         |         |         |      |         |         |         |         |         |
                                       S__RED,   S__RED,   S__RED,   S__RED,   S__RED,          S__RED,   B__RED,   S__RED,   S__RED,   S__RED,
     // ______________________________|_________|_________|_________|_________|_________|      |_________|_________|_________|_________|_________|______________________________
     //                                underglow                                                                                        underglow 
         L__OFF,                       L__OFF,                       L__OFF,                              L__OFF,                       L__OFF,                       L__OFF,
         L__OFF,                       L__OFF,                       L__OFF,                              L__OFF,                       L__OFF,                       L__OFF
),

[_FUNC] = RGB_MATRIX_LAYOUT( 
     // .-----------------------------------------------------------.                                              ,-----------------------------------------------------------.
     // |         |F1        |F2      |F3       |F4       |F5       |                                              |F6       |F7       |F8       |F9       |F10      |F11      |
         S__RED,   S_ORAN,   S_ORAN,   S_ORAN,   S_ORAN,   S_ORAN,                                                  S_ORAN,   S_ORAN,   S_ORAN,   S_ORAN,   S_ORAN,  S_ORAN,
     // |---------+---------+---------+---------|---------+---------|                                              |---------+---------|---------|---------|---------+---------|
     // |         |app menu |prnt scrn|         |max win  |tmux term|                                              |         |         |         |         |         |F12      |
         S__RED,   S_ROSE,   S_BLUE,   S__RED,   S_ROSE,   S_BLUE,                                                  S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S_ORAN,
     // |---------+---------+---------+---------+---------+---------+-------------------.      .-------------------|---------+---------+---------+---------+---------+---------|
     // |         |         |         |         |         |bash term|         |         |      |         |         |play/paus|mute     |previous |next     |         |         |
         S__RED,   S__RED,   S__RED,   S__RED,   S__RED,   S_BLUE,   S__RED,   S__RED,          S__RED,   S__RED,   S_GREN,   S_GREN,   S_GREN,   S_GREN,   S__RED,   S__RED,
     // .---------+-------------------------------------------------|-------------------|      |---------+---------|-------------------------------------------------+---------'
     //                               |         |         |         |         |         |      |         |         |vol -    |vol +    |         |
                                       S__RED,   S__RED,   S__RED,   B__RED,   S__RED,          S__RED,   B__RED,   S_GREN,   S_GREN,   S__RED,
     // ______________________________|_________|_________|_________|_________|_________|      |_________|_________|_________|_________|_________|______________________________
     //                                underglow                                                                                        underglow 
         L__OFF,                       L__OFF,                       L__OFF,                              L__OFF,                       L__OFF,                       L__OFF,
         L__OFF,                       L__OFF,                       L__OFF,                              L__OFF,                       L__OFF,                       L__OFF
),

[_ADJUST] = RGB_MATRIX_LAYOUT( 
     // .-----------------------------------------------------------.                                              ,-----------------------------------------------------------.
     // |boot     |         |         |         |rgb togg |rgb deflt|                                              |         |         |         |oled tgl |oled slep|boot     |
         B_LIME,   L__OFF,   L__OFF,   L__OFF,   B_CYAN,   S_CYAN,                                                  L__OFF,   L__OFF,   L__OFF,   B_VIOL,   S_VIOL,   B_LIME,
     // |---------+---------+---------+---------+---------+---------|                                              |---------+---------+---------+---------+---------+---------|
     // |reboot   |         |sys sleep|         |         |game layr|                                              |         |         |key log  |         |         |reboot   |
         B_GREN,   L__OFF,   B_BLUE,   L__OFF,   L__OFF,   B_ROSE,                                                  L__OFF,   L__OFF,   B_ORAN,   L__OFF,   L__OFF,   B_GREN,
     // |---------+---------+---------+---------+---------+---------+-------------------.      .-------------------|---------+---------+---------+---------+---------+---------|
     // |         |         |         |clear mem|         |base layr|         |         |      |         |         |         |         |clear mem|         |         |autoshift|
         L__OFF,   L__OFF,   L__OFF,   B_YELL,   L__OFF,   B_ROSE,   L__OFF,   L__OFF,          L__OFF,   L__OFF,   L__OFF,   L__OFF,   B_YELL,   L__OFF,   L__OFF,   B_SKYB,
     // .---------+-------------------------------------------------|-------------------|      |---------+---------|-------------------------------------------------+---------'
     //                               |         |         |         |         |         |      |         |         |rgb -    |rgb +    |         |
                                       L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,          L__OFF,   L__OFF,   S_CYAN,   S_CYAN,   B__RED,
     // ______________________________|_________|_________|_________|_________|_________|      |_________|_________|_________|_________|_________|______________________________
     //                                underglow                                                                                        underglow 
         L__OFF,                       L__OFF,                       L__OFF,                              L__OFF,                       L__OFF,                       L__OFF,
         L__OFF,                       L__OFF,                       L__OFF,                              L__OFF,                       L__OFF,                       L__OFF
)
};


// Set LED for caps word
// NOTE caps word state is not synced to slave side, so setting led index on
// slave side will not work
void set_caps_word_led(void) {
    if (is_caps_word_on()) {
        HSVB hsvb = B_GREN;
        set_led_color(LSHIFT_LED_INDEX, hsvb, USE_RGB_MATRIX_VALUE_ON);
        // TODO so this will not work:
        set_led_color(RSHIFT_LED_INDEX, hsvb, USE_RGB_MATRIX_VALUE_ON);
    } 
}


// TODO func for tapdance rshift hold (=shift+ctrl)

// Set LED for Caps Lock
void set_caps_led_color(void) {
    if (host_keyboard_led_state().caps_lock) {
        HSVB hsvb = B_BLUE;
        set_led_color(CAPS_LED_INDEX, hsvb, USE_RGB_MATRIX_VALUE_ON);
    }
}


// SET INDIVIDUAL LED RGB
// NOTE: Per key breathing effect cycle timer.
// Effect cycle timer example using user config:
// uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);
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


// SET LED RGB & BREATHING CYCLE BASED ON LAYER
void set_layer_color( uint8_t layer, uint8_t led_min, uint8_t led_max) {

    // By default, use global LED brightness set by user
    bool use_curr_brightness = USE_RGB_MATRIX_VALUE_ON;

    for (uint8_t index = led_min; index < led_max; index++) {
        HSVB hsvb = ledmaps[layer][index].hsvb;
        set_led_color(index, hsvb, use_curr_brightness);
    }
}

