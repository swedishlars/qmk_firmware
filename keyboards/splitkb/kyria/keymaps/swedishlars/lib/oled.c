// Copyright 2024 Lars Johansson (github.com/swedishlars)
// SPDX-License-Identifier: GPL-2.0-or-later

// TODO rm:
/* #include <stdio.h> */

#include "oled.h"
#include "swedishlars.h"


/* bool oled_startup_done = false; */
bool oled_keylogger_enabled = false;


// Deferred execution callback to clear and rotate display.
// Returns 0 to indicate it should not be repeated.
// TODO not used
/* uint32_t oled_startup(uint32_t trigger_time, void *cb_arg) { */
/*     oled_clear(); */
/*     oled_startup_done = true; */
/*     return 0; */
/* } */


// Advance multiple chars at once.
void oled_advance_chars(uint8_t chars, bool clear_char) {
    for (uint8_t i = 0; i < chars; i++) {
        if (clear_char) {
            oled_write(PSTR(" "), false);
        }
        else {
            oled_advance_char();
        }
    }
}

// Advance multiple pages (lines) at once.
void oled_advance_pages(uint8_t pages, bool clear_page) {
    for (uint8_t i = 0; i < pages; i++) {
        if (clear_page) {
            oled_advance_page(true);
        }
        else {
            oled_advance_page(false);
        }
    }
}


// Setup a mask which can be or'd with bytes to turn off pixels
// Fade oled screen in a random pixel fashion
// TODO not used
// -------------------------------------------------------------------------------
/* const uint8_t single_bit_masks[8] = {127, 191, 223, 239, 247, 251, 253, 254}; */

/* void oled_render_fade(void) { */
/*     //Define the reader structure */
/*     oled_buffer_reader_t reader; */
/*     uint8_t buff_char; */

/*     // define timer */
/*     static uint16_t timer = 0; */
    
/*     if (timer_elapsed(timer) > 50) { */
/*         timer = timer_read(); */
/*         reader = oled_read_raw(0); */

/*         // Loop over the remaining buffer and erase pixels as we go */
/*         for (uint16_t i = 0; i < reader.remaining_element_count; i++) { */
/*             // Get the actual byte in the buffer by dereferencing the pointer */
/*             buff_char = *reader.current_element; */
/*             if (buff_char != 0) { */
/*                 oled_write_raw_byte(buff_char & single_bit_masks[rand() % 8], i); */
/*             } */
/*             // increment the pointer to fetch a new byte during the next loop */
/*             reader.current_element++; */
/*         } */
/*     } */
/* } */


// Keyboard startup logo
// TODO not used, rm
/* void oled_startup_logo(void) { */
/*     static uint16_t logo_timer; */
/*     uint16_t timer = timer_elapsed(logo_timer); */
    
/*     if (timer < OLED_LOGO_TIME) { */
/*         oled_write_raw(qmk_logo, sizeof(qmk_logo)); */
/*         return; */
/*     } */
/*     if (timer > OLED_LOGO_TIME) { */
/*         oled_render_fade(); */
/*     } */
/* } */


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

    // TODO use OLED_EMPTY_LN
    return "          ";
} 

// Store current key code
char oled_key_code[OLED_KEYLOG_LENGTH] = {0};

// Store current active modifiers
char oled_key_mod[OLED_KEYLOG_LENGTH] = {0};

// Store current key description
char oled_key_desc[OLED_KEYLOG_LENGTH] = {0};

void add_keylog(uint16_t keycode, keyrecord_t *record) {
    // Set keycode description override for modifier
    uint8_t key_desc_mod = KEYCODE_DEFAULT;

    // temp store any active modifiers
    char active_mods[OLED_KEYLOG_LENGTH] = {0};

    // Get active real modifiers (actual mod keys pressed)
    const uint8_t mods = get_mods() | get_oneshot_mods() | get_weak_mods();

    // Get active weak mods, mods that are part of macros & modifier keycodes like LALT(kc) 
    // NOTE: get_weak_mods() above does not seem to cover all of it.
    const uint8_t weak_mods = QK_MODS_GET_MODS(keycode);

    // Temp store description for all active modifiers
    // Concatenate 5 char strings so oled renders max 2 mods per line
    if ((mods & MOD_MASK_SHIFT) || (weak_mods & MOD_MASK_SHIFT)) {
        strcat(active_mods, "Shift+");
        key_desc_mod = KEYCODE_SHIFT;
    }

    // Temp store description for alt mod
    if ((mods & MOD_MASK_ALT) || (weak_mods & MOD_MASK_ALT)) {
        strcat(active_mods, "Alt+");
    }

    // Temp store description for ctrl mod
    if ((mods & MOD_MASK_CTRL) || (weak_mods & MOD_MASK_CTRL)) {
        strcat(active_mods, "Ctrl+");
    }

    // Store all current active modifier descriptions.
    if (sizeof(active_mods)) {
        snprintf(oled_key_mod, OLED_KEYLOG_LENGTH, active_mods);
    } 
    else {
        // TODO is there a more elegant way?
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
    // TODO adjust padding
    if (keycode < ARRAY_SIZE(keycode_to_desc[KEYCODE_DEFAULT])) {
        snprintf(oled_key_code, OLED_KEYLOG_LENGTH, "key code: %3d", keycode);
    } 

    // store key description
    snprintf(oled_key_desc, OLED_KEYLOG_LENGTH, get_keycode_desc(keycode, key_desc_mod));
}


// Renders keylog to oled
// NOTE only works on master side
bool play_forward = true;

void oled_render_keylog(uint8_t clear_lines) {
    // TODO make func?
    static uint16_t timer = 0;
    static uint8_t  frame = 0;

    if (timer_elapsed(timer) > 50) {
        if (frame == 0) {
            play_forward = true;
        }
        if (frame == 11) {
            play_forward = false;
        }
        if (play_forward) {
            frame++;
        }
        else {
            frame--;
        }
        timer = timer_read();
    }

    oled_write_raw_P(keylogger_logo[frame], sizeof(keylogger_logo[0]));
    oled_advance_page(false);
    oled_advance_page(true);

    // render keycode
    oled_write_ln(oled_key_code, false);
    oled_advance_page(true);

    // render key description
    oled_write_ln(PSTR("Key Description: "), false);
    oled_advance_page(true);
    oled_write_ln(oled_key_mod, false);
    oled_write_ln(oled_key_desc, false);

    // clear remaining display
    oled_advance_pages(clear_lines, true);
}


// Caps status
void oled_render_caps(void) {
    // TODO orig:
    /* led_t led_state = host_keyboard_led_state(); */
    /* if (!led_state.caps_lock) { */
    // TODO using caps word
    if (!is_caps_word_on()) {
        oled_advance_page(true);
        return;
    }

    // TODO make func?
    static uint16_t timer = 0;
    static uint8_t  frame = 0;

    if (timer_elapsed(timer) > 50) {
        if (frame == 0) {
            play_forward = true;
        }
        if (frame == 7) {
            play_forward = false;
        }
        if (play_forward) {
            frame++;
        }
        else {
            frame--;
        }
        timer = timer_read();
    }

        /* oled_write_raw(caps_logo, sizeof(caps_logo)); */
        oled_write_raw(caps_logo[frame], sizeof(caps_logo[0]));
        oled_advance_page(false);
}


void oled_render_mods(void) {
    // empty line
    oled_advance_page(true);

    // Shift modifier status
    if ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT) {
        oled_write_raw(shift_logo, sizeof(shift_logo));
        oled_advance_chars(6, false);
    } 
    else { oled_advance_chars(6, true); }

    // Ctrl modifier status
    if ((get_mods() | get_oneshot_mods()) & MOD_MASK_CTRL) {
        oled_write_raw(ctrl_logo, sizeof(ctrl_logo));
        oled_advance_chars(5, false);
    } 
    else { oled_advance_chars(5, true); }

    // Alt modifier status
    if ((get_mods() | get_oneshot_mods()) & MOD_MASK_ALT) {
        oled_write_raw(alt_logo, sizeof(alt_logo));
        oled_advance_chars(5, false);
    } 
    else { oled_advance_chars(5, true); }

    // Gui modifier status
    oled_advance_chars(5, false);
    if ((get_mods() | get_oneshot_mods()) & MOD_MASK_GUI) {
        oled_write_raw(gui_logo, sizeof(gui_logo));
        oled_advance_chars(5, false);
    } 
    else { oled_advance_chars(5, true); }

    // empty line
    oled_advance_page(true);
}


void oled_render_settings(uint8_t clear_lines) {
    // auto shift status
    oled_write_raw(autoshift_logo, sizeof(autoshift_logo));
    oled_advance_chars(17, false);
    oled_write_raw(get_autoshift_state() ? on_logo : off_logo, sizeof(on_logo));
    oled_advance_page(false);

    // Oled sleep status
    oled_write_raw(oled_sleep_logo, sizeof(oled_sleep_logo));
    oled_advance_chars(17, false);
    oled_write_raw(user_config.oled_sleep_enabled ? on_logo : off_logo, sizeof(on_logo));
    oled_advance_page(false);

    // rgb status
    oled_write_raw(leds_logo, sizeof(leds_logo));
    oled_advance_chars(17, false);
    oled_write_raw(rgb_matrix_is_enabled() ? on_logo : off_logo, sizeof(on_logo));
    oled_advance_page(false);

    // clear remaining display
    oled_advance_pages(clear_lines, true);
}


/* void oled_render_base(uint8_t line) { */
void oled_render_base(void) {
    oled_advance_page(true);
    oled_write(PSTR("LOWER : numpad  nav  "), false);
    oled_advance_page(true);
    oled_write(PSTR("RAISE : symbols  nav "), false);
    oled_advance_page(true);
    oled_write(PSTR("FUNC  : LOWER + RAISE"), false);
    oled_write(PSTR("      : apps  media  "), false);
    oled_write(PSTR("      : F1-F12       "), false);
    oled_advance_page(true);
    oled_write(PSTR("ADJUST: HOLD CAPSLOCK"), false);
    oled_write(PSTR("      : help  keylog "), false);
    oled_write(PSTR("      : settings     "), false);
}

void oled_render_lower(void) {
    oled_advance_pages(3, true);
    oled_write(PSTR("NUMBER PAD           "), false);
    oled_advance_page(true);
    oled_write(PSTR("numbers     :  orange"), false);
    oled_advance_page(true);
    oled_write(PSTR("cursor move :  blue  "), false);
    oled_advance_page(true);
    oled_write(PSTR("punctuation :  rose  "), false);
    oled_advance_page(true);
    oled_write(PSTR("math        :  green "), false);
}

void oled_render_raise(void) {
    oled_advance_page(true);
    oled_write(PSTR("SYMBOLS -- NAVIGATION"), false);
    oled_advance_page(true);
    oled_write(PSTR("symbols     :  orange"), false);
    oled_advance_page(true);
    oled_write(PSTR("arrows      :  blue  "), false);
    oled_advance_page(true);
    oled_write(PSTR("page nav    :  azure "), false);
    oled_advance_page(true);
    oled_write(PSTR("Punctuation :  rose  "), false);
    oled_advance_page(true);
    oled_write(PSTR("modifier    :  green "), false);
}

void oled_render_func(void) {
    oled_advance_pages(3, true);
    oled_write(PSTR("F-KEYS - APPS - MEDIA"), false);
    oled_advance_page(true);
    oled_write(PSTR("f-keys      :  orange"), false);
    oled_advance_page(true);
    oled_write(PSTR("apps        :  blue  "), false);
    oled_advance_page(true);
    oled_write(PSTR("window      :  Rose: "), false);
    oled_advance_page(true);
    oled_write(PSTR("media       :  green "), false);
}

void oled_render_adjust(void) {
    oled_advance_page(true);
    oled_write(PSTR("CONFIGURATION - RESET"), false);
    oled_advance_page(true);
    oled_write(PSTR("Key help   :  orange "), false);
    oled_write(PSTR("pc system  :  blue   "), false);
    oled_write(PSTR("reset layer:  rose   "), false);
    oled_write(PSTR("bootloader :  red    "), false);
    oled_write(PSTR("clear eeprm:  yellow "), false);
    oled_write(PSTR("reboot     :  green  "), false);
    oled_advance_page(true);
    oled_write(PSTR("rgb light  :  cyan   "), false);
    oled_write(PSTR("oled       :  violet "), false);
}

/* void oled_render_mouse(uint8_t line) { */
/*     oled_set_cursor(0, line); */
/*     oled_write(PSTR("Left pad:           "), false); */
/*     oled_write(PSTR("Scrolling           "), false); */
/*     oled_write(PSTR("                    "), false); */
/*     oled_write(PSTR("Right pad:          "), false); */
/*     oled_write(PSTR("Mouse               "), false); */
/*     oled_write(PSTR("                    "), false); */
/*     oled_write(PSTR("Orange:             "), false); */
/*     oled_write(PSTR("Mouse btns          "), false); */
/*     oled_write(PSTR("                    "), false); */
/*     oled_write(PSTR("Yellow:             "), false); */
/*     oled_write(PSTR("Mouse dpi           "), false); */
/* } */

// line char count: 21
void oled_render_left(void) {
    // header banner
    oled_write_raw(norrland_header_logo, sizeof(norrland_header_logo));
    oled_advance_pages(2, false);

    // empty line
    oled_advance_page(true);

    oled_render_caps();

    // render active modifiers
    oled_render_mods();

    // keylogger
    if (oled_keylogger_enabled) {
        oled_render_keylog(1);
    }
    else {
        oled_render_settings(6);
    }
}


// render info for current layer
void oled_render_right(void) {
    oled_write_raw(layer_header_logo, sizeof(layer_header_logo));
    oled_advance_pages(2, false);

    // TODO make eeprom option to hide help and perhaps display a cool anim instead?
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_raw(layer_base_logo, sizeof(layer_base_logo));
            oled_advance_pages(2, false);
            oled_render_base();
            break;

        case _LOWER:
            oled_write_raw(layer_lower_logo, sizeof(layer_lower_logo));
            oled_advance_pages(2, false);
            oled_render_lower();
            break;

        case _RAISE:
            oled_write_raw(layer_raise_logo, sizeof(layer_raise_logo));
            oled_advance_pages(2, false);
            oled_render_raise();
            break;

        // TODO
        /* case _MOUSE: */
        /*     oled_write_raw(layer_mouse_logo, sizeof(layer_mouse_logo)); */
        /*     oled_render_mouse(5); */
        /*     break; */

        case _FUNC:
            oled_write_raw(layer_function_logo, sizeof(layer_function_logo));
            oled_advance_pages(2, false);
            oled_render_func();
            break;

        case _ADJUST:
            oled_write_raw(layer_adjust_logo, sizeof(layer_adjust_logo));
            oled_advance_pages(2, false);
            oled_render_adjust();
            break;

        default:
            oled_write_raw(layer_undefined_logo, sizeof(layer_undefined_logo));
            oled_advance_pages(2, false);
    }

}

// render a message when entering bootloader mode
void oled_render_boot(bool bootloader) {
    oled_clear();

    // test if I can write this as one string with line breaks instead
    if (bootloader) {
        oled_write(PSTR("Boot Loader          "), false);
        oled_write(PSTR("                     "), false);
        oled_write(PSTR("Ready for new        "), false);
        oled_write(PSTR("firmware...          "), false);
        oled_write(PSTR("                     "), false);
    } 
    else {
        oled_write(PSTR("Rebooting...         "), false);
        oled_write(PSTR("                     "), false);
        oled_write(PSTR("                     "), false);
        oled_write(PSTR("                     "), false);
    }
    oled_render_dirty(true);
    oled_scroll_left();
}


bool process_record_user_oled(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {

            // Toggle oled display on/off
            case KC_OTGL:
                user_config.oled_enabled = !user_config.oled_enabled;
                eeconfig_update_user(user_config.raw);
                break;

            // toggle oled sleep
            case KC_OSLEEP:
                user_config.oled_sleep_enabled = !user_config.oled_sleep_enabled;
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
            case KC_KEYLOG:
                oled_keylogger_enabled = !oled_keylogger_enabled;
                return false;
        }
    }
    
    return true;

}

