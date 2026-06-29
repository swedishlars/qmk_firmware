/* Copyright 2024 Lars Johansson (github.com/swedishlars)
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include QMK_KEYBOARD_H

// LIB USED FOR  LED INDICATOR BREATHING EFFECT
#include "lib/lib8tion/lib8tion.h"
#include "swedishlars.h"
#include "lib/rgb.h"
#include "lib/tapdance.h"

// TODO MAKE FN BUTTON TD. Tap: LGUI. Hold: ACTIVATE FN LAYER
// TODO keep tri-layer for FUNC and use TD_RGUI for something else, or remove tri-layer?
// perhaps rearrange:
// CAPS Key: tap = MACRO, hold = LOWR
// FN Key: tap = LGUI, hold = FUNC
// WIN Key: tap = "useful key", hold = LOWR or useful key
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT_65_iso_blocker(
    //  ESC       1         2         3         4         5         6         7         8         9         0         -         =         BCKSPC    DEL
        QK_GESC,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_DEL,
    //  TAB       Q         W         E         R         T         Y         U         I         O         P         [         ]                   INSERT
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,            KC_INS,
    //  Macro/Low A         S         D         F         G         H         J         K         L         ;         '         #         ENTER     PG UP
        TD(T_CAP),KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,  KC_ENT,   KC_PGUP,
    //  SHIFT     \         Z         X         C         V         B         N         M         ,         .         ?         SHIFT     UP        PG DOWN
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  TD(T_RSFT),KC_UP,    KC_PGDN,
    //  CTRL      FN        ALT                                     SPACE                         ALTGR     GUI/fn              LEFT      DOWN      RIGHT
        KC_LCTL,  MO(_FUNC),KC_LALT,                                KC_SPC,                       KC_RALT,  TD(T_RGUI),         KC_LEFT,  KC_DOWN,  KC_RGHT
),

[_LOWR] = LAYOUT_65_iso_blocker(
    //  ESC       1         2         3         4         5         6         7         8         9         0         -         =         BCKSPC    DEL
        TO(0),    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_HOME,  KC_INS,
    //  TAB       Q         W         E         R         T         Y         U         I         O         P         [         ]                   INSERT
        _______,  LCA(KC_Q),_______,  _______,  _______,  LCA(KC_T),_______,  MS_WHLU,  _______,  _______,  KC_MPLY,  _______,  _______,            KC_HOME,
    //  CAPS      A         S         D         F         G         H         J         K         L         ;         '         #         ENTER     PG UP
        _______,  _______,  KC_MSTP,  LCA(KC_D),LCA(KC_F),_______,  MS_LEFT,  MS_DOWN,  MS_UP,    MS_RGHT,  _______,  _______,  _______,  _______,  _______,
    //  SHIFT     \         Z         X         C         V         B         N         M         ,         .         ?         SHIFT     UP        PG DOWN
        _______,  _______,  _______,  _______,  _______,  _______,  MS_BTN2,  MS_WHLD,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  KC_VOLU,  _______,
    //  CTRL      FN        ALT                                     SPACE                         ALTGR     FN                  LEFT      DOWN      RIGHT
        _______,  _______,  MO(_CONF),                                MS_BTN1,                      _______,  _______,            KC_MPRV,  KC_VOLD,  KC_MNXT
),

// TODO add additional mouse button keys, if there's support for it.
// TODO rename _RAISE
[_FUNC] = LAYOUT_65_iso_blocker(
    //  ESC       1         2         3         4         5         6         7         8         9         0         -         =         BCKSPC    DEL
        TO(0),    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_HOME,  KC_INS,
    //  TAB       Q         W         E         R         T         Y         U         I         O         P         [         ]                   INSERT
        _______,  LCA(KC_Q),_______,  _______,  _______,  LCA(KC_T),_______,  MS_WHLU,  _______,  _______,  KC_MPLY,  _______,  _______,            KC_HOME,
    //  CAPS      A         S         D         F         G         H         J         K         L         ;         '         #         ENTER     PG UP
        _______,  _______,  KC_MSTP,  LCA(KC_D),LCA(KC_F),_______,  MS_LEFT,  MS_DOWN,  MS_UP,    MS_RGHT,  _______,  _______,  _______,  _______,  _______,
    //  SHIFT     \         Z         X         C         V         B         N         M         ,         .         ?         SHIFT     UP        PG DOWN
        _______,  _______,  _______,  _______,  _______,  _______,  MS_BTN2,  MS_WHLD,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  KC_VOLU,  _______,
    //  CTRL      FN        ALT                                     SPACE                         ALTGR     FN                  LEFT      DOWN      RIGHT
        _______,  _______,  MO(_CONF),                                MS_BTN1,                      _______,  _______,            KC_MPRV,  KC_VOLD,  KC_MNXT
),

[_MACRO] = LAYOUT_65_iso_blocker(
    //  ESC       1         2         3         4         5         6         7         8         9         0         -         =         BCKSPC    DEL
        TO(0),    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    RM_VALD,  RM_VALU,  KC_NO,    KC_NO,
    //  TAB       Q         W         E         R         T         Y         U         I         O         P         [         ]                   INSERT
        KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    RM_TOGG,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,              KC_NO,
    //  CAPS      A         S         D         F         G         H         J         K         L         ;         '         #         ENTER     PG UP
        _______,  KC_NO,    RM_SATU,  KC_NO,    KC_NO,    KC_NO,    RM_HUEU,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
    //  SHIFT     \         Z         X         C         V         B         N         M         ,         .         ?         SHIFT     UP        PG DOWN
        KC_NO,    KC_NO,    KC_NO,    RM_SATD,  KC_NO,    KC_NO,    KC_NO,    RM_HUED,  RM_NEXT,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    RM_VALU,  KC_NO,
    //  CTRL      FN        ALT                                     SPACE                         ALTGR     FN                  LEFT      DOWN      RIGHT
        KC_NO,    KC_NO,    KC_NO,                                  KC_NO,                        KC_NO,    KC_NO,              RM_PREV, RM_VALD,  RM_NEXT
),

[_CONF] = LAYOUT_65_iso_blocker(
    //  ESC       1         2         3         4         5         6         7         8         9         0         -         =         BCKSPC    DEL
        TO(0),    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
    //  TAB       Q         W         E         R         T         Y         U         I         O         P         [         ]                   INSERT
        KC_NO,    KC_NO,    KC_NO,    KC_NO,    RM_TOGG,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,              KC_NO,
    //  CAPS      A         S         D         F         G         H         J         K         L         ;         '         #         ENTER     PG UP
        KC_NO,    KC_NO,    KC_NO,    DB_TOGG,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
    //  SHIFT     \         Z         X         C         V         B         N         M         ,         .         ?         SHIFT     UP        PG DOWN
        AS_TOGL,  KC_NO,    KC_NO,    KC_NO,    EE_CLR,   KC_NO,    QK_BOOT,  KC_NO,    QK_MAKE,  KC_NO,    KC_NO,    KC_NO,    AS_TOGL,  KC_NO,    KC_NO,
    //  CTRL      FN        ALT                                     SPACE                         ALTGR     FN                  LEFT      DOWN      RIGHT
        KC_NO,    KC_NO,    KC_NO,                                  KC_NO,                        KC_NO,    KC_NO,              KC_NO,    KC_NO,    KC_NO
)
};


// Declare persistent eeprom config
user_config_t user_config;

void eeconfig_init_user(void) {
    user_config.raw = 0;
    user_config.autoshift_enabled = true;
    eeconfig_update_user(user_config.raw);
}


void keyboard_post_init_user(void) {
    // Initialise eeprom user config
    user_config.raw = eeconfig_read_user();

    // Custom eeprom autoshift init)
    if (user_config.autoshift_enabled) { autoshift_enable(); }
    else { autoshift_disable(); }
}


// TAPPING TERM PER KEY - determines timeout for what is a tap and what is a hold (default 200)
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // fn layer
        case TD(T_CAP):
        case TD(T_RGUI):
            return 160;
        // case TD(LR1C):
        //     return 140;
        // rgb layer
        // case TD(LR2):
        //     return 400;
        // advanced layer
        // case TD(LR3):
        //     return 600;
        default:
            return TAPPING_TERM;
    }
}

// add lshift+rshift combo that toggles autoshift
/*
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case SE_ARNG:
        case SE_ADIA:
        case SE_ODIA:
            return true;
        default:
            return false;
    }
}
*/

/*
// Configure keys that continue caps word. Includes tapdances for example.
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        // case KC_MINS:
        case KC_SLSH:
        case SE_ARNG:
        case SE_ADIA:
        case SE_ODIA:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        // Deactivate Caps Word.
        default:
            return false;
    }
}
*/


layer_state_t layer_state_set_user(layer_state_t state) {
    // Turn off auto shift for gaming layer
    /*
    if (user_config.autoshift_enabled && IS_LAYER_OFF_STATE(state, _GAME)) {
        autoshift_enable();
    } else { autoshift_disable(); }
    */

    // TODO Keep tri-layer for CONF layer, or use TD_RGUI?
    state = update_tri_layer_state(state, _LOWR, _FUNC, _CONF);
    return state;
}


// Associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
    // Tap to activate oneshot MACRO layer. Hold to momentarily activate LOW layer.
    [T_CAP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, caps_finished, caps_reset),

    // Tap to toggle MACRO layer. Hold to momentarily activate LOW layer.
    // [T_CAP] = ACTION_TAP_DANCE_FN_PAIR(NULL, tg_mo_layer_finished, tg_mo_layer_reset, _MACRO, _LOWR),

    // Tap to activate Caps Word. Hold to activate Right Shift.
    [T_RSFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rshift_finished, rshift_reset),

    // Tap to activate Left GUI. Hold to momenarily activate CONF layer.
    [T_RGUI] = ACTION_TAP_DANCE_FN_PAIR(NULL, kc_layer_finished, kc_layer_reset, KC_LGUI, _CONF),

    // ---- Layer 2 ----
    // Hold Left Alt to activate.
    // [LR2] = ACTION_TAP_DANCE_FN_PAIR(NULL, td_lr_holdon_finished, td_lr_holdon_reset, KC_LALT, 2),

    // ---- Layer 3 ----
    // Hold Right Alt to activate.
    // [LR3] = ACTION_TAP_DANCE_FN_PAIR(NULL, td_lr_holdon_finished, td_lr_holdon_reset, KC_RALT, 3),

    // ---- Hold to send ALT+KC_F1-12 ----
    // [AF1] = ACTION_TAP_DANCE_FN_PAIR(NULL, td_alt_finished, td_alt_reset, KC_F1, 0),
};


// store current modifier state for later ref
// TODO move inside func?
uint8_t mod_state;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    mod_state = get_mods();

    // keep track of if shift is registered
    static bool is_shifted;

    switch (keycode) {
        // Custom eeprom autoshift toggle
        case AS_TOGL:
            if (record->event.pressed) {
                user_config.autoshift_enabled = !user_config.autoshift_enabled;
                eeconfig_update_user(user_config.raw);
                if (user_config.autoshift_enabled) {
                    autoshift_enable();
                }
                else {
                    autoshift_disable();
                }
            }
            break;

        case SS_ILST:
            if (record->event.pressed) { SEND_STRING("ileanastr"); }
            return false; break;
        case SS_ILEA:
            if (record->event.pressed) { SEND_STRING("Ileana"); }
            return false; break;
        case SS_IOAN:
            if (record->event.pressed) { SEND_STRING("Ioanna"); }
            return false; break;
        case SS_STRA:
            if (record->event.pressed) { SEND_STRING("Stravoskiadi"); }
            return false; break;
        case SS_HEEM:
            if (record->event.pressed) { SEND_STRING("henryemmanouil"); }
            return false; break;
        case SS_HENR:
            if (record->event.pressed) { SEND_STRING("Henry"); }
            return false; break;
        case SS_EMMA:
            if (record->event.pressed) { SEND_STRING("Emmanouil"); }
            return false; break;
        case SS_SWEL:
            if (record->event.pressed) { SEND_STRING("swedishlars"); }
            return false; break;
        case SS_LAIL:
            if (record->event.pressed) { SEND_STRING("swedishlars"); }
            return false; break;
        case SS_LARS:
            if (record->event.pressed) { SEND_STRING("Lars"); }
            return false; break;
        case SS_GUNN:
            if (record->event.pressed) { SEND_STRING("Gunnar"); }
            return false; break;
        case SS_JOHA:
            if (record->event.pressed) { SEND_STRING("Johansson"); }
            return false; break;
        case SS_GMIL:
            if (record->event.pressed) { SEND_STRING("@gmail.com"); }
            return false; break;

        // convert Swedish keycode to US key: ` and ~
        case SW_GRV:
            if (record->event.pressed) {
                is_shifted = mod_state & MOD_MASK_SHIFT;
                // temp unregister Shift
                // register new keycode
                // reapply original mod state (reapply Shift)
                if (is_shifted) {
                    del_mods(MOD_MASK_SHIFT);
                    register_code16(RALT(KC_RBRC));
                    set_mods(mod_state);
                }
                else { register_code16(S(KC_EQL)); }
            }
            else {
                if (is_shifted) { unregister_code16(RALT(KC_RBRC)); }
                else { unregister_code16(S(KC_EQL)); }
            }
            return false;
            break;

        // convert Swedish keycode to US key: ; and :
        case SW_SCLN:
            if (record->event.pressed) {
                is_shifted = mod_state & MOD_MASK_SHIFT;
                if (is_shifted) { register_code16(S(KC_DOT)); }
                else { register_code16(S(KC_COMM)); }
            }
            else {
                if (is_shifted) { unregister_code16(S(KC_DOT)); }
                else { unregister_code16(S(KC_COMM)); }
            }
            return false;
            break;

        // convert Swedish keycode to US key: \ and |
        case SW_BSLS:
            if (record->event.pressed) {
                is_shifted = mod_state & MOD_MASK_SHIFT;
                if (is_shifted) {
                    del_mods(MOD_MASK_SHIFT);
                    register_code16(RALT(KC_NUBS));
                    set_mods(mod_state);
                }
                else { register_code16(RALT(KC_MINS)); }
            }
            else {
                if (is_shifted) { unregister_code16(RALT(KC_NUBS)); }
                else { unregister_code16(RALT(KC_MINS)); }
            }
            return false;
            break;

        // convert Swedish keycode to US key: = and +
        case SW_EQL:
            if (record->event.pressed) {
                is_shifted = mod_state & MOD_MASK_SHIFT;
                if (is_shifted) {
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_MINS);
                    set_mods(mod_state);
                }
                else { register_code16(S(KC_0)); }
            }
            else {
                if (is_shifted) { unregister_code(KC_MINS); }
                else { unregister_code16(S(KC_0)); }
            }
            return false;
            break;
    }
    return true;
}


bool rgb_matrix_indicators_user(void) {
    uint8_t layer = get_highest_layer(layer_state);
    set_layer_color(layer);
    // TODO not using Caps Lock anymore, but perhaps use as Caps Word or Autoshift indicator?
    set_caps_led();
    set_caps_word_led();
    return false;
}

// TODO new choc version, rm
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


