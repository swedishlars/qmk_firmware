/* Copyright 2024 Lars Johansson (github.com/swedishlars)
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

// TODO testing for LAYOUT:
/* #include QMK_KEYBOARD_H */

#include "rgb.h"

// LIB USED FOR  LED INDICATOR BREATHING EFFECT
#include "lib/lib8tion/lib8tion.h"


// Per layer, per key rgb maps
const led_color_t PROGMEM ledmaps[][RGB_MATRIX_LED_COUNT] = {
[0] = RGB_MATRIX_LAYOUT( 
     // .-----------------------------------------------------------.                                              ,-----------------------------------------------------------.
     // |esc      |    Q    |    W    |    E    |    R    |    T    |                                              |    Y    |    U    |    I    |    O    |    P    |backspace|
         L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,  L_DRED,                                                   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,
     // |---------+---------+---------+---------|---------+---------|                                              |---------+---------|---------|---------|---------+---------|
     // | tab     |    A    |    S    |    D    |    F    |   G     |                                              |    H    |    J    |    K    |    L    |    ;    |   '     |
         L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,                                                  L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,
     // |---------+---------+---------+---------+---------+---------+-------------------.      .-------------------|---------+---------+---------+---------+---------+---------|
     // | lshift  |    Z    |    X    |         |         |    B    |         |         |      |         |         |    N    |    M    | , and < | . and>  | / and ? | rshift  |
         L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,          L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,
     // .---------+-------------------------------------------------|-------------------|      |---------+---------|-------------------------------------------------+---------'
     //                               | \ and | |left ctl |left alt | lower   | space   |      | enter   |  raise  |right alt| - and _ | = and + |
                                       L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,          L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,
     // ______________________________|_________|_________|_________|_________|_________|      |_________|_________|_________|_________|_________|______________________________
     //                                underglow                                                                                        underglow 
         L__OFF,                       L__OFF,                       L__OFF,                              L__OFF,                       L__OFF,                       L__OFF,
         L__OFF,                       L__OFF,                       L__OFF,                              L__OFF,                       L__OFF,                       L__OFF

),

// LOWER numpad
[1] = RGB_MATRIX_LAYOUT( 
     // .-----------------------------------------------------------.                                              ,------------------------------------------------ ----------.
     // |= equal  |/ div    |7        |8        |9        |backspace|                                              |         |         |         |         |         |insert   |
         L_LRED,   L_DGRE,   L_LORA,   L_LORA,   L_LORA,   L_DBLU,                                                  L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DBLU,
     // |---------+---------+---------+---------|---------+---------|                                              |---------+---------|---------|---------|---------+---------|
     // |delete   |* mult   |4        |5        |6        |- minus  |                                              |         |         |         |         |         |         |
         L_DBLU,   L_DGRE,   L_LORA,   L_LORA,   L_LORA,   L_DGRE,                                                  L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_MRED,   L_DRED,
     // |---------+---------+---------+---------+---------+---------+-------------------.      .-------------------|---------+---------+---------+---------+---------+---------|
     // |         |0        |1        |2        |3        |- plus   |         |         |      |         |         |         |         |         |         |         |         |
         L_DRED,   L_LORA,   L_LORA,   L_LORA,   L_LORA,   L_DGRE,   L_DRED,   L_DRED,          L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,
     // .---------+-------------------------------------------------|-------------------|      |---------+---------|-------------------------------------------------+---------'
     //                               |         |. dot    |enter    |         |         |      |         |         |         |         |         |
                                       L_DRED,   L_LRED,   L_DBLU,   L_DRED,   L_DRED,          L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,
     // ______________________________|_________|_________|_________|_________|_________|      |_________|_________|_________|_________|_________|______________________________
     //                                underglow                                                                                        underglow 
         L__OFF,                       L__OFF,                       L__OFF,                              L__OFF,                       L__OFF,                       L__OFF,
         L__OFF,                       L__OFF,                       L__OFF,                              L__OFF,                       L__OFF,                       L__OFF
),

// RAISE symbols
[2] = RGB_MATRIX_LAYOUT( 
     // .-----------------------------------------------------------.                                              ,------------------------------------------------ ----------.
     // |         |    !    |    "    |    £    |    $    |    %    |                                              |    ^    |    &    |    *    |    (    |    )    |del      |
         L_DRED,   L_LORA,   L_LORA,   L_LORA,   L_LORA,   L_LORA,                                                  L_LORA,   L_LORA,   L_LORA,   L_LORA,   L_LORA,   L_LRED,
     // |---------+---------+---------+---------|---------+---------|                                              |---------+---------|---------|---------|---------+---------|
     // |         |home     |page down|page up  |end      |         |                                              |left     |down     |up       |right    |    :    |         |
         L_DRED,   L_DBLU,   L_DBLU,   L_DBLU,   L_DBLU,   L_DRED,                                                  L_LBLU,   L_LBLU,   L_LBLU,   L_LBLU,   L_LRED,   L_DRED,
     // |---------+---------+---------+---------+---------+---------+-------------------.      .-------------------|---------+---------+---------+---------+---------+---------|
     // |shift+ctl|         |         |         |         |         |         |         |      |         |         |alt+left |alt+down |alt+up   |alt+right|         |         |
         L_DGRE,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,          L_DRED,   L_DRED,   L_DBLU,   L_DBLU,   L_DBLU,   L_DBLU,   L_DRED,   L_DRED,
     // .---------+-------------------------------------------------|-------------------|      |---------+---------|-------------------------------------------------+---------'
     //                               |         |         |         |         |         |      |         |         |         |         |         |
                                       L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,          L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,
     // ______________________________|_________|_________|_________|_________|_________|      |_________|_________|_________|_________|_________|______________________________
     //                                underglow                                                                                        underglow 
         L__OFF,                       L__OFF,                       L__OFF,                              L__OFF,                       L__OFF,                       L__OFF,
         L__OFF,                       L__OFF,                       L__OFF,                              L__OFF,                       L__OFF,                       L__OFF
),

// FUNC F/media/apps
[3] = RGB_MATRIX_LAYOUT( 
     // .-----------------------------------------------------------.                                              ,-----------------------------------------------------------.
     // |         |F1        |F2      |F3       |F4       |F5       |                                              |F6       |F7       |F8       |F9       |F10      |F11      |
         L_DRED,   L_LORA,   L_LORA,   L_LORA,   L_LORA,   L_LORA,                                                  L_LORA,   L_LORA,   L_LORA,   L_LORA,   L_LORA,  L_LORA,
     // |---------+---------+---------+---------|---------+---------|                                              |---------+---------|---------|---------|---------+---------|
     // |         |app menu |prnt scrn|         |max win  |tmux term|                                              |         |         |         |         |         |F12      |
         L_DRED,   L_LRED,   L_DBLU,   L_DRED,   L_LRED,   L_DBLU,                                                  L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_LORA,
     // |---------+---------+---------+---------+---------+---------+-------------------.      .-------------------|---------+---------+---------+---------+---------+---------|
     // |         |         |         |         |         |bash term|         |         |      |         |         |play/paus|mute     |previous |next     |         |         |
         L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DBLU,   L_DRED,   L_DRED,          L_DRED,   L_DRED,   L_DGRE,   L_DGRE,   L_DGRE,   L_DGRE,   L_DRED,   L_DRED,
     // .---------+-------------------------------------------------|-------------------|      |---------+---------|-------------------------------------------------+---------'
     //                               |         |         |         |         |         |      |         |         |vol -    |vol +    |         |
                                       L_DRED,   L_DRED,   L_DRED,   L_BRED,   L_DRED,          L_DRED,   L_DRED,   L_DGRE,   L_DGRE,   L_DRED,
     // ______________________________|_________|_________|_________|_________|_________|      |_________|_________|_________|_________|_________|______________________________
     //                                underglow                                                                                        underglow 
         L__OFF,                       L__OFF,                       L__OFF,                              L__OFF,                       L__OFF,                       L__OFF,
         L__OFF,                       L__OFF,                       L__OFF,                              L__OFF,                       L__OFF,                       L__OFF
),

// ADJUST
[4] = RGB_MATRIX_LAYOUT( 
     // .-----------------------------------------------------------.                                              ,-----------------------------------------------------------.
     // |boot     |         |         |         |rgb togg |rgb deflt|                                              |         |         |         |oled tgl |oled slep|boot     |
         L_BRED,   L__OFF,   L__OFF,   L__OFF,   L_BCYA,   L_DCYA,                                                  L__OFF,   L__OFF,   L__OFF,   L_BVIO,   L_DVIO,   L_BRED,
     // |---------+---------+---------+---------+---------+---------|                                              |---------+---------+---------+---------+---------+---------|
     // |reboot   |         |sys sleep|         |         |         |                                              |         |         |key log  |base layr|         |reboot   |
         L_BGRE,   L__OFF,   L_BBLU,   L__OFF,   L__OFF,   L__OFF,                                                  L__OFF,   L__OFF,   L_BORA,   L_BROS,   L__OFF,   L_BGRE,
     // |---------+---------+---------+---------+---------+---------+-------------------.      .-------------------|---------+---------+---------+---------+---------+---------|
     // |         |         |         |clear mem|         |         |         |         |      |         |         |         |         |clear mem|         |         |autoshift|
         L__OFF,   L__OFF,   L__OFF,   L_BYEL,   L__OFF,   L__OFF,   L__OFF,   L__OFF,          L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_BYEL,   L__OFF,   L__OFF,   L_BAZU,
     // .---------+-------------------------------------------------|-------------------|      |---------+---------|-------------------------------------------------+---------'
     //                               |         |         |         |         |         |      |         |         |rgb -    |rgb +    |         |
                                       L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,          L__OFF,   L__OFF,   L_DCYA,   L_DCYA,   L__OFF,
     // ______________________________|_________|_________|_________|_________|_________|      |_________|_________|_________|_________|_________|______________________________
     //                                underglow                                                                                        underglow 
         L__OFF,                       L__OFF,                       L__OFF,                              L__OFF,                       L__OFF,                       L__OFF,
         L__OFF,                       L__OFF,                       L__OFF,                              L__OFF,                       L__OFF,                       L__OFF
)
};


// Set LED for Caps Lock
// TODO get correct index
void set_caps_led_color(void) {
    if (host_keyboard_led_state().caps_lock) {
        HSVB hsvb = L_BRED;
        // TODO orig:
        //set_led_color(26, hsvb, USE_RGB_MATRIX_VALUE_ON);
        // TODO use define to declare caps index
        set_led_color(35, hsvb, USE_RGB_MATRIX_VALUE_ON);
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


// SET LED RGB & BREATHING CYCLE BASED ON LAYER AND KEYCODES
// TODO orig:
/* void set_layer_color( uint8_t layer, uint8_t index, uint16_t keycode) { */
// TODO this works
void set_layer_color( uint8_t layer, uint8_t led_min, uint8_t led_max) {

    // By default, use global LED brightness set by user
    bool use_curr_brightness = USE_RGB_MATRIX_VALUE_ON;

    // TODO testing
    for (uint8_t index = led_min; index < led_max; index++) {
        HSVB hsvb = ledmaps[layer][index].hsvb;
        set_led_color(index, hsvb, use_curr_brightness);
    }

    // TODO orig:
    /* HSVB hsvb = ledmaps[layer][index].hsvb; */

    // flag if ledcolor is set for key without keycode
    /* if (keycode == KC_NO) { */
    /*     if (hsvb.v > 0) { */
    /*         hsvb.h = 0; */
    /*         hsvb.s = 0; */
    /*         hsvb.v = 25; */
    /*         hsvb.b = 30; */
    /*     } */
    /* } */

    // flag if ledcolor is not set for keys with transparent keycode
    // flag if ledcolor is not set for key with keycode.
    /* else if (keycode >= KC_TRNS) { */
    /*     if (hsvb.v == 0) { */
    /*         hsvb.h = 0; */
    /*         hsvb.s = 25; */
    /*         hsvb.v = 25; */
    /*         hsvb.b = 30; */
    /*     } */
    /* } */

    /* set_led_color(index, hsvb, use_curr_brightness); */
}

