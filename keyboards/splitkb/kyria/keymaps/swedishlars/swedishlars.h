// Copyright 2024 Lars Johansson (github.com/swedishlars)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// keycode macros
// --------------
// Move to left desktop: C( = LCTL, G( = LGUI   result: LCTL + LGUI (meta) + LEFT ARROW
// TODO use:
#define DESK_L C(G(KC_LEFT))
#define DESK_R C(G(KC_RIGHT))

// momentarily activate layer when held
#define CAPS_ADJUST LT(_ADJUST, KC_CAPS)

// Apps
#define KC_TERM LCA(KC_T)
#define KC_TMUX LCA(KC_D)

// TODO are some unused?
enum custom_keycodes {
    /* KC_KEYLOG, // TODO rename KL_TOGL */
    KC_KEYLOG = SAFE_RANGE,
    KC_OSLEEP, // TODO rename OL_SLEEP
    KC_OTGL,   // TODO rename OL_TOGL
    AS_TOGL    // Custom autoshift
    /* KC_OLED_INC, */
    /* KC_OLED_DEC */
};

enum layers {
    _BASE = 0,
    _GAME,
    _LOWER,
    _RAISE,
    _FUNC,
    _ADJUST,
};

// persistent user config written to eeprom
typedef union {
    uint32_t raw;
    struct {
        bool oled_enabled : 1;
        bool oled_sleep_enabled : 1;
        bool autoshift_enabled : 1;
    };
} user_config_t; 

extern user_config_t user_config;

