/* Copyright 2024 Lars Johansson (github.com/swedishlars)
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include "quantum.h"

// Tap Dance keycodes
enum td_keycodes {
    T_RSFT,   // Tap: toggle caps word. Hold: send right shift
    T_CAP,    // Tap: macro one shot layer. Hold: func layer.
    T_RGUI,   // Tap: Left GUI. Hold: momenarily activate layer.
    // SWE_A,
    // SWE_O
};

// Define a type containing as many tapdance tap/hold states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;


// Define a tapdance state type
typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;


// Function to determine the current tapdance state
td_state_t cur_dance(tap_dance_state_t *state);

// finished and reset functions for tapdances
void rshift_finished(tap_dance_state_t *state, void *user_data);
void rshift_reset(tap_dance_state_t *state, void *user_data);

void caps_finished(tap_dance_state_t *state, void *user_data);
void caps_reset(tap_dance_state_t *state, void *user_data);

// GENERIC - activate layer. Tap to toggle, hold to activate momentarily.
void tg_mo_layer_finished(tap_dance_state_t *state, void *user_data);
void tg_mo_layer_reset(tap_dance_state_t *state, void *user_data);

// GENERIC - Tap to send normal KC_X, hold to momentarily enable layer
void kc_layer_finished(tap_dance_state_t *state, void *user_data);
void kc_layer_reset(tap_dance_state_t *state, void *user_data);

// TAPDANCE - Alt+KC_X on hold functions
// void td_alt_finished(tap_dance_state_t *state, void *user_data);
// void td_alt_reset(tap_dance_state_t *state, void *user_data);

