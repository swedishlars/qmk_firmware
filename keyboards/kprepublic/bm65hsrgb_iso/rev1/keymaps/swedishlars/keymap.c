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

// TODO use digitizer to position cursor on top bar + ALT + TAB to cycle between pcoip window??
#include QMK_KEYBOARD_H

// LIB USED FOR  LED INDICATOR BREATHING EFFECT
#include "lib/lib8tion/lib8tion.h"

// LED colors 
// First 3 values are Hue, Saturation, Value (value=brightness).
// Last value sets breathing effect. 0 = no breathing. > 0 sets cycle time
#define L_DRED { 0, 255, 255, 0 }
#define L_BRED { 0, 255, 255, 30 }

#define L_DORA { 8, 255, 255, 0 }
#define L_LORA { 14, 255, 255, 0 }

#define L_DYEL { 36, 255, 255, 0 }
#define L_LYEL { 41, 255, 255, 0 }
#define L_BYEL { 36, 255, 255, 36 }

#define L_DGRE { 85, 255, 255, 0 }
#define L_LGRE { 60, 255, 255, 0 }
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

// TAPDANCE - definitions
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
// LR enables layers
// TF1-12 will send Alt+FX on hold
enum {
    LR1,
    LR1G,
    LR1C,
    LR2,
    LR3,
    AF1, AF2, AF3, AF4, AF5, AF6, AF7, AF8, AF9, AF10, AF11, AF12
};


//  TAPDANCE - Function associated with all tap dances
td_state_t cur_dance(tap_dance_state_t *state);

// TAPDANCE - activate layer. Tap to toggle, hold to activate momentarily.
void td_lr_tglholdmo_finished(tap_dance_state_t *state, void *user_data);
void td_lr_tglholdmo_reset(tap_dance_state_t *state, void *user_data);

// TAPDANCE - Tap to send normal KC_X, hold to momentarily enable layer
void td_lr_holdmo_finished(tap_dance_state_t *state, void *user_data);
void td_lr_holdmo_reset(tap_dance_state_t *state, void *user_data);

// TAPDANCE - Tap sends kc. Hold to activate layer.
void td_lr_holdon_finished(tap_dance_state_t *state, void *user_data);
void td_lr_holdon_reset(tap_dance_state_t *state, void *user_data);

// TAPDANCE - Alt+KC_X on hold functions
void td_alt_finished(tap_dance_state_t *state, void *user_data);
void td_alt_reset(tap_dance_state_t *state, void *user_data);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // DEFAULT LAYER
    [0] = LAYOUT_65_iso_blocker(
    //  ESC       1         2         3         4         5         6         7         8         9         0         -         =         BCKSPC    DEL
        QK_GESC,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_DEL,
    //  TAB       Q         W         E         R         T         Y         U         I         O         P         [         ]                   INSERT
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,            KC_INS,
    //  CAPS      A         S         D         F         G         H         J         K         L         ;         '         #         ENTER     PG UP
        TD(LR1C), KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,  KC_ENT,   KC_PGUP,
    //  SHIFT     \         Z         X         C         V         B         N         M         ,         .         ?         SHIFT     UP        PG DOWN
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_PGDN,
    //  CTRL      FN        ALT                                     SPACE                         ALTGR     FN                  LEFT      DOWN      RIGHT
        KC_LCTL,  TD(LR1),  KC_LALT,                                KC_SPC,                       KC_RALT,  TD(LR1G),           KC_LEFT,  KC_DOWN,  KC_RGHT
    ),

    // FN LAYER
    // TODO add additional mouse button keys, if there's support for it.
    [1] = LAYOUT_65_iso_blocker(
    //  ESC       1         2         3         4         5         6         7         8         9         0         -         =         BCKSPC    DEL
        TO(0),    TD(AF1),  TD(AF2),  TD(AF3),  TD(AF4),  TD(AF5),  TD(AF6),  TD(AF7),  TD(AF8),  TD(AF9),  TD(AF10), TD(AF11), TD(AF12), _______,  _______,
    //  TAB       Q         W         E         R         T         Y         U         I         O         P         [         ]                   INSERT
        _______,  LCA(KC_Q),_______,  _______,  _______,  LCA(KC_T),_______,  KC_WH_U,  _______,  _______,  KC_MPLY,  _______,  _______,            KC_HOME,
    //  CAPS      A         S         D         F         G         H         J         K         L         ;         '         #         ENTER     PG UP
        _______,  _______,  KC_MSTP,  LCA(KC_D),LCA(KC_F),_______,  KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R,  _______,  _______,  _______,  _______,  _______,
    //  SHIFT     \         Z         X         C         V         B         N         M         ,         .         ?         SHIFT     UP        PG DOWN
        _______,  _______,  _______,  _______,  _______,  _______,  KC_BTN2,  KC_WH_D,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  KC_VOLU,  _______,
    //  CTRL      FN        ALT                                     SPACE                         ALTGR     FN                  LEFT      DOWN      RIGHT
        _______,  TD(LR1),  TD(LR2),                                KC_BTN1,                      TD(LR3),  _______,            KC_MPRV,  KC_VOLD,  KC_MNXT
    ),

    // RGB LAYER
    [2] = LAYOUT_65_iso_blocker(
    //  ESC       1         2         3         4         5         6         7         8         9         0         -         =         BCKSPC    DEL
        TG(2),    RGB_M_P,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    RGB_VAD,  RGB_VAI,  KC_NO,    KC_NO,
    //  TAB       Q         W         E         R         T         Y         U         I         O         P         [         ]                   INSERT
        KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    RGB_TOG,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,              KC_NO,
    //  CAPS      A         S         D         F         G         H         J         K         L         ;         '         #         ENTER     PG UP
        KC_NO,    KC_NO,    RGB_SAI,  KC_NO,    KC_NO,    KC_NO,    RGB_HUI,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
    //  SHIFT     \         Z         X         C         V         B         N         M         ,         .         ?         SHIFT     UP        PG DOWN
        KC_NO,    KC_NO,    KC_NO,    RGB_SAD,  KC_NO,    KC_NO,    KC_NO,    RGB_HUD,  RGB_MOD,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    RGB_SPI,  KC_NO,
    //  CTRL      FN        ALT                                     SPACE                         ALTGR     FN                  LEFT      DOWN      RIGHT
        KC_NO,    KC_NO,    KC_NO,                                  KC_NO,                        KC_NO,    KC_NO,              RGB_RMOD, RGB_SPD,  RGB_MOD
    ),

    // ADVANCED LAYER
    [3] = LAYOUT_65_iso_blocker(
    //  ESC       1         2         3         4         5         6         7         8         9         0         -         =         BCKSPC    DEL
        TG(3),    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
    //  TAB       Q         W         E         R         T         Y         U         I         O         P         [         ]                   INSERT
        KC_NO,    KC_NO,    KC_NO,    KC_NO,    QK_BOOT,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,              KC_NO,
    //  CAPS      A         S         D         F         G         H         J         K         L         ;         '         #         ENTER     PG UP
        KC_NO,    KC_NO,    KC_NO,    DB_TOGG,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
    //  SHIFT     \         Z         X         C         V         B         N         M         ,         .         ?         SHIFT     UP        PG DOWN
        KC_NO,    KC_NO,    KC_NO,    KC_NO,    EE_CLR,   KC_NO,    QK_BOOT,  KC_NO,    QK_MAKE,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
    //  CTRL      FN        ALT                                     SPACE                         ALTGR     FN                  LEFT      DOWN      RIGHT
        KC_NO,    KC_NO,    KC_NO,                                  KC_NO,                        KC_NO,    KC_NO,              KC_NO,    KC_NO,    KC_NO
    )
};

// CUSTOM RGB COLORS PER LAYER
const uint8_t PROGMEM ledcolors[][RGB_MATRIX_LED_COUNT][4] = {
    // DEFAULT LAYER
    [0] = {
    //  ESC       1         2         3         4         5         6         7         8         9         0         -         =         BCKSPC    DEL     0-14 = 15 leds
        L_DYEL,   L_DORA,   L_DORA,   L_DORA,   L_DORA,   L_DORA,   L_DORA,   L_DORA,   L_DORA,   L_DORA,   L_DORA,   L_DORA,   L_DORA,   L_DYEL,   L_DYEL,
    //  TAB       Q         W         E         R         T         Y         U         I         O         P         [         ]         ENTER     INSERT  15-29 = 15 leds
        L_DORA,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DYEL,
    //  CAPS      A         S         D         F         G         H         J         K         L         ;         '         #                   PG UP   30-43 = 14 leds
        L_DORA,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,             L_DYEL,
    //  SHIFT     \         Z         X         C         V         B         N         M         ,         .         ?         SHIFT     UP        PG DOWN 44-58 = 15 leds
        L_DORA,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DORA,   L_DRED,   L_DYEL,   L_DYEL,
    //  CTRL      FN        ALT                                     SPACE                         ALTGR     FN                  LEFT      DOWN      RIGHT   59-67 = 9 leds
        L_LGRE,   L_LGRE,   L_LGRE,                                 L_DRED,                       L_LGRE,   L_LGRE,             L_DYEL,   L_LYEL,   L_DYEL,
    //  UGLW69              UGLW68                        UGLW67              UGLW66                        UGLW65              UGLW64                      68-73 = 6 leds underglow 
        L__OFF,             L__OFF,                       L__OFF,             L__OFF,                       L__OFF,             L__OFF
    },

    // FN LAYER
    [1] = {
    //  ESC       1         2         3         4         5         6         7         8         9         0         -         =         BCKSPC    DEL 
        L_BRED,   L_DORA,   L_DORA,   L_DORA,   L_DORA,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DORA,   L_DORA,   L_DORA,   L_DORA,   L__OFF,   L__OFF,
    //  TAB       Q         W         E         R         T         Y         U         I         O         P         [         ]         ENTER     INSERT
        L__OFF,   L_DVIO,   L__OFF,   L__OFF,   L__OFF,   L_LGRE,   L__OFF,   L_DMAG,   L__OFF,   L__OFF,   L_DCYA,   L__OFF,   L__OFF,   L__OFF,   L_DORA,
    //  CAPS      A         S         D         F         G         H         J         K         L         ;         '         #                   PG UP
        L__OFF,   L__OFF,   L_DCYA,   L_LGRE,   L_DVIO,   L__OFF,   L_DROS,   L_DROS,   L_DROS,   L_DROS,   L__OFF,   L__OFF,   L__OFF,             L__OFF,
    //  SHIFT     \         Z         X         C         V         B         N         M         ,         .         ?         SHIFT     UP        PG DOWN
        L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_DRED,   L_DMAG,   L_DCYA,   L_DCYA,   L_DCYA,   L__OFF,   L__OFF,   L_DCYA,   L__OFF,
    //  CTRL      FN        ALT                                     SPACE                         ALTGR     FN                  LEFT      DOWN      RIGHT
        L__OFF,   L_BRED,   L_DGRE,                                 L_DRED,                       L__OFF,   L__OFF,             L_DCYA,   L_DCYA,   L_DCYA,
    //  UGLW69              UGLW68                        UGLW67              UGLW66                        UGLW65              UGLW64 
        L_BRED,             L_BRED,                       L_BRED,             L_BRED,                       L_BRED,             L_BRED
    },

    // RGB LAYER
    [2] = {
    //  ESC       1         2         3         4         5         6         7         8         9         0         -         =         BCKSPC    DEL
        L_BBLU,   L_BRED,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_BCYA,   L_BCYA,   L__OFF,   L__OFF,
    //  TAB       Q         W         E         R         T         Y         U         I         O         P         [         ]         ENTER     INSERT
        L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_BBLU,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,
    //  CAPS      A         S         D         F         G         H         J         K         L         ;         '         #                   PG UP
        L__OFF,   L__OFF,   L_BVIO,   L__OFF,   L__OFF,   L__OFF,   L_BMAG,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,             L__OFF,
    //  SHIFT     \         Z         X         C         V         B         N         M         ,         .         ?         SHIFT     UP        PG DOWN
        L__OFF,   L__OFF,   L__OFF,   L_BVIO,   L__OFF,   L__OFF,   L__OFF,   L_BMAG,   L_BBLU,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_BAZU,   L__OFF,
    //  CTRL      FN        ALT                                     SPACE                         ALTGR     FN                  LEFT      DOWN      RIGHT
        L__OFF,   L__OFF,   L__OFF,                                 L__OFF,                       L__OFF,   L__OFF,             L_BBLU,   L_BAZU,   L_BBLU,
    //  UGLW69              UGLW68                        UGLW67              UGLW66                        UGLW65              UGLW64 
        L_BBLU,             L_BBLU,                       L_BBLU,             L_BBLU,                       L_BBLU,             L_BBLU
    },

    // ADVANCED LAYER
    [3] = {
    //  ESC       1         2         3         4         5         6         7         8         9         0         -         =         BCKSPC    DEL
        L_BYEL,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,
    //  TAB       Q         W         E         R         T         Y         U         I         O         P         [         ]         ENTER     INSERT
        L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_BBLU,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,
    //  CAPS28    A         S         D         F         G         H         J         K         L         ;         '         #                   PG UP
        L__OFF,   L__OFF,   L__OFF,   L_BMAG,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,             L__OFF,
    //  SHIFT     \         Z         X         C         V         B         N         M         ,         .         ?         SHIFT     UP        PG DOWN
        L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_BBLU,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,
    //  CTRL      FN        ALT                                     SPACE                         ALTGR     FN                  LEFT      DOWN      RIGHT
        L__OFF,   L__OFF,   L__OFF,                                 L__OFF,                       L__OFF,   L__OFF,             L__OFF,   L__OFF,   L__OFF,
    //  UGLW69              UGLW68                        UGLW67              UGLW66                        UGLW65              UGLW64 
        L_BYEL,             L_BYEL,                       L_BYEL,             L_BYEL,                       L_BYEL,             L_BYEL
    }
};

// TAPPING TERM PER KEY - determines timeout for what is a tap and what is a hold 
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // fn layer
        case TD(LR1):
        case TD(LR1G):
            return 160;
        // fn layer - hold to mometarily activate
        case TD(LR1C):
            return 140;
        // rgb layer
        case TD(LR2):
            return 400;
        // advanced layer
        case TD(LR3):
            return 600;
        default:
            return TAPPING_TERM;
    }
}

// suspend rgb on suspend
void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
}


// SET INDIVIDUAL LED RGB
void set_led_color( uint8_t ledindex, HSVB hsv, bool use_matrix_value) {
    // NOTE: effect cycle timer example using user config:
    // uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);
    uint8_t val = hsv.v;

    // if the brightness of the led is set to 0 in the map, the value is not overriden by matrix effect, 
    // allowing the led to appear turned off. Else, set brightness to current rgb matrix value.
    if (val != 0 && use_matrix_value) {
        val = rgb_matrix_get_val();
    }

    // If breathe, set val based on time cycle
    if (hsv.b > 0) {
        // per key breathing effect cycle timer.
        uint16_t time = scale16by8(g_rgb_timer, hsv.b);
        uint8_t hsv_breathe_val = abs8(sin8(time) - 128) * 2;
        val = scale8(hsv_breathe_val, val);
    }

    HSV _hsv = { .h=hsv.h, .s=hsv.s, .v = val};
    RGB rgb = hsv_to_rgb( _hsv );
    rgb_matrix_set_color(ledindex, rgb.r, rgb.g, rgb.b);
}

// SET LED RGB & BREATHING CYCLE BASED ON LAYER
void set_layer_color( uint8_t layer) {
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        // Get hsv + breathing cycle for current led index
        HSVB hsvb = { 
            .h = pgm_read_byte(&ledcolors[layer][i][0]),
            .s = pgm_read_byte(&ledcolors[layer][i][1]),
            .v = pgm_read_byte(&ledcolors[layer][i][2]),
            .b = pgm_read_byte(&ledcolors[layer][i][3])
        };

        // If RGB layer is enabled, skip all leds with brightness set to 0.
        // This is so that the rgb effect mode can be previewed in layer.
        if (layer == 2 && hsvb.v == 0) continue;

        // By default, use LED brightness set by user
        bool use_curr_brightness = USE_RGB_MATRIX_VALUE_ON;

        // For key leds (index 0-67), allow brightness to be set by user.
        // But for underglow, always use brigthness value set in ledcolors map above.
        if (i > 67) {
            use_curr_brightness = USE_RGB_MATRIX_VALUE_OFF;
        }

        set_led_color(i, hsvb, use_curr_brightness);
    }
}

// LED INDICATORS
// TODO new refactor change:
/* void rgb_matrix_indicators_user(void) { */
bool rgb_matrix_indicators_user(void) {
    uint32_t mode = rgb_matrix_get_mode();

    // Assign custom layer colors if the rgb matrix is on.
    // For default layer only assign colors if mode is SOLID COLORS => No animations running.
    // For all other layers, always set custom colors.
    // For some layers, set an underglow breathing effect.
    if (rgb_matrix_is_enabled() == 1) {
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

    // Set LED for Caps Lock
    if (host_keyboard_led_state().caps_lock) {
        HSVB hsvb = L_BCYA;
        set_led_color(30, hsvb, USE_RGB_MATRIX_VALUE_ON);
    }

    // TODO new refactor change:
    return false;
}


// TAPDANCE - Common.
// Determine the current tap dance state
// Double and triple tap is handled to make tapping more stable
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held.
        // Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } 
    else if (state->count == 2) return TD_DOUBLE_TAP;
    else if (state->count == 3) return TD_TRIPLE_TAP;
    else return TD_UNKNOWN;
}


// TAPDANCE - Tap to toggle layer. Hold to momentarily activate layer.
// Desired layer is passed in user data
// -----------------------------------------------------------------------
static td_tap_t td_lr_tglholdmo_tapstate = {.is_press_action = true, .state = TD_NONE};

void td_lr_tglholdmo_finished(tap_dance_state_t *state, void *user_data) {
    td_lr_tglholdmo_tapstate.state = cur_dance(state);
    tap_dance_dual_role_t *pair = (tap_dance_dual_role_t *)user_data;

    switch (td_lr_tglholdmo_tapstate.state) {
        // Toggle layer
        case TD_SINGLE_TAP:
            if (layer_state_is(pair->layer)) layer_off(pair->layer);
            else layer_on(pair->layer);
            break;
        // Momentarily turn on layer
        case TD_SINGLE_HOLD: layer_on(pair->layer); break;
        case TD_DOUBLE_TAP: break;
        case TD_TRIPLE_TAP: break;
        case TD_NONE: break;
        case TD_UNKNOWN: break;
    }
}

void td_lr_tglholdmo_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (td_lr_tglholdmo_tapstate.state == TD_SINGLE_HOLD) {
        tap_dance_dual_role_t *pair = (tap_dance_dual_role_t *)user_data;
        layer_off(pair->layer);
    }
    td_lr_tglholdmo_tapstate.state = TD_NONE;
}


// TAPDANCE - Tap to send normal KC_X, hold to momentarily enable layer
// --------------------------------------------------------------------
// Func retreives current keycode and desired layer from user_data in custom tapdance action.
// See: https://github.com/qmk/qmk_firmware/blob/master/quantum/process_keycode/process_tap_dance.c
static td_tap_t td_lr_holdmo_tapstate = {.is_press_action = true, .state = TD_NONE};

void td_lr_holdmo_finished(tap_dance_state_t *state, void *user_data) {
    td_lr_holdmo_tapstate.state = cur_dance(state);
    tap_dance_dual_role_t *pair = (tap_dance_dual_role_t *)user_data;

    switch (td_lr_holdmo_tapstate.state) {
        case TD_SINGLE_TAP: register_code(pair->kc); break;
        case TD_SINGLE_HOLD: layer_on(pair->layer); break;
        case TD_DOUBLE_TAP: register_code(pair->kc); break;
        case TD_TRIPLE_TAP: register_code(pair->kc); break;
        case TD_NONE: break;
        case TD_UNKNOWN: break;
    }
}

void td_lr_holdmo_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_dual_role_t *pair = (tap_dance_dual_role_t *)user_data;

    switch (td_lr_holdmo_tapstate.state) {
        case TD_SINGLE_TAP: unregister_code(pair->kc); break;
        case TD_SINGLE_HOLD: layer_off(pair->layer); break;
        case TD_DOUBLE_TAP: unregister_code(pair->kc); break;
        case TD_TRIPLE_TAP: unregister_code(pair->kc); break;
        case TD_UNKNOWN: break;
        case TD_NONE: break; 
    }
    td_lr_holdmo_tapstate.state = TD_NONE;
}


// TAPDANCE - Tap sends kc. Hold to activate layer.
// ------------------------------------------------
static td_tap_t td_lr_holdon_tapstate = {.is_press_action = true, .state = TD_NONE};

void td_lr_holdon_finished(tap_dance_state_t *state, void *user_data) {
    td_lr_holdon_tapstate.state = cur_dance(state);
    tap_dance_dual_role_t *pair = (tap_dance_dual_role_t *)user_data;

    switch (td_lr_holdon_tapstate.state) {
        case TD_SINGLE_TAP: register_code(pair->kc); break;
        case TD_SINGLE_HOLD: layer_on(pair->layer); break;
        case TD_DOUBLE_TAP: register_code(pair->kc); break;
        case TD_TRIPLE_TAP: register_code(pair->kc); break;
        case TD_NONE: break;
        case TD_UNKNOWN: break;
    }
}

void td_lr_holdon_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_dual_role_t *pair = (tap_dance_dual_role_t *)user_data;

    switch (td_lr_holdon_tapstate.state) {
        case TD_SINGLE_TAP: unregister_code(pair->kc); break;
        case TD_SINGLE_HOLD: break;
        case TD_DOUBLE_TAP: unregister_code(pair->kc); break;
        case TD_TRIPLE_TAP: unregister_code(pair->kc); break;
        case TD_UNKNOWN: break;
        case TD_NONE: break; 
    }
    td_lr_holdon_tapstate.state = TD_NONE;
}


// TAPDANCE - Tap for normal KC_X. Hold to send Alt+KC_X
// -----------------------------------------------------
// Func retreives current keycode from user_data in custom tapdance action.
// This means I can use this func for any keycodes.
// see: https://github.com/qmk/qmk_firmware/commit/ad7a5bdc4f2527f47ca22885e5d0b689fb8d4518
// and this one: https://www.reddit.com/r/olkb/comments/kcfs52/qmk_generic_handler_for_tap_dance/
static td_tap_t td_alt_tap_state = {.is_press_action = true, .state = TD_NONE};

void td_alt_finished(tap_dance_state_t *state, void *user_data) {
    td_alt_tap_state.state = cur_dance(state);
    tap_dance_pair_t *pair = (tap_dance_pair_t *)user_data;
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

void td_alt_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_pair_t *pair = (tap_dance_pair_t *)user_data;
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
tap_dance_action_t tap_dance_actions[] = {
    // ---- Layer 1 - FN ----
    // Tap to toggle layer. Hold to momentarily activate.
    [LR1] = ACTION_TAP_DANCE_FN_KEY_LAYER(NULL, td_lr_tglholdmo_finished, td_lr_tglholdmo_reset, 0, 1),
    // Hold to momenarily activate. Tap send Left GUI
    [LR1G] = ACTION_TAP_DANCE_FN_KEY_LAYER(NULL, td_lr_holdmo_finished, td_lr_holdmo_reset, KC_LGUI, 1),
    // Hold to momentarily activate. Tap send Caps
    [LR1C] = ACTION_TAP_DANCE_FN_KEY_LAYER(NULL, td_lr_holdmo_finished, td_lr_holdmo_reset, KC_CAPS, 1),

    // ---- Layer 2 - RGB ----
    // Hold Left Alt to activate.
    [LR2] = ACTION_TAP_DANCE_FN_KEY_LAYER(NULL, td_lr_holdon_finished, td_lr_holdon_reset, KC_LALT, 2),

    // ---- Layer 3 - Advanced ----
    // Hold Right Alt to activate.
    [LR3] = ACTION_TAP_DANCE_FN_KEY_LAYER(NULL, td_lr_holdon_finished, td_lr_holdon_reset, KC_RALT, 3),

    // ---- Hold to send ALT+KC_F1-12 ----
    [AF1] = ACTION_TAP_DANCE_FN_KEY(NULL, td_alt_finished, td_alt_reset, KC_F1),
    [AF2] = ACTION_TAP_DANCE_FN_KEY(NULL, td_alt_finished, td_alt_reset, KC_F2),
    [AF3] = ACTION_TAP_DANCE_FN_KEY(NULL, td_alt_finished, td_alt_reset, KC_F3),
    [AF4] = ACTION_TAP_DANCE_FN_KEY(NULL, td_alt_finished, td_alt_reset, KC_F4),
    [AF5] = ACTION_TAP_DANCE_FN_KEY(NULL, td_alt_finished, td_alt_reset, KC_F5),
    [AF6] = ACTION_TAP_DANCE_FN_KEY(NULL, td_alt_finished, td_alt_reset, KC_F6),
    [AF7] = ACTION_TAP_DANCE_FN_KEY(NULL, td_alt_finished, td_alt_reset, KC_F7),
    [AF8] = ACTION_TAP_DANCE_FN_KEY(NULL, td_alt_finished, td_alt_reset, KC_F8),
    [AF9] = ACTION_TAP_DANCE_FN_KEY(NULL, td_alt_finished, td_alt_reset, KC_F9),
    [AF10] = ACTION_TAP_DANCE_FN_KEY(NULL, td_alt_finished, td_alt_reset, KC_F10),
    [AF11] = ACTION_TAP_DANCE_FN_KEY(NULL, td_alt_finished, td_alt_reset, KC_F11),
    [AF12] = ACTION_TAP_DANCE_FN_KEY(NULL, td_alt_finished, td_alt_reset, KC_F12)
};
