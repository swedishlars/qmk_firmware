/* Copyright 2024 Lars Johansson (github.com/swedishlars)
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

 #include "tapdance.h"


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

