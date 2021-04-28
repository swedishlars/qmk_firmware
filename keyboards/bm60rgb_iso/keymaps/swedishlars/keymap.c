/* Copyright 2021 swedishlars
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

// LIB USED FOR  LED INDICATOR BREATHING EFFECT
#include "lib/lib8tion/lib8tion.h"

// CUSTOM KEYCODES
enum my_keycodes {
  RGB_TMOD = SAFE_RANGE
};

// TAPDANCE - definitions
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

// TAPDANCE KEYCODES
// LYR enables layers
// F1-12 will send Alt+FX on hold
enum {
    LYR,
    SLYR,
    CLYR,
    TF1, TF2, TF3, TF4, TF5, TF6, TF7, TF8, TF9, TF10, TF11, TF12
};

//  TAPDANCE - Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

//  TAPDANCE - switch layer functions
void td_lyr_finished(qk_tap_dance_state_t *state, void *user_data);
void td_lyr_reset(qk_tap_dance_state_t *state, void *user_data);

//  TAPDANCE - switch layer on hold functions
void td_lyrhold_finished(qk_tap_dance_state_t *state, void *user_data);
void td_lyrhold_reset(qk_tap_dance_state_t *state, void *user_data);

// TAPDANCE - alt functions
void td_alt_finished(qk_tap_dance_state_t *state, void *user_data);
void td_alt_reset(qk_tap_dance_state_t *state, void *user_data);


// LED colors 
// First 3 values are Hue, Saturation, Value (value=brightness).
// Last value sets breathing effect. 0 = no breathing. > 0 sets cycle time
#define L_DRED { 0, 255, 255, 0 }
// TODO rm: not enough difference:
#define L_LRED { 5, 250, 255, 0 }
#define L_BRED { 0, 255, 255, 30 }

#define L_DORA { 7, 255, 255, 0 }

#define L_DYEL { 25, 255, 255, 0 }
#define L_LYEL { 25, 240, 255, 0 }
#define L_BYEL { 25, 255, 255, 36 }

#define L_LGRE { 60, 255, 255, 0 }
#define L_DGRE { 85, 255, 255, 0 }
#define L_BGRE { 85, 255, 255, 37 }

#define L_DCYA { 127, 255, 255, 0 }
#define L_BCYA { 127, 255, 255, 38 }

#define L_DAZU { 150, 255, 255, 0 }
#define L_BAZU { 150, 255, 255, 39 }

#define L_DBLU { 169, 255, 255, 0 }
#define L_BBLU { 169, 255, 255, 41 }

#define L_DVIO { 180, 255, 255, 0 }
#define L_BVIO { 180, 255, 255, 42 }

#define L_DMAG { 201, 255, 255, 0 }
#define L_BMAG { 201, 255, 255, 46 }

#define L_DROS { 253, 255, 255, 0 }
#define L_BROS { 222, 255, 255, 40 }
#define L__OFF { 0, 0, 0, 0 }

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // DEFAULT LAYER
    [0] = LAYOUT_60_iso_arrow(
    //  ESC       1         2         3         4         5         6         7         8         9         0         -         =         BCKSPC
        KC_GESC,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,
    //  TAB       Q         W         E         R         T         Y         U         I         O         P         [         ]         ENTER
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,
    //  CAPS      A         S         D         F         G         H         J         K         L         ;         '         #
        TD(CLYR), KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,  KC_ENT,
    //  SHIFT     \         Z         X         C         V         B         N         M         ,         .         SHIFT     UP        ?
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_RSFT,  KC_UP,    KC_SLSH,
    //  CTRL      FN        ALT                                     SPACE                         ALTGR     SUPER     LEFT      DOWN      RIGHT
        KC_LCTL,  TD(LYR),  KC_LALT,                                KC_SPC,                       KC_RALT,  TD(SLYR), KC_LEFT,  KC_DOWN,  KC_RGHT
    ),

    // FN LAYER
    // TODO add mouse additionaljbutton keys
    [1] = LAYOUT_60_iso_arrow(
    //  ESC       1         2         3         4         5         6         7         8         9         0         -         =         BCKSPC
        TO(0),    TD(TF1),  TD(TF2),  TD(TF3),  TD(TF4),  TD(TF5),  TD(TF6),  TD(TF7),  TD(TF8),  TD(TF9),  TD(TF10), TD(TF11), TD(TF12), KC_DEL,
    //  TAB       Q         W         E         R         T         Y         U         I         O         P         [         ]         ENTER
        _______,  _______,  _______,  _______,  _______,  LCA(KC_T),_______,  KC_WH_U,  _______,  _______,  _______,  _______,  _______,
    //  CAPS      A         S         D         F         G         H         J         K         L         ;         '         #
        _______,  _______,  _______,  _______,  _______,  _______,  KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R,  _______,  _______,  _______,  _______,
    //  SHIFT     \         Z         X         C         V         B         N         M         ,         .         SHIFT     UP        ?
        _______,  _______,  _______,  _______,  _______,  _______,  KC_BTN2,  KC_WH_D,  _______,  _______,  _______,  _______,  KC_PGUP,  _______,
    //  CTRL      FN        ALT                                     SPACE                         ALTGR     SUPER     LEFT      DOWN      RIGHT
        _______,  _______,  TO(2),                                  KC_BTN1,                      TO(3),    _______,  KC_HOME,  KC_PGDN,  KC_END
    ),

    // RGB LAYER
    // TODO add default effect key!
    [2] = LAYOUT_60_iso_arrow(
    //  ESC       1         2         3         4         5         6         7         8         9         0         -         =         BCKSPC
        TO(0),    RGB_M_P,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_VAD,  RGB_VAI,  _______,
    //  TAB       Q         W         E         R         T         Y         U         I         O         P         [         ]         ENTER
        _______,  _______,  _______,  _______,  _______,  RGB_TOG,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    //  CAPS      A         S         D         F         G         H         J         K         L         ;         '         #
        _______,  _______,  RGB_SAI,  _______,  _______,  _______,  RGB_HUI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    //  SHIFT     \         Z         X         C         V         B         N         M         ,         .         SHIFT     UP        ?
        _______,  _______,  _______,  _______,  _______,  _______,  RGB_VAI,  _______,  RGB_MOD,  _______,  _______,  _______,  RGB_SPI,  _______,
    //  CTRL      FN        ALT                                     SPACE                         ALTGR     SUPER     LEFT      DOWN      RIGHT
        _______,  _______,  _______,                                _______,                      _______,  _______,  RGB_RMOD, RGB_SPD,  RGB_MOD
    ),

    // ADVANCED LAYER
    [3] = LAYOUT_60_iso_arrow(
    //  ESC       1         2         3         4         5         6         7         8         9         0         -         =         BCKSPC
        TO(0),    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    //  TAB       Q         W         E         R         T         Y         U         I         O         P         [         ]         ENTER
        _______,  _______,  _______,  _______,  RESET,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    //  CAPS      A         S         D         F         G         H         J         K         L         ;         '         #
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    //  SHIFT     \         Z         X         C         V         B         N         M         ,         .         SHIFT     UP        ?
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    //  CTRL      FN        ALT                                     SPACE                         ALTGR     SUPER     LEFT      DOWN      RIGHT
        _______,  _______,  _______,                                _______,                      _______,  _______,  _______,  _______,  _______
    ),
};

// CUSTOM RGB COLORS PER LAYER
const uint8_t PROGMEM ledcolors[][DRIVER_LED_TOTAL][4] = {
    // DEFAULT LAYER
    [0] = {
    //  ESC       1         2         3         4         5         6         7         8         9         0         -         =         BCKSPC
        L_DYEL,   L_DORA,   L_DORA,   L_DORA,   L_DORA,   L_DORA,   L_DORA,   L_DORA,   L_DORA,   L_DORA,   L_DORA,   L_DORA,   L_DORA,   L_DYEL,
    //  TAB       Q         W         E         R         T         Y         U         I         O         P         [         ]         ENTER
        L_DORA,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DORA,
    //  CAPS      A         S         D         F         G         H         J         K         L         ;         '         #
        L_DORA,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,
    //  SHIFT     \         Z         X         C         V         B         N         M         ,         .         SHIFT     UP        ?
        L_DORA,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DORA,   L_DYEL,   L_DRED,
    //  CTRL      FN        ALT                                     SPACE                         ALTGR     FN        LEFT      DOWN      RIGHT
        L_LGRE,   L_LGRE,   L_LGRE,                                 L_DRED,                       L_LGRE,   L_LGRE,   L_LYEL,   L_LYEL,   L_LYEL,
    //  UGLW69              UGLW68                        UGLW67              UGLW66                        UGLW65              UGLW64 
        L__OFF,             L__OFF,                       L__OFF,             L__OFF,                       L__OFF,             L__OFF
    },

    // FN LAYER   
    [1] = {
    //  ESC       1         2         3         4         5         6         7         8         9         0         -         =         BCKSPC
        L_BRED,   L_DORA,   L_DORA,   L_DORA,   L_DORA,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DORA,   L_DORA,   L_DORA,   L_DORA,   L_DYEL,
    //  TAB       Q         W         E         R         T         Y         U         I         O         P         [         ]         ENTER
        L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_DRED,   L__OFF,   L_DMAG,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,
    //  CAPS      A         S         D         F         G         H         J         K         L         ;         '         #
        L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_DROS,   L_DROS,   L_DROS,   L_DROS,   L__OFF,   L__OFF,   L__OFF,   
    //  SHIFT     \         Z         X         C         V         B         N         M         ,         .         SHIFT     UP        ?
        L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_DRED,   L_DMAG,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_LYEL,   L__OFF,
    //  CTRL      FN        ALT                                     SPACE                         ALTGR     FN        LEFT      DOWN      RIGHT
        L__OFF,   L__OFF,   L_DGRE,                                 L_DRED,                       L__OFF,   L__OFF,   L_LYEL,   L_LYEL,   L_LYEL,
    //  UGLW69              UGLW68                        UGLW67              UGLW66                        UGLW65              UGLW64 
        L_BRED,             L_BRED,                       L_BRED,             L_BRED,                       L_BRED,             L_BRED
    },

    // RGB LAYER  TODO change colors to greenish range
    [2] = {
    //  ESC       1         2         3         4         5         6         7         8         9         0         -         =         BCKSPC
        L_BGRE,   L_BBLU,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_BCYA,   L_BCYA,   L__OFF,
    //  TAB       Q         W         E         R         T         Y         U         I         O         P         [         ]         ENTER
        L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_BBLU,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,
    //  CAPS      A         S         D         F         G         H         J         K         L         ;         '         #
        L__OFF,   L__OFF,   L_BVIO,   L__OFF,   L__OFF,   L__OFF,   L_BMAG,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   
    //  SHIFT     \         Z         X         C         V         B         N         M         ,         .         SHIFT     UP        ?
        L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_BCYA,   L__OFF,   L_BBLU,   L__OFF,   L__OFF,   L__OFF,   L_BAZU,   L__OFF,
    //  CTRL      FN        ALT                                     SPACE                         ALTGR     FN        LEFT      DOWN      RIGHT
        L__OFF,   L__OFF,   L__OFF,                                 L__OFF,                       L__OFF,   L__OFF,   L_BBLU,   L_BAZU,   L_BBLU,
    //  UGLW69              UGLW68                        UGLW67              UGLW66                        UGLW65              UGLW64 
        L_BGRE,             L_BGRE,                       L_BGRE,             L_BGRE,                       L_BGRE,             L_BGRE
    },

    // ADVANCED   LAYER
    [3] = {
    //  ESC       1         2         3         4         5         6         7         8         9         0         -         =         BCKSPC
        L_BBLU,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,
    //  TAB       Q         W         E         R         T         Y         U         I         O         P         [         ]         ENTER
        L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_BBLU,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,
    //  CAPS28    A         S         D         F         G         H         J         K         L         ;         '         #
        L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   
    //  SHIFT     \         Z         X         C         V         B         N         M         ,         .         SHIFT     UP        ?
        L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,
    //  CTRL      FN        ALT                                     SPACE                         ALTGR     FN        LEFT      DOWN      RIGHT
        L__OFF,   L__OFF,   L__OFF,                                 L__OFF,                       L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,
    //  UGLW69              UGLW68                        UGLW67              UGLW66                        UGLW65              UGLW64 
        L_BBLU,             L_BBLU,                       L_BBLU,             L_BBLU,                       L_BBLU,             L_BBLU
    }
};

HSV get_hsv_color(uint8_t colorcode[]) {
    HSV hsv = {.h=pgm_read_byte(colorcode[0]), .s=pgm_read_byte(colorcode[1]), .v=pgm_read_byte(colorcode[2])};
    return hsv;
}

// TAPPING TERM PER KEY - determines timeout for what is a tap and what is a hold 
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(LYR):
        case TD(SLYR):
            return 160;
        case TD(CLYR):
            return 140;
        default:
            return TAPPING_TERM;
    }
}

// TODO testing rgb suspend. No diff unfortunately
void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
}


// SET RGB LEDS BASED ON LAYER
void set_layer_color( uint8_t layer) {
    // effect cycle timer example using user config:
    // uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);

    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        uint8_t val = pgm_read_byte(&ledcolors[layer][i][2]);
        uint8_t breathe = pgm_read_byte(&ledcolors[layer][i][3]);

        // If RGB layer is enabled, skip all leds with brightness set to 0.
        // This is so that the rgb effect mode can be previewed in layer.
        if (layer == 2 && val == 0) continue;

        // For key leds (index 0-63), allow brightness to be set by user.
        // But for underglow, always use bragthness vaule set in map above.
        if (i < 64) {
            // if the brightness of the led is set to 0 in the map, the value is not overriden by matrix effect, 
            // allowing the led to appear turned off. Else, set brightness to current rgb matrix value.
            if (val != 0) {
                val = rgb_matrix_get_val();
            }
        } 

        // If breathe, set val based on time cycle
        if (breathe > 0) {
            // per key breathing effect cycle timer.
            uint16_t time = scale16by8(g_rgb_timer, breathe);
            uint8_t hsv_breathe_val = abs8(sin8(time) - 128) * 2;
            val = scale8(hsv_breathe_val, val);
        }

        HSV hsv = { .h = pgm_read_byte(&ledcolors[layer][i][0]), .s = pgm_read_byte(&ledcolors[layer][i][1]), .v = val};
        RGB rgb = hsv_to_rgb( hsv );
        rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
    }
}


// CUSTOM KEYCODES & MACROS
// TODO make super hold == fn
/* bool process_record_user(uint16_t keycode, keyrecord_t *record) { */
/*     switch (keycode) { */
/*         case KC_X: { */
/*             break; */
/*         } */
/*         default: */
/*             return true; // Process all other keycodes normally */
/*     } */
/* } */


// LED INDICATORS
void rgb_matrix_indicators_user(void) {
    uint32_t mode = rgb_matrix_get_mode();

    // Assign custom layer colors if the rgb matrix is on.
    // For default layer only assign colors if mode is SOLID COLORS => No animations running.
    // For all other layers, always set custom colors.
    // For some layers, set an underglow breathing effect.
    if(rgb_matrix_is_enabled() == 1) {
        uint8_t layer = biton32(layer_state);
        switch (layer) {
            case 0:
                if (mode == 1) set_layer_color(0);
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
    if (host_keyboard_led_state().caps_lock) {
        uint8_t hsv_col[4] = L_DBLU;
        // TODO add get_rgb_color()!
        HSV hsv = get_hsv_color(hsv_col);
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(28, rgb.r, rgb.g, rgb.b);
    }
}


// TAPDANCE - Common. Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } 
    else if (state->count == 2) return TD_DOUBLE_TAP;
    else if (state->count == 3) return TD_TRIPLE_TAP;
    else return TD_UNKNOWN;
}


// TAPDANCE - layers. Tap to enable layers
static td_tap_t td_lyr_tap_state = {.is_press_action = true, .state = TD_NONE};

void td_lyr_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_lyr_tap_state.state = cur_dance(state);

    switch (td_lyr_tap_state.state) {
        // Toggle layer 1
        case TD_SINGLE_TAP:
            if (layer_state_is(1)) layer_off(1);
            else layer_on(1);
            break;
        // Momentarily turn on layer 1
        case TD_SINGLE_HOLD: layer_on(1); break;
        // Toggle layer 2
        case TD_DOUBLE_TAP:
            if (layer_state_is(2)) layer_off(2);
            else layer_on(2);
            break;
        // Toggle layer 3
        case TD_TRIPLE_TAP:
            if (layer_state_is(3)) layer_off(3);
            else layer_on(3);
            break;
        case TD_NONE: break;
        case TD_UNKNOWN: break;
    }
}

void td_lyr_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (td_lyr_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(1);
    }
    td_lyr_tap_state.state = TD_NONE;
}


// TAPDANCE - Tap for normal KC_X, hold to enable layers
// Func retreives current keycode from user_data in custom tapdance action.
static td_tap_t td_lyrhold_tap_state = {.is_press_action = true, .state = TD_NONE};

void td_lyrhold_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_lyrhold_tap_state.state = cur_dance(state);
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;
    uint16_t keycode = pair->kc1;

    switch (td_lyrhold_tap_state.state) {
        case TD_SINGLE_TAP: register_code(keycode); break;
        case TD_SINGLE_HOLD: layer_on(1); break;
        case TD_DOUBLE_TAP: register_code(keycode); break;
        case TD_TRIPLE_TAP: register_code(keycode); break;
        case TD_NONE: break;
        case TD_UNKNOWN: break;
    }
}

void td_lyrhold_reset(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;
    uint16_t keycode = pair->kc1;

    switch (td_lyrhold_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(keycode); break;
        case TD_SINGLE_HOLD: layer_off(1); break;
        case TD_DOUBLE_TAP: unregister_code(keycode); break;
        case TD_TRIPLE_TAP: unregister_code(keycode); break;
        case TD_UNKNOWN: break;
        case TD_NONE: break; 
    }
    td_lyrhold_tap_state.state = TD_NONE;
}


// TAPDANCE - Tap for normal KC_X. Hold to send Alt+KC_X
// Func retreives current keycode from user_data in custom tapdance action.
// This means I can use this func for any keycodes.
// see: https://github.com/qmk/qmk_firmware/commit/ad7a5bdc4f2527f47ca22885e5d0b689fb8d4518
// and this one: https://www.reddit.com/r/olkb/comments/kcfs52/qmk_generic_handler_for_tap_dance/
static td_tap_t td_alt_tap_state = {.is_press_action = true, .state = TD_NONE};

void td_alt_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_alt_tap_state.state = cur_dance(state);
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;
    uint16_t keycode = pair->kc1;

    switch (td_alt_tap_state.state) {
        case TD_SINGLE_TAP: register_code(keycode); break;
        case TD_SINGLE_HOLD: register_code16(LALT(keycode)); break;
        case TD_DOUBLE_TAP: register_code(keycode); break;
        case TD_TRIPLE_TAP: register_code(keycode); break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
}

void td_alt_reset(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;
    uint16_t keycode = pair->kc1;

    switch (td_alt_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(keycode); break;
        case TD_SINGLE_HOLD: unregister_code16(LALT(keycode)); break;
        case TD_DOUBLE_TAP: unregister_code(keycode); break;
        case TD_TRIPLE_TAP: unregister_code(keycode); break;
        case TD_UNKNOWN: break;
        case TD_NONE: break; 
    }
    td_alt_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    // Layer tapdance for right FN
    [LYR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_lyr_finished, td_lyr_reset),
    // Layer change on right Super hold
    [SLYR] = ACTION_TAP_DANCE_FN_ADVANCED_KEYCODE(NULL, td_lyrhold_finished, td_lyrhold_reset, KC_LGUI),
    // Layer change on Caps hold
    [CLYR] = ACTION_TAP_DANCE_FN_ADVANCED_KEYCODE(NULL, td_lyrhold_finished, td_lyrhold_reset, KC_CAPS),
    // Hold to send ALT+KC_X
    [TF1] = ACTION_TAP_DANCE_FN_ADVANCED_KEYCODE(NULL, td_alt_finished, td_alt_reset, KC_F1),
    [TF2] = ACTION_TAP_DANCE_FN_ADVANCED_KEYCODE(NULL, td_alt_finished, td_alt_reset, KC_F2),
    [TF3] = ACTION_TAP_DANCE_FN_ADVANCED_KEYCODE(NULL, td_alt_finished, td_alt_reset, KC_F3),
    [TF4] = ACTION_TAP_DANCE_FN_ADVANCED_KEYCODE(NULL, td_alt_finished, td_alt_reset, KC_F4),
    [TF5] = ACTION_TAP_DANCE_FN_ADVANCED_KEYCODE(NULL, td_alt_finished, td_alt_reset, KC_F5),
    [TF6] = ACTION_TAP_DANCE_FN_ADVANCED_KEYCODE(NULL, td_alt_finished, td_alt_reset, KC_F6),
    [TF7] = ACTION_TAP_DANCE_FN_ADVANCED_KEYCODE(NULL, td_alt_finished, td_alt_reset, KC_F7),
    [TF8] = ACTION_TAP_DANCE_FN_ADVANCED_KEYCODE(NULL, td_alt_finished, td_alt_reset, KC_F8),
    [TF9] = ACTION_TAP_DANCE_FN_ADVANCED_KEYCODE(NULL, td_alt_finished, td_alt_reset, KC_F9),
    [TF10] = ACTION_TAP_DANCE_FN_ADVANCED_KEYCODE(NULL, td_alt_finished, td_alt_reset, KC_F10),
    [TF11] = ACTION_TAP_DANCE_FN_ADVANCED_KEYCODE(NULL, td_alt_finished, td_alt_reset, KC_F11),
    [TF12] = ACTION_TAP_DANCE_FN_ADVANCED_KEYCODE(NULL, td_alt_finished, td_alt_reset, KC_F12)
};
