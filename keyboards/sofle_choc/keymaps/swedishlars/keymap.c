/* Copyright 2021 Dane Evans
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>

#include QMK_KEYBOARD_H

// LIB USED FOR  LED INDICATOR BREATHING EFFECT
#include "lib/lib8tion/lib8tion.h"

#include "lib/rgb.h"
#include "lib/oled.h"
#include "lib/pointing_device.h"
#include "swedishlars.h"


// TODO make haptic func?
// TODO add fullscreen, quit app
// TODO Add tapdance for numpad layer switching (tap/hold)

// custom sounds
float click_sound[][2] = SONG(TERMINAL_SOUND);
/* float close_encounter_song[][2] = SONG(CLOSE_ENCOUNTERS_SONG); */


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 // layer 0
[_QWERTY] = LAYOUT(
 // .-----------------------------------------------------------------------.                          ,-----------------------------------------------------------------------.
 // | esc       |    1      |    2      |   3       |    4      |   5       |                          |    6      |    7      |    8      |    9      |    0      | back      |
     KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,                                  KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_BSPC,
 // |-----------+-----------+-----------+-----------+-----------+-----------|                          |-----------+-----------+-----------+-----------+-----------+-----------|
 // | tab/swtc  |    Q      |    W      |    E      |    R      |    T      |                          |    Y      |    U      |    I      |    O      |    P      | # and ~   |
     KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,                                  KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_NUHS,
 // |-----------+-----------+-----------+-----------+-----------+-----------|                          |-----------+-----------+-----------+-----------+-----------+-----------|
 // | caps/num  |    A      |    S      |    D      |    F      |   G       |                          |    H      |    J      |    K      |    L      | ; and :   | ' and @   |
     LT_NUMP,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,                                  KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,
 // |-----------+-----------+-----------+-----------+-----------+-----------+-----------.  .-----------|-----------+---------- +-----------+-----------+-----------+-----------|
 // | lshift    |    Z      |    X      |    C      |    V      |    B      |           |  |           |    N      |    M      | , and <   | . and >   | / and ?   | rshift    |
     KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_NO,          KC_NO,     KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,
 // .-----------+-----------+-----------+-----------+-----------------------|-----------|  |-----------|-----------+-----------+-----------+-----------+-----------+-----------'
 //                         | \ and |   |left ctl   |left alt   | lower     | space     |  | enter     |  raise    |right alt  | - and _   | = and +   |
                             KC_NUBS,    KC_LCTL,     KC_LALT,   TT(_LOWER), KC_SPC,        KC_ENT,     TT(_RAISE), KC_RALT,    KC_MINS,    KC_EQL
 //                         |___________|___________|___________|___________|___________|  |___________|___________|___________|___________|___________|
),

// layer 1
// NOTE shift+ctl is a combo for work
[_LOWER] = LAYOUT(
 // .-----------------------------------------------------------------------.                          ,-----------------------------------------------------------------------.
 // |           | F1        | F2        | F3        | F4        | F5        |                          | F6        | F7        | F8        |F9         | F10       |frw del    |
     _______,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,                                 KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_DEL,
 // |-----------+-----------+-----------+-----------+-----------+-----------|                          |-----------+-----------+-----------+-----------+-----------+-----------|
 // | ` and ¬   | F11       | F12       |           |           | terminal  |                          |           |           | [ and {   | ] and }   |print scren|           |
     KC_GRV,     KC_F11,     KC_F12,     _______,    _______,    KC_TERM,                               _______,    _______,    KC_LBRC,    KC_RBRC,    KC_PSCR,    _______,
 // |-----------+-----------+-----------+-----------+-----------+-----------|                          |-----------+-----------+-----------+-----------+-----------+-----------|
 // |           | app menu  |           | tmux term |max win tgl|page up    |                          | left      | down      | up        |  right    |           |           |
     _______,    KC_APP,     _______,    KC_TMUX,    LCA(KC_F),  KC_PGUP,                               KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,    _______,    _______,
 // |-----------+-----------+-----------+-----------+-----------+-----------+-----------.  .-----------|-----------+-----------+-----------+-----------+-----------+-----------|
 // | lshift+ctl|           |           |           |           |page down  |           |  |           |           |           |           |           |           | rshift    |
     S(KC_LCTL), _______,    _______,    _______,    _______,    KC_PGDN,    _______,       _______,    _______,    _______,    _______,    _______,    _______,    _______,
 // .-----------+-----------+-----------+-----------+-----------+-----------+-----------|  |-----------+-----------+-----------+-----------+-----------+-----------+-----------'
 //                         |           |           |           |           |           |  |           |           |           |           |           |
                             _______,    _______,    _______,    _______,    _______,       _______,    _______,    _______,    _______,    _______
 //                         |___________|___________|___________|___________|___________|  |___________|___________|___________|___________|___________|
),

// layer 2
[_RAISE] = LAYOUT(
 // .-----------------------------------------------------------------------.                          ,-----------------------------------------------------------------------.
 // |           | alt+F1    | alt+F2    | alt+F3    | alt+F4    | alt+F5    |                          | alt+F6    | alt+F7    | alt+F8    | alt+F9    | alt+F10   |insert     |
     _______,    A(KC_F1),     A(KC_F2),   A(KC_F3),   A(KC_F4),   A(KC_F5),                              A(KC_F6),   A(KC_F7),   A(KC_F8),   A(KC_F9),   A(KC_F10),  KC_INS,
 // |-----------+-----------+-----------+-----------+-----------+-----------|                          |-----------+-----------+-----------+-----------+-----------+-----------|
 // |    ¬      | alt+F11   | alt+F12   |           |           |           |                          |           |           |    {      |    }      | play      |           |
     S(KC_GRV),  A(KC_F11),  A(KC_F12),  _______,    _______,    _______,                               _______,    _______,    KC_LCBR,    KC_RCBR,    KC_MPLY,    _______,
 // |-----------+-----------+-----------+-----------+-----------+-----------|                          |-----------+-----------+-----------+-----------+-----------+-----------|
 // |           |           |           |           |           |           |                          | alt+left  | alt+down  | alt+up    | alt+right |           |           |
     _______,    _______,    _______,    _______,    _______,    KC_HOME,                               A(KC_LEFT), A(KC_DOWN), A(KC_UP), A(KC_RGHT),    _______,    _______,
 // |-----------+-----------+-----------+-----------+-----------+-----------+-----------.  .-----------|-----------+-----------+-----------+-----------+-----------+-----------|
 // |           | undo      | cut       |copy       |paste      |           |           |  |           |           |           |           |           |           |           |
     _______,    KC_UNDO,    KC_CUT,     KC_COPY,    KC_PASTE,   KC_END,     _______,       _______,    _______,    KC_MUTE,    KC_MPRV,    KC_MNXT,    _______,    _______,
 // .-----------+-----------+-----------+-----------+-----------+-----------+-----------|  |-----------+-----------+-----------+-----------+-----------+-----------+-----------'
 //                         |           |           |           |           |           |  |           |           |           | vol -     | vol+l     |
                             _______,    _______,    _______,    _______,    _______,       _______,    _______,    _______,    KC_VOLD,    KC_VOLU
 //                         |___________|___________|___________|___________|___________|  |___________|___________|___________|___________|___________|
),

// layer 3
[_NUMPAD] = LAYOUT(
 // .-----------------------------------------------------------------------.                          ,-----------------------------------------------------------------------.
 // |           |           |           |           |           |           |                          |    ^      |     7     |     8     |     9     |     0     | back      |
     _______,    _______,    _______,    _______,    _______,    _______,                               KC_CIRC,    KC_7,       KC_8,       KC_9,       KC_0,      KC_BSPC,
 // |-----------+-----------+-----------+-----------+-----------+-----------|                          |-----------+-----------+-----------+-----------+-----------+-----------|
 // |           |           |           |     =     |           |           |                          |           |     4     |     5     |     6     |           |           |
     _______,    _______,    _______,    KC_PEQL,    _______,    _______,                               _______,    KC_4,       KC_5,       KC_6,       KC_P,       _______,
 // |-----------+-----------+-----------+-----------+-----------+-----------|                          |-----------+-----------+-----------+-----------+-----------+-----------|
 // |           |           |           |           |           |           |                          |     H     |     1     |     2     |     3     |           |           |
     _______,    _______,    _______,    _______,    _______,     _______,                               KC_H,       KC_1,       KC_2,       KC_3,       _______,    _______,
 // |-----------+-----------+-----------+-----------+-----------+-----------+-----------.  .-----------|-----------+-----------+-----------+-----------+-----------+-----------|
 // |           |           |           |           |           |           |           |  |           |           |     *     |     ,     |   .       |     /     |           |
     _______,    _______,    _______,    _______,    _______,    _______,    _______,        _______,   _______,    KC_PAST,    KC_COMM,    KC_DOT,     _______,    _______,
 // .-----------+-----------+-----------+-----------+-----------+-----------+-----------|  |-----------+-----------+-----------+-----------+-----------+-----------+-----------'
 //                         |           |           |           |           |           |  |           |           |     =     |  - minus  |  + plus   |
                             _______,    _______,    _______,    _______,    _______,       _______,    _______,    KC_PEQL,    KC_PMNS,    KC_PPLS
 //                         |___________|___________|___________|___________|___________|  |___________|___________|___________|___________|___________|
),

// layer 4
[_MOUSE] = LAYOUT(
 // .-----------------------------------------------------------------------.                          ,-----------------------------------------------------------------------.
 // |           |           |           |           |           |           |                          |           |           |           |           |           |           |
     _______,    KC_ACL0,    KC_ACL1,    KC_ACL2,    _______,    _______,                               _______,    _______,    _______,    _______,    _______,    _______,
 // |-----------+-----------+-----------+-----------+-----------+-----------|                          |-----------+-----------+-----------+-----------+-----------+-----------|
 // |           |           |           |           |           |           |                          |           |           |           |           |           |           |
     _______,    _______,    _______,    _______,    _______,    _______,                               _______,    _______,    _______,    _______,    _______,    _______,
 // |-----------+-----------+-----------+-----------+-----------+-----------|                          |-----------+-----------+-----------+-----------+-----------+-----------|
 // |           |alt+mouse2 |alt+mouse3 |alt+mouse1 |           |wheel up   |                          |           |           |           |           |           |           |
     _______,    A(KC_BTN2), A(KC_BTN3), A(KC_BTN1), _______,    KC_WH_U,                               _______,    _______,    _______,    _______,    _______,    _______,
 // |-----------+-----------+-----------+-----------+-----------+-----------+-----------.  .-----------|-----------+---------- +-----------+-----------+-----------+-----------|
 // |           |           |           |           |           |wheel down |           |  |           |           |           |           |           |           |           |
     _______,    _______,    _______,    _______,    _______,    KC_WH_D,    _______,       _______,    _______,    _______,    _______,    _______,    _______,    _______,
 // .-----------+-----------+-----------+-----------+-----------+-----------+-----------|  |-----------|-----------+-----------+-----------+-----------+-----------+-----------'
 //                         |           |           |           |           |  Space    |  | rgb mode  |           |           |           |           |
                             _______,    _______,    _______,    KC_BTN3,    KC_BTN1,       KC_BTN2,    _______,    _______,    _______,    _______
 //                         |___________|___________|___________|___________|___________|  |___________|___________|___________|___________|___________|
),

// layer 5
[_ADJUST] = LAYOUT(
 // .-----------------------------------------------------------------------.                          ,-----------------------------------------------------------------------.
 // |           |  base lyr |  lower    |  raise    |  numpad   |  mouse    |                          |adjust     |           |           |           |           |  reboot   |
     QK_BOOT,    TO(_QWERTY),TO(_LOWER), TO(_RAISE), TO(_NUMPAD),TO(_MOUSE),                            TO(_ADJUST),XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    QK_BOOT,
 // |-----------+-----------+-----------+-----------+-----------+-----------|                          |-----------+-----------+-----------+-----------+-----------+-----------|
 // | clear mem |           |           |           |  rgb togg |rgb default|                          |           |           |oled sleep |oled tgl   |           | clear mem |
     EE_CLR,     XXXXXXX,    XXXXXXX,    XXXXXXX,    RGB_TOG,    RGB_M_P,                               XXXXXXX,    XXXXXXX,    KC_OSLEEP,  KC_OTGL,    XXXXXXX,    EE_CLR,
 // |-----------+-----------+-----------+-----------+-----------+-----------|                          |-----------+-----------+-----------+-----------+-----------+-----------|
 // |           | audio tog | sys sleep |           |           |           |                          | haptic tg |           |           |           |           |           |
     XXXXXXX,    AU_TOGG,    KC_SLEP,    XXXXXXX,    XXXXXXX,    XXXXXXX,                               HF_TOGG,    XXXXXXX,    KC_KEYLOG,  XXXXXXX,    XXXXXXX,    XXXXXXX,
 // |-----------+-----------+-----------+-----------+-----------+-----------+-----------.  .-----------|-----------+---------- +-----------+-----------+-----------+-----------|
 // |           |           |           |           |           |           |           |  |           |           |           |           |           |           |           |
     XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
 // .-----------+-----------+-----------+-----------+-----------+-----------+-----------|  |-----------|-----------+-----------+-----------+-----------+-----------+-----------'
 //                         |           |           |           |           |           |  |           |           |           | rgb -     |  bright + |
                             XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX,    RGB_VAD,    RGB_VAI
 //                         |___________|___________|___________|___________|___________|  |___________|___________|___________|___________|___________|

),

};

// Declare persistent eeprom config
user_config_t user_config;

// Oled help msg timer
uint16_t oled_help_timer = 0;


void pointing_device_init_user(void) {
    set_auto_mouse_layer(_MOUSE);
    set_auto_mouse_enable(true);
    set_auto_mouse_timeout(1000);  //default 650ms
}


void eeconfig_init_user(void) {
    user_config.raw = 0;
    /* user_config.oled_brightness = OLED_BRIGHTNESS; */
    user_config.oled_enabled = true;
    user_config.oled_sleep_enabled = true;
    eeconfig_update_user(user_config.raw);
}

void keyboard_post_init_user(void) {
    // Initialise eeprom user config
    user_config.raw = eeconfig_read_user();

    // left trackpad -use for vertical/horizontal scrolling
    pointing_device_set_cpi_on_side(true, 500);
    pointing_device_set_cpi_on_side(false, 500);

    // start timer for displaying help msg.
    oled_help_timer = timer_read();
}


layer_state_t layer_state_set_user(layer_state_t state) {
    // tri-layer, tap to toggle, hold to activate momentarily
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);

    switch (get_highest_layer(state)) {
    case _ADJUST:
        PLAY_SONG(click_sound);
        // TODO do I need to set this everytime?
        haptic_set_mode(1);
        haptic_play();
        break;
    }

    return state;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Process oled keycodes
    process_record_user_oled(keycode, record);

    // TODO add audio & haptic for rest of adjust layer keys (audio, rgb, sys sleep, oled)
    switch (keycode) {
        // TODO rm, use layer_state_set_user instead
        // tri_layer, when lower and raise keys are pressed, activate a third layer
        /* case KC_LOWER: */
        /*     if (record->event.pressed) { */
        /*         layer_on(_LOWER); */
        /*         update_tri_layer(_LOWER, _RAISE, _ADJUST); */
        /*         if (IS_LAYER_ON(_ADJUST)) { */
        /*             PLAY_SONG(click_sound); */
        /*             haptic_set_mode(1); */
        /*             haptic_play(); */
        /*         } */
        /*     } else { */
        /*         layer_off(_LOWER); */
        /*         update_tri_layer(_LOWER, _RAISE, _ADJUST); */
        /*     } */
        /*     return false; */

        /* case KC_RAISE: */
        /*     if (record->event.pressed) { */
        /*         layer_on(_RAISE); */
        /*         update_tri_layer(_LOWER, _RAISE, _ADJUST); */
        /*         if (IS_LAYER_ON(_ADJUST)) { */
        /*             PLAY_SONG(click_sound); */
        /*             haptic_set_mode(1); */
        /*             haptic_play(); */
        /*         } */
        /*     } else { */
        /*         layer_off(_RAISE); */
        /*         update_tri_layer(_LOWER, _RAISE, _ADJUST); */
        /*     } */
        /*     return false; */



        // allow normal process of modifiers and layer change
        // disregarding if keylogger is enabled 
        // TODO This did not work well with logger:
        // QK_MODS ... QK_LAYER_TAP_TOGGLE_MAX to include both mods and layers
        /* case QK_MODS ... QK_LAYER_TAP_TOGGLE_MAX: */
        // maybe works if I update keylogger?

        case QK_LAYER_TAP ... QK_LAYER_TAP_TOGGLE_MAX:
        case KC_LCTL ... KC_RGUI:
            return true;
    }

    // do not send key if keylogger help is enabled
    // (except for modifiers & layer change)
    if (oled_keylogger_enabled) {
        add_keylog(keycode, record);
        return false;
    }

    return true;
}



#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {

            // get led index
            uint8_t index = g_led_config.matrix_co[row][col];

            // get keycode
            uint16_t kc = keymap_key_to_keycode(layer, (keypos_t){col,row});

            // set rgb based on layer & key function
            if (index >= led_min && index < led_max) {
                set_layer_color(layer, index, kc);
            }
        }
    }

    // Set LED for Caps Lock
     set_caps_led_color();   
    return false;
}
#endif


#ifdef OLED_ENABLE
// Oled rotation on master side should be 0, while slave is flipper 180
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_0;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // Turn off oled by user
        if (!user_config.oled_enabled) {
            oled_off();
            return false;
        }

        // Turn off oled when keyboard is idle
        if (user_config.oled_sleep_enabled) {
            if (last_input_activity_elapsed() > OLED_SUSPEND_TIME) {
                oled_off();
                return false;
            }
        } 
        oled_render_left();
    }
    else {
        if (!oled_startup_done) {
            oled_startup_logo();
            defer_exec(OLED_LOGO_TIME + 1000, oled_startup, NULL);
        }
        else {
            oled_render_right();
        }
    }
    return false;
}
#endif


#ifdef POINTING_DEVICE_ENABLE
report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
    // Left side for horisontal/vertical scrolling
    left_report = pointing_device_set_scroll(left_report);

    // Right side as mouse pointer
    if (right_report.buttons > 0) {
        PLAY_SONG(click_sound);
        haptic_play();
    }

    return pointing_device_combine_reports(left_report, right_report);
}
#endif


// wake callbacks
void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
}


// suspend callbacks
void suspend_power_down_user(void) {
    oled_off();
    rgb_matrix_set_suspend_state(true);
}


// Firmware reset: either soft reset or reset to boot loader
bool shutdown_user(bool jump_to_bootloader) {
    // Disable by default when booting
    haptic_disable();

    oled_render_boot(jump_to_bootloader);
    return true;
}
