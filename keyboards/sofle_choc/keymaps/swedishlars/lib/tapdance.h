// Copyright 2024 Lars Johansson (github.com/swedishlars)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Tap Dance keycodes
enum td_keycodes {
    CW_SFT,     // Tap: toggle caps word. Hold: send shift+ctrl
    SWE_A,
    SWE_O
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

// finished and reset functions for each tapdance keycode
void rshift_finished(tap_dance_state_t *state, void *user_data);
void rshift_reset(tap_dance_state_t *state, void *user_data);

void swe_a_finished(tap_dance_state_t *state, void *user_data);
void swe_a_reset(tap_dance_state_t *state, void *user_data);

void swe_o_finished(tap_dance_state_t *state, void *user_data);
void swe_o_reset(tap_dance_state_t *state, void *user_data);
