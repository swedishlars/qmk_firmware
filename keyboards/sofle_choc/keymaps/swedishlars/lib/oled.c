// Copyright 2024 Lars Johansson (github.com/swedishlars)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "oled.h"
#include "swedishlars.h"


// NOTE To implement drashna oled brightness adjust would require custom sync
// qadd8, qsub8 func
/* #include "lib/lib8tion/lib8tion.h" */


bool oled_startup_done = false;
bool oled_keylogger_enabled = false;

// custom audio
float keylog_sound[][2] = SONG(KEYLOGGER_SONG);
float adjust_sound[][2] = SONG(ADJUST_SOUND);


// Deferred execution callback to clear and rotate display.
// Returns 0 to indicate it should not be repeated.
uint32_t oled_startup(uint32_t trigger_time, void *cb_arg) {
    oled_clear();
    oled_startup_done = true;
    return 0;
}

// KEY LOGGER
// --------------------------------------------------------------------------
// Get a description of keycode that can be rendered on oled.
// First check if there is a layer enabled which has a description override.
// Then check if shift is held and there is a shifted keycode description.
// If none of the above is true, return a default keycode description.
const char* get_keycode_desc(uint16_t keycode, uint8_t key_desc_mod) {
    // Set keycode description override for layer
    uint8_t key_desc_layer = KEYCODE_DEFAULT;

    switch (get_highest_layer(layer_state)) {
        case _LOWER:
            key_desc_layer = KEYCODE_LOWER;
            break;
        case _RAISE:
            key_desc_layer = KEYCODE_RAISE;
            break;
    }

    if (keycode < ARRAY_SIZE(keycode_to_desc[KEYCODE_DEFAULT])) {
        // check if layer is enabled, get layer code description if available
        if (key_desc_layer > KEYCODE_DEFAULT) {
            if (strlen(keycode_to_desc[key_desc_layer][keycode]) > 0) {
                return keycode_to_desc[key_desc_layer][keycode];
            } 
        }

        // check if modifier is enabled (shift), get modifier description if available
        if (strlen(keycode_to_desc[key_desc_mod][keycode]) > 0) {
            return keycode_to_desc[key_desc_mod][keycode];
        } 

        // get default keycode description
        return keycode_to_desc[KEYCODE_DEFAULT][keycode];
    }

    return "          ";
} 

// Store current key code
char oled_key_code[OLED_KEYLOG_LENGTH] = {0};

// Store current active modifiers
// Use 20 char array (double line on oled)
char oled_key_mod[OLED_KEYLOG_LENGTH + 10] = {0};

// Store current key description
char oled_key_desc[OLED_KEYLOG_LENGTH] = {0};

void add_keylog(uint16_t keycode, keyrecord_t *record) {
    // Set keycode description override for modifier
    uint8_t key_desc_mod = KEYCODE_DEFAULT;

    // temp store any active modifiers
    char active_mods[OLED_KEYLOG_LENGTH + 10] = {0};

    // Get active real modifiers (actual mod keys pressed)
    const uint8_t mods = get_mods() | get_oneshot_mods() | get_weak_mods();

    // Get active weak mods, mods that are part of macros & modifier keycodes like LALT(kc) 
    // NOTE: get_weak_mods() above does not seem to cover all of it.
    const uint8_t weak_mods = QK_MODS_GET_MODS(keycode);

    // Temp store description for all active modifiers
    // Concatenate 5 char strings so oled renders max 2 mods per line
    if ((mods & MOD_MASK_SHIFT) || (weak_mods & MOD_MASK_SHIFT)) {
        strcat(active_mods, "SHFT+");
        key_desc_mod = KEYCODE_SHIFT;
    }

    // Temp store description for alt mod
    if ((mods & MOD_MASK_ALT) || (weak_mods & MOD_MASK_ALT)) {
        strcat(active_mods, " Alt+");
    }

    // Temp store description for ctrl mod
    if ((mods & MOD_MASK_CTRL) || (weak_mods & MOD_MASK_CTRL)) {
        strcat(active_mods, "Ctrl+");
    }

    // Store all current active modifier descriptions.
    // Pad string right aligned to 20 chars (double lines on oled)
    if (sizeof(active_mods)) {
        snprintf(oled_key_mod, OLED_KEYLOG_LENGTH + 10,"%20s", active_mods);
    } 
    // Store empty 20 char string if there are not modifiers
    else {
        snprintf(oled_key_mod, OLED_KEYLOG_LENGTH, "                    ");
    }

    // Set keycode
    if (IS_QK_MOD_TAP(keycode) && record->tap.count) {
        keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
    } 
    else if (IS_QK_LAYER_TAP(keycode) && record->tap.count) {
        keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    } 
    else if (IS_QK_MODS(keycode)) {
        keycode = QK_MODS_GET_BASIC_KEYCODE(keycode);
    } 

    // store keycode
    // NOTE If I get rid of if statement then I can render full range codes,
    if (keycode < ARRAY_SIZE(keycode_to_desc[KEYCODE_DEFAULT])) {
        snprintf(oled_key_code, OLED_KEYLOG_LENGTH, "kcode: %3d", keycode);
    } 

    // store key description
    snprintf(oled_key_desc, OLED_KEYLOG_LENGTH, get_keycode_desc(keycode, key_desc_mod));
}


// Renders keylog to oled
// NOTE only works on master side
void oled_render_keylog(uint8_t line) {
    oled_set_cursor(0, line);
    if (oled_keylogger_enabled) {
        oled_write_raw(keylogger_logo, sizeof(keylogger_logo));
        oled_set_cursor(0, line + 1);
        oled_write(oled_key_code, false);

        // This will write 20 char (double line)
        oled_write(oled_key_mod, false);
        oled_write(oled_key_desc, false);
    }
    else {
        oled_write(PSTR("          "), false);
        oled_write(PSTR("          "), false);
        oled_write(PSTR("          "), false);
        oled_write(PSTR("          "), false);
        oled_write(PSTR("          "), false);
    }
}


// Setup a mask which can be or'd with bytes to turn off pixels
// Fade oled screen in a random pixel fashion
// -------------------------------------------------------------------------------
const uint8_t single_bit_masks[8] = {127, 191, 223, 239, 247, 251, 253, 254};

void oled_render_fade(void) {
    //Define the reader structure
    oled_buffer_reader_t reader;
    uint8_t buff_char;

    // define timer
    static uint16_t timer = 0;
    
    if (timer_elapsed(timer) > 50) {
        timer = timer_read();
        reader = oled_read_raw(0);

        // Loop over the remaining buffer and erase pixels as we go
        for (uint16_t i = 0; i < reader.remaining_element_count; i++) {
            // Get the actual byte in the buffer by dereferencing the pointer
            buff_char = *reader.current_element;
            if (buff_char != 0) {
                oled_write_raw_byte(buff_char & single_bit_masks[rand() % 8], i);
            }
            // increment the pointer to fetch a new byte during the next loop
            reader.current_element++;
        }
    }
}


// Keyboard startup logo
void oled_startup_logo(void) {
    static uint16_t logo_timer;
    uint16_t timer = timer_elapsed(logo_timer);
    
    if (timer < OLED_LOGO_TIME) {
        oled_write_raw(qmk_logo, sizeof(qmk_logo));
        return;
    }
    if (timer > OLED_LOGO_TIME) {
        oled_render_fade();
    }
}


void oled_render_base(uint8_t line) {
    oled_set_cursor(0, line);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
}

void oled_render_base_help(uint8_t line) {
    oled_set_cursor(0, line);
    oled_write(PSTR("NumPad:   "), false);
    oled_write(PSTR("(Hold)    "), false);
    oled_write(PSTR("CapsLock  "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("Adjust:   "), false);
    oled_write(PSTR("Lower +   "), false);
    oled_write(PSTR("Raise     "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("Key help: "), false);
    oled_write(PSTR("Adjust + k"), false);
    oled_write(PSTR("          "), false);
}

void oled_render_lower(uint8_t line) {
    oled_set_cursor(0, line);
    oled_write(PSTR("Orange:   "), false);
    oled_write(PSTR("F keys    "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("Rose:     "), false);
    oled_write(PSTR("alt. keys "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("Blue:     "), false);
    oled_write(PSTR("navigation"), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("Green: PC "), false);
    oled_write(PSTR("commands  "), false);
}

void oled_render_raise(uint8_t line) {
    oled_set_cursor(0, line);
    oled_write(PSTR("Yellow:   "), false);
    oled_write(PSTR("Alt+F keys"), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("Rose:     "), false);
    oled_write(PSTR("alt. keys "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("Blue:     "), false);
    oled_write(PSTR("navigation"), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("Green:    "), false);
    oled_write(PSTR("media keys"), false);
}

void oled_render_numpad(uint8_t line) {
    oled_set_cursor(0, line);
    oled_write(PSTR("Orange:   "), false);
    oled_write(PSTR("Num keys  "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("Rose:     "), false);
    oled_write(PSTR("alt. keys "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
}

void oled_render_mouse(uint8_t line) {
    oled_set_cursor(0, line);
    oled_write(PSTR("Left pad: "), false);
    oled_write(PSTR("Scrolling "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("Right pad:"), false);
    oled_write(PSTR("Mouse     "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("Orange:   "), false);
    oled_write(PSTR("Mouse btns"), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("Yellow:   "), false);
    oled_write(PSTR("Mouse dpi "), false);
}

void oled_render_adjust(uint8_t line) {
    oled_set_cursor(0, line);
    oled_write(PSTR("Key help  "), false);
    oled_write(PSTR("press: K  "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
}


void oled_render_left(void) {
    // Led status
    led_t led_state = host_keyboard_led_state();
    oled_write_raw(leds_logo, sizeof(leds_logo));
    oled_set_cursor(7, 0);
    oled_write_raw(rgb_matrix_is_enabled() ? on_btn_logo : off_btn_logo, sizeof(on_btn_logo));

    // Oled sleep status
    oled_set_cursor(0, 1);
    oled_write_raw(oled_sleep_logo, sizeof(oled_sleep_logo));
    oled_set_cursor(7, 1);
    oled_write_raw(user_config.oled_sleep_enabled ? on_btn_logo : off_btn_logo, sizeof(on_btn_logo));

    // audio status
    oled_set_cursor(0, 2);
    oled_write_raw(audio_logo, sizeof(audio_logo));
    oled_set_cursor(7, 2);
    oled_write_raw(audio_is_on() ? on_btn_logo : off_btn_logo, sizeof(on_btn_logo));

    // haptic status
    oled_set_cursor(0, 3);
    oled_write_raw(haptic_logo, sizeof(haptic_logo));
    oled_set_cursor(7, 3);
    oled_write_raw(haptic_get_enable() ? on_btn_logo : off_btn_logo, sizeof(on_btn_logo));

    // Caps status
    oled_set_cursor(0, 4);
    oled_write_raw(caps_logo, sizeof(caps_logo));
    oled_set_cursor(7, 4);
    oled_write_raw(led_state.caps_lock ? on_btn_logo : off_btn_logo, sizeof(on_btn_logo));

    // bottom banner
    oled_set_cursor(0, 5);
    oled_write_raw(bottom_banner_logo, sizeof(bottom_banner_logo));

    // Shift modifier status
    oled_set_cursor(0, 6);
    if ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT) {
        oled_write_raw(shift_logo, sizeof(shift_logo));
    } 
    else { oled_write(PSTR("     "), false); }

    // Alt modifier status
    oled_set_cursor(5,6);
    if ((get_mods() | get_oneshot_mods()) & MOD_MASK_ALT) {
        oled_write_raw(alt_logo, sizeof(alt_logo));
    } 
    else { oled_write(PSTR("     "), false); }

    // Ctrl modifier status
    oled_set_cursor(0, 7);
    if ((get_mods() | get_oneshot_mods()) & MOD_MASK_CTRL) {
        oled_write_raw(ctrl_logo, sizeof(ctrl_logo));
    } 
    else { oled_write(PSTR("     "), false); }

    // Gui modifier status
    oled_set_cursor(5, 7);
    if ((get_mods() | get_oneshot_mods()) & MOD_MASK_GUI) {
        oled_write_raw(gui_logo, sizeof(gui_logo));
    } 
    else { oled_write(PSTR("     "), false); }

    // NOTE need to be on master side. Require custom sync.
    /* oled_set_cursor(0, 8); */
    /* oled_write(PSTR("Oled light"), false); */
    /* oled_write_ln(get_u8_str(oled_get_brightness(), ' '), false); */

    // keylogger
    oled_render_keylog(11);
}


// render info for current layer
void oled_render_right(void) {
    oled_write_raw(layer_logo, sizeof(layer_logo));
    oled_set_cursor(0, 2);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_raw(layer_base_logo, sizeof(layer_base_logo));

            if (timer_elapsed(oled_help_timer) < OLED_HELP_TIME) {
                oled_render_base_help(5);
            } else {
                oled_render_base(5);
            }
            break;
        case _LOWER:
            oled_write_raw(layer_lower_logo, sizeof(layer_lower_logo));
            oled_render_lower(5);
            break;
        case _RAISE:
            oled_write_raw(layer_raise_logo, sizeof(layer_raise_logo));
            oled_render_raise(5);
            break;
        case _NUMPAD:
            oled_write_raw(layer_numpad_logo, sizeof(layer_numpad_logo));
            oled_render_numpad(5);
            break;
        case _MOUSE:
            oled_write_raw(layer_mouse_logo, sizeof(layer_mouse_logo));
            oled_render_mouse(5);
            break;
        case _ADJUST:
            oled_write_raw(layer_adjust_logo, sizeof(layer_adjust_logo));
            oled_render_adjust(5);
            break;
        default:
            oled_write_raw_P(layer_undefined_logo, sizeof(layer_undefined_logo));
    }

}

// render a message when entering bootloader mode
void oled_render_boot(bool bootloader) {
    oled_clear();

    // test if I can write this as one string with line breaks instead
    if (bootloader) {
        oled_write(PSTR("Ready for "), false);
        oled_write(PSTR("new       "), false);
        oled_write(PSTR("Firmware.."), false);
    } 
    else {
        oled_write(PSTR("Rebooting "), false);
        oled_write(PSTR("...       "), false);
    }
    oled_render_dirty(true);
    oled_scroll_left();
}


bool process_record_user_oled(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {

            // toggle oled sleep
            case KC_OSLEEP:
                PLAY_SONG(adjust_sound);
                haptic_set_mode(1);
                haptic_play();
                user_config.oled_sleep_enabled = !user_config.oled_sleep_enabled;
                eeconfig_update_user(user_config.raw);
                break;

            // Toggle oled display on/off
            case KC_OTGL:
                PLAY_SONG(adjust_sound);
                haptic_set_mode(1);
                haptic_play();
                user_config.oled_enabled = !user_config.oled_enabled;
                eeconfig_update_user(user_config.raw);
                break;

            // NOTE: Increase oled brightness example
            // This require custom sync for slave side
            /* case KC_OLED_INC: */
            /*     user_config.oled_brightness = qadd8(user_config.oled_brightness, OLED_BRIGTHNESS_STEP); */
            /*     oled_set_brightness(user_config.oled_brightness); */
            /*     eeconfig_update_user(user_config.raw); */
            /*     break; */

            // toggle keylogger
            // TODO Need a visual queue that it is enabled
            case KC_KEYLOG:
                PLAY_SONG(keylog_sound);
                haptic_set_mode(1);
                haptic_play();
                oled_keylogger_enabled = !oled_keylogger_enabled;
                return false;
        }
    }
    
    return true;

}

