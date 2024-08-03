/* Copyright 2024 Lars Johansson (github.com/swedishlars)
 * SPDX-License-Identifier: GPL-2.0-or-later
 */
 
#include QMK_KEYBOARD_H

#include "lib/rgb.h"
#include "lib/oled.h"
#include "swedishlars.h"

// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).
// TODO move CTL_QUOT to KC+EQL
// TODO do similar with RALT
// TODO Add mouse keys?
// TODO Use KC_GRV for something better? KC_LGUI?

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// TODO add mouse layer?
// TODO add mouse keys
// TODO I do not use r shift, replace with mouse layer?
// or to toggle some functionality? Maybe for mouse layer?
// TODO testing caps word on r shift
// TODO remove caps lock, I do not need it.
[_QWERTY] = LAYOUT(
// ,------------------------------------------------------------------------.                                                  ,-----------------------------------------------------------------------.
// |esc        |     Q     |     W     |     E      |     R     |     T     |                                                  |     Y     |     U     |     I     |     O     |     P     |backspace  | 
    KC_ESC,     KC_Q,       KC_W,       KC_E,        KC_R,       KC_T ,                                                         KC_Y,       KC_U ,      KC_I ,      KC_O ,      KC_P ,      KC_BSPC,
// |------------------------------------------------------------------------|                                                  ,-----------------------------------------------------------------------.
// |tab        |     A     |     S     |     D      |     F     |     G     |                                                  |     H     |     J     |     K     |     L     |    ;  :   | Ctr / ' " |
    KC_TAB,     KC_A,       KC_S,       KC_D,        KC_F,       KC_G ,                                                         KC_H,       KC_J ,      KC_K ,      KC_L ,      KC_SCLN,    CTL_QUOT,
// |-----------+-----------+-----------+------------+-----------+-----------+-----------------------.  ,-----------------------+-----------+-----------+-----------+-----------+-----------+-----------|
// |Left Shift |   Z       |   X       |   C        |   V       |   B       |[ {        |` and ¬    |  |# and ~    |] }        |   N       |   M       |   ,  <    | . >       |   /  ?    | RShift    |
    KC_LSFT,    KC_Z,       KC_X,       KC_C,        KC_V,       KC_B,       KC_LBRC,    KC_GRV,        KC_NUHS,    KC_RBRC,    KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    QK_CAPS_WORD_TOGGLE,
// `-----------------------------------+------------+-----------+-----------+-----------+-----------|  |-----------+-----------+-----------+-----------+-----------+-----------------------------------'
//                                     |\ and |     |L ctl      |L Alt      |lower      |space      |  |enter      |raise      |- and _    |= and +    |caps/adjust|
                                        KC_NUBS,     KC_LCTL,    KC_LALT,    TT(_LOWER), KC_SPC,        KC_ENT,     TT(_RAISE), KC_MINS,    KC_EQL,     CAPS_ADJUST
//                                     `------------------------------------------------------------'  `-----------------------------------------------------------'
),

// Numpad - follow standard pad layout as close as possible
[_LOWER] = LAYOUT(
// ,------------------------------------------------------------------------.                                                  ,-----------------------------------------------------------------------.
// |= equal    |/ div      |7          |8           |9          |backspace  |                                                  |           |           |           |           |           |insert     | 
    KC_PEQL,    KC_SLSH,    KC_7,       KC_8,        KC_9,       KC_BSPC,                                                       _______,    _______,    _______,    _______,    _______,    KC_INS,
// |------------------------------------------------------------------------|                                                  ,-----------------------------------------------------------------------.
// |delete     |* mult     |4          5|           |6          |- minus    |                                                  |           |           |           |           |           |           |      
    KC_DEL,     KC_ASTR,     KC_4,      KC_5,        KC_6,       KC_PMNS,                                                       _______,    _______,    _______,    _______,    _______,    _______,
// |-----------+-----------+-----------+------------+-----------+-----------+-----------------------.  ,-----------------------+-----------+-----------+-----------+-----------+-----------+-----------|
// |           |0          |1          |2           |3          |- plus     |           |           |  |           |           |           |           |           |           |           |           |
    _______,    KC_0,       KC_1,       KC_2,        KC_3,       KC_PPLS,    _______,    _______,       _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
// `-----------------------------------+-----------+------------+-----------+-----------+-----------|  |-----------+-----------+-----------+-----------+-----------+-----------------------------------'
//                                     |           |. dot       |enter      |           |           |  |           |           |           |           |           |
                                        _______,    KC_DOT,      KC_ENT,   _______,     _______,       _______,    _______,    _______,    _______,    _______
//                                     `------------------------------------------------------------'  `-----------------------------------------------------------'
),


// Symbols / nav keys
[_RAISE] = LAYOUT(
// ,------------------------------------------------------------------------.                                                  ,-----------------------------------------------------------------------.
// |           |     !     |     "     |     £      |     $     |     %     |                                                  |     ^     |     &     |     *     |     (     |     )     |delete     | 
    _______,    KC_EXLM,    KC_AT,      KC_HASH ,    KC_DLR,     KC_PERC,                                                       KC_CIRC,    KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RPRN,    KC_DEL,
// |------------------------------------------------------------------------|                                                  ,-----------------------------------------------------------------------.
// |           |home       |page down  |page up     |end        |           |                                                  |left       |down       |up         |right      |     :     |           |      
    _______,    KC_HOME,    KC_PGDN,    KC_PGUP,     KC_END,     _______,                                                       KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,    KC_COLN,    _______,
// |-----------+-----------+-----------+------------+-----------+-----------+-----------------------.  ,-----------------------+-----------+-----------+-----------+-----------+-----------+-----------|
// |lshift+ctl |           |           |            |           |           |           |           |  |           |           |alt + left |alt + down |alt + up   |alt + right|           |           |
    S(KC_LCTL), _______,    _______,    _______,     _______,    _______,    _______,    _______,       _______,    _______,    A(KC_LEFT), A(KC_DOWN), A(KC_UP),   A(KC_RGHT), _______,    _______,
// `-----------------------------------+-----------+------------+-----------+-----------+-----------|  |-----------+-----------+-----------+-----------+-----------+-----------------------------------'
//                                     |            |           |           |           |           |  |           |           |           |           |           |
                                        _______,     _______,    _______,    _______,    _______,       _______,    _______,    _______,    _______,    _______
//                                     `------------------------------------------------------------'  `-----------------------------------------------------------'
),


// Function / media / app keys 
[_FUNC] = LAYOUT(
// ,------------------------------------------------------------------------.                                                  ,-----------------------------------------------------------------------.
// |           |F1         |F2         |F3          |F4         |F5         |                                                  |F6         |F7         |F8         |F9         |F10        |F11        | 
    _______,    KC_F1,      KC_F2,      KC_F3,       KC_F4,      KC_F5,                                                         KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,
// |------------------------------------------------------------------------|                                                  ,-----------------------------------------------------------------------.
// |           |app menu   |print scren|            |max win tgl|tmux term  |                                                  |           |           |           |           |           |F12        |
    _______,    KC_APP,     KC_PSCR,    _______,     LCA(KC_F),  KC_TMUX,                                                       _______,    _______,    _______,    _______,    _______,    KC_F12,
// |-----------+-----------+-----------+------------+-----------+-----------+-----------------------.  ,-----------------------+-----------+-----------+-----------+-----------+-----------+-----------|
// |           |           |           |            |           |bash term  |           |           |  |           |           |play/pause |mute       |previous   |next       |           |           |
    _______,    _______,    _______,    _______,     _______,    KC_TERM,    _______,    _______,       _______,    _______,    KC_MPLY,    KC_MUTE,    KC_MPRV,    KC_MNXT,    _______,    _______,
// `-----------------------------------+-----------+------------+-----------+-----------+-----------|  |-----------+-----------+-----------+-----------+-----------+-----------------------------------'
//                                     |            |           |           |           |           |  |           |           |vol -      |vol +      |           |
                                        _______,     _______,    _______,    _______,    _______,       _______,    _______,    KC_VOLD,    KC_VOLU,    _______
//                                     `------------------------------------------------------------'  `-----------------------------------------------------------'
),

[_ADJUST] = LAYOUT(
// ,------------------------------------------------------------------------.                                                  ,-----------------------------------------------------------------------.
// |bootloader |           |           |            |toggle rgb |reset rgb  |                                                  |           |           |           |oled toggle|oled sleep |bootloader | 
    QK_BOOT,    XXXXXXX,    XXXXXXX,    XXXXXXX,     RGB_TOG,    RGB_M_P,                                                       XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_OTGL,    KC_OSLEEP,  QK_BOOT,
// |------------------------------------------------------------------------|                                                  ,-----------------------------------------------------------------------.
// |reboot     |           |           |            |           |           |                                                  |           |           |           |reset layer|           |reboot     |
    QK_RBT,     XXXXXXX,    XXXXXXX,    XXXXXXX,     XXXXXXX,    XXXXXXX,                                                       XXXXXXX,    XXXXXXX,    KC_KEYLOG,  TO(_QWERTY),XXXXXXX,    QK_RBT,
// |-----------+-----------+-----------+------------+-----------+-----------+-----------------------.  ,-----------------------+-----------+-----------+-----------+-----------+-----------+-----------|
// |           |           |           |clear eeprom|           |           |           |           |  |           |           |           |           |clear eeprm|           |           |auto shift |
    XXXXXXX,    XXXXXXX,    XXXXXXX,    EE_CLR,      XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    EE_CLR,     XXXXXXX,    XXXXXXX,    AS_TOGG,
// `-----------------------------------+------------+-----------+-----------+-----------+-----------|  |-----------+-----------+-----------+-----------+-----------+-----------------------------------'
//                                     |            |           |           |           |           |  |           |           | rgb -     | rgb +     |           |
                                        XXXXXXX,     XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,       XXXXXXX,    XXXXXXX,    RGB_VAD,    RGB_VAI,    XXXXXXX
//                                     `------------------------------------------------------------'  `-----------------------------------------------------------'
),
};

// Declare persistent eeprom config
user_config_t user_config;

// Oled help msg timer
/* uint16_t oled_help_timer = 0; */


void eeconfig_init_user(void) {
    user_config.raw = 0;
    /* user_config.oled_brightness = OLED_BRIGHTNESS; */
    user_config.oled_enabled = true;
    user_config.oled_sleep_enabled = true;
    eeconfig_update_user(user_config.raw);
}


// Oled rotation should be 0
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
        return OLED_ROTATION_0;
}


void keyboard_post_init_user(void) {
    // Initialise eeprom user config
    user_config.raw = eeconfig_read_user();

    // start timer for displaying help msg.
    // TODO use this for blinking logo?
    /* oled_help_timer = timer_read(); */
}


// tapping term per key (default is 200)
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TT(_LOWER):
        case TT(_RAISE):
            return 120;
        default:
            return TAPPING_TERM;
    }
}


// tri-layer, tap to toggle, hold to activate momentarily
layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _FUNC);
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Process oled keycodes
    process_record_user_oled(keycode, record);

    // do not send key if keylogger help is enabled
    // (except for modifiers & layer change)
    // TODO move to oled?
    if (oled_keylogger_enabled) {
        // allow normal process of modifiers and layer change
        // disregarding if keylogger is enabled 
        // NOTE cannot use QK_MODS ... QK_MODS_MAX here:
        switch (keycode) {
            case QK_LAYER_TAP ... QK_LAYER_TAP_TOGGLE_MAX:
            case KC_LCTL ... KC_RGUI:
                return true;
        }
        add_keylog(keycode, record);
        return false;
    }

    return true;
}


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);
    set_layer_color(layer, led_min, led_max);
    set_caps_led_color();   
    return false;
}

bool oled_task_user(void) {
    // TODO try moving this outside keyboard_master again, see if it fixes pc power off state
    // drashna has this and sleep in housekeeping_task_oled() which is called by housekeeping_task_user()
    if (is_keyboard_master()) {
        // Turn off oled by user
        if (!user_config.oled_enabled) {
            oled_off();
            return false;
        }

        // Turn off oled when keyboard input is idle
        if (user_config.oled_sleep_enabled) {
            if (last_input_activity_elapsed() > OLED_SUSPEND_TIME) {
                oled_off();
                return false;
            }
        } 
        oled_render_left();
    }
    else {
        oled_render_right();
    }
    return false;
}

// wake callbacks
void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
    oled_on();
}


// suspend callbacks
void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
    oled_off();
}


// Firmware reset: either soft reset or reset to boot loader
bool shutdown_user(bool jump_to_bootloader) {
    // Disable by default when booting
    oled_render_boot(jump_to_bootloader);
    return true;
}

