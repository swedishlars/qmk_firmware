#include "oled.h"
#include "swedishlars.h"

// TODO make oled timeout longer!
// TODO implement drashna oled brightness adjust

bool oled_startup_done = false;
bool oled_keylogger_enabled = false;

// Deferred execution callback to clear and rotate display.
// Returns 0 to indicate it should not be repeated.
// TODO rename func now that no rotation is needed
uint32_t oled_rotate(uint32_t trigger_time, void *cb_arg) {
    oled_clear();
    // TODO rotation for orig screen:
    /* oled_init(OLED_ROTATION_270); */

    oled_startup_done = true;
    return 0;
}


//Setup a mask which can be or'd with bytes to turn off pixels
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
    
    // TODO define logo time in .h
    if (timer < 2000) {
        /* oled_write_P(qmk_logo, false); */
        oled_write_raw(qmk_logo, sizeof(qmk_logo));
        return;
    }
    if (timer > 2000) {
        oled_render_fade();
    }
}


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

    /* return "     "; */
    return "          ";
} 

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

    // render keycode
    // TODO do I need if statement?
    if (keycode < ARRAY_SIZE(keycode_to_name)) {
        /* snprintf(oled_keylog_code, OLED_KEYLOG_LENGTH, "k:%3d", keycode); */

        // TODO new oled:
        snprintf(oled_keylog_code, OLED_KEYLOG_LENGTH, "kcode: %3d", keycode);
    }

    snprintf(oled_keylog_str, OLED_KEYLOG_LENGTH, get_keycode_desc(keycode));
}


// Renders keylog to oled
// NOTE only works on master side
void oled_render_keylog(uint8_t line) {
    oled_set_cursor(0, line);
    if (oled_keylogger_enabled) {
        // TODO make this blink using a timer:
        /* oled_write(PSTR(OLED_RENDER_KEYLOGGER), false); */
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
    
    if (oled_keylogger_enabled) {
        if (record->event.pressed) {
            add_keylog(keycode, record);
        }
        return true;
    }
    return true;
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
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
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
    oled_write(PSTR("          "), false);
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
    oled_write(PSTR("          "), false);
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
    oled_write(PSTR("          "), false);
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
    oled_write(PSTR("          "), false);
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
    oled_write(PSTR("          "), false);
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
    oled_write(PSTR("          "), false);
}

void oled_render_right(void) {
    // Keyboard LED Status
    led_t led_state = host_keyboard_led_state();

    // TODO test new oled, new width is 10 chars
    oled_write(led_state.caps_lock ? PSTR("Caps    ON") : PSTR("Caps   OFF"), false);

    // TODO add insert if possible

    // rgb status
    oled_write(rgb_matrix_is_enabled() ? PSTR("Leds    ON") : PSTR("Rgb    OFF"), false);

    // audio
    oled_write(audio_is_on() ? PSTR("Audio   ON") : PSTR("Audio  OFF"), false);

    // haptic
    uint8_t haptic_state = haptic_get_enable();
    oled_write(haptic_state ? PSTR("Haptic  ON") : PSTR("Haptic OFF"), false);

    // keylogger
    oled_render_keylog(11);
}


// render info for current layer
void oled_render_left(void) {
    oled_write(PSTR("  Layer:  "), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write(PSTR("  Base    "), false);
            // TODO define timeout in oled.h
            if (timer_elapsed(oled_help_timer) < 10000) {
                oled_render_base_help(3);
            } else {
                oled_render_no_help(3);
            }
            break;
        case _LOWER:
            oled_write(PSTR("  Lower   "), false);
            oled_render_lower_help(3);
            break;
        case _RAISE:
            oled_write(PSTR("  Raise   "), false);
            oled_render_raise_help(3);
            break;
        case _NUMPAD:
            oled_write(PSTR("  NumPad  "), false);
            oled_render_numpad_help(3);
            break;
        case _MOUSE:
            oled_write(PSTR("  Mouse   "), false);
            oled_render_mouse_help(3);
            break;
        case _SWITCH:
            oled_write(PSTR("  Switch  "), false);
            oled_render_setup_help(3);
            break;
        default:
            oled_write(PSTR(" Undefined"), false);
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

