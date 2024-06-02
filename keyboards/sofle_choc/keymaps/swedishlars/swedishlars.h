#pragma once

// Custom keycode names
//
// TODO create send cmd to open terminal & also tmux?

// Movement
// Move to left desktop: C( = LCTL, G( = LGUI   result: LCTL + LGUI (meta) + LEFT ARROW
#define DESK_L C(G(KC_LEFT))
#define DESK_R C(G(KC_RIGHT))

// momentarily activate layer when held
#define LT_NUMP LT(_NUMPAD,KC_CAPS)

// Maya custom mouse keys (alt + mouse btn)
// TODO test maya keys as custom keycode so oled keylog works. I do not need this for keylog any longer!
// TODO rename KC_ABTN1
#define MAYA_R A(KC_BTN1)
#define MAYA_T A(KC_BTN3)
#define MAYA_S A(KC_BTN2)

// actions
#define KC_UNDO C(KC_Z)
#define KC_CUT C(KC_X)
#define KC_COPY C(KC_C)
#define KC_PASTE C(KC_V)

// Apps
#define KC_TERM LCA(KC_T)

// Modifiers
#define KC_AF1 A(KC_F1)       // alt + F1

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_LOWER,
    KC_RAISE,
    KC_ADJUST,
    KC_KEYLOG,
    KC_OSLEEP,
    /* MAYA_R, */
    /* MAYA_S */
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
