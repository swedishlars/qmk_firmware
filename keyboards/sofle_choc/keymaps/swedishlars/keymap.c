/* Copyright 2024 Lars Johansson (github.com/swedishlars)
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

// TODO do I need?
// #include <stdio.h>

#include QMK_KEYBOARD_H

#include "keymap_swedish.h"

// LIB USED FOR  LED INDICATOR BREATHING EFFECT
#include "lib/lib8tion/lib8tion.h"

#include "swedishlars.h"
#include "lib/rgb.h"
#include "lib/oled.h"
#include "lib/tapdance.h"
#include "lib/pointing_device.h"
#include "lib/keylogger.h"


// TODO make haptic func?
// TODO add fullscreen, quit app

// custom sounds
float click_sound[][2] = SONG(TERMINAL_SOUND);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// TODO Use tap-hold on KC_LCTL for something? or add One Shot
// TODO Use tap-hold on LALT for something? Or add One Shot.
// TODO Use One Shot on LSFT: OS_LSFT
// TODO remove caps lock, I do not need it. Use OneShotLayer (OSL(layer) for macros to send strings (names, addresses, words)
[_BASE] = LAYOUT(
 // .-----------------------------------------------------------------------.                          ,-----------------------------------------------------------------------.
 // | esc       |    1      |    2      |   3       |    4      |   5       |                          |    6      |    7      |    8      |    9      |    0      | back      |
     KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,                                  KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_BSPC,
 // |-----------+-----------+-----------+-----------+-----------+-----------|                          |-----------+-----------+-----------+-----------+-----------+-----------|
 // | tab/swtc  |    Q      |    W      |    E      |    R      |    T      |                          |    Y      |    U      |    I      |    O      |    P      | ` and ~   |
  // KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,                                  KC_Y,       KC_U,       KC_I,       TD(SWE_O),  KC_P,       KC_NUHS,
     KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,                                  KC_Y,       KC_U,       KC_I,       TD(SWE_O),  KC_P,       SW_GRV,
 // |-----------+-----------+-----------+-----------+-----------+-----------|                          |-----------+-----------+-----------+-----------+-----------+-----------|
 // | caps/num  |    A      |    S      |    D      |    F      |   G       |                          |    H      |    J      |    K      |    L      | ; and :   | ' and "   |
  // LT_NUMP,    TD(SWE_A),  KC_S,       KC_D,       KC_F,       KC_G,                                  KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,
     LT_NUMP,    TD(SWE_A),  KC_S,       KC_D,       KC_F,       KC_G,                                  KC_H,       KC_J,       KC_K,       KC_L,       SW_SCLN,    SE_QUOT,
 // |-----------+-----------+-----------+-----------+-----------+-----------+-----------.  .-----------|-----------+---------- +-----------+-----------+-----------+-----------|
 // | lshift    |    Z      |    X      |    C      |    V      |    B      |           |  |           |    N      |    M      | , and <   | . and >   | / and ?   | caps word |
  // KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_NO,          KC_NO,     KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    TD(CW_SFT),
     KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_NO,          KC_NO,     KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_PSLS,    TD(CW_SFT),
 // .-----------+-----------+-----------+-----------+-----------------------|-----------|  |-----------|-----------+-----------+-----------+-----------+-----------+-----------'
 //                         | \ and |   |left ctl   |left alt   | lower     | space     |  | enter     |  raise    |right alt  | - and _   | = and +   |
                          // KC_NUBS,    KC_LCTL,     KC_LALT,   TT(_LOWER), KC_SPC,        KC_ENT,     TT(_RAISE), KC_RALT,    KC_MINS,    KC_EQL
                             SW_BSLS,    KC_LCTL,     KC_LALT,   TT(_LOWER), KC_SPC,        KC_ENT,     TT(_RAISE), KC_RALT,    SE_MINS,    SW_EQL
 //                         |___________|___________|___________|___________|___________|  |___________|___________|___________|___________|___________|
),

// TODO add gaming layer

// NOTE shift+ctl is a combo for work, rm
// Add numpad, swe å, ä, ö?
[_LOWER] = LAYOUT(
 // .-----------------------------------------------------------------------.                          ,-----------------------------------------------------------------------.
 // |           | F1        | F2        | F3        | F4        | F5        |                          | F6        | F7        | F8        |F9         | F10       |frw del    |
     _______,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,                                 KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_DEL,
 // |-----------+-----------+-----------+-----------+-----------+-----------|                          |-----------+-----------+-----------+-----------+-----------+-----------|
 // |           | F11       | F12       |           |           | terminal  |                          |           |           | [ and {   | ] and }   |print scren|           |
     _______,    KC_F11,     KC_F12,     _______,    _______,    KC_TERM,                               _______,    _______,    KC_LBRC,    SE_ODIA,    KC_PSCR,    _______,
 // |-----------+-----------+-----------+-----------+-----------+-----------|                          |-----------+-----------+-----------+-----------+-----------+-----------|
 // |           | app menu  |           | tmux term |max win tgl|page up    |                          | left      | down      | up        |  right    |           |           |
     SE_ADIA,    SE_ARNG,    _______,    KC_TMUX,    LCA(KC_F),  KC_PGUP,                               KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,    _______,    _______,
 // |-----------+-----------+-----------+-----------+-----------+-----------+-----------.  .-----------|-----------+-----------+-----------+-----------+-----------+-----------|
 // | lshift+ctl|           |           |           |           |page down  |           |  |           |           |           |           |           |           | rshift    |
     S(KC_LCTL), _______,    _______,    _______,    _______,    KC_PGDN,    _______,       _______,    _______,    _______,    _______,    _______,    _______,    _______,
 // .-----------+-----------+-----------+-----------+-----------+-----------+-----------|  |-----------+-----------+-----------+-----------+-----------+-----------+-----------'
 //                         |           |           |           |           |           |  |           |           |           |           |           |
                             _______,    _______,    _______,    _______,    _______,       _______,    _______,    _______,    _______,    _______
 //                         |___________|___________|___________|___________|___________|  |___________|___________|___________|___________|___________|
),

// func?
[_RAISE] = LAYOUT(
 // .-----------------------------------------------------------------------.                          ,-----------------------------------------------------------------------.
 // |           | alt+F1    | alt+F2    | alt+F3    | alt+F4    | alt+F5    |                          | alt+F6    | alt+F7    | alt+F8    | alt+F9    | alt+F10   |insert     |
     _______,    A(KC_F1),     A(KC_F2),   A(KC_F3),   A(KC_F4),   A(KC_F5),                              A(KC_F6),   A(KC_F7),   A(KC_F8),   A(KC_F9),   A(KC_F10),  KC_INS,
 // |-----------+-----------+-----------+-----------+-----------+-----------|                          |-----------+-----------+-----------+-----------+-----------+-----------|
 // |    ¬      | alt+F11   | alt+F12   |           |           |           |                          |           |           |    {      |    }      | play      |           |
     S(KC_GRV),  A(KC_F11),  A(KC_F12),  _______,    _______,    _______,                               _______,    _______,    KC_LCBR,    KC_RCBR,    KC_MPLY,    _______,
 // |-----------+-----------+-----------+-----------+-----------+-----------|                          |-----------+-----------+-----------+-----------+-----------+-----------|
 // |           |           |           |           |           |           |                          | alt+left  | alt+down  | alt+up    | alt+right |           |           |
     _______,    _______,    _______,    _______,    _______,    KC_HOME,                               A(KC_LEFT), A(KC_DOWN), A(KC_UP), A(KC_RGHT),    _______,    _______,
 // |-----------+-----------+-----------+-----------+-----------+-----------+-----------.  .-----------|-----------+-----------+-----------+-----------+-----------+-----------|
 // |           | undo      | cut       |copy       |paste      |           |           |  |           |           |           |           |           |           |           |
     _______,    KC_UNDO,    KC_CUT,     KC_COPY,    KC_PASTE,   KC_END,     _______,       _______,    _______,    KC_MUTE,    KC_MPRV,    KC_MNXT,    _______,    _______,
 // .-----------+-----------+-----------+-----------+-----------+-----------+-----------|  |-----------+-----------+-----------+-----------+-----------+-----------+-----------'
 //                         |           |           |           |           |           |  |           |           |           | vol -     | vol+l     |
                             _______,    _______,    _______,    _______,    _______,       _______,    _______,    _______,    KC_VOLD,    KC_VOLU
 //                         |___________|___________|___________|___________|___________|  |___________|___________|___________|___________|___________|
),

// TODO Rename to _MEDIA or _FUNC. Move numpad on LOWER
[_NUMPAD] = LAYOUT(
 // .-----------------------------------------------------------------------.                          ,-----------------------------------------------------------------------.
 // |           |     1     |     2     |     3     |     $     |     %     |                          |    ^      |     &     |     *     |     (     |     )     |           |
     KC_0,       KC_1,       KC_2,       KC_3,       KC_DLR,     KC_PERC,                               KC_CIRC,    KC_AMPR,    KC_ASTR,     KC_LPRN,    KC_RPRN,    _______,
 // |-----------+-----------+-----------+-----------+-----------+-----------|                          |-----------+-----------+-----------+-----------+-----------+-----------|
 // |           |     4     |     5     |     6     |     (     |     )     |                          |           |           |           |           |           |           |
     _______,    KC_4,       KC_5,       KC_6,       KC_LPRN,    KC_RPRN,                               _______,    _______,    _______,    _______,    _______,    _______,
 // |-----------+-----------+-----------+-----------+-----------+-----------|                          |-----------+-----------+-----------+-----------+-----------+-----------|
 // |           |     7     |     8     |     9     |     -     |     +     |                          |           |           |           |           |     :     |           |
     _______,    KC_7,       KC_8,       KC_9,       KC_PMNS,    KC_PPLS,                               _______,    _______,    _______,    _______,    KC_COLN,    _______,
 // |-----------+-----------+-----------+-----------+-----------+-----------+-----------.  .-----------|-----------+-----------+-----------+-----------+-----------+-----------|
 // |           |           |           |     =     |     /     |     *     |           |  |           |           |           |     ,     |    .      |     /     |           |
     _______,    _______,    _______,    KC_PEQL,    KC_PSLS,    KC_PAST,    _______,        _______,   _______,    _______,    _______,    _______,    _______,    _______,
 // .-----------+-----------+-----------+-----------+-----------+-----------+-----------|  |-----------+-----------+-----------+-----------+-----------+-----------+-----------'
 //                         |           |           |           |           |           |  |           |           |           |  - minus  |  + plus   |
                             _______,    KC_COLN,    KC_BSPC,    KC_ENT,     _______,        _______,   _______,    _______,    KC_PMNS,    KC_PPLS
 //                         |___________|___________|___________|___________|___________|  |___________|___________|___________|___________|___________|
),

[_MOUSE] = LAYOUT(
 // .-----------------------------------------------------------------------.                          ,-----------------------------------------------------------------------.
 // |           |accel 1    |           |           |           |           |                          |           |           |           |           |           |           |
     _______,    MS_ACL0,    MS_ACL1,    MS_ACL2,    _______,    _______,                               _______,    _______,    _______,    _______,    _______,    _______,
 // |-----------+-----------+-----------+-----------+-----------+-----------|                          |-----------+-----------+-----------+-----------+-----------+-----------|
 // |           |           |           |           |           |           |                          |           |           |           |           |           |           |
     _______,    _______,    _______,    _______,    _______,    _______,                               _______,    _______,    _______,    _______,    _______,    _______,
 // |-----------+-----------+-----------+-----------+-----------+-----------|                          |-----------+-----------+-----------+-----------+-----------+-----------|
 // |           |alt+mouse2 |alt+mouse3 |alt+mouse1 |           |wheel up   |                          |           |           |           |           |           |           |
     _______,    A(MS_BTN2), A(MS_BTN3), A(MS_BTN1), _______,    MS_WHLU,                               _______,    _______,    _______,    _______,    _______,    _______,
 // |-----------+-----------+-----------+-----------+-----------+-----------+-----------.  .-----------|-----------+---------- +-----------+-----------+-----------+-----------|
 // |           |           |           |           |           |wheel down |           |  |           |           |           |           |           |           |           |
     _______,    _______,    _______,    _______,    _______,    MS_WHLD,    _______,       _______,    _______,    _______,    _______,    _______,    _______,    _______,
 // .-----------+-----------+-----------+-----------+-----------+-----------+-----------|  |-----------|-----------+-----------+-----------+-----------+-----------+-----------'
 //                         |           |           |           |           |  Space    |  | rgb mode  |           |           |           |           |
                             _______,    _______,    _______,    MS_BTN3,    MS_BTN1,       MS_BTN2,    _______,    _______,    _______,    _______
 //                         |___________|___________|___________|___________|___________|  |___________|___________|___________|___________|___________|
),

// TODO activate with hold caps lock
[_ADJUST] = LAYOUT(
 // .-----------------------------------------------------------------------.                          ,-----------------------------------------------------------------------.
 // |           |  base lyr |  lower    |  raise    |  numpad   |  mouse    |                          |adjust     |           |           |           |           |  reboot   |
     QK_BOOT,    TO(_BASE),TO(_LOWER), TO(_RAISE), TO(_NUMPAD),TO(_MOUSE),                            TO(_ADJUST),XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    QK_BOOT,
 // |-----------+-----------+-----------+-----------+-----------+-----------|                          |-----------+-----------+-----------+-----------+-----------+-----------|
 // | clear mem |           |           |           |  rgb togg |rgb default|                          |           |           |oled sleep |oled tgl   |           | clear mem |
     EE_CLR,     XXXXXXX,    XXXXXXX,    XXXXXXX,    RM_TOGG,    RGB_M_P,                               XXXXXXX,    XXXXXXX,    KC_OSLEEP,  KC_OTGL,    XXXXXXX,    EE_CLR,
 // |-----------+-----------+-----------+-----------+-----------+-----------|                          |-----------+-----------+-----------+-----------+-----------+-----------|
 // |           | audio tog | sys sleep |           |           |           |                          | haptic tg |           |           |           |           |           |
     XXXXXXX,    AU_TOGG,    KC_SLEP,    XXXXXXX,    XXXXXXX,    XXXXXXX,                               HF_TOGG,    XXXXXXX,    KC_KEYLOG,  XXXXXXX,    XXXXXXX,    XXXXXXX,
 // |-----------+-----------+-----------+-----------+-----------+-----------+-----------.  .-----------|-----------+---------- +-----------+-----------+-----------+-----------|
 // |           |           |           |           |           |           |           |  |           |           |           |           |           |           |auto shift |
     XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    AS_TOGL,
 // .-----------+-----------+-----------+-----------+-----------+-----------+-----------|  |-----------|-----------+-----------+-----------+-----------+-----------+-----------'
 //                         |           |           |           |           |           |  |           |           |           | rgb -     |  bright + |
                             XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX,    RM_VALD,    RM_VALU
 //                         |___________|___________|___________|___________|___________|  |___________|___________|___________|___________|___________|

),

};

// TODO key overrides to convert Swedish to US symbol layout (swedish layout sucks)
const key_override_t kc_bksp_or = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t kc_2_or =    ko_make_basic(MOD_MASK_SHIFT, KC_2, RALT(KC_2));
const key_override_t kc_4_or =    ko_make_basic(MOD_MASK_SHIFT, KC_4, RALT(KC_4));
const key_override_t kc_6_or =    ko_make_basic(MOD_MASK_SHIFT, KC_6, S(KC_RBRC));
const key_override_t kc_7_or =    ko_make_basic(MOD_MASK_SHIFT, KC_7, S(KC_6));
const key_override_t kc_8_or =    ko_make_basic(MOD_MASK_SHIFT, KC_8, S(KC_NUHS));
const key_override_t kc_9_or =    ko_make_basic(MOD_MASK_SHIFT, KC_9, S(KC_8));        // 9 and (
const key_override_t kc_0_or =    ko_make_basic(MOD_MASK_SHIFT, KC_0, S(KC_9));        // 0 and )
const key_override_t kc_nuhs_or = ko_make_basic(MOD_MASK_SHIFT, KC_NUHS, S(KC_2));     // ' and "
const key_override_t kc_comm_or = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_NUBS);     // , and <
const key_override_t kc_dot_or = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, S(KC_NUBS));    // . and >
const key_override_t kc_psls_or =  ko_make_basic(MOD_MASK_SHIFT, KC_PSLS, S(KC_MINS)); // / and ?

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
    &kc_bksp_or,
    &kc_2_or,
    &kc_4_or,
    &kc_6_or,
    &kc_7_or,
    &kc_8_or,
    &kc_9_or,
    &kc_0_or,
    &kc_nuhs_or,
    &kc_comm_or,
    &kc_dot_or,
    &kc_psls_or,
};

// Declare persistent eeprom config
user_config_t user_config;


void eeconfig_init_user(void) {
    user_config.raw = 0;
    user_config.oled_enabled = true;
    user_config.oled_sleep_enabled = true;
    user_config.autoshift_enabled = true;
    eeconfig_update_user(user_config.raw);
}


// Oled help msg timer
// uint16_t oled_help_timer = 0;

// Oled rotation on master side should be 0, while slave is flipped 180
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_0;
    }
    return rotation;
}


void pointing_device_init_user(void) {
    set_auto_mouse_layer(_MOUSE);
    set_auto_mouse_enable(true);
    // set_auto_mouse_timeout(1000);  //default 650ms
    set_auto_mouse_timeout(700);  //default 650ms
}


void keyboard_post_init_user(void) {
    // Initialise eeprom user config
    user_config.raw = eeconfig_read_user();

    // Custom eeprom autoshift init)
    if (user_config.autoshift_enabled) { autoshift_enable(); }
    else { autoshift_disable(); }

    // left trackpad -use for vertical/horizontal scrolling
    pointing_device_set_cpi_on_side(true, 500);
    pointing_device_set_cpi_on_side(false, 500);

    // start timer for displaying help msg.
    // oled_help_timer = timer_read();
}


// tapping term per key (default is 200)
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TT(_LOWER):
        case TT(_RAISE):
            return 120;
        case TD(SWE_A):
        case TD(SWE_O):
            return 250;
        default:
            return TAPPING_TERM;
    }
}


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


// Configure keys that continue caps word. Includes tapdances for example.
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        // case KC_MINS:
        case KC_SLSH:
        case TD(SWE_A):
        case TD(SWE_O):
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


layer_state_t layer_state_set_user(layer_state_t state) {
    // TODO enable when I have a gaming layer
    // Turn off auto shift for gaming layer
    // if (user_config.autoshift_enabled && IS_LAYER_OFF_STATE(state, _GAME)) {
    //     autoshift_enable();
    // } else { autoshift_disable(); }

    // tri-layer, tap to toggle, hold to activate momentarily
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);

    switch (get_highest_layer(state)) {
    case _ADJUST:
        PLAY_SONG(click_sound);
        // TODO do I need to set this everytime?
        haptic_set_mode(1);
        haptic_play();
        break;
    }

    return state;
}


// tap dance
// --------------------------------------------------------------------------------------
// Return an integer that corresponds to what kind of tap dance should be executed.
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) { return TD_SINGLE_TAP; }
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else { return TD_SINGLE_HOLD; }
    }
    // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
    // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
    // keystrokes of the key, and not the 'double tap' action/macro.
    else if (state->count == 2) {
        if (state->interrupted) { return TD_DOUBLE_SINGLE_TAP; }
        else if (state->pressed) { return TD_DOUBLE_HOLD; }
        else { return TD_DOUBLE_TAP; }

    }
    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) { return TD_TRIPLE_TAP; }
        else { return TD_TRIPLE_HOLD; }
    }
    else { return TD_UNKNOWN; }
}

// Right Shift: Tap turns on caps word. Hold outputs shift+ctrl
// TODO change this to just a normal right shift on hold? Depends if I need it for Maya?
// ---------------------------------------------------------------------
// Instance of td_tap_t for right shift tapdance
static td_tap_t td_rshift = {
    .is_press_action = true,
    .state = TD_NONE
};

void rshift_finished(tap_dance_state_t *state, void *user_data) {
    td_rshift.state = cur_dance(state);
    switch (td_rshift.state) {
        case TD_SINGLE_TAP: caps_word_on(); break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LSFT));
            // register_mods(MOD_BIT(KC_LCTL));
            break;
        default:
            break;
    }
}

void rshift_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_rshift.state) {
        case TD_SINGLE_TAP: break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LSFT));
            // unregister_mods(MOD_BIT(KC_LCTL));
            break;
        default:
            break;
    }
}

// Swedish letter a tapdance
// ---------------------------------------------------------------------
// Instance of td_tap_t for swedish a tapdance
static td_tap_t td_swe_a = {
    .is_press_action = true,
    .state = TD_NONE
};

void swe_a_finished(tap_dance_state_t *state, void *user_data) {
    td_swe_a.state = cur_dance(state);
    switch (td_swe_a.state) {
        case TD_SINGLE_TAP:  register_code(KC_A); break;
        case TD_SINGLE_HOLD: register_code16(S(KC_A)); break;
        // register unicode for swedish a with ring above
        case TD_DOUBLE_TAP:
            unicode_input_start();
            register_hex(0x00e5);
            unicode_input_finish();
            break;
        // register unicode for swedish capital A with ring above it.
        case TD_DOUBLE_HOLD:
            unicode_input_start();
            register_hex(0x00c5);
            unicode_input_finish();
            break;
        // When typing the word `buffer`, and you want to make sure that you send `ff`.
        // In other words, you are typing two single taps.
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_A); register_code(KC_A); break;
        // register unicode for swedish a with two dots above
        case TD_TRIPLE_TAP:
            unicode_input_start();
            register_hex(0x00e4);
            unicode_input_finish();
            break;
        // register unicode for swedish capital A with two dots above
        case TD_TRIPLE_HOLD:
            unicode_input_start();
            register_hex(0x00c4);
            unicode_input_finish();
            break;
        default: break;
    }
}

void swe_a_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_swe_a.state) {
        case TD_SINGLE_TAP: unregister_code(KC_A); break;
        case TD_SINGLE_HOLD: unregister_code16(S(KC_A)); break;
        case TD_DOUBLE_TAP: break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_A); break;
        case TD_TRIPLE_TAP: break;
        case TD_TRIPLE_HOLD: break;
        default: break;
    }
}

// Swedish o tapdance
// ---------------------------------------------------------------------
// Instance of td_tap_t for swedish o tapdance
static td_tap_t td_swe_o = {
    .is_press_action = true,
    .state = TD_NONE
};

void swe_o_finished(tap_dance_state_t *state, void *user_data) {
    td_swe_o.state = cur_dance(state);
    switch (td_swe_o.state) {
        case TD_SINGLE_TAP:  register_code(KC_O); break;
        case TD_SINGLE_HOLD: register_code16(S(KC_O)); break;
        // register unicode for swedish o with dots above
        case TD_DOUBLE_TAP:
            unicode_input_start();
            register_hex(0x00f6);
            unicode_input_finish();
            break;
        // register unicode for swedish capital O with dots above it.
        case TD_DOUBLE_HOLD:
            unicode_input_start();
            register_hex(0x00d6);
            unicode_input_finish();
            break;
        // When typing the word `buffer`, and you want to make sure that you send `ff`.
        // In other words, you are typing two single taps.
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_O); register_code(KC_O); break;
        default: break;
    }
}

void swe_o_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_swe_o.state) {
        case TD_SINGLE_TAP: unregister_code(KC_O); break;
        case TD_SINGLE_HOLD: unregister_code16(S(KC_O)); break;
        case TD_DOUBLE_TAP: break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_O); break;
        default: break;
    }
}

tap_dance_action_t tap_dance_actions[] = {
        [CW_SFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rshift_finished, rshift_reset),
        [SWE_A] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, swe_a_finished, swe_a_reset),
        [SWE_O] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, swe_o_finished, swe_o_reset)
};
// --------------------------------------------------------------------------------------

// TODO move to swedishlars.h?
// store current modifier state for later ref
uint8_t mod_state;

// TODO test set here? do I need to declare bool?
bool oled_keylogger_enabled = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    mod_state = get_mods();

    // keep track of if shift is registered
    static bool is_shifted;

    // TODO orig:
    // Process oled keycodes
    //process_record_user_oled(keycode, record);

    // Key logger that will display key function on Oled display.
    // Do not send key to host if keylogger help is enabled, with a few exceptions.
    // Allow normal process of:
    //   1. modifiers
    //   2. Dedicated layer change keys.
    // Otherwise the consectutive key press will not be handled.
    // Active modifiers will be checked by keylogger and displayed on oled.
    if (oled_keylogger_enabled) {
        /*
        switch (keycode) {
            // Allow normal process of layer change keys.
            case QK_LAYER_TAP ... QK_LAYER_TAP_TOGGLE_MAX:
                // Except explicit layer changes done from a layer.
                // Those should be checked by keylogger and displayed on oled.
                // TODO This works but is hardcoded. Test again if I can check if current layer is not base and break?
                // TODO orig:
                // if (keycode == TG(_GAME) || keycode == TO(_BASE)) {
                if  (keycode == TO(_BASE)) {
                    break;
                } else {
                    return true;
                }

            // Allow normal process of real mods.
            case MODIFIER_KEYCODE_RANGE:
                return true;

            // Allow normal process of mod combos like  S(KC_LCTL) = shift+ctrl
            // NOTE this works but is hardcoded. Have not found a dynamic way.
            case S(KC_LCTL):
                return true;

        }
        // Display key log on Oled and do not send key press to host (return false).
        // But first, make sure key in not the keylog toggler.
        if (keycode != KC_KEYLOG) {
            add_keylog(keycode, record);
            return false;
        }
    */
        // TODO make func return int 0-3 to represent 0-cont. 1-return false, 2-return true?
        // or keep if (keycode != KC_KEYLOG)?
        uint8_t process_option = process_record_keylogger(keycode, record);
        switch (process_option) {
            case 1:
                return false;
            case 2:
                return true;
        }
    }

    // TODO add audio & haptic for rest of adjust layer keys (audio, rgb, sys sleep, oled)
    switch (keycode) {
        // Custom eeprom autoshift toggle
        case AS_TOGL:
            if (record->event.pressed) {
                user_config.autoshift_enabled = !user_config.autoshift_enabled;
                eeconfig_update_user(user_config.raw);

                if (user_config.autoshift_enabled) { autoshift_enable(); }
                else { autoshift_disable(); }
            }
            break;

        // Toggle oled display on/off
        case KC_OTGL:
            if (record->event.pressed) {
                user_config.oled_enabled = !user_config.oled_enabled;
                eeconfig_update_user(user_config.raw);
            }
            break;

        // toggle oled sleep
        case KC_OSLEEP:
            if (record->event.pressed) {
                user_config.oled_sleep_enabled = !user_config.oled_sleep_enabled;
                eeconfig_update_user(user_config.raw);
            }
            break;

        // toggle keylogger
        case KC_KEYLOG:
            if (record->event.pressed) {
                oled_keylogger_enabled = !oled_keylogger_enabled;
            }
            return false;
            break;

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

        // convert Swedish keycode to US key: \ and |
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


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {

            // get led index
            uint8_t index = g_led_config.matrix_co[row][col];

            // get keycode
            uint16_t kc = keymap_key_to_keycode(layer, (keypos_t){col,row});

            // set rgb based on layer & key function
            if (index >= led_min && index < led_max) {
                set_layer_color(layer, index, kc);
            }
        }
    }

    // Set LED for Caps Lock
     set_caps_led_color();
    return false;
}


bool oled_task_user(void) {
    // Turn off oled by user
    if (!user_config.oled_enabled) {
        oled_off();
        return false;
    }

    // Turn off oled when keyboard input is idle
    if (user_config.oled_sleep_enabled) {
        if (last_input_activity_elapsed() > OLED_SUSPEND_TIME) {
            oled_off();
            return false;
        }
    }

    if (is_keyboard_master()) {
        oled_on();
        oled_render_left();
    }
    else {
        if (!oled_startup_done) {
            oled_startup_logo();
            defer_exec(OLED_LOGO_TIME + 1000, oled_startup, NULL);
        }
        else {
            oled_render_right();
        }
    }
    return false;
}


report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
    // Left side for horisontal/vertical scrolling
    left_report = pointing_device_set_scroll(left_report);

    // Right side as mouse pointer
    if (right_report.buttons > 0) {
        PLAY_SONG(click_sound);
        haptic_play();
    }

    return pointing_device_combine_reports(left_report, right_report);
}


// wake callbacks
void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
    oled_on();
}


// suspend callbacks
void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
    oled_off();
}


// Firmware reset: either soft reset or reset to boot loader
bool shutdown_user(bool jump_to_bootloader) {
    // Disable by default when booting
    haptic_disable();

    oled_render_boot(jump_to_bootloader);
    return true;
}

