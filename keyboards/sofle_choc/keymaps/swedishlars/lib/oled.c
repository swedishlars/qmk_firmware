#include "oled.h"
#include "swedishlars.h"

// TODO implement drashna oled brightness adjust

bool oled_startup_done = false;
bool oled_keylogger_enabled = false;

// Deferred execution callback to clear and rotate display.
// Returns 0 to indicate it should not be repeated.
// TODO rename func now that no rotation is needed
uint32_t oled_rotate(uint32_t trigger_time, void *cb_arg) {
    oled_clear();

    // NOTE: rotation for orig screen:
    /* oled_init(OLED_ROTATION_270); */

    oled_startup_done = true;
    return 0;
}

// KEY LOGGER
// --------------------------------------------------------------------------
const char* get_keycode_desc(uint16_t keycode) {
    // check if we have a layer code desc
    if (layer_state_is(_LOWER)) {
        if ( (keycode < ARRAY_SIZE(lower_keycode_to_name)) &&
            (strlen(lower_keycode_to_name[keycode]) > 0)
        ) {
            return lower_keycode_to_name[keycode];
        }
    }

    if (layer_state_is(_RAISE)) {
        if ( (keycode < ARRAY_SIZE(raise_keycode_to_name)) &&
            (strlen(raise_keycode_to_name[keycode]) > 0)
        ) {
            return raise_keycode_to_name[keycode];
        }
    }

    // check if we have a shifted code
    if ( (keycode < ARRAY_SIZE(shifted_keycode_to_name)) && 
        (get_mods() & MOD_MASK_SHIFT)
    ) {
        return shifted_keycode_to_name[keycode];
    }

    // check if we have a un-modified code
    if (keycode < ARRAY_SIZE(keycode_to_name)) {
        return keycode_to_name[keycode];
    }

    return "          ";
} 

// Store keylog
char oled_keylog_str[OLED_KEYLOG_LENGTH] = {0};
char oled_keylog_code[OLED_KEYLOG_LENGTH] = {0};

void add_keylog(uint16_t keycode, keyrecord_t *record) {
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
    if (keycode < ARRAY_SIZE(keycode_to_name)) {
        // orig 128x32 oled
        /* snprintf(oled_keylog_code, OLED_KEYLOG_LENGTH, "k:%3d", keycode); */

        // new 64x128 oled:
        snprintf(oled_keylog_code, OLED_KEYLOG_LENGTH, "kcode: %3d", keycode);
    }

    // store key description
    snprintf(oled_keylog_str, OLED_KEYLOG_LENGTH, get_keycode_desc(keycode));
}


// Renders keylog to oled
// NOTE only works on master side
void oled_render_keylog(uint8_t line) {
    oled_set_cursor(0, line);
    if (oled_keylogger_enabled) {
        oled_write(PSTR("KEY LOGGER"), false);
        oled_write(oled_keylog_code, false);
        /* oled_set_cursor(0, line + 2); */
        oled_write(PSTR("          "), false);
        oled_write(oled_keylog_str, false);
    }
    else {
        oled_write(PSTR("          "), false);
        oled_write(PSTR("          "), false);
        oled_write(PSTR("          "), false);
    }
}

// Setup a mask which can be or'd with bytes to turn off pixels
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


// use as startup logo
void oled_render_logo(void) {
    static uint16_t logo_timer;
    uint16_t timer = timer_elapsed(logo_timer);
    
    if (timer < OLED_LOGO_TIME) {
        // NOTE logo for orig display:
        /* oled_write_P(qmk_logo, false); */

        // 64x128 oled
        oled_write_raw(qmk_logo, sizeof(qmk_logo));
        return;
    }
    if (timer > OLED_LOGO_TIME) {
        oled_render_fade();
    }
}





void oled_render_base_help(uint8_t line) {
    oled_set_cursor(0, line);
    oled_write(PSTR("Hold      "), false);
    oled_write(PSTR("Caps Lock "), false);
    oled_write(PSTR("for NumPad"), false);
    oled_write(PSTR("layer     "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("Lower     "), false);
    oled_write(PSTR("  +       "), false);
    oled_write(PSTR("Raise     "), false);
    oled_write(PSTR("for Setup "), false);
    oled_write(PSTR("layer     "), false);
    oled_write(PSTR("   ---    "), false);
    /* oled_write(PSTR("          "), false); */
}

void oled_render_lower_help(uint8_t line) {
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
    /* oled_write(PSTR("          "), false); */
}

void oled_render_raise_help(uint8_t line) {
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
    /* oled_write(PSTR("          "), false); */
}

void oled_render_numpad_help(uint8_t line) {
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
    /* oled_write(PSTR("          "), false); */
}

void oled_render_mouse_help(uint8_t line) {
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
    /* oled_write(PSTR("          "), false); */
}

void oled_render_setup_help(uint8_t line) {
    oled_set_cursor(0, line);
    oled_write(PSTR("For help  "), false);
    oled_write(PSTR("with keys "), false);
    oled_write(PSTR("press:  K "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
    /* oled_write(PSTR("          "), false); */
}

void oled_render_no_help(uint8_t line) {
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
    /* oled_write(PSTR("          "), false); */
}

/* void oled_render_right(void) { */
void oled_render_left(void) {
    // TODO test
    /* if (!is_oled_on()) { */
    /*     return; */
    /* } */

    // Keyboard LED Status
    led_t led_state = host_keyboard_led_state();

    /* oled_write(led_state.caps_lock ? PSTR("Caps    ON") : PSTR("Caps   OFF"), false); */

    // new oled, new width is 10 chars
    oled_write_raw(caps_logo, sizeof(caps_logo));
    oled_set_cursor(7, 0);
    oled_write_raw(led_state.caps_lock ? on_btn_logo : off_btn_logo, sizeof(on_btn_logo));

    // TODO add insert if possible

    // rgb status
    oled_set_cursor(0, 1);
    /* oled_write(rgb_matrix_is_enabled() ? PSTR("Leds    ON") : PSTR("Rgb    OFF"), false); */

    oled_write_raw(leds_logo, sizeof(leds_logo));
    oled_set_cursor(7, 1);
    oled_write_raw(rgb_matrix_is_enabled() ? on_btn_logo : off_btn_logo, sizeof(on_btn_logo));

    // audio
    oled_set_cursor(0, 2);
    /* oled_write(audio_is_on() ? PSTR("Audio   ON") : PSTR("Audio  OFF"), false); */
    oled_write_raw(audio_logo, sizeof(audio_logo));
    oled_set_cursor(7, 2);
    oled_write_raw(audio_is_on() ? on_btn_logo : off_btn_logo, sizeof(on_btn_logo));

    // haptic
    oled_set_cursor(0, 3);
    /* uint8_t haptic_state = haptic_get_enable(); */
    /* oled_write(haptic_state ? PSTR("Haptic  ON") : PSTR("Haptic OFF"), false); */
    oled_write_raw(haptic_logo, sizeof(haptic_logo));
    oled_set_cursor(7, 3);
    oled_write_raw(haptic_get_enable() ? on_btn_logo : off_btn_logo, sizeof(on_btn_logo));

    oled_set_cursor(0, 4);
    oled_write_raw(bottom_banner_logo, sizeof(bottom_banner_logo));

    // modifier
    oled_set_cursor(0, 5);
    /* oled_write((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT ? PSTR("SHIFT") : PSTR("     "), false); */

    if ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT) {
        oled_write_raw(shift_logo, sizeof(shift_logo));
    } 
    else { oled_write(PSTR("     "), false); }

    oled_set_cursor(5,5);
    /* oled_write((get_mods() | get_oneshot_mods()) & MOD_MASK_ALT ? PSTR("  ALT") : PSTR("     "), false); */

    if ((get_mods() | get_oneshot_mods()) & MOD_MASK_ALT) {
        oled_write_raw(alt_logo, sizeof(alt_logo));
    } 
    else { oled_write(PSTR("     "), false); }

    oled_set_cursor(0, 6);
    /* oled_write((get_mods() | get_oneshot_mods()) & MOD_MASK_CTRL ? PSTR("CTRL ") : PSTR("     "), false); */

    if ((get_mods() | get_oneshot_mods()) & MOD_MASK_CTRL) {
        oled_write_raw(ctrl_logo, sizeof(ctrl_logo));
    } 
    else { oled_write(PSTR("     "), false); }

    // TODO logo
    oled_set_cursor(5, 6);
    oled_write((get_mods() | get_oneshot_mods()) & MOD_MASK_GUI ? PSTR("  GUI") : PSTR("     "), false);

    // keylogger
    oled_render_keylog(11);
}


// render info for current layer
// TODO used oled_write_raw instead of oled_write_raw_P
void oled_render_right(void) {
    /* oled_write(PSTR("  Layer:  "), false); */

    // 64x128 oled
    oled_write_raw_P(layer_logo, sizeof(layer_logo));
    oled_set_cursor(0, 2);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            /* oled_write(PSTR("  Base    "), false); */
            oled_write_raw_P(layer_base_logo, sizeof(layer_base_logo));

            // TODO check if this is what causes oled to not timeout
            if (timer_elapsed(oled_help_timer) < OLED_HELP_TIME) {
                oled_render_base_help(5);
            } else {
                oled_render_no_help(5);
            }
            break;
        case _LOWER:
            /* oled_write(PSTR("  Lower   "), false); */
            oled_write_raw_P(layer_lower_logo, sizeof(layer_lower_logo));
            oled_render_lower_help(5);
            break;
        case _RAISE:
            /* oled_write(PSTR("  Raise   "), false); */
            oled_write_raw_P(layer_raise_logo, sizeof(layer_raise_logo));
            oled_render_raise_help(5);
            break;
        case _NUMPAD:
            /* oled_write(PSTR("  NumPad  "), false); */
            oled_write_raw_P(layer_numpad_logo, sizeof(layer_numpad_logo));
            oled_render_numpad_help(5);
            break;
        case _MOUSE:
            /* oled_write(PSTR("  Mouse   "), false); */
            oled_write_raw_P(layer_mouse_logo, sizeof(layer_mouse_logo));
            oled_render_mouse_help(5);
            break;
        case _ADJUST:
            /* oled_write(PSTR("  Adjust  "), false); */
            oled_write_raw_P(layer_adjust_logo, sizeof(layer_adjust_logo));
            oled_render_setup_help(5);
            break;
        default:
            /* oled_write(PSTR(" Undefined"), false); */
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


// TODO add key process for oled brightness, see drashna
bool process_record_user_oled(uint16_t keycode, keyrecord_t *record) {
    // toggle keylogger
    if (keycode == KC_KEYLOG) {
        if (record->event.pressed) {
            // TODO uncomment when I have audio.h
            /* PLAY_SONG(click_sound); */
            haptic_set_mode(1);
            haptic_play();
            oled_keylogger_enabled = !oled_keylogger_enabled;
        }
        return false;
    }
    
    // render keylog on oled
    if (oled_keylogger_enabled) {
        if (record->event.pressed) {
            add_keylog(keycode, record);
        }
        return true;
    }

    // TODO
    return true;

}

