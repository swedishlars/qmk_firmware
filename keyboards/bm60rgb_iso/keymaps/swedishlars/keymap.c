/* Copyright 2020 markva
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
#include QMK_KEYBOARD_H


// TAP DANCE - definitions
// TODO move after keymaps
// TODO not sure double triple tap is comfortable?
// prhaps better use simpler enable layer 2-3 from layer 1?
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_TRIPLE_TAP
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    LYR, // Our custom tap dance key; add any other tap dance keys to this enum 
};

//  TAP DANCE - Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

//  TAP DANCE - Functions associated with individual tap dances
void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);


// TODO move RGB to layer 2, move RESET to layer 3
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // DEFAULT LAYER
    [0] = LAYOUT_60_iso_arrow(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_RSFT, KC_UP,   KC_SLSH,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                    KC_RALT, TD(LYR), KC_LEFT, KC_DOWN, KC_RGHT
    ),
    // FN LAYER TODO rm rgb
    [1] = LAYOUT_60_iso_arrow(
        _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGUP, _______,
        _______, _______, _______,                            _______,                   TO(0),   _______, KC_HOME, KC_PGDN, KC_END
    ),

    // RGB LAYER
    [2] = LAYOUT_60_iso_arrow(
        TO(0),   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_VAD, RGB_VAI, TO(0),
        _______, _______, _______, RGB_HUI, _______, RGB_TOG, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, RGB_SAI, _______, _______, _______, RGB_HUI, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, RGB_VAI, _______, RGB_MOD, _______, _______, _______, RGB_SPI, _______,
        _______, _______, _______,                            _______,                   TO(0),   _______, RGB_RMOD,RGB_SPD, RGB_MOD
    ),

    // ADVANCED LAYER
    [3] = LAYOUT_60_iso_arrow(
        TO(0),   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TO(0),
        _______, _______, _______, _______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                            _______,                   TO(0),   _______, _______, _______, _______
    ),
};

// TAPPING TERM PER KEY - determines timeout for what is a tap and what is a hold
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(LYR):
            return 170;
        default:
            return TAPPING_TERM;
    }
}

// LED colors as Hue Saturation Value (value=brightness)
#define L_DRED 0, 255, 255
#define L_DORA 7, 255, 255
#define L_DYEL 25, 255, 255
#define L_DAZU 150, 255, 255
#define L_DGRE 85, 255, 255
#define L_LGRE 60, 255, 255
#define L_DMAG 201, 255, 255
#define L_DBLU 169, 255, 255
#define L__OFF 0, 0, 0

// TODO can I remove the value (last int)?:
/* const uint8_t PROGMEM ledcolors[][DRIVER_LED_TOTAL][2] = { */
const uint8_t PROGMEM ledcolors[][DRIVER_LED_TOTAL][3] = {
    // DEFAULT LAYER
    [0] = {
        // row 1, Esc to backspace - 14 keys TODO add led index range here in comment
        {L_DYEL}, {L_DORA}, {L_DORA}, {L_DORA}, {L_DORA}, {L_DORA}, {L_DORA}, {L_DORA}, {L_DORA}, {L_DORA}, {L_DORA}, {L_DORA}, {L_DORA}, {L_DYEL},
        // row 2, tab to Enter - 14 keys
        {L_DORA}, {L_DRED}, {L_DRED}, {L_DRED}, {L_DRED}, {L_DRED}, {L_DRED}, {L_DRED}, {L_DRED}, {L_DRED}, {L_DRED}, {L_DRED}, {L_DRED}, {L_DGRE},
        // row 3, capslock to #~ - 13 keys
        {L_DORA}, {L_DRED}, {L_DRED}, {L_DRED}, {L_DRED}, {L_DRED}, {L_DRED}, {L_DRED}, {L_DRED}, {L_DRED}, {L_DRED}, {L_DRED}, {L_DRED},
        // row 4, shift to /? - 14 keys
        {L_DORA}, {L_DRED}, {L_DRED}, {L_DRED}, {L_DRED}, {L_DRED}, {L_DRED}, {L_DRED}, {L_DRED}, {L_DRED}, {L_DRED}, {L_DORA}, {L_DMAG}, {L_DRED},
        // row 5, ctrl to right arrow - 9 keys
        {L_DGRE}, {L_DGRE}, {L_DGRE}, {L_DRED}, {L_DGRE}, {L_DGRE}, {L_DMAG}, {L_DMAG}, {L_DMAG},
        // underglow, right to left??
        {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}
    },

    // FN LAYER
    [1] = {
        // row 1, Esc to backspace - 14 keys
        {L_DRED}, {L_LGRE}, {L_LGRE}, {L_LGRE}, {L_LGRE}, {L_DORA}, {L_DORA}, {L_DORA}, {L_DORA}, {L_LGRE}, {L_LGRE}, {L_LGRE}, {L_LGRE}, {L_DYEL},
        // row 2, tab to Enter - 14 keys
        {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF},
        // row 3, capslock to #~ - 13 keys
        {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, 
        // row 4, shift to /? - 14 keys
        {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L_DMAG}, {L__OFF},
        // row 5, ctrl to right arrow - 9 keys
        {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L_DRED}, {L_DRED}, {L_DMAG}, {L_DMAG}, {L_DMAG},
        // underglow, right to left??
        {L_DRED}, {L_DRED}, {L_DRED}, {L_DRED}, {L_DRED}, {L_DRED}
    },

    // RGB LAYER
    [2] = {
        // row 1, Esc to backspace - 14 keys
        {L_DRED}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L_DYEL}, {L_DYEL}, {L_DRED},
        // row 2, tab to Enter - 14 keys
        {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF},
        // row 3, capslock to #~ - 13 keys
        {L__OFF}, {L__OFF}, {L_DORA}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, 
        // row 4, shift to /? - 14 keys
        {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L_DYEL}, {L__OFF}, {L_DGRE}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF},
        // row 5, ctrl to right arrow - 9 keys
        {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L_DRED}, {L_DRED}, {L_DGRE}, {L__OFF}, {L_DGRE},
        // underglow, right to left??
        {L_DGRE}, {L_DGRE}, {L_DGRE}, {L_DGRE}, {L_DGRE}, {L_LGRE}
    },

    // ADVANCED LAYER
    [3] = {
        // row 1, Esc to backspace - 14 keys
        {L_DRED}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L_DRED},
        // row 2, tab to Enter - 14 keys
        {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L_DBLU}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF},
        // row 3, capslock to #~ - 13 keys
        {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, 
        // row 4, shift to /? - 14 keys
        {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF},
        // row 5, ctrl to right arrow - 9 keys
        {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF}, {L_DRED}, {L__OFF}, {L__OFF}, {L__OFF}, {L__OFF},
        // underglow, right to left??
        {L_DBLU}, {L_DBLU}, {L_DBLU}, {L_DBLU}, {L_DBLU}, {L_DBLU}
    }
};

// set per layer color
// TODO not used, rm?
const uint8_t PROGMEM layercolors[][2] = {
    [0] = {240,155}
};

void set_layer_color( int layer) {
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        uint8_t val = pgm_read_byte(&ledcolors[layer][i][2]);
        // if the brightness of the led is set to 0 in the map,
        // the value is not overriden with global controls, allowing the led
        // to appear turned off
        HSV hsv = { .h = pgm_read_byte(&ledcolors[layer][i][0]), .s = pgm_read_byte(&ledcolors[layer][i][1]), .v = val == 0 ? 0 : rgb_matrix_get_val()};
        RGB rgb = hsv_to_rgb( hsv );
        rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
    }
}

// Set layer color for all leds
void set_layer_color_all( uint8_t layer ) {
    HSV hsv = { .h = pgm_read_byte(&layercolors[layer][0]), .s = pgm_read_byte(&layercolors[layer][1]), .v = rgb_matrix_get_val()};
    RGB rgb = hsv_to_rgb( hsv );
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
    }
}

// Set indicator led colors for layers
// Set led per key led color when certain keys are pressed or different layers are enabled
// see: https://gist.github.com/fdidron/ca9f4a70089ce4f15753fac54be59c44
void rgb_matrix_indicators_user(void) {
    // Get rgb mode
    uint32_t mode = rgb_matrix_get_mode();

    // assign colors if the matrix is on and the current mode
    // is SOLID COLORS => No animations running
    if(rgb_matrix_is_enabled() == 1 && mode == 1) {
        uint8_t layer = biton32(layer_state);
        switch (layer) {
            case 0:
                /* set_layer_color_all(0); */
                set_layer_color(0);
                break;
            case 1:
                set_layer_color(1);
                break;
            case 2:
                set_layer_color(2);
                break;
            case 3:
                set_layer_color(3);
                break;
        }
    }

    // Set led for Caps Lock
    // TODO create func for setting individual led using my hsv color defines
    // or use builtin set_hsv_color method? This is temp using rgb
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(28, 0, 200, 200);
    }
}

// TAPDANCE - Common. Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        return TD_DOUBLE_TAP;
    } else if (state->count == 3) {
        return TD_TRIPLE_TAP;
    } else return TD_UNKNOWN;
}

// TAPDANCE - Common. Initialize tap structure associated with example tap dance key
// TODO make single line
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// TAPDANCE - Individual. Enable layers
// TODO rename to td_layer_finished
void ql_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            /* tap_code(KC_QUOT); */
            if (layer_state_is(1)) {
                layer_off(1);
            } else {
                layer_on(1);
            }
            break;
        case TD_SINGLE_HOLD:
            // turn on layer 1
            layer_on(1);
            break;
        case TD_DOUBLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(2)) {
                // If already set, then switch it off
                layer_off(2);
            } else {
                // If not already set, then switch the layer on
                layer_on(2);
            }
            break;
        case TD_TRIPLE_TAP:
            if (layer_state_is(3)) {
                layer_off(3);
            } else {
                layer_on(3);
            }
            break;
        case TD_NONE:
            break;
        case TD_UNKNOWN:
            break;
    }
}

// TODO rename to td_layer_reset
void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(1);
    }
    ql_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    /* [TD_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ql_finished, ql_reset, 275) */
    [LYR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset)
};
