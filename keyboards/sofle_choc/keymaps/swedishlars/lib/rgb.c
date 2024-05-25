#include "rgb.h"

// TODO SHould this be in rgb.h?
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

const led_color_t PROGMEM ledcolors[] = {

// QWERTY
[0] = {{
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
                   L_DRED,    L_DRED,       L_DRED,    L_DRED,       L_DRED,            L_DRED,    L_DRED,    L_DRED,    L_DRED,       L_DRED,
     //           |__________|_____________|__________|__________/__________/          \__________\__________|__________|_____________|__________|
}},

// LOWER
[1] = {{
     // .-----------------------------------------------------------.                          ,-----------------------------------------------------------.
     // |         | F1      | F2      | F3      | F4      | F5      |                          | F6      | F7      | F8      |F9       | F10     |frw del  |
         L_DRED,   L_DORA,   L_DORA,   L_DORA,   L_DORA,   L_DORA,                              L_DORA,   L_DORA,   L_DORA,   L_DORA,   L_DORA,   L_MRED,
     // |---------+---------+---------+---------+---------+---------|                          |---------+---------+---------+---------+---------+---------|
     // |    `    | F11     | F12     |         |         | terminal|                          |         |         |    [    |    ]    |print scn|         |
         L_MRED,    L_DORA,   L_DORA,   L_DRED,   L_DRED,   L_DGRE,                              L_DRED,   L_DRED,   L_MRED,   L_MRED,   L_DGRE,  L_DRED,
     // |---------+---------+---------+---------|---------+---------|                          |---------+---------|---------|---------|---------+---------|
     // |         | app menu|         |tmux term|         |page up  |                          | left    |  down   | up      | right   |         |         |
         L_DRED,   L_DGRE,   L_DRED,   L_DGRE,   L_DRED,   L_DBLU,                              L_DBLU,   L_DBLU,   L_DBLU,   L_DBLU,   L_DRED,   L_DRED,
     // |---------+---------+---------+---------+---------+---------+----------.    .----------|---------+---------+---------+---------+---------+---------|
     // |         |         |         |         |         |page down|          |    |          |         |         |         |         |         |         |
         L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DBLU,                              L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,
     // .---------+-------------------------------------------------/----------/    \----------\-------------------------------------------------+---------'
     //           |    |     |             |          |            /          /      \          \            |          |             |          |
                   L_DRED,    L_DRED,       L_DRED,    L_BRED,       L_DRED,             L_DRED,   L_BRED,    L_DRED,    L_DRED,       L_DRED
     //           |__________|_____________|__________|__________/__________/          \__________\__________|__________|_____________|__________|
}},

// RAISE
[2] = {{
     // .-----------------------------------------------------------.                          ,------------------------------------------------ ----------.
     // |         | alt+F1  | alt+F2  | alt+F3  | alt+F4  | alt+F5  |                          | alt+F6  | alt+F7  | alt+F8  | alt+F9  | alt+F10 |insert   |
         L_DRED,   L_LORA,   L_LORA,   L_LORA,   L_LORA,   L_LORA,                              L_LORA,   L_LORA,   L_LORA,   L_LORA,   L_LORA,   L_LRED,
     // |---------+---------+---------+---------+---------+---------|                          |---------+---------+---------+---------+---------+---------|
     // |    ¬    | alt+F11 | alt+F12 |         |         |         |                          |         |         |    {    |    }    | play    |         |
         L_LRED,   L_LORA,   L_LORA,   L_DRED,   L_DRED,   L_DRED,                              L_DRED,   L_DRED,   L_LRED,   L_LRED,   L_LGRE,   L_DRED,
     // |---------+---------+---------+---------|---------+---------|                          |---------+---------|---------|---------|---------+---------|
     // |         | app menu|         |         |         | home    |                          |alt+left |alt+down |alt+up   |alt+right|         |         |
         L_DRED,   L_DVIO,   L_DRED,   L_DRED,   L_DRED,   L_LBLU,                              L_LBLU,   L_LBLU,   L_LBLU,   L_DBLU,   L_DRED,   L_DRED,
     // |---------+---------+---------+---------+---------+---------+----------.    .----------|---------+---------+---------+---------+---------+---------|
     // |         | undo    | cut     |copy     |paste    | end     |          |    |          |         | mute    | prev    | next    |         |         |
         L_DRED,   L_DCYA,   L_DCYA,   L_DCYA,   L_DCYA,   L_LBLU,                              L_DRED,   L_DGRE,   L_DGRE,   L_DGRE,   L_DRED,   L_DRED,
     // .---------+-------------------------------------------------/----------/    \----------\-------------------------------------------------+---------'
     //           |          |             |          |            /          /      \          \            |          | vol -       | vol +    |
                   L_DRED,    L_DRED,       L_DRED,    L_BRED,       L_DRED,             L_DRED,   L_BRED,    L_DRED,    L_DGRE,       L_DGRE
     //           |__________|_____________|__________|__________/__________/          \__________\__________|__________|_____________|__________|
}},

// NUMPAD
[3] = {{
     // .-----------------------------------------------------------.                          ,------------------------------------------------ ----------.
     // |         |         |         |         |         |         |                          |         |    7    |    8    |    9    |         |         |
         L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,                              L_LRED,   L_DORA,   L_DORA,   L_DORA,   L_DORA,   L_DRED,
     // |---------+---------+---------+---------+---------+---------|                          |---------+---------+---------+---------+---------+---------|
     // |         |         |         |         |         |         |                          |         |    4    |   5     |    6    |         |         |
         L_DRED,   L_DRED,   L_DRED,   L_MRED,   L_DRED,   L_DRED,                              L_DRED,   L_DORA,   L_DORA,   L_DORA,   L_DRED,   L_DRED,
     // |---------+---------+---------+---------|---------+---------|                          |---------+---------|---------|---------|---------+---------|
     // |         |         |         |         |         |         |                          |    =    |    1    |   2     |    3    |         |         |
         L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,                              L_DRED,   L_DORA,   L_DORA,   L_DORA,   L_DRED,   L_DRED,
     // |---------+---------+---------+---------+---------+---------+----------.    .----------|---------+---------+---------+---------+---------+---------|
     // |         |         |         |         |         |         |          |    |          |         |    *    |    ,    |    .    |   /     |         |
         L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,                              L_DRED,   L_LRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,
     // .---------+-------------------------------------------------/----------/    \----------\-------------------------------------------------+---------'
     //           |    |     |             |          | lower      /  Space   /      \ Enter    \  raise     |          |  - minus    | + plus   |
                   L_DRED,    L_DRED,       L_DRED,    L_DRED,       L_DRED,             L_DRED,   L_DRED,    L_MRED,    L_LRED,       L_LRED
     //           |__________|_____________|__________|__________/__________/          \__________\__________|__________|_____________|__________|
}},

// MOUSE
[4] = {{
     // .-----------------------------------------------------------.                          ,------------------------------------------------ ----------.
     // |         |         |         |         |         |         |                          |         |         |         |         |         |         |
         L__OFF,   L_DYEL,   L_DYEL,   L_DYEL,   L__OFF,   L__OFF,                              L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,
     // |---------+---------+---------+---------+---------+---------|                          |---------+---------+---------+---------+---------+---------|
     // |         |         |         |         |         |         |                          |         |         |         |         |         |         |
         L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,                              L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,
     // |---------+---------+---------+---------+---------+---------|                          |---------+---------+---------+---------+---------+---------|
     // |         |         |         |         |         |         |                          |         |         |         |         |         |         |
         L__OFF,   L_BCYA,   L_BCYA,   L_BCYA,   L__OFF,   L_DBLU,                              L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,
     // |---------+---------+---------+---------+---------+---------+----------.    .----------|---------+---------+---------+---------+---------+---------|
     // |         |         |         |         |         |         |          |    |          |         |         |         |         |         |         |
         L_DRED,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_DBLU,                              L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_DRED,
     // .---------+-------------------------------------------------/----------/    \----------\-------------------------------------------------+---------'
     //           |          |   ctrl      | alt      | mouse 3    /  mouse 1 /      \ mouse 2  \            |          |             |          |
                   L__OFF,    L_DRED,       L_DRED,    L_BORA,       L_BORA,             L_BORA,   L_DRED,    L_DRED,    L__OFF,       L__OFF
     //           |__________|_____________|__________|__________/__________/          \__________\__________|__________|_____________|__________|
}},

// ADJUST
[5] = {{
     // .-----------------------------------------------------------.                          ,------------------------------------------------ ----------.
     // |reboot    |base lyr|lower    |raise    |numpad   |mouse    |                          |switch   |         |         |         |         |reboot   |
         L_BRED,   L_BGRE,   L_BGRE,   L_BGRE,   L_BGRE,   L_BGRE,                              L_BGRE,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_BRED,
     // |---------+---------+---------+---------+---------+---------|                          |---------+---------+---------+---------+---------+---------|
     // |clear mem|         |         |         |rgb togg |rgb deflt|                          |         |         |         |         |         |clear mem|
         L_BYEL,   L__OFF,   L__OFF,   L__OFF,   L_BCYA,   L_DCYA,                              L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_BYEL,
     // |---------+---------+---------+---------+---------+---------|                          |---------+---------+---------+---------+---------+---------|
     // |         |audio tog|sys sleep|         |         |         |                          |haptic tg|         |         |         |         |         |
         L__OFF,   L_BORA,   L_BVIO,   L__OFF,   L__OFF,   L__OFF,                              L_BORA,   L__OFF,   L_BORA,   L__OFF,   L__OFF,   L__OFF,
     // |---------+---------+---------+---------+---------+---------+----------.    .----------|---------+---------+---------+---------+---------+---------|
     // |         |         |         |         |         |         |          |    |          |         |         |         |         |         |         |
         L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,                              L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,
     // .---------+-------------------------------------------------/----------/    \----------\-------------------------------------------------+---------'
     //           |          |             |          |            /          /      \          \            |          |rgb brght-   |rgb brght+|
                   L__OFF,    L__OFF,       L__OFF,    L__OFF,       L__OFF,             L__OFF,   L__OFF,    L__OFF,    L_DCYA,       L_DCYA
     //           |__________|_____________|__________|__________/__________/          \__________\__________|__________|_____________|__________|
}}

};


// Set LED for Caps Lock
void set_caps_led_color(void) {
    if (host_keyboard_led_state().caps_lock) {
        HSVB hsvb = L_BRED;
        set_led_color(26, hsvb, USE_RGB_MATRIX_VALUE_ON);
    }
}


// SET INDIVIDUAL LED RGB
// NOTE: Per key breathing effect cycle timer.
// Effect cycle timer example using user config:
// uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);
//
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
// TODO see if key matrix index is the same as my rgb_matrix_index
void set_layer_color( uint8_t layer, uint8_t index, uint16_t keycode) {

    // By default, use global LED brightness set by user
    bool use_curr_brightness = USE_RGB_MATRIX_VALUE_ON;

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
}

