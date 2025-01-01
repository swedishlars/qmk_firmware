// Copyright 2024 Lars Johansson (github.com/swedishlars)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Tap Dance keycodes
enum td_keycodes {
    CW_SFT     // Tap: toggle caps word. Hold: send shift+ctrl
};

// Define a type containing as many tapdance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD
} td_state_t;

// Create a global instance of the tapdance state type
static td_state_t td_state;

// Function to determine the current tapdance state
td_state_t cur_dance(tap_dance_state_t *state);

// finished and reset functions for each tapdance keycode
void rshift_finished(tap_dance_state_t *state, void *user_data);
void rshift_reset(tap_dance_state_t *state, void *user_data);
