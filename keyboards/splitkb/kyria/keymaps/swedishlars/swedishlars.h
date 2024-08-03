// Copyright 2024 Lars Johansson (github.com/swedishlars)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Custom keycode names
//-------------------------------------------------------------------------------------
// Movement
// Move to left desktop: C( = LCTL, G( = LGUI   result: LCTL + LGUI (meta) + LEFT ARROW
// TODO use:
#define DESK_L C(G(KC_LEFT))
#define DESK_R C(G(KC_RIGHT))

// momentarily activate layer when held
// TODO orig:
#define CAPS_ADJUST LT(_ADJUST, KC_CAPS)

// TODO using caps word LT will not work with this keycode, I need tapdance
/* #define CAPS_ADJUST LT(_ADJUST, QK_CAPS_WORD_TOGGLE) */

// TODO not used:
/* #define TAB_NUMP LT(_NUMP, KC_TAB) */

// actions
// TODO not used:
/* #define KC_UNDO C(KC_Z) */
/* #define KC_CUT C(KC_X) */
/* #define KC_COPY C(KC_C) */
/* #define KC_PASTE C(KC_V) */

// Apps
#define KC_TERM LCA(KC_T)
#define KC_TMUX LCA(KC_D)

// Aliases for readability
// TODO unused?
/* #define QWERTY   DF(_QWERTY) */
/* #define SYM      MO(_RAISE) */
/* #define NAV      MO(_LOWER) */
/* #define ADJUST   MO(_ADJUST) */

// TODO use?
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
// TODO not used:
/* #define CTL_ESC  MT(MOD_LCTL, KC_ESC) */
/* #define ALT_ENT  MT(MOD_LALT, KC_ENT) */
//-------------------------------------------------------------------------------------
// TODO are some unused?
enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_LOWER,
    KC_RAISE,
    KC_ADJUST,
    KC_KEYLOG,
    KC_OSLEEP,
    KC_OTGL,
    /* KC_OLED_INC, */
    /* KC_OLED_DEC */
};

enum layers {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _FUNC,
    _ADJUST,
};

// persistent user config written to eeprom
typedef union {
    uint32_t raw;
    struct {
        //uint8_t oled_brightness : 8;
        bool oled_enabled : 1;
        bool oled_sleep_enabled : 1;
        bool haptic_enabled : 1;
    };
} user_config_t; 

extern user_config_t user_config;

