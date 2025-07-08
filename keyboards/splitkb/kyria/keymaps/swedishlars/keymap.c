/* Copyright 2024 Lars Johansson (github.com/swedishlars)
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include QMK_KEYBOARD_H

#include "lib/rgb.h"
#include "lib/oled.h"
#include "lib/tapdance.h"
#include "swedishlars.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// TODO Use tap-hold on KC_LCTL for something? or add One Shot
// TODO Use tap-hold on LALT for something? Or add One Shot.
// TODO Use One Shot on LSFT: OS_LSFT
// TODO remove caps lock, I do not need it. Use OneShotLayer (OSL(layer) for macros to send strings (names, addresses, words)
[_BASE] = LAYOUT(
// ,------------------------------------------------------------------------.                                                  ,-----------------------------------------------------------------------.
// |esc        |     Q     |     W     |     E      |     R     |     T     |                                                  |     Y     |     U     |     I     |     O     |     P     |backspace  |
    KC_ESC,     KC_Q,       KC_W,       KC_E,        KC_R,       KC_T ,                                                         KC_Y,       KC_U ,      KC_I ,      TD(SWE_O),  KC_P ,      KC_BSPC,
// |------------------------------------------------------------------------|                                                  ,-----------------------------------------------------------------------.
// |tab        |     A     |     S     |     D      |     F     |     G     |                                                  |     H     |     J     |     K     |     L     |    ;  :   |   '  @    |
    KC_TAB,     TD(SWE_A),  KC_S,       KC_D,        KC_F,       KC_G ,                                                         KC_H,       KC_J ,      KC_K ,      KC_L ,      KC_SCLN,    KC_QUOT,
// |-----------+-----------+-----------+------------+-----------+-----------+-----------------------.  ,-----------------------+-----------+-----------+-----------+-----------+-----------+-----------|
// |Left Shift |   Z       |   X       |     C      |   V       |   B       |  [ and {  |  \ and |  |  |  # and ~  |  ] and }  |     N     |   M       |   ,  <    | . >       |   /  ?    |cw/sft+ctl |
    KC_LSFT,    KC_Z,       KC_X,       KC_C,        KC_V,       KC_B,       KC_LBRC,    KC_NUBS,       KC_NUHS,    KC_RBRC,    KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    TD(CW_SFT),
// `-----------------------------------+------------+-----------+-----------+-----------+-----------|  |-----------+-----------+-----------+-----------+-----------+-----------------------------------'
//                                     |  ` and ¬   |  L ctl    |  L Alt    |  lower    |  space    |  |  enter    |  raise    |  - and _  |  = and +  |caps/adjust|
                                        KC_GRV,       KC_LCTL,    KC_LALT,   MO(_LOWER), KC_SPC,        KC_ENT,     MO(_RAISE), KC_MINS,    KC_EQL,     CAPS_ADJUST
//                                     `------------------------------------------------------------'  `-----------------------------------------------------------'
),

// Gaming layer
[_GAME] = LAYOUT(
// ,------------------------------------------------------------------------.                                                  ,-----------------------------------------------------------------------.
// |           |     A     |     W     |            |           |           |                                                  |           |           |           |           |           |           |
    _______,    KC_A,       _______,    _______,     _______,    _______,                                                       _______,    _______,    _______,    _______,    _______,    _______,
// |------------------------------------------------------------------------|                                                  ,-----------------------------------------------------------------------.
// |           |     Q     |     S     |     D      |     D     |           |                                                  |           |           |           |           |           |           |
    _______,    KC_Q,       _______,    _______,     _______,    _______,                                                       _______,    _______,    _______,    _______,    _______,    _______,
// |-----------+-----------+-----------+------------+-----------+-----------+-----------------------.  ,-----------------------+-----------+-----------+-----------+-----------+-----------+-----------|
// |           |           |           |            |           |           |           |           |  |           |           |           |           |           |           |           |           |
    _______,    _______,    _______,    _______,     _______,    _______,    _______,    _______,       _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
// `-----------------------------------+-----------+------------+-----------+-----------+-----------|  |-----------+-----------+-----------+-----------+-----------+-----------------------------------'
//                                     |            |           |           |           |           |  |           |           |           |           |           |
                                        _______,     _______,    _______,    LT(_LOWER,KC_SPC),_______, _______,    _______,    _______,    _______,    _______
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
        case TD(SWE_A):
        case TD(SWE_O):
            return 250;
        default:
            return TAPPING_TERM;
    }
}


// Configure keys that continue caps word. Includes tapdances for example.
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
        case TD(SWE_A):
        case TD(SWE_O):
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        // Deactivate Caps Word.
        default:
            return false;
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
// --------------------------------------------------------------------------------------
// Return an integer that corresponds to what kind of tap dance should be executed.
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) { return TD_SINGLE_TAP; }
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else { return TD_SINGLE_HOLD; }
    }
    // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
    // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
    // keystrokes of the key, and not the 'double tap' action/macro.
    else if (state->count == 2) {
        if (state->interrupted) { return TD_DOUBLE_SINGLE_TAP; }
        else if (state->pressed) { return TD_DOUBLE_HOLD; }
        else { return TD_DOUBLE_TAP; }

    }
    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) { return TD_TRIPLE_TAP; }
        else { return TD_TRIPLE_HOLD; }
    }
    else { return TD_UNKNOWN; }
}

// Right Shift: Tap turns on caps word. Hold outputs shift+ctrl
// TODO change this to just a normal right shift on hold? Depends if I need it for Maya?
// ---------------------------------------------------------------------
// Instance of td_tap_t for right shift tapdance
static td_tap_t td_rshift = {
    .is_press_action = true,
    .state = TD_NONE
};

void rshift_finished(tap_dance_state_t *state, void *user_data) {
    td_rshift.state = cur_dance(state);
    switch (td_rshift.state) {
        case TD_SINGLE_TAP: caps_word_on(); break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LSFT));
            // register_mods(MOD_BIT(KC_LCTL));
            break;
        default:
            break;
    }
}

void rshift_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_rshift.state) {
        case TD_SINGLE_TAP: break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LSFT));
            // unregister_mods(MOD_BIT(KC_LCTL));
            break;
        default:
            break;
    }
}

// Swedish letter a tapdance
// ---------------------------------------------------------------------
// Instance of td_tap_t for swedish a tapdance
static td_tap_t td_swe_a = {
    .is_press_action = true,
    .state = TD_NONE
};

void swe_a_finished(tap_dance_state_t *state, void *user_data) {
    td_swe_a.state = cur_dance(state);
    switch (td_swe_a.state) {
        case TD_SINGLE_TAP:  register_code(KC_A); break;
        case TD_SINGLE_HOLD: register_code16(S(KC_A)); break;
        // register unicode for swedish a with ring above
        case TD_DOUBLE_TAP:
            unicode_input_start();
            register_hex(0x00e5);
            unicode_input_finish();
            break;
        // register unicode for swedish capital A with ring above it.
        case TD_DOUBLE_HOLD:
            unicode_input_start();
            register_hex(0x00c5);
            unicode_input_finish();
            break;
        // When typing the word `buffer`, and you want to make sure that you send `ff`.
        // In other words, you are typing two single taps.
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_A); register_code(KC_A); break;
        // register unicode for swedish a with two dots above
        case TD_TRIPLE_TAP:
            unicode_input_start();
            register_hex(0x00e4);
            unicode_input_finish();
            break;
        // register unicode for swedish capital A with two dots above
        case TD_TRIPLE_HOLD:
            unicode_input_start();
            register_hex(0x00c4);
            unicode_input_finish();
            break;
        default: break;
    }
}

void swe_a_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_swe_a.state) {
        case TD_SINGLE_TAP: unregister_code(KC_A); break;
        case TD_SINGLE_HOLD: unregister_code16(S(KC_A)); break;
        case TD_DOUBLE_TAP: break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_A); break;
        case TD_TRIPLE_TAP: break;
        case TD_TRIPLE_HOLD: break;
        default: break;
    }
}

// Swedish o tapdance
// ---------------------------------------------------------------------
// Instance of td_tap_t for swedish o tapdance
static td_tap_t td_swe_o = {
    .is_press_action = true,
    .state = TD_NONE
};

void swe_o_finished(tap_dance_state_t *state, void *user_data) {
    td_swe_o.state = cur_dance(state);
    switch (td_swe_o.state) {
        case TD_SINGLE_TAP:  register_code(KC_O); break;
        case TD_SINGLE_HOLD: register_code16(S(KC_O)); break;
        // register unicode for swedish o with dots above
        case TD_DOUBLE_TAP:
            unicode_input_start();
            register_hex(0x00f6);
            unicode_input_finish();
            break;
        // register unicode for swedish capital O with dots above it.
        case TD_DOUBLE_HOLD:
            unicode_input_start();
            register_hex(0x00d6);
            unicode_input_finish();
            break;
        // When typing the word `buffer`, and you want to make sure that you send `ff`.
        // In other words, you are typing two single taps.
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_O); register_code(KC_O); break;
        default: break;
    }
}

void swe_o_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_swe_o.state) {
        case TD_SINGLE_TAP: unregister_code(KC_O); break;
        case TD_SINGLE_HOLD: unregister_code16(S(KC_O)); break;
        case TD_DOUBLE_TAP: break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_O); break;
        default: break;
    }
}

tap_dance_action_t tap_dance_actions[] = {
        [CW_SFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rshift_finished, rshift_reset),
        [SWE_A] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, swe_a_finished, swe_a_reset),
        [SWE_O] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, swe_o_finished, swe_o_reset)
};
// --------------------------------------------------------------------------------------


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Key logger that will display key function on Oled display.
    // Do not send key to host if keylogger help is enabled, with a few exceptions.
    // Allow normal process of:
    //   1. modifiers
    //   2. Dedicated layer change keys.
    // Otherwise the consectutive key press will not be handled.
    // Active modifiers will be checked by keylogger and displayed on oled.
    if (oled_keylogger_enabled) {
        switch (keycode) {
            // Allow normal process of layer change keys.
            case QK_LAYER_TAP ... QK_LAYER_TAP_TOGGLE_MAX:
                // Except explicit layer changes done from a layer.
                // Those should be checked by keylogger and displayed on oled.
                // TODO This works but is hardcoded. Test again if I can check if current layer is not base and break?
                if (keycode == TG(_GAME) || keycode == TO(_BASE)) {
                    break;
                } else {
                    return true;
                }

            // Allow normal process of real mods.
            case MODIFIER_KEYCODE_RANGE:
                return true;

            // Allow normal process of mod combos like  S(KC_LCTL) = shift+ctrl
            // NOTE this works but is hardcoded. Have not found a dynamic way.
            case S(KC_LCTL):
                return true;

        }
        // Display key log on Oled and do not send key press to host (return false).
        // But first, make sure key in not the keylog toggler.
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

