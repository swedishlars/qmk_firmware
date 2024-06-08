#pragma once

// Custom keycode names
//-------------------------------------------------------------------------------------
// Movement
// Move to left desktop: C( = LCTL, G( = LGUI   result: LCTL + LGUI (meta) + LEFT ARROW
#define DESK_L C(G(KC_LEFT))
#define DESK_R C(G(KC_RIGHT))

// momentarily activate layer when held
#define LT_NUMP LT(_NUMPAD,KC_CAPS)

// actions
#define KC_UNDO C(KC_Z)
#define KC_CUT C(KC_X)
#define KC_COPY C(KC_C)
#define KC_PASTE C(KC_V)

// Apps
#define KC_TERM LCA(KC_T)
#define KC_TMUX LCA(KC_D)
//-------------------------------------------------------------------------------------

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

enum sofle_layers {
    _DEFAULT = 0,
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _NUMPAD,
    _MOUSE,
    _ADJUST
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

