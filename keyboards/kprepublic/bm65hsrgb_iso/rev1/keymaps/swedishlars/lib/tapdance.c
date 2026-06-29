/* Copyright 2024 Lars Johansson (github.com/swedishlars)
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "tapdance.h"
#include "swedishlars.h"


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

// Capslock: Tap to switch to MACRO layer for one keypress, OSL(_MACRO). Hold for _FUNC layer.
// -------------------------------------------------------------------------------------------
// Instance of td_tap_t for this tapdance
static td_tap_t td_caps = { .is_press_action = true, .state = TD_NONE };

void caps_finished(tap_dance_state_t *state, void *user_data) {
    td_caps.state = cur_dance(state);
    switch (td_caps.state) {
        case TD_SINGLE_TAP:
            set_oneshot_layer(_MACRO, ONESHOT_START);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_LOWR);
            break;
        default: break;
    }
}

void caps_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_caps.state) {
        case TD_SINGLE_TAP:
            clear_oneshot_layer_state(ONESHOT_PRESSED);
            break;
        case TD_SINGLE_HOLD:
            layer_off(_LOWR);
            break;
        default: break;
    }
}

// Right Shift: Tap turns on caps word. Hold outputs Right Shift
// -------------------------------------------------------------
// Instance of td_tap_t for this tapdance
static td_tap_t td_rshift = { .is_press_action = true, .state = TD_NONE };

void rshift_finished(tap_dance_state_t *state, void *user_data) {
    td_rshift.state = cur_dance(state);
    switch (td_rshift.state) {
        case TD_SINGLE_TAP: caps_word_on(); break;
        // TODO testing:
        case TD_DOUBLE_TAP: caps_word_off(); break;
        case TD_SINGLE_HOLD: register_mods(MOD_BIT(KC_RSFT)); break;
        default: break;
    }
}

void rshift_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_rshift.state) {
        case TD_SINGLE_TAP: break;
        case TD_DOUBLE_TAP: break;
        case TD_SINGLE_HOLD: unregister_mods(MOD_BIT(KC_RSFT)); break;
        default: break;
    }
}


// GENERIC: Tap to send KC_X, hold to momentarily enable layer
// --------------------------------------------------------------------
// Instance of td_tap_t for this tapdance
static td_tap_t td_kc_layer = { .is_press_action = true, .state = TD_NONE };

void kc_layer_finished(tap_dance_state_t *state, void *user_data) {
    td_kc_layer.state = cur_dance(state);
    tap_dance_pair_t *pair = (tap_dance_pair_t *)user_data;

    switch (td_kc_layer.state) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_TRIPLE_TAP: register_code(pair->kc1); break;
        case TD_SINGLE_HOLD:
        case TD_DOUBLE_HOLD:
        case TD_TRIPLE_HOLD: layer_on(pair->kc2); break;
        default: break;
    }
}

void kc_layer_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_pair_t *pair = (tap_dance_pair_t *)user_data;

    switch (td_kc_layer.state) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
        case TD_TRIPLE_TAP: unregister_code(pair->kc1); break;
        case TD_SINGLE_HOLD:
        case TD_DOUBLE_HOLD:
        case TD_TRIPLE_HOLD: layer_off(pair->kc2); break;
        default: break;
    }
    td_kc_layer.state = TD_NONE;
}


// GENERIC - Tap to toggle a layer. Hold to momentarily activate a layer.
// Tap and hold layer does not have to be the same. Desired layers are passed in user data:
// [T_CAP] = ACTION_TAP_DANCE_DUAL_DATA(NULL, tg_mo_layer_finished, tg_mo_layer_reset, _MACRO, _LOWR),
// -----------------------------------------------------------------------
// Instance of td_tap_t for this tapdance
static td_tap_t td_tg_mo_layer = {.is_press_action = true, .state = TD_NONE};

void tg_mo_layer_finished(tap_dance_state_t *state, void *user_data) {
    td_tg_mo_layer.state = cur_dance(state);
    tap_dance_pair_t *pair = (tap_dance_pair_t *)user_data;

    switch (td_tg_mo_layer.state) {
        case TD_SINGLE_TAP:
            if (layer_state_is(pair->kc1)) layer_off(pair->kc1);
            else layer_on(pair->kc1);
            break;
        case TD_DOUBLE_TAP: break;
        case TD_TRIPLE_TAP: break;
        case TD_SINGLE_HOLD:
        case TD_DOUBLE_HOLD:
        case TD_TRIPLE_HOLD: layer_on(pair->kc2); break;
        default: break;
    }
}

void tg_mo_layer_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (td_tg_mo_layer.state == TD_SINGLE_HOLD) {
        tap_dance_pair_t *pair = (tap_dance_pair_t *)user_data;
        layer_off(pair->kc2);
    }
    td_tg_mo_layer.state = TD_NONE;
}


// TODO this can be made GENERIC to send tap: KC_X, hold: KC_Y
// TAPDANCE - Tap for normal KC_X. Hold to send Alt+KC_X
// -----------------------------------------------------
// Instance of td_tap_t for this tapdance
// static td_tap_t td_alt_tap_state = {.is_press_action = true, .state = TD_NONE};
//
// void td_alt_finished(tap_dance_state_t *state, void *user_data) {
//     td_alt_tap_state.state = cur_dance(state);
//     tap_dance_pair_t *pair = (tap_dance_pair_t *)user_data;
//     uint16_t keycode = pair->kc1;
//
//     switch (td_alt_tap_state.state) {
//         case TD_SINGLE_TAP: register_code(keycode); break;
//         case TD_SINGLE_HOLD: register_code16(LALT(keycode)); break;
//         case TD_DOUBLE_TAP: register_code(keycode); break;
//         case TD_TRIPLE_TAP: register_code(keycode); break;
//         case TD_UNKNOWN: break;
//         case TD_NONE: break;
//     }
// }
//
// void td_alt_reset(tap_dance_state_t *state, void *user_data) {
//     tap_dance_pair_t *pair = (tap_dance_pair_t *)user_data;
//     uint16_t keycode = pair->kc1;
//
//     switch (td_alt_tap_state.state) {
//         case TD_SINGLE_TAP: unregister_code(keycode); break;
//         case TD_SINGLE_HOLD: unregister_code16(LALT(keycode)); break;
//         case TD_DOUBLE_TAP: unregister_code(keycode); break;
//         case TD_TRIPLE_TAP: unregister_code(keycode); break;
//         case TD_UNKNOWN: break;
//         case TD_NONE: break;
//     }
//     td_alt_tap_state.state = TD_NONE;
// }

