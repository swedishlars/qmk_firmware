// Copyright 2024 Lars Johansson (github.com/swedishlars)
// SPDX-License-Identifier: GPL-2.0-or-later

// TODO delete file

/* #include "tapdance.h" */


/* // Determine the tapdance state to return */
/* td_state_t cur_dance(tap_dance_state_t *state) { */
/*     if (state->count == 1) { */
/*         if (state->interrupted || !state->pressed) { return TD_SINGLE_TAP; } */
/*         else { return TD_SINGLE_HOLD; } */
/*     } */

/*     // TODO test without: */
/*     /1* if (state->count == 2) return TD_DOUBLE_SINGLE_TAP; *1/ */
/*     else { return TD_UNKNOWN; } */
/* } */

/* // Tap: turn on caps word. Hold: shift+ctrl */
/* // NOTE: to use caps_word_toggle(), add TD(KC) to caps_word_press_user() */
/* void rshift_finished(tap_dance_state_t *state, void *user_data) { */
/*     td_state = cur_dance(state); */
/*     switch (td_state) { */
/*         case TD_SINGLE_TAP: */
/*             caps_word_on(); */
/*             break; */
/*         case TD_SINGLE_HOLD: */
/*             register_mods(MOD_BIT(KC_LSFT)); */
/*             register_mods(MOD_BIT(KC_LCTL)); */
/*             break; */
/*         default: */
/*             break; */
/*     } */
/* } */

/* void rshift_reset(tap_dance_state_t *state, void *user_data) { */
/*     switch (td_state) { */
/*         case TD_SINGLE_TAP: */
/*             break; */
/*         case TD_SINGLE_HOLD: */
/*             unregister_mods(MOD_BIT(KC_LSFT)); */
/*             unregister_mods(MOD_BIT(KC_LCTL)); */
/*             break; */
/*         default: */
/*             break; */
/*     } */
/* } */

