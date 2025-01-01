/* Copyright 2024 Lars Johansson (github.com/swedishlars)
 * SPDX-License-Identifier: GPL-2.0-or-later
 */
 
#include QMK_KEYBOARD_H

#include "lib/rgb.h"
#include "lib/oled.h"
#include "lib/tapdance.h"
#include "swedishlars.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// TODO use tap-hold on KC_LCTL for something?
// TODO do similar with LALT
// TODO remove caps lock, I do not need it?
[_BASE] = LAYOUT(
// ,------------------------------------------------------------------------.                                                  ,-----------------------------------------------------------------------.
// |esc        |     Q     |     W     |     E      |     R     |     T     |                                                  |     Y     |     U     |     I     |     O     |     P     |backspace  | 
    KC_ESC,     KC_Q,       KC_W,       KC_E,        KC_R,       KC_T ,                                                         KC_Y,       KC_U ,      KC_I ,      KC_O ,      KC_P ,      KC_BSPC,
// |------------------------------------------------------------------------|                                                  ,-----------------------------------------------------------------------.
// |tab        |     A     |     S     |     D      |     F     |     G     |                                                  |     H     |     J     |     K     |     L     |    ;  :   |   '  @    |
    KC_TAB,     KC_A,       KC_S,       KC_D,        KC_F,       KC_G ,                                                         KC_H,       KC_J ,      KC_K ,      KC_L ,      KC_SCLN,    KC_QUOT,
// |-----------+-----------+-----------+------------+-----------+-----------+-----------------------.  ,-----------------------+-----------+-----------+-----------+-----------+-----------+-----------|
// |Left Shift |   Z       |   X       |     C      |   V       |   B       |  [ and {  |  \ and |  |  |  # and ~  |  ] and }  |     N     |   M       |   ,  <    | . >       |   /  ?    |cw/sft+ctl |
    KC_LSFT,    KC_Z,       KC_X,       KC_C,        KC_V,       KC_B,       KC_LBRC,    KC_NUBS,       KC_NUHS,    KC_RBRC,    KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    TD(CW_SFT),
// `-----------------------------------+------------+-----------+-----------+-----------+-----------|  |-----------+-----------+-----------+-----------+-----------+-----------------------------------'
//                                     |  ` and ¬   |  L ctl    |  L Alt    |  lower    |  space    |  |  enter    |  raise    |  - and _  |  = and +  |caps/adjust|
                                        KC_GRV,       KC_LCTL,    KC_LALT,    TT(_LOWER), KC_SPC,        KC_ENT,     TT(_RAISE), KC_MINS,    KC_EQL,     CAPS_ADJUST
//                                     `------------------------------------------------------------'  `-----------------------------------------------------------'
),

// Gaming layer
[_GAME] = LAYOUT(
// ,------------------------------------------------------------------------.                                                  ,-----------------------------------------------------------------------.
// |           |           |     E     |      W     |           |           |                                                  |           |           |           |           |           |           | 
    _______,    _______,    KC_E,       KC_W,        _______,    _______,                                                       _______,    _______,    _______,    _______,    _______,    _______,
// |------------------------------------------------------------------------|                                                  ,-----------------------------------------------------------------------.
// |           |     F     |     A     |     S      |     D     |           |                                                  |           |           |           |           |           |           |
    _______,    KC_F,       KC_A,       KC_S,        KC_D,       _______,                                                       _______,    _______,    _______,    _______,    _______,    _______,
// |-----------+-----------+-----------+------------+-----------+-----------+-----------------------.  ,-----------------------+-----------+-----------+-----------+-----------+-----------+-----------|
// |           |           |           |            |           |           |           |           |  |           |           |           |           |           |           |           |           |
    _______,    _______,    _______,    _______,     _______,    _______,    _______,    _______,       _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
// `-----------------------------------+-----------+------------+-----------+-----------+-----------|  |-----------+-----------+-----------+-----------+-----------+-----------------------------------'
//                                     |            |           |           |           |           |  |           |           |           |           |           |
                                        _______,     _______,    _______,    _______,    _______,       _______,    _______,    _______,    _______,    _______
//                                     `------------------------------------------------------------'  `-----------------------------------------------------------'
),

// Numpad - follow standard pad layout as close as possible
[_LOWER] = LAYOUT(
// ,------------------------------------------------------------------------.                                                  ,-----------------------------------------------------------------------.
// |delete     |/ div      |7          |8           |9          |backspace  |                                                  |           |           |mouse up   |           |           |insert     | 
    KC_DEL,     KC_SLSH,    KC_7,       KC_8,        KC_9,       KC_BSPC,                                                       _______,    _______,    MS_UP,      _______,    _______,    KC_INS,
// |------------------------------------------------------------------------|                                                  ,-----------------------------------------------------------------------.
// |= equal    |* mult     |4          |5           |6          |- minus    |                                                  |wheel up   |mouse left |mouse down |mouse right|           |           |      
    KC_PEQL,    KC_ASTR,    KC_4,       KC_5,        KC_6,       KC_PMNS,                                                       MS_WHLU,    MS_LEFT,    MS_DOWN,    MS_UP,      MS_RGHT,    _______,
// |-----------+-----------+-----------+------------+-----------+-----------+-----------------------.  ,-----------------------+-----------+-----------+-----------+-----------+-----------+-----------|
// |. dot      |0          |1          |2           |3          |- plus     |           |           |  |mouse 2    |mouse 3    |wheel down |           |           |           |           |           |
    KC_DOT,     KC_0,       KC_1,       KC_2,        KC_3,       KC_PPLS,    _______,    _______,       MS_BTN2,    MS_BTN3,    MS_WHLD,    _______,    _______,    _______,    _______,    _______,
// `-----------------------------------+-----------+------------+-----------+-----------+-----------|  |-----------+-----------+-----------+-----------+-----------+-----------------------------------'
//                                     |           |            |enter      |           |           |  |mouse 1    |           |           |           |           |
                                        _______,    _______,     KC_ENT,     _______,    _______,       MS_BTN1,    _______,    _______,    _______,    _______
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
// |           |           |           |            |           |           |           |           |  |           |           |alt + left |alt + down |alt + up   |alt + right|           |           |
    _______,    _______,    _______,    _______,     _______,    _______,    _______,    _______,       _______,    _______,    A(KC_LEFT), A(KC_DOWN), A(KC_UP),   A(KC_RGHT), _______,    _______,
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
// |reboot     |           | pc sleep  |            |           |game layer |                                                  |           |           |           |           |           |reboot     |
    QK_RBT,     XXXXXXX,    KC_SLEP,    XXXXXXX,     XXXXXXX,    TG(_GAME),                                                     XXXXXXX,    XXXXXXX,    KC_KEYLOG,  XXXXXXX    ,XXXXXXX,    QK_RBT,
// |-----------+-----------+-----------+------------+-----------+-----------+-----------------------.  ,-----------------------+-----------+-----------+-----------+-----------+-----------+-----------|
// |           |           |           |clear eeprom|           |base layer |           |           |  |           |           |           |           |clear eeprm|           |           |auto shift |
    XXXXXXX,    XXXXXXX,    XXXXXXX,    EE_CLR,      XXXXXXX,    TO(_BASE),  XXXXXXX,    XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    EE_CLR,     XXXXXXX,    XXXXXXX,    AS_TOGL,
// `-----------------------------------+------------+-----------+-----------+-----------+-----------|  |-----------+-----------+-----------+-----------+-----------+-----------------------------------'
//                                     |            |           |           |           |           |  |           |           | rgb -     | rgb +     |           |
                                        XXXXXXX,     XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,       XXXXXXX,    XXXXXXX,    RGB_VAD,    RGB_VAI,    XXXXXXX
//                                     `------------------------------------------------------------'  `-----------------------------------------------------------'
),
};

// Declare persistent eeprom config
user_config_t user_config;

// TODO rm:
// Oled help msg timer
/* uint16_t oled_help_timer = 0; */


void eeconfig_init_user(void) {
    user_config.raw = 0;
    user_config.oled_enabled = true;
    user_config.oled_sleep_enabled = true;
    user_config.autoshift_enabled = true;
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

    // Custom eeprom autoshift init)
    if (user_config.autoshift_enabled) { autoshift_enable(); } 
    else { autoshift_disable(); }
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


layer_state_t layer_state_set_user(layer_state_t state) {
    // Turn off auto shift for gaming layer
    if (user_config.autoshift_enabled && IS_LAYER_OFF_STATE(state, _GAME)) {
        autoshift_enable();
    } else { autoshift_disable(); }

    // tri-layer, tap to toggle, hold to activate momentarily
    state = update_tri_layer_state(state, _LOWER, _RAISE, _FUNC);
    return state;
}


// tap dance
// Determine the tapdance state to return
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) { return TD_SINGLE_TAP; }
        else { return TD_SINGLE_HOLD; }
    }
    else { return TD_UNKNOWN; }
}

// Tap: turn on caps word. Hold: shift+ctrl
// NOTE: to use caps_word_toggle(), add TD(KC) to caps_word_press_user()
void rshift_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            caps_word_on();
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LSFT));
            register_mods(MOD_BIT(KC_LCTL));
            break;
        default:
            break;
    }
}

void rshift_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LSFT));
            unregister_mods(MOD_BIT(KC_LCTL));
            break;
        default:
            break;
    }
}

tap_dance_action_t tap_dance_actions[] = {
        [CW_SFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rshift_finished, rshift_reset)
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Key help/logger.
    // Do not send key to host if keylogger help is enabled.
    // Allow normal process of modifiers and dedicated layer change keys.
    // Otherwise the consectutive key press will not be handled.
    // Active modifiers will be checked by keylogger and displayed on oled.
    //
    if (oled_keylogger_enabled) {
        // disregarding if keylogger is enabled 
        switch (keycode) {
            case QK_LAYER_TAP ... QK_LAYER_TAP_TOGGLE_MAX:
                // Exept layer changes done from a layer.
                // Those should be checked by keylogger and displayed on oled.
                // TODO This works but is very hardcoded. test again if I can
                // check if current layer is not base and break?
                if (keycode == TG(_GAME) || keycode == TO(_BASE)) {
                    break;
                } else { 
                    return true;
                }

            // Allow normal process of real mods. 
            case MODIFIER_KEYCODE_RANGE:
                return true;

            // Allow normal process of mod combos like  S(KC_LCTL) = shift+ctrl
            // NOTE this works but s hardcoded. Have not found a dynamic way.
            case S(KC_LCTL):
                return true;

        }
        // make sure key in not the keylog toggler
        if (keycode != KC_KEYLOG) {
            add_keylog(keycode, record);
            return false;
        }
    }

    switch (keycode) {
        // Custom eeprom autoshift toggle
        case AS_TOGL:
            if (record->event.pressed) {
                user_config.autoshift_enabled = !user_config.autoshift_enabled;
                eeconfig_update_user(user_config.raw);

                if (user_config.autoshift_enabled) { autoshift_enable(); } 
                else { autoshift_disable(); }
            }
            break;
             
        // Toggle oled display on/off
        case KC_OTGL:
            if (record->event.pressed) {
                user_config.oled_enabled = !user_config.oled_enabled;
                eeconfig_update_user(user_config.raw);
            }
            break;

        // toggle oled sleep
        case KC_OSLEEP:
            if (record->event.pressed) {
                user_config.oled_sleep_enabled = !user_config.oled_sleep_enabled;
                eeconfig_update_user(user_config.raw);
            }
            break;

        // toggle keylogger
        case KC_KEYLOG:
            if (record->event.pressed) {
                oled_keylogger_enabled = !oled_keylogger_enabled;
            }
            return false;
    }
    return true;
}


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);
    set_layer_color(layer, led_min, led_max);
    set_caps_led_color();   
    
    // TODO this work if led index is on master side
    set_caps_word_led();
    return false;
}


bool oled_task_user(void) {
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

    if (is_keyboard_master()) {
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

