/* Copyright 2024 Lars Johansson (github.com/swedishlars)
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "rgb.h"
// include to use layer enums
#include "swedishlars.h"

// LIB USED FOR  LED INDICATOR BREATHING EFFECT
#include "lib/lib8tion/lib8tion.h"


// rgb to key index conversion. Array index order represents rgb index.
// value represents key index. Example:
// First array element [0] is first LED in rgb matrix on key index 5.
// Here's what it looks like on keymap:
// .-----------------------------------------------.                  ,-----------------------------------------------.
// | esc   |  1    |  2    |  3    |  4    |  5    |                  |  6    |  7    |  8    |  9    |  0    | back  |    KEY:
//   [28]    [21]    [20]    [11]    [10]    [0]                        [29]    [39]    [40]    [49]    [50]    [57]    // 0-5 , 6-11
// |-------+-------+-------+-------+---------------|                  |-------+-------+-------+-------+-------+-------|
// | tab   |  Q    |  W    |  E    |  R    |  T    |                  |  Y    |  U    |  I    |  O    |  P    |  #    |
//   [27]    [22]    [19]    [12]    [9]     [1]                        [30]    [38]    [41]    [48]    [51]    [56]    // 12-17 , 18-23
// |-------+--------+------+-------+-------+-------|                  |-------+-------+-------+-------+---------------|
// | caps  |  A    |  S    |  D    |  F    |  G    |                  |  H    |  J    |  K    |  L    |  ;    |  '    |
//   [26]    [23]    [18]    [13]    [8]     [2]                        [31]    [37]    [42]    [47]    [52]    [55]    // 24-29 , 30-35
// |-------+-------+-------+------+----+----+------+-------.  .-------+-------+-------+-------+-------+-------+-------|
// | lshift|  Z    |  X    |  C    |  V    |  B    |       |  |       |  N    |  M    |  ,    |  .    |  /    | rshift|
//   [25]    [24]    [17]    [14]    [7]     [3]                        [32]    [36]    [43]    [46]    [53]    [54]    // 36-41 , 42-47
// .---------------+-------+-------+-------+-------|-------   |---------------+-------+-------+-------+-------+-------'
//                 | lgui  | L ctl | L alt | lower | space |  | enter | raise | R alt | R ctl | R gui |
//                   [16]    [15]    [6]     [5]     [4]        [33]    [34]    [35]    [44]    [45]                    // 48-52 , 53-57
//                 |_______|_______|_______|_______|_______|  |_______|_______|_______|_______|_______|

/*
const uint8_t PROGMEM rgb_matrix_index[58] ={
    // led index 0 - 5         // led index  6 - 11
    5, 17, 29, 41, 52, 51,     50, 40, 28, 16, 4, 3,

    // led index 12 - 17       // led index 18 - 23
    15, 27, 39, 49, 48, 38,    26, 14, 2, 1, 13, 25,

    // led index 24 -29        // led index 30 - 35
    37, 36, 24, 12, 0, 6,      18, 30, 42, 53, 54, 55,

    // led index 36 - 41       // led index 42 - 47
    43, 31, 19, 7, 8, 20,      32, 44, 56, 57, 45, 33,

    // led index 48 - 52      // led index 53 - 57
    21, 9, 10, 22, 34,        46, 47, 35, 23, 11
};
*/

// Per layer, per key rgb maps
const led_color_t PROGMEM ledmaps[][RGB_MATRIX_LED_COUNT] = {
// TODO orig rm:
//const led_color_t PROGMEM ledcolors[] = {

// BASE TODO orig rm:
//[0] = {{
[_BASE] = RGB_MATRIX_LAYOUT(
     // .-----------------------------------------------------------.                          ,-----------------------------------------------------------.
     // | esc     |    1    |    2    |   3     |    4    |   5     |                          |    6    |    7    |    8    |    9    |    0    | back    |
         L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,                              L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,
     // |---------+---------+---------+---------+---------+---------|                          |---------+---------+---------+---------+---------+---------|
     // | tab     |    Q    |    W    |    E    |    R    |    T    |                          |    Y    |    U    |    I    |    O    |    P    |   #     |
         L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,  L_DRED,                               L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,
     // |---------+---------+---------+---------|---------+---------|                          |---------+---------|---------|---------|---------+---------|
     // | caps/num|    A    |    S    |    D    |    F    |   G     |                          |    H    |    J    |    K    |    L    |    ;    |   '     |
         L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,                              L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,
     // |---------+---------+---------+---------+---------+---------+----------.    .----------|---------+---------+---------+---------+---------+---------|
     // | lshift  |    Z    |    X    |         |         |    B    |          |    |          |    N    |    M    | , and < | . and>  | / and ? | rshift  |
         L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,                              L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,
     // .---------+-------------------------------------------------/----------/    \----------\-------------------------------------------------+---------'
     //           | \ and | |left ctl     |left alt  | lower      / space    /      \ enter    \  raise     |right alt | - and _     | = and +  |
                   L_DRED,    L_DRED,       L_DRED,    L_DRED,       L_DRED,            L_DRED,    L_DRED,    L_DRED,    L_DRED,       L_DRED
     //           |__________|_____________|__________|__________/__________/          \__________\__________|__________|_____________|__________|
// TODO orig:
//}},
),

// LOWER
//[1] = {{
[_LOWER] = RGB_MATRIX_LAYOUT(
     // .-----------------------------------------------------------.                          ,-----------------------------------------------------------.
     // |         |delete   |backspace|/ div    |* mult   |         |                          |         |         |         |         |         |frw del  |
         L_DRED,   L_DBLU,   L_DBLU,   L_DGRE,   L_DGRE,   L_DRED,                              L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_MRED,
     // |---------+---------+---------+---------+---------+---------|                          |---------+---------+---------+---------+---------+---------|
     // |         |= equal  |7        |8        |9        |- minus  |                          |         |         |         |Ö        |         |         |
         L_DRED,    L_DCYA,   L_DORA,   L_DORA,   L_DORA,   L_DGRE,                              L_DRED,   L_DRED,   L_DRED,   L_MRED,   L_DRED,  L_DRED,
     // |---------+---------+---------+---------|---------+---------|                          |---------+---------|---------|---------|---------+---------|
     // |Ä        |Å        |4        |5        |6        |+ plus   |                          | left    |  down   | up      | right   |         |         |
         L_MRED,   L_MRED,   L_DORA,   L_DORA,   L_DORA,   L_DGRE,                              L_DBLU,   L_DBLU,   L_DBLU,   L_DBLU,   L_DRED,   L_DRED,
     // |---------+---------+---------+---------+---------+---------+----------.    .----------|---------+---------+---------+---------+---------+---------|
     // |= equal  |0        |1        |2        |3        |enter    |          |    |          |alt+left |alt+down |alt+up   |alt+right|         |         |
         L_DCYA,   L_DORA,   L_DORA,   L_DORA,   L_DORA,   L_DBLU,                              L_LBLU,   L_LBLU,   L_LBLU,   L_LBLU,   L_DRED,   L_DRED,
     // .---------+-------------------------------------------------/----------/    \----------\-------------------------------------------------+---------'
     //           |    |     |0            |. dot     |            /          /      \          \            |          |             |          |
                   L_DRED,    L_DORA,       L_DCYA,    L_BRED,       L_DRED,             L_DRED,   L_DRED,    L_DRED,    L_DRED,       L_MRED
     //           |__________|_____________|__________|__________/__________/          \__________\__________|__________|_____________|__________|
//}},
),

// RAISE
//[2] = {{
[_RAISE] = RGB_MATRIX_LAYOUT(
     // .-----------------------------------------------------------.                          ,------------------------------------------------ ----------.
     // |         |         | "       | £       | $       | €       |                          |         |         |         | [       | ]       |insert   |
         L_DRED,   L_DRED,   L_LRED,   L_LRED,   L_LRED,   L_LRED,                              L_DRED,   L_DRED,   L_DRED,   L_LORA,   L_LORA,   L_LRED,
     // |---------+---------+---------+---------+---------+---------|                          |---------+---------+---------+---------+---------+---------|
     // |         |         |         |         |         |         |                          |         |         |         | {       | }       |         |
         L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,                              L_DRED,   L_DRED,   L_DRED,   L_LORA,   L_LORA,   L_DRED,
     // |---------+---------+---------+---------|---------+---------|                          |---------+---------|---------|---------|---------+---------|
     // |         | home    |page down|page up  | end     |         |                          |left     |down     |up       |right    |         |         |
         L_DRED,   L_DCYA,   L_DCYA,   L_DCYA,   L_DCYA,   L_DRED,                              L_DBLU,   L_DBLU,   L_DBLU,   L_DBLU,   L_DRED,   L_DRED,
     // |---------+---------+---------+---------+---------+---------+----------.    .----------|---------+---------+---------+---------+---------+---------|
     // |         | undo    | cut     |copy     |paste    |         |          |    |          |alt+left |alt+down |alt+up   |alt+right|         |         |
         L_DRED,   L_LBLU,   L_LBLU,   L_LBLU,   L_LBLU,   L_DRED,                              L_LBLU,   L_LBLU,   L_LBLU,   L_LBLU,   L_DRED,   L_DRED,
     // .---------+-------------------------------------------------/----------/    \----------\-------------------------------------------------+---------'
     //           |          |             |          |            /          /      \          \            |          | vol -       | vol +    |
                   L_DRED,    L_DRED,       L_DRED,    L_DRED,       L_DRED,             L_DRED,   L_BRED,    L_DRED,    L_DGRE,       L_DGRE
     //           |__________|_____________|__________|__________/__________/          \__________\__________|__________|_____________|__________|
//}},
),

// FUNC
//[3] = {{
[_FUNC] = RGB_MATRIX_LAYOUT(
     // .-----------------------------------------------------------.                          ,------------------------------------------------ ----------.
     // |F1       |F2       |F2       |F3       |F4       |F5       |                          |F6       |F7       |F8       |F9       |F10      |F11      |
         L_DRED,   L_DORA,   L_DORA,   L_DORA,   L_DORA,   L_DORA,                              L_DORA,   L_DORA,   L_DORA,   L_DORA,   L_DORA,   L_DORA,
     // |---------+---------+---------+---------+---------+---------|                          |---------+---------+---------+---------+---------+---------|
     // |         |         |         |         |max win  |wezterm  |                          |         |         |         |         |prnt scrn|F12      |
         L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DCYA,   L_DBLU,                              L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DCYA,   L_DORA,
     // |---------+---------+---------+---------|---------+---------|                          |---------+---------|---------|---------|---------+---------|
     // |         |app menu |         |         |         |         |                          |         |         |         |         |         |         |
         L_DRED,   L_DVIO,   L_DRED,   L_DRED,   L_DRED,   L_DRED,                              L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,
     // |---------+---------+---------+---------+---------+---------+----------.    .----------|---------+---------+---------+---------+---------+---------|
     // |         |         |         |         |         |bash term|          |    |          |play/paus|mute     |prev     |next     |         |         |
         L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DBLU,                              L_DGRE,   L_DGRE,   L_DGRE,   L_DGRE,   L_DRED,   L_DRED,
     // .---------+-------------------------------------------------/----------/    \----------\-------------------------------------------------+---------'
     //           |          |             |          |            /  Space   /      \ Enter    \            |          |  - minus    | + plus   |
                   L_DRED,    L_DRED,       L_DRED,    L_DRED,       L_DRED,             L_DRED,   L_DRED,    L_DRED,    L_DGRE,       L_DGRE
     //           |__________|_____________|__________|__________/__________/          \__________\__________|__________|_____________|__________|
//}},
),

// MOUSE
//[4] = {{
[_MOUSE] = RGB_MATRIX_LAYOUT(
     // .-----------------------------------------------------------.                          ,------------------------------------------------ ----------.
     // |         |         |         |         |         |         |                          |         |         |         |         |         |         |
         L_DRED,   L_DYEL,   L_DYEL,   L_DYEL,   L_DRED,   L_DRED,                              L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,
     // |---------+---------+---------+---------+---------+---------|                          |---------+---------+---------+---------+---------+---------|
     // |         |         |         |         |         |         |                          |         |         |         |         |         |         |
         L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,                              L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,
     // |---------+---------+---------+---------+---------+---------|                          |---------+---------+---------+---------+---------+---------|
     // |         |         |         |         |         |         |                          |         |         |         |         |         |         |
         L_DRED,   L_BCYA,   L_BCYA,   L_BCYA,   L_DRED,   L_DBLU,                              L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,
     // |---------+---------+---------+---------+---------+---------+----------.    .----------|---------+---------+---------+---------+---------+---------|
     // |         |         |         |         |         |         |          |    |          |         |         |         |         |         |         |
         L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DBLU,                              L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,
     // .---------+-------------------------------------------------/----------/    \----------\-------------------------------------------------+---------'
     //           |          |   ctrl      | alt      | mouse 3    /  mouse 1 /      \ mouse 2  \            |          |             |          |
                   L_DRED,    L_DRED,       L_DRED,    L_BORA,       L_BORA,             L_BORA,   L_DRED,    L_DRED,    L_DRED,       L_DRED
     //           |__________|_____________|__________|__________/__________/          \__________\__________|__________|_____________|__________|
//}},
),

// CONF
//[5] = {{
[_CONF] = RGB_MATRIX_LAYOUT(
     // .-----------------------------------------------------------.                          ,------------------------------------------------ ----------.
     // |reboot    |base lyr|lower    |raise    |numpad   |mouse    |                          |switch   |         |         |         |         |reboot   |
         L_BRED,   L_BGRE,   L_BGRE,   L_BGRE,   L_BGRE,   L_BGRE,                              L_BGRE,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_BRED,
     // |---------+---------+---------+---------+---------+---------|                          |---------+---------+---------+---------+---------+---------|
     // |clear mem|         |         |         |rgb togg |rgb deflt|                          |         |         |oled slp |oled tgl |         |clear mem|
         L_BYEL,   L__OFF,   L__OFF,   L__OFF,   L_BCYA,   L_DCYA,                              L__OFF,   L__OFF,   L_DVIO,   L_BVIO,   L__OFF,   L_BYEL,
     // |---------+---------+---------+---------+---------+---------|                          |---------+---------+---------+---------+---------+---------|
     // |         |Audio tgl|sys sleep|         |         |         |                          |haptic tg|         |         |         |         |         |
         L__OFF,   L_BVIO,   L_BBLU,   L__OFF,   L__OFF,   L__OFF,                              L_BORA,   L__OFF,   L_BORA,   L__OFF,   L__OFF,   L__OFF,
     // |---------+---------+---------+---------+---------+---------+----------.    .----------|---------+---------+---------+---------+---------+---------|
     // |         |         |         |         |         |         |          |    |          |         |         |         |         |         |         |
         L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,                              L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,
     // .---------+-------------------------------------------------/----------/    \----------\-------------------------------------------------+---------'
     //           |          |             |          |            /          /      \          \            |          |rgb brght-   |rgb brght+|
                   L__OFF,    L__OFF,       L__OFF,    L__OFF,       L__OFF,             L__OFF,   L__OFF,    L__OFF,    L_DCYA,       L_DCYA
     //           |__________|_____________|__________|__________/__________/          \__________\__________|__________|_____________|__________|
//}}
)
};


// Set LED for caps word
// NOTE caps word state is not synced to slave side, so setting led index on
// slave side will not work
void set_caps_word_led(void) {
    if (is_caps_word_on()) {
        HSVB hsvb = L_BGRE;
        set_led_color(LSHIFT_LED_INDEX, hsvb, USE_RGB_MATRIX_VALUE_ON);
        // NOTE so this will not work:
        set_led_color(RSHIFT_LED_INDEX, hsvb, USE_RGB_MATRIX_VALUE_ON);
    }
}


// TODO func for tapdance rshift hold (=shift+ctrl)

// Set LED for Caps Lock
void set_caps_led_color(void) {
    if (host_keyboard_led_state().caps_lock) {
        HSVB hsvb = L_BRED;
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

// SET LED RGB & BREATHING CYCLE BASED ON LAYER AND KEYCODES
// TODO orig:
//void set_layer_color( uint8_t layer, uint8_t index, uint16_t keycode) {
void set_layer_color( uint8_t layer, uint8_t led_min, uint8_t led_max) {
    // By default, use global LED brightness set by user
    bool use_curr_brightness = USE_RGB_MATRIX_VALUE_ON;

    for (uint8_t index = led_min; index < led_max; index++) {
        HSVB hsvb = ledmaps[layer][index].hsvb;
        set_led_color(index, hsvb, use_curr_brightness);
    }

    // TODO orig rm:
    /*
    //-------------------------------------------------------
    HSVB hsvb = ledcolors[layer].hsvb[rgb_matrix_index[index]];

    // flag if ledcolor is set for key without keycode
    if (keycode == KC_NO) {
        if (hsvb.v > 0) {
            hsvb.h = 0;
            hsvb.s = 0;
            hsvb.v = 25;
            hsvb.b = 30;
        }
    }

    // flag if ledcolor is not set for keys with transparent keycode
    // flag if ledcolor is not set for key with keycode.
    else if (keycode >= KC_TRNS) {
        if (hsvb.v == 0) {
            hsvb.h = 0;
            hsvb.s = 25;
            hsvb.v = 25;
            hsvb.b = 30;
        }
    }

    set_led_color(index, hsvb, use_curr_brightness);
    //-------------------------------------------------------
    */
}

