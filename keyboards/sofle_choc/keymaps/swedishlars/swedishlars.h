// Copyright 2024 Lars Johansson (github.com/swedishlars)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Custom keycode names
//-------------------------------------------------------------------------------------
// Movement
// Move to left desktop: C( = LCTL, G( = LGUI   result: LCTL + LGUI (meta) + LEFT ARROW
#define DESK_L C(G(KC_LEFT))
#define DESK_R C(G(KC_RIGHT))

// momentarily activate layer when held
#define CAPS_ADJUST LT(_CONF, KC_CAPS)
#define LT_FUNC LT(_FUNC,KC_CAPS)

// actions
#define KC_UNDO C(KC_Z)
#define KC_CUT C(KC_X)
#define KC_COPY C(KC_C)
#define KC_PASTE C(KC_V)

// Apps
#define KC_TERM LCA(KC_T)
#define KC_TMUX LCA(KC_D)
//-------------------------------------------------------------------------------------

// TODO split out into own header?
enum custom_keycodes {
    /* KC_KEYLOG, // TODO rename KL_TOGL */
    KC_KEYLOG = SAFE_RANGE,
    KC_OSLEEP, // TODO rename OL_SLEEP
    KC_OTGL,   // TODO rename OL_TOGL
    AS_TOGL,   // Custom autoshift
    SW_SCLN,    // Custom SEMICOLON: converts Swedish to US layout
    SW_GRV,     // Custom GRAVE: converts Swedish to US layout
    SW_BSLS,     // Custom BACKSLASH: converts Swedish to US layout
    SW_EQL     // Custom EQUAL: converts Swedish to US layout
};

enum sofle_layers {
    _BASE = 0,
    _LOWER,
    _RAISE,
    _FUNC,
    _MOUSE,
    _CONF
};


// persistent user config written to eeprom
typedef union {
    uint32_t raw;
    struct {
        bool oled_enabled : 1;
        bool oled_sleep_enabled : 1;
        bool haptic_enabled : 1;
        bool autoshift_enabled : 1;
    };
} user_config_t;

extern user_config_t user_config;

