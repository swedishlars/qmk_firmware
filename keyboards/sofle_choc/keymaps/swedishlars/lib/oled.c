// Copyright 2024 Lars Johansson (github.com/swedishlars)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "oled.h"
#include "swedishlars.h"
// TODO use swedishlars.h instead?
#include "keylogger.h"

bool oled_startup_done = false;

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


// audio
float keylog_sound[][2] = SONG(VIOLIN_SOUND);
float adjust_sound[][2] = SONG(AG_NORM_SOUND);


// Deferred execution callback to clear and rotate display.
// Returns 0 to indicate it should not be repeated.
uint32_t oled_startup(uint32_t trigger_time, void *cb_arg) {
    oled_clear();
    oled_startup_done = true;
    return 0;
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


// Renders keylog to oled
// NOTE only works on master side
bool play_forward = true;

void oled_render_keylog(void) {
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

    // TODO do I need _ln version?
    oled_write_ln(PSTR(keylogger_logo[frame]), false);
    oled_advance_page(false);

    // render keycode
    oled_write_ln(oled_key_code, false);
    oled_advance_page(false);

    // render key description
    oled_write_ln(PSTR("Key Desc:"), false);
    oled_advance_page(true);
    oled_write_ln(oled_key_mod, false);
    oled_write_ln(oled_key_desc, false);

    // clear remaining display
    oled_advance_page(false);
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


// Caps status
void oled_caps_status(void) {
    // TODO keep unless I ditch caps lock:
    /* led_t led_state = host_keyboard_led_state(); */
    /* if (!led_state.caps_lock) { */

    // render caps word status
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

        oled_write_raw(caps_logo[frame], sizeof(caps_logo[0]));
        oled_advance_page(false);
}


void oled_render_mods(void) {
    // Shift modifier status
    if ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT) {
        oled_write_raw(shift_logo, sizeof(shift_logo));
        oled_advance_chars(5, false);
    }
    else { oled_advance_chars(5, true); }

    // Alt modifier status
    if ((get_mods() | get_oneshot_mods()) & MOD_MASK_ALT) {
        oled_write_raw(alt_logo, sizeof(alt_logo));
        oled_advance_chars(5, false);
    }
    else { oled_advance_chars(5, true); }

    // Ctrl modifier status
    if ((get_mods() | get_oneshot_mods()) & MOD_MASK_CTRL) {
        oled_write_raw(ctrl_logo, sizeof(ctrl_logo));
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
    oled_advance_page(false);
}


void oled_render_settings(void) {
    // auto shift status
    oled_write(PSTR("A-SHIFT  "), false);
    oled_write(PSTR(get_autoshift_state() ? "Y" : "N"), false);
    oled_advance_page(false);

    // Oled sleep status
    oled_write(PSTR("OLED Zzz "), false);
    oled_write(PSTR(user_config.oled_sleep_enabled ? "Y" : "N"), false);
    oled_advance_page(false);

    // rgb status
    oled_write(PSTR("RGB      "), false);
    oled_write(PSTR(rgb_matrix_is_enabled() ? "Y" : "N"), false);
    oled_advance_page(false);

    // audio status
    oled_write(PSTR("AUDIO    "), false);
    oled_write(PSTR(audio_is_on() ? "Y" : "N"), false);
    oled_advance_page(false);

    // haptic status
    oled_write(PSTR("HAPTIC   "), false);
    oled_write(PSTR(haptic_get_enable() ? "Y" : "N"), false);
    oled_advance_page(false);
}

void oled_render_base(void) {
    oled_write(PSTR(" B A S E  "), false);
    oled_advance_page(true);
    // oled_write(PSTR("----------"), false);
    oled_write(PSTR("NumPad:   "), false);
    oled_write(PSTR("(Hold)    "), false);
    oled_write(PSTR("CapsLock  "), false);
    oled_advance_page(true);
    oled_write(PSTR("Adjust:   "), false);
    oled_write(PSTR("Lower +   "), false);
    oled_write(PSTR("Raise     "), false);
    oled_advance_page(true);
    oled_write(PSTR("Key help: "), false);
    oled_write(PSTR("Adjust + k"), false);
}

void oled_render_lower(void) {
    oled_write(PSTR("L O W E R "), false);
    oled_advance_page(true);
    // oled_write(PSTR("----------"), false);
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

void oled_render_raise(void) {
    oled_write(PSTR("R A I S E "), false);
    oled_advance_page(true);
    // oled_write(PSTR("__________"), false);
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

void oled_render_func(void) {
    oled_write(PSTR(" F U N C  "), false);
    oled_advance_page(true);
    // oled_write(PSTR("----------"), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("Orange:   "), false);
    oled_write(PSTR("Num keys  "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("Rose:     "), false);
    oled_write(PSTR("alt. keys "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
    oled_write(PSTR("          "), false);
    oled_advance_pages(3, true);
}

void oled_render_mouse(void) {
    oled_write(PSTR("M O U S E "), false);
    oled_advance_page(true);
    // oled_write(PSTR("----------"), false);
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

void oled_render_adjust(void) {
    oled_write(PSTR(" C O N F  "), false);
    oled_advance_page(true);
    // oled_write(PSTR("----------"), false);
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

void oled_render_undef(void) {
    oled_write(PSTR("UNDEFINED "), false);
    oled_advance_page(true);
    // oled_write(PSTR("----------"), false);
    oled_write(PSTR("something "), false);
    oled_write(PSTR("is wrong  "), false);
    oled_write(PSTR("...       "), false);
    oled_advance_pages(6, true);
}


void oled_render_left(void) {
    // keylogger
    if (oled_keylogger_enabled) {
        oled_render_keylog();
        oled_advance_pages(7, true);
    }
    else {
        // TODO rename
        oled_render_settings();

        // Caps status
        oled_caps_status();

        // render active modifiers
        oled_render_mods();

        // oled_advance_page(true);
        oled_advance_pages(2, true);
    }
}


void oled_render_right(void) {
    oled_write(PSTR("L A Y E R "), false);
    oled_advance_page(false);
    // oled_advance_pages(2, false);

    // render info for current layer
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_render_base();
            break;
        case _LOWER:
            oled_render_lower();
            break;
        case _RAISE:
            oled_render_raise();
            break;
        case _FUNC:
            oled_render_func();
            break;
        case _MOUSE:
            oled_render_mouse();
            break;
        case _CONF:
            oled_render_adjust();
            break;
        default:
            oled_render_undef();
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

