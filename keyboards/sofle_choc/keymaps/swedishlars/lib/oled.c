#include "oled.h"
/* #include "audio.h" */
#include "swedishlars.h"

// TODO implement drashna oled brightness adjust

bool oled_startup_done = false;
bool oled_sleep_enabled = true;
bool oled_keylogger_enabled = false;

// custom audio
float keylog_sound[][2] = SONG(CHROMATIC_SOUND);


// Deferred execution callback to clear and rotate display.
// Returns 0 to indicate it should not be repeated.
uint32_t oled_startup(uint32_t trigger_time, void *cb_arg) {
    oled_clear();

    // NOTE: rotation for orig screen:
    /* oled_init(OLED_ROTATION_270); */

    oled_startup_done = true;
    return 0;
}

// KEY LOGGER
// --------------------------------------------------------------------------
// Get a description of keycode that can be rendered on oled.
// First check if there is a layer enabled which has a description override.
// Then check if shift is held and there is a shifted keycode description.
// If none of the above is true, return a default keycode description.

// TODO orig:
/* const char* get_keycode_desc(uint16_t keycode) { */
const char* get_keycode_desc(uint16_t keycode, uint8_t keycode_mod) {
    /* // Lower layer */
    /* if (layer_state_is(_LOWER)) { */
    /*     if ( (keycode < ARRAY_SIZE(keycode_to_desc_lower)) && */
    /*         (strlen(keycode_to_desc_lower[keycode]) > 0) */
    /*     ) { */
    /*         return keycode_to_desc_lower[keycode]; */
    /*     } */
    /* } */

    /* // Raise layer */
    /* if (layer_state_is(_RAISE)) { */
    /*     if ( (keycode < ARRAY_SIZE(keycode_to_desc_raise)) && */
    /*         (strlen(keycode_to_desc_raise[keycode]) > 0) */
    /*     ) { */
    /*         return keycode_to_desc_raise[keycode]; */
    /*     } */
    /* } */

    /* // shifted keycode description */
    /* if ( (get_mods() & MOD_MASK_SHIFT) && */
    /*      (keycode < ARRAY_SIZE(keycode_to_desc_shift)) */
    /* ) { */
    /*     return keycode_to_desc_shift[keycode]; */
    /* } */

    /* // Default keycode description */
    /* if (keycode < ARRAY_SIZE(keycode_to_desc)) { */
    /*     return keycode_to_desc[keycode]; */
    /* } */

    // TODO this works now!
    uint8_t keycode_layer = KEYCODE_DEFAULT;

    switch (get_highest_layer(layer_state)) {
        case _LOWER:
            keycode_layer = KEYCODE_LOWER;
            break;
        case _RAISE:
            keycode_layer = KEYCODE_RAISE;
            break;
    }

    if (keycode < ARRAY_SIZE(keycode_to_desc[KEYCODE_DEFAULT])) {
        if (keycode_layer > KEYCODE_DEFAULT) {
            if (strlen(keycode_to_desc[keycode_layer][keycode]) > 0) {
                return keycode_to_desc[keycode_layer][keycode];
            } 
        }

        if (strlen(keycode_to_desc[keycode_mod][keycode]) > 0) {
            return keycode_to_desc[keycode_mod][keycode];
        } 

        return keycode_to_desc[KEYCODE_DEFAULT][keycode];
    }

    return "          ";
} 

// Store current key code
// TODO set LENGTH to 10 and char array to +1?
char oled_keylog_code[OLED_KEYLOG_LENGTH] = {0};

// Store current active modifiers
// Use 20 char array (double line on oled)
char oled_keylog_mod[OLED_KEYLOG_LENGTH + 10] = {0};

// Store current key description
char oled_keylog_desc[OLED_KEYLOG_LENGTH] = {0};

void add_keylog(uint16_t keycode, keyrecord_t *record) {
    // TODO works!
    uint8_t keycode_mod = KEYCODE_DEFAULT;

    // temp store any active modifiers
    char active_mods[21] = {0};

    // Get active real modifiers (actual mod keys pressed)
    const uint8_t mods = get_mods() | get_oneshot_mods() | get_weak_mods();

    // Get active weak mods, mods that are part of macros & modifier keycodes like LALT(kc) 
    // NOTE: get_weak_mods() above does not seem to cover all of it.
    const uint8_t weak_mods = QK_MODS_GET_MODS(keycode);


    // Temp store description for all active modifiers
    // Concatenate 5 char strings so oled renders max 2 mods per line
    if ((mods & MOD_MASK_SHIFT) || (weak_mods & MOD_MASK_SHIFT)) {
        strcat(active_mods, "SHFT+");
        // TODO works!
        keycode_mod = KEYCODE_SHIFT;
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
        snprintf(oled_keylog_mod, OLED_KEYLOG_LENGTH + 10,"%20s", active_mods);
    } 
    // Store empty 20 char string if there are not modifiers
    else {
        snprintf(oled_keylog_mod, OLED_KEYLOG_LENGTH, "                    ");
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

    // TODO testing user. It works but code is a very high index
    /* if (IS_USER_KEYCODE(keycode)) { */
    /*     snprintf(oled_keylog_code, OLED_KEYLOG_LENGTH, "uk %3d", keycode); */
    /* } */

    // store keycode
    // TODO If I get rid of if statement then I can render full range codes,
    // but I need to cater for character space on oled.
    /* if (keycode < ARRAY_SIZE(keycode_to_desc)) { */
    if (keycode < ARRAY_SIZE(keycode_to_desc[KEYCODE_DEFAULT])) {
        // 128x32 oled
        /* snprintf(oled_keylog_code, OLED_KEYLOG_LENGTH, "k:%3d", keycode); */

        // New 64x128 oled:
        snprintf(oled_keylog_code, OLED_KEYLOG_LENGTH, "kcode: %3d", keycode);
    } 

    // store key description
    /* snprintf(oled_keylog_desc, OLED_KEYLOG_LENGTH, get_keycode_desc(keycode)); */
    snprintf(oled_keylog_desc, OLED_KEYLOG_LENGTH, get_keycode_desc(keycode, keycode_mod));
}


// Renders keylog to oled
// NOTE only works on master side
void oled_render_keylog(uint8_t line) {
    oled_set_cursor(0, line);
    if (oled_keylogger_enabled) {
        oled_write_raw(keylogger_logo, sizeof(keylogger_logo));
        oled_set_cursor(0, line + 1);
        oled_write(oled_keylog_code, false);
        // TODO orig:
        /* oled_write(PSTR("          "), false); */

        // TODO test double line mod
        // _ln writes new line it seems?
        oled_write(oled_keylog_mod, false);

        /* oled_set_cursor(0, line + 4); */

        oled_write(oled_keylog_desc, false);
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
}

// TODO add insert if possible
void oled_render_left(void) {
    // Led status
    led_t led_state = host_keyboard_led_state();
    /* oled_set_cursor(0, 1); */
    oled_write_raw(leds_logo, sizeof(leds_logo));
    oled_set_cursor(7, 0);
    oled_write_raw(rgb_matrix_is_enabled() ? on_btn_logo : off_btn_logo, sizeof(on_btn_logo));

    // Oled sleep status
    oled_set_cursor(0, 1);
    oled_write_raw(oled_sleep_logo, sizeof(oled_sleep_logo));
    oled_set_cursor(7, 1);
    oled_write_raw(oled_sleep_enabled ? on_btn_logo : off_btn_logo, sizeof(on_btn_logo));

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
                oled_render_no_help(5);
            }
            break;
        case _LOWER:
            oled_write_raw(layer_lower_logo, sizeof(layer_lower_logo));
            oled_render_lower_help(5);
            break;
        case _RAISE:
            oled_write_raw(layer_raise_logo, sizeof(layer_raise_logo));
            oled_render_raise_help(5);
            break;
        case _NUMPAD:
            oled_write_raw(layer_numpad_logo, sizeof(layer_numpad_logo));
            oled_render_numpad_help(5);
            break;
        case _MOUSE:
            oled_write_raw(layer_mouse_logo, sizeof(layer_mouse_logo));
            oled_render_mouse_help(5);
            break;
        case _ADJUST:
            oled_write_raw(layer_adjust_logo, sizeof(layer_adjust_logo));
            oled_render_setup_help(5);
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


// TODO add key process for oled brightness, see drashna
bool process_record_user_oled(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {

            // toggle oled sleep
            case KC_OSLEEP:
                oled_sleep_enabled = !oled_sleep_enabled;
                if (!oled_sleep_enabled) {
                    oled_on();
                }
                break;

            // toggle keylogger
            case KC_KEYLOG:
                // TODO change song, make a warning siren
                PLAY_SONG(keylog_sound);
                haptic_set_mode(1);
                haptic_play();
                oled_keylogger_enabled = !oled_keylogger_enabled;
                return false;
        }
    }
    
    // render keylog on oled
    // TODO test calling directly from keymap.c
    /* if (oled_keylogger_enabled) { */
    /*     add_keylog(keycode, record); */
    /* } */

    return true;

}

