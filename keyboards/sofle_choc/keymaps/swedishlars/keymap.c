/* Copyright 2021 Dane Evans
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>

#include QMK_KEYBOARD_H

// TODO this is used for rgb lighting, not matrix, keep for ref in casee I can use similar for defining custom key effects?
/*
#define INDICATOR_BRIGHTNESS 30

#define HSV_OVERRIDE_HELP(h, s, v, Override) h, s , Override
#define HSV_OVERRIDE(hsv, Override) HSV_OVERRIDE_HELP(hsv,Override)

// Light combinations
#define SET_INDICATORS(hsv) \
	{0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {35+0, 1, hsv}
#define SET_UNDERGLOW(hsv) \
	{1, 6, hsv}, \
    {35+1, 6,hsv}
#define SET_NUMPAD(hsv)     \
	{35+15, 5, hsv},\
	  {35+22, 3, hsv},\
	  {35+27, 3, hsv}
#define SET_NUMROW(hsv) \
	{10, 2, hsv}, \
		{20, 2, hsv}, \
		{30, 2, hsv}, \
	  {35+ 10, 2, hsv}, \
	  {35+ 20, 2, hsv}, \
	  {35+ 30, 2, hsv}
#define SET_INNER_COL(hsv)	\
	{33, 4, hsv}, \
	  {35+ 33, 4, hsv}

#define SET_OUTER_COL(hsv) \
	{7, 4, hsv}, \
	  {35+ 7, 4, hsv}
#define SET_THUMB_CLUSTER(hsv) 	\
	{25, 2, hsv}, \
	  {35+ 25, 2, hsv}
#define SET_LAYER_ID(hsv) 	\
	{0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {35+0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
		{1, 6, hsv}, \
    {35+1, 6, hsv}, \
		{7, 4, hsv}, \
	  {35+ 7, 4, hsv}, \
		{25, 2, hsv}, \
	  {35+ 25, 2, hsv}
*/

enum sofle_layers {
    _DEFAULTS = 0,
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
    _NUMPAD,
    _SWITCH
};

// TODO cleanup
enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_LOWER,
    KC_RAISE,
    KC_ADJUST
};

// Custom keycode names
// Move to left desktop: C( = LCTL, G( = LGUI   result: LCTL + LGUI (meta) + LEFT ARROW
#define DESK_L C(G(KC_LEFT))
#define DESK_R C(G(KC_RIGHT))

// momentarily activate layer when held
#define LT_NUMP LT(_NUMPAD,KC_CAPS)
#define LT_SWITCH LT(_SWITCH,KC_LGUI)

// TODO tri-layer does not work well. lower and raise layers
/* #define KC_LOWER MO(_LOWER) */
/* #define KC_RAISE MO(_RAISE) */

// custom sounds
float click_sound[][2] = SONG(TERMINAL_SOUND);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 // layer 0
  [_QWERTY] = LAYOUT(
 // .-----------------------------------------------------------.                          ,-----------------------------------------------------------.
 // | esc     |    1    |    2    |   3     |    4    |   5     |                          |    6    |    7    |    8    |    9    |    0    | back    |
     KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                                KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_BSPC,
 // |---------+---------+---------+---------+---------+---------|                          |---------+---------+---------+---------+---------+---------|
 // | tab     |    Q    |    W    |    E    |    R    |    T    |                          |    Y    |    U    |    I    |    O    |    P    |   #     |
     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                                KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_NUHS,
 // |---------+---------+---------+---------|---------+---------|                          |---------+---------|---------|---------|---------+---------|
 // | caps/num|    A    |    S    |    D    |    F    |   G     |                          |    H    |    J    |    K    |    L    |    ;    |   '     |
     LT_NUMP,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                                KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
 // |---------+---------+---------+---------+---------+---------+----------.    .----------|---------+---------+---------+---------+---------+---------|
 // | lshift  |    Z    |    X    |         |         |    B    |          |    |          |         |left arr |down arr |right arr|         |         |
     KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_NO,          KC_NO,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
 // .---------+-------------------------------------------------/----------/    \----------\-------------------------------------------------+---------'
 //           |lgui/swtch|left ctl     |left alt  | lower      / space    /      \ enter    \  raise     |right alt |right ctl    |right gui |
               LT_SWITCH, KC_LCTL,      KC_LALT,   KC_LOWER,     KC_SPC,             KC_ENT,   KC_RAISE,  KC_RALT,   KC_RCTL,      KC_RGUI
 //           |__________|_____________|__________|__________/__________/          \__________\__________|__________|_____________|__________|
),

// layer 1
[_LOWER] = LAYOUT(
 // .-----------------------------------------------------------.                          ,-----------------------------------------------------------.
 // |         | F1      | F2      | F3      | F4      | F5      |                          | F6      | F7      | F8      |F9       | F10     |frw del  |
     _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,                               KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_DEL,
 // |---------+---------+---------+---------+---------+---------|                          |---------+---------+---------+---------+---------+---------|
 // | `       | F11     | F12     |         | 4       | 5       |                          | -       | =       |         |         | [       | ]       |
     KC_GRV,   KC_F11,   KC_F12,   KC_NO,    KC_4,     KC_5,                                KC_MINS,  KC_EQL,   KC_NO,    KC_NO,    KC_LBRC,  KC_RBRC,
 // |---------+---------+---------+---------|---------+---------|                          |---------+---------|---------|---------|---------+---------|
 // |         |         |         |         |         |page up  |                          |         |         |up arr   |         |         |         |
     _______,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_PGUP,                             KC_NO,    KC_NO,    KC_UP,    KC_NO,    KC_NO,    KC_NO,
 // |---------+---------+---------+---------+---------+---------+----------.    .----------|---------+---------+---------+---------+---------+---------|
 // |         | \       |         |         |         |page down|          |    |          |         |left arr |down arr |right arr|         |         |
     _______,  KC_BSLS,  KC_NO,    KC_NO,    KC_NO,    KC_PGDN,  _______,        _______,   KC_NO,    KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_NO,    _______,
 // .---------+-------------------------------------------------/----------/    \----------\-------------------------------------------------+---------'
 //           |          |             |          |            /          /      \          \            |          |             |          |
               _______,   _______,      _______,   _______,     _______,            _______,   _______,   _______,   _______,      _______
 //           |__________|_____________|__________|__________/__________/          \__________\__________|__________|_____________|__________|
),

// layer 2
[_RAISE] = LAYOUT(
 // .-----------------------------------------------------------.                          ,------------------------------------------------ ----------.
 // |         |         |         |         |         |         |                          |         |         |         |         |         |frw del  |
     _______,  _______,  _______,  _______,  _______,  _______,                             _______,  _______,  _______,  _______,  _______,  KC_DEL,
 // |---------+---------+---------+---------+---------+---------|                          |---------+---------+---------+---------+---------+---------|
 // |         |insert   |print scr|app menu |         |         |                          | ^       | &       | *       | (       | )       |backspace|
     _______,  KC_INS,   KC_PSCR,  KC_APP,   XXXXXXX,  XXXXXXX,                             KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_BSPC,
 // |---------+---------+---------+---------|---------+---------|                          |---------+---------|---------|---------|---------+---------|
 // |         |left alt |left ctl |left shft|         |cap lock |                          | -       | =       | {       | }       | |       | ~       |
     _______,  KC_LALT,  KC_LCTL,  KC_LSFT,  XXXXXXX,  KC_CAPS,                             KC_MINS,  KC_EQL,   KC_LCBR,  KC_RCBR,  KC_PIPE,  KC_GRV,
 // |---------+---------+---------+---------+---------+---------+----------.    .----------|---------+---------+---------+---------+---------+---------|
 // |         | undo    | cut     |copy     |paste    |         |          |    |          | _ uscore| +       | [ and { | ] and } | \ and | | ~       |
     _______,  KC_UNDO,  KC_CUT,   KC_COPY,  KC_PASTE, XXXXXXX,  _______,        _______,   KC_UNDS,  KC_PLUS,  KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_TILD,
 // .---------+-------------------------------------------------/----------/    \----------\-------------------------------------------------+---------'
 //           |          |             |          |            /          /      \          \            |          |             |          |
               _______,   _______,      _______,   _______,     _______,            _______,   _______,   _______,   _______,      _______
 //           |__________|_____________|__________|__________/__________/          \__________\__________|__________|_____________|__________|
),

// layer 3
[_ADJUST] = LAYOUT(
 // .-----------------------------------------------------------.                          ,------------------------------------------------ ----------.
 // |clear mem|         |         |         |         |         |                          |         |         |         |         |         |         |
     EE_CLR,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                             XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
 // |---------+---------+---------+---------+---------+---------|                          |---------+---------+---------+---------+---------+---------|
 // |         |         |         |         |         |         |                          |         |         |         |         |         |         |
     QK_BOOT,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                             XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
 // |---------+---------+---------+---------|---------+---------|                          |---------+---------|---------|---------|---------+---------|
 // |rgb toggl| hue +-  | sat +-  |bright +-|         |         |                          |desktop <|         |         |desktop >|         |         |
     RGB_TOG,  RGB_HUI,  RGB_SAI,  RGB_VAI,  XXXXXXX,  XXXXXXX,                             DESK_L,   KC_NO,    KC_NO,    DESK_R,   XXXXXXX,  XXXXXXX,
 // |---------+---------+---------+---------+---------+---------+----------.    .----------|---------+---------+---------+---------+---------+---------|
 // |rgb mode | hue -   | sat -   |bright - |         |         |          |    |          |         | prev    | play    | next    |         |         |
     RGB_MOD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  XXXXXXX,  XXXXXXX,  XXXXXXX,        XXXXXXX,   XXXXXXX,  KC_MPRV,  KC_MPLY,  KC_MNXT,  XXXXXXX,  XXXXXXX,
 // .---------+-------------------------------------------------/----------/    \----------\-------------------------------------------------+---------'
 //           |          |             |          |            /          /      \          \            |          |             |          |
               _______,   _______,      _______,   _______,     _______,            _______,   _______,   _______,   _______,      _______
 //           |__________|_____________|__________|__________/__________/          \__________\__________|__________|_____________|__________|
),

// layer 4
// TODO custom name for OSM(MOD_MEH): one shot (activate modifier for next key pressed) LCTL + SHIFT + ALT + KEY
// although I don't know what I would use this for?
[_NUMPAD] = LAYOUT(
 // .-----------------------------------------------------------.                          ,------------------------------------------------ ----------.
 // |         |         |         |         |         |         |                          |         | NumLck  |         |         |         |         |
     _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                             _______,  KC_NUM,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
 // |---------+---------+---------+---------+---------+---------|                          |---------+---------+---------+---------+---------+---------|
 // |  `      |         |         |         |         |         |                          |   ^     |   7     |   8     |   9     |   *     |         |
     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                             KC_CIRC,  KC_P7,    KC_P8,    KC_P9,    KC_ASTR,  XXXXXXX,
 // |---------+---------+---------+---------|---------+---------|                          |---------+---------|---------|---------|---------+---------|
 // |         |         |         |         |         |         |                          |   -     |   4     |   5     |   6     |         |   |     |
     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                             KC_MINS,  KC_P4,    KC_P5,    KC_P6,    KC_EQL,   KC_PIPE,
 // |---------+---------+---------+---------+---------+---------+----------.    .----------|---------+---------+---------+---------+---------+---------|
 // |         |         |         |         |         |         |          |    |          |   +     |   1     |   2     |   3     |   \     | Shift   |
     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,        _______,   KC_PLUS,  KC_P1,    KC_P2,    KC_P3,    KC_SLSH,  _______,
 // .---------+-------------------------------------------------/----------/    \----------\-------------------------------------------------+---------'
 //           | Bspc     | WIN         | LOWER    | Enter      /  Space   /      \ Enter    \ SPACE      | 0        |  . (dot)    | RAlt     |
               _______,   OSM(MOD_MEH), _______,   _______,     _______,            _______,   _______,   KC_P0,     KC_PDOT,      _______
 //           |__________|_____________|__________|__________/__________/          \__________\__________|__________|_____________|__________|
),

// layer 5
// TODO testing haptic toggle, rgb_matrix modes, audio toggle
[_SWITCH] = LAYOUT(
 // .-----------------------------------------------------------.                          ,------------------------------------------------ ----------.
 // |         |         |         |         |         |         |                          |         |         |         |         |         |audio tog|
     _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                             XXXXXXX, XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  AU_TOGG,
 // |---------+---------+---------+---------+---------+---------|                          |---------+---------+---------+---------+---------+---------|
 // |base lyr |lower    |raise    |adjust   |numpad   |switch   |                          |         |         |         |         |         |reboot   |
     TO(0),    TO(1),    TO(2),    TO(3),    TO(4),    TO(5),                               KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    QK_BOOT,
 // |---------+---------+---------+---------+---------+---------|                          |---------+---------+---------+---------+---------+---------|
 // |         |         |         |         |         |         |                          |         |         |         |         |         |clear mem|
     KC_NO,    KC_NO,    KC_BRIU,  KC_NO,    KC_NO,    KC_NO,                               KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    EE_CLR,
 // |---------+---------+---------+---------+---------+---------+----------.    .----------|---------+---------+---------+---------+---------+---------|
 // |sys sleep|         |         |         |         |         |          |    |          |hapt cont|         |         |         |         |haptic on|
     KC_SLEP,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,          KC_NO,     HF_CONT,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    HF_TOGG,
 // .---------+-------------------------------------------------/----------/    \----------\-------------------------------------------------+---------'
 //           |          |             |          |            /  Space   /      \ rgb mode \            |          |             |          |
               KC_NO,     KC_NO,        KC_NO,     KC_NO,       KC_NO,              RGB_MOD,   KC_NO,     KC_NO,     KC_NO,        KC_NO
 //           |__________|_____________|__________|__________/__________/          \__________\__________|__________|_____________|__________|

	),
};

#ifdef RGBLIGHT_ENABLE
// TODO rm
/* char layer_state_str[70]; */
// Now define the array of layers. Later layers take precedence

// QWERTY
// Light on inner column and underglow
/* const rgblight_segment_t PROGMEM layer_qwerty_lights[] = RGBLIGHT_LAYER_SEGMENTS( */
/*   SET_LAYER_ID(HSV_RED), */
/*   // TODO test: */
/*   SET_INDICATORS(HSV_ORANGE) */
/* ); */

// _NUM
// Light on outer column and underglow
/* const rgblight_segment_t PROGMEM layer_num_lights[] = RGBLIGHT_LAYER_SEGMENTS( */
/* 	SET_LAYER_ID(HSV_TEAL) */

/* ); */
// _SYMBOL,
// Light on inner column and underglow
/* const rgblight_segment_t PROGMEM layer_symbol_lights[] = RGBLIGHT_LAYER_SEGMENTS( */
/* 	SET_LAYER_ID(HSV_BLUE) */

/*     ); */
// _COMMAND
// Light on inner column and underglow
/* const rgblight_segment_t PROGMEM layer_command_lights[] = RGBLIGHT_LAYER_SEGMENTS( */
/*   SET_LAYER_ID(HSV_PURPLE) */
/* ); */

//_NUMPAD
/* const rgblight_segment_t PROGMEM layer_numpad_lights[] = RGBLIGHT_LAYER_SEGMENTS( */
/* 	SET_INDICATORS(HSV_ORANGE), */
/*     SET_UNDERGLOW(HSV_ORANGE), */
/* 	SET_NUMPAD(HSV_BLUE), */
/*     {7, 4, HSV_ORANGE}, */
/*     {25, 2, HSV_ORANGE}, */
/*     {35+6, 4, HSV_ORANGE}, */
/*     {35+25, 2, HSV_ORANGE} */
/*     ); */
// _SWITCHER   // light up top row
/* const rgblight_segment_t PROGMEM layer_switcher_lights[] = RGBLIGHT_LAYER_SEGMENTS( */
/* 	SET_LAYER_ID(HSV_GREEN), */
/* 	SET_NUMROW(HSV_GREEN) */
/* ); */

// TODO not used
/* const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST( */

/*     layer_qwerty_lights, */
/* 	layer_num_lights,// overrides layer 1 */
/* 	layer_symbol_lights, */
/*     layer_command_lights, */
/* 	layer_numpad_lights, */
/* 	layer_switcher_lights,  // Overrides other layers */
/* 	layer_colemakdh_lights */
/* ); */

// TODO this is used for rgblight, not rgb_matrix, rm:
/* layer_state_t layer_state_set_user(layer_state_t state) { */
/* 	rgblight_set_layer_state(0, layer_state_cmp(state, _DEFAULTS) && layer_state_cmp(default_layer_state,_QWERTY)); */
/* 	rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER)); */
/* 	rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE)); */
/* 	rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST)); */
/* 	rgblight_set_layer_state(4, layer_state_cmp(state, _NUMPAD)); */
/* 	rgblight_set_layer_state(5, layer_state_cmp(state, _SWITCH)); */
/*     return state; */
/* } */
#endif


#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    // TODO testing layer indicator only on keys with configured keycodes
    // TODO see bm65 set_led_color for breathing effect
    // or can I use matrix flags? not found any docs on it
    if (get_highest_layer(layer_state) > 0) {
        uint8_t layer = get_highest_layer(layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                // TODO use this to store keycode:
                uint16_t kc = keymap_key_to_keycode(layer, (keypos_t){col,row});

                if (index >= led_min && index < led_max && index != NO_LED &&
                // TODO orig:
                /* keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) { */
                kc > KC_TRNS) {
                    // TODO use kc case?

                    // TODO default colors set max 255 values, which might draw too much current
                    // 100 seem to be a safe value?
                    /* rgb_matrix_set_color(index, RGB_GREEN); */
                    rgb_matrix_set_color(index, 0,100,0);
                }
                else {
                    rgb_matrix_set_color(index, RGB_OFF);
                }
            }
        }
    }

    // TODO testing layer indicator for all keys
    /* for (uint8_t i = led_min; i < led_max; i++) { */
    /*     switch(get_highest_layer(layer_state|default_layer_state)) { */
    /*         case 5: */
    /*             rgb_matrix_set_color(i, RGB_BLUE); */
    /*             break; */
    /*         case 4: */
    /*         case 3: */
    /*         case 2: */
    /*             rgb_matrix_set_color(i, RGB_BLUE); */
    /*             break; */
    /*         case 1: */
    /*             rgb_matrix_set_color(i, RGB_YELLOW); */
    /*             break; */
    /*         default: */
    /*             break; */
    /*     } */
    /* } */
    return false;
}

// TODO not used
/* void keyboard_post_init_user(void) { */
/*     // Enable the LED layers */
/*     rgblight_layers = my_rgb_layers; */
/* } */
#endif


#ifdef OLED_ENABLE
// TODO replace
static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

static void print_status_narrow(void) {
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adj\n"), false);
            break;
        case _NUMPAD:
            oled_write_P(PSTR("Nump\n"), false);
            break;
        case _SWITCH:
            oled_write_P(PSTR("Switch\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }

    // Keyboard LED Status
    // TODO check if this works
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
    return false;
}
#endif


// Enable sound and haptic for pointing device
#ifdef POINTING_DEVICE_ENABLE
report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
    if (left_report.buttons > 0) {
        PLAY_SONG(click_sound);
        haptic_play();
    }

    if (right_report.buttons > 0) {
        PLAY_SONG(click_sound);
        haptic_play();
    }

    return pointing_device_combine_reports(left_report, right_report);
}
#endif


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // TODO don't need this:
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;

        // tri_layer, when lower and raise keys are pressed, activate a third layer
        // TODO this is now built-in, do not need it:
        case KC_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;

        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;

        case KC_ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;

        // TODO testing custom sound, haptic - works on simple keycodes
        // rm:
        case KC_ENT:
            if (record->event.pressed) {
                PLAY_SONG(click_sound);
                haptic_play();
            }
            return true;

        // Process all other keycodes normally
        default:
            return true;
    }
}
