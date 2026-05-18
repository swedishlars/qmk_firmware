/* Copyright 2024 Lars Johansson (github.com/swedishlars)
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include "quantum.h"

// Custom keycode names
//-------------------------------------------------------------------------------------
// Movement
// Move to left desktop: C( = LCTL, G( = LGUI   result: LCTL + LGUI (meta) + LEFT ARROW
#define DESK_L C(G(KC_LEFT))
#define DESK_R C(G(KC_RIGHT))

// momentarily activate layer when held
// #define CAPS_ADJUST LT(_CONF, KC_CAPS)
#define LT_FUNC LT(_FUNC,KC_CAPS)

// actions
#define KC_UNDO C(KC_Z)
#define KC_CUT C(KC_X)
#define KC_COPY C(KC_C)
#define KC_PASTE C(KC_V)

// Apps
#define KC_TERM LCA(KC_T)
#define KC_TMUX LCA(KC_D)


enum custom_keycodes {
    KL_TOGL = SAFE_RANGE, // keylogger toggle
    OL_SLEEP,             // oled sleep
    OL_TOGL,              // oled toggle
    AS_TOGL,              // autoshift toggle
    SS_ILST,              // send str: Ileanastr
    SS_ILEA,              // send str: Ileana
    SS_IOAN,              // send str: Ioanna
    SS_STRA,              // send str: Stravoskiadi
    SS_LAIL,              // send str: larsileana
    SS_GMIL,              // send str: @gmail.com
    SS_HEEM,              // send str: henryemmanouil
    SS_HENR,              // send str: Henry
    SS_EMMA,              // send str: Emmanouil
    SS_SWEL,              // send str: swedishlars
    SS_LARS,              // send str: Lars
    SS_GUNN,              // send str: Gunnar
    SS_JOHA,              // send str: Johansson
    SW_SCLN,              // Custom SEMICOLON: converts Swedish to US layout
    SW_GRV,               // Custom GRAVE: converts Swedish to US layout
    SW_BSLS,              // Custom BACKSLASH: converts Swedish to US layout
    SW_EQL                // Custom EQUAL: converts Swedish to US layout
};

enum sofle_layers {
    _BASE = 0,
    _GAME,
    _LOWER,
    _RAISE,
    _FUNC,
    _MOUSE,
    _MACRO,
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

