/* Copyright 2024 Lars Johansson (github.com/swedishlars)
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include QMK_KEYBOARD_H

// LIB USED FOR  LED INDICATOR BREATHING EFFECT
#include "lib/lib8tion/lib8tion.h"
#include "swedishlars.h"
#include "lib/rgb.h"

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
[_BASE] = LAYOUT_65_iso_blocker(
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
[_FUNC] = LAYOUT_65_iso_blocker(
    //  ESC       1         2         3         4         5         6         7         8         9         0         -         =         BCKSPC    DEL
        TO(0),    TD(AF1),  TD(AF2),  TD(AF3),  TD(AF4),  TD(AF5),  TD(AF6),  TD(AF7),  TD(AF8),  TD(AF9),  TD(AF10), TD(AF11), TD(AF12), _______,  _______,
    //  TAB       Q         W         E         R         T         Y         U         I         O         P         [         ]                   INSERT
        _______,  LCA(KC_Q),_______,  _______,  _______,  LCA(KC_T),_______,  MS_WHLU,  _______,  _______,  KC_MPLY,  _______,  _______,            KC_HOME,
    //  CAPS      A         S         D         F         G         H         J         K         L         ;         '         #         ENTER     PG UP
        _______,  _______,  KC_MSTP,  LCA(KC_D),LCA(KC_F),_______,  MS_LEFT,  MS_DOWN,  MS_UP,    MS_RGHT,  _______,  _______,  _______,  _______,  _______,
    //  SHIFT     \         Z         X         C         V         B         N         M         ,         .         ?         SHIFT     UP        PG DOWN
        _______,  _______,  _______,  _______,  _______,  _______,  MS_BTN2,  MS_WHLD,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  KC_VOLU,  _______,
    //  CTRL      FN        ALT                                     SPACE                         ALTGR     FN                  LEFT      DOWN      RIGHT
        _______,  TD(LR1),  TD(LR2),                                MS_BTN1,                      TD(LR3),  _______,            KC_MPRV,  KC_VOLD,  KC_MNXT
),

// RGB LAYER
[_MACRO] = LAYOUT_65_iso_blocker(
    //  ESC       1         2         3         4         5         6         7         8         9         0         -         =         BCKSPC    DEL
        TG(2),    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    RM_VALD,  RM_VALU,  KC_NO,    KC_NO,
    //  TAB       Q         W         E         R         T         Y         U         I         O         P         [         ]                   INSERT
        KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    RM_TOGG,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,              KC_NO,
    //  CAPS      A         S         D         F         G         H         J         K         L         ;         '         #         ENTER     PG UP
        KC_NO,    KC_NO,    RM_SATU,  KC_NO,    KC_NO,    KC_NO,    RM_HUEU,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
    //  SHIFT     \         Z         X         C         V         B         N         M         ,         .         ?         SHIFT     UP        PG DOWN
        KC_NO,    KC_NO,    KC_NO,    RM_SATD,  KC_NO,    KC_NO,    KC_NO,    RM_HUED,  RM_NEXT,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    RM_VALU,  KC_NO,
    //  CTRL      FN        ALT                                     SPACE                         ALTGR     FN                  LEFT      DOWN      RIGHT
        KC_NO,    KC_NO,    KC_NO,                                  KC_NO,                        KC_NO,    KC_NO,              RM_PREV, RM_VALD,  RM_NEXT
),

// ADVANCED LAYER
[_CONF] = LAYOUT_65_iso_blocker(
    //  ESC       1         2         3         4         5         6         7         8         9         0         -         =         BCKSPC    DEL
        TG(3),    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
    //  TAB       Q         W         E         R         T         Y         U         I         O         P         [         ]                   INSERT
        KC_NO,    KC_NO,    KC_NO,    KC_NO,    RM_TOGG,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,              KC_NO,
    //  CAPS      A         S         D         F         G         H         J         K         L         ;         '         #         ENTER     PG UP
        KC_NO,    KC_NO,    KC_NO,    DB_TOGG,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
    //  SHIFT     \         Z         X         C         V         B         N         M         ,         .         ?         SHIFT     UP        PG DOWN
        KC_NO,    KC_NO,    KC_NO,    KC_NO,    EE_CLR,   KC_NO,    QK_BOOT,  KC_NO,    QK_MAKE,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
    //  CTRL      FN        ALT                                     SPACE                         ALTGR     FN                  LEFT      DOWN      RIGHT
        KC_NO,    KC_NO,    KC_NO,                                  KC_NO,                        KC_NO,    KC_NO,              KC_NO,    KC_NO,    KC_NO
)
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


bool rgb_matrix_indicators_user(void) {
    uint8_t layer = get_highest_layer(layer_state);
    set_layer_color(layer);
    set_caps_led();
    set_caps_word_led();
    return false;
}

// TODO new choc version
/*
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);
    set_layer_color(layer, led_min, led_max);
    set_caps_led();
    set_caps_word_led();
    return false;
}
*/

// wake callbacks
void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
}


// suspend callbacks
void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
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
