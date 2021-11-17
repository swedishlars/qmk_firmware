/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

// LIB USED FOR  LED INDICATOR BREATHING EFFECT
#include "lib/lib8tion/lib8tion.h"

// TAPDANCE - definitions
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_TRIPLE_TAP
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// TAPDANCE KEYCODES
// LR enables layers
// TF1-12 will send Alt+FX on hold
enum {
    LR1,
    LR1S,
    LR1C,
    LR2,
    LR3,
    AF1, AF2, AF3, AF4, AF5, AF6, AF7, AF8, AF9, AF10, AF11, AF12
};

//  TAPDANCE - Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

//  TAPDANCE - activate layer 1. Tap to toggle, hold to activate momentarily.
void td_lr1_finished(qk_tap_dance_state_t *state, void *user_data);
void td_lr1_reset(qk_tap_dance_state_t *state, void *user_data);

// TAPDANCE - Tap to send normal KC_X, hold to momentarily enable layer
void td_lr_holdmo_finished(qk_tap_dance_state_t *state, void *user_data);
void td_lr_holdmo_reset(qk_tap_dance_state_t *state, void *user_data);

// TAPDANCE - Tap sends kc. Hold to activate layer.
void td_lr_holdon_finished(qk_tap_dance_state_t *state, void *user_data);
void td_lr_holdon_reset(qk_tap_dance_state_t *state, void *user_data);

// TAPDANCE - Alt+KC_X on hold functions
void td_alt_finished(qk_tap_dance_state_t *state, void *user_data);
void td_alt_reset(qk_tap_dance_state_t *state, void *user_data);

// LED colors 
// First 3 values are Hue, Saturation, Value (value=brightness).
// Last value sets breathing effect. 
// 0 = no breathing. 
// > 0 sets cycle time
#define L_DRED { 0, 255, 255, 0 }
// TODO rm: not enough difference:
#define L_LRED { 5, 250, 255, 0 }
#define L_BRED { 0, 255, 255, 30 }

#define L_DORA { 7, 255, 255, 0 }

#define L_DYEL { 25, 255, 255, 0 }
#define L_LYEL { 25, 240, 255, 0 }
#define L_BYEL { 25, 255, 255, 36 }

#define L_LGRE { 60, 255, 255, 0 }
#define L_DGRE { 85, 255, 255, 0 }
#define L_BGRE { 85, 255, 255, 37 }

#define L_DCYA { 127, 255, 255, 0 }
#define L_BCYA { 127, 255, 255, 38 }

#define L_DAZU { 150, 255, 255, 0 }
#define L_BAZU { 150, 255, 255, 39 }

#define L_DBLU { 169, 255, 255, 0 }
#define L_BBLU { 169, 255, 255, 41 }

#define L_DVIO { 180, 255, 255, 0 }
#define L_BVIO { 180, 255, 255, 42 }

#define L_DMAG { 201, 255, 255, 0 }
#define L_BMAG { 201, 255, 255, 46 }

#define L_DROS { 253, 255, 255, 0 }
#define L_BROS { 222, 255, 255, 40 }
#define L__OFF { 0, 0, 0, 0 }

// clang-format off

// The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
// this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
// cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
// if that's your preference.
//
// To put the keyboard in bootloader mode, use FN+backspace. If you accidentally put it into bootloader, you can just unplug the USB cable and
// it'll be back to normal when you plug it back in.
//
// This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
// Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
// Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.
//
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//      ESC       F1        F2        F3        F4        F5        F6        F7        F8        F9        F10       F11       F12	      Print               Rotary(Mute)
//      ~         1         2         3         4         5         6         7         8         9         0          -        (=)	      BackSpc             Del
//      Tab       Q         W         E         R         T         Y         U         I         O         P         [         ]                             PgUp
//      Caps      A         S         D         F         G         H         J         K         L         ;         "         #         Enter               PgDn
//      Sh_L      /         Z         X         C         V         B         N         M         ,         .         ?                   Sh_R      Up        End
//      Ct_L      Win_L     Alt_L                                   SPACE                                   Alt_R     FN        Ct_R      Left      Down      Right

    [0] = LAYOUT(
        KC_ESC,   TD(AF1),  TD(AF2),  TD(AF3),  TD(AF4),  TD(AF5),  TD(AF6),  TD(AF7),  TD(AF8),  TD(AF9),  TD(AF10), TD(AF11), TD(AF12), KC_PSCR,            KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_DEL,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,                      KC_PGUP,
        TD(LR1C), KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,  KC_ENT,             KC_PGDN,
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,    KC_END,
        KC_LCTL,  TD(LR1),  KC_LALT,                                KC_SPC,                                 KC_RALT,  TD(LR1S), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT
    ),

    // FN LAYER TODO rm reset
    [1] = LAYOUT(
        TO(0),    KC_MYCM,  KC_WHOM,  KC_CALC,  KC_MSEL,  KC_MPRV,  KC_MNXT,  KC_MPLY,  KC_MSTP,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RESET,              _______,
        _______,  _______,  _______,  _______,  _______,  LCA(KC_T),_______,  KC_WH_U,  _______,  _______,  _______,  _______,  _______,                      KC_HOME,
        _______,  _______,  _______,  _______,  _______,  _______,  KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  KC_BTN2,  KC_WH_D,  _______,  _______,  _______,  _______,            _______,  _______,  KC_INS,
        _______,  _______,  TD(LR2),                                KC_BTN1,                                TD(LR3),  _______,  _______,  _______,  _______, _______
    ),

    // RGB LAYER
    [2] = LAYOUT(
        TO(0),    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  RGB_M_P,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_VAD,  RGB_VAI,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  RGB_TOG,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,
        _______,  _______,  RGB_SAI,  _______,  _______,  _______,  RGB_HUI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  RGB_SAD,  _______,  _______,  _______,  RGB_HUD,  RGB_MOD,  _______,  _______,  _______,            _______,  RGB_SPI,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  RGB_RMOD, RGB_SPD,  RGB_MOD
    ),

    // ADVANCED LAYER
    [3] = LAYOUT(
        TO(0),    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  RESET,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,            _______,  _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,  _______
    ),
};

// CUSTOM RGB COLORS PER LAYER
// Leds are numbered column wise, not by row
const uint8_t PROGMEM ledcolors[][DRIVER_LED_TOTAL][4] = {
    // DEFAULT LAYER
    [0] = {
    //  ESC       `         Tab       Caps      L_SHIFT   L_CTL     F1        1         Q         A         Z         L_WIN     
        L_DORA,   L_DRED,   L_DORA,   L_DORA,   L_DORA,   L_LGRE,   L_DORA,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_LGRE,   
    //  F2        2         W         S         X         L_ALT     F3        3         E         D         C         F4        4         R         F         V
        L_DORA,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_LGRE,   L_DORA,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DORA,   L_DRED,   L_DRED,   L_DRED,   L_DRED,
    //  F5        5         T         G         B         SPACE     F6        6         Y         H         N         F7        7         U         J         M
        L_DORA,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DORA,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DORA,   L_DRED,   L_DRED,   L_DRED,   L_DRED,  
    //  F8        8         I         K         ,         R_ALT     F9        9         O         L         .         FN
        L_DORA,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_LGRE,   L_DORA,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DRED,  
    //  F10       0         P         ;         /         F11       -         [         "         Ct_R      F12       \         L_LED1    R_LED1
        L_DORA,   L_DRED,   L_DRED,   L_DRED,   L_DRED,   L_DORA,   L_DRED,   L_DRED,   L_DRED,   L_LGRE,   L_DORA,   L_DRED,   L_DRED,   L_DRED,   
    //  Print     L_LED2    R_LED2    Del       L_LED3    R_LED3    PgUp      L_LED4    R_LED4    =         Right     L_LED5    R_LED5    End       L_LED6    R_LED6
        L_LGRE,   L_DRED,   L_DRED,   L_LGRE,   L_DRED,   L_DRED,   L_LGRE,   L_DRED,   L_DRED,   L_DORA,   L_LYEL,   L_DRED,   L_DRED,   L_LGRE,   L_DRED,   L_DRED,  
    //  BSpc      PgDn      L_LED7    R_RED7    ]         R_SHIFT   L_LED8    R_LED8    Up        #         Left      Enter     Down
        L_DORA,   L_LGRE,   L_DRED,   L_DRED,   L_DRED,   L_DORA,   L_DRED,   L_DRED,   L_LYEL,   L_DRED,   L_LYEL,   L_DORA,   L_LYEL  
    },

    // FN LAYER
    [1] = {
    //  ESC       `         Tab       Caps      L_SHIFT   L_CTL     F1        1         Q         A         Z         L_WIN     
        L_BRED,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_DORA,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_BRED,   
    //  F2        2         W         S         X         L_ALT     F3        3         E         D         C         F4        4         R         F         V
        L_DORA,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_DGRE,   L_DORA,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_DORA,   L__OFF,   L__OFF,   L__OFF,   L__OFF,
    //  F5        5         T         G         B         SPACE     F6        6         Y         H         N         F7        7         U         J         M
        L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_DRED,   L_DRED,   L_DORA,   L__OFF,   L__OFF,   L_DROS,   L_DMAG,   L_DORA,   L__OFF,   L_DMAG,   L_DROS,   L__OFF,  
    //  F8        8         I         K         ,         R_ALT     F9        9         O         L         .         FN
        L_DORA,   L__OFF,   L__OFF,   L_DROS,   L__OFF,   L__OFF,   L_DORA,   L__OFF,   L__OFF,   L_DROS,   L__OFF,   L__OFF,  
    //  F10       0         P         ;         /         F11       -         [         "         Ct_R      F12       \         L_LED1    R_LED1
        L_DORA,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_DORA,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_BRED,   L_BRED,   
    //  Print     L_LED2    R_LED2    Del       L_LED3    R_LED3    PgUp      L_LED4    R_LED4    =         Right     L_LED5    R_LED5    End       L_LED6    R_LED6
        L__OFF,   L_BRED,   L_BRED,   L__OFF,   L_BRED,   L_BRED,   L__OFF,   L_BRED,   L_BRED,   L__OFF,   L__OFF,   L_BRED,   L_BRED,   L__OFF,   L_BRED,   L_BRED,  
    //  BSpc      PgDn      L_LED7    L_LED7    ]         R_SHIFT   L_LED8    R_LED8    Up        #         Left      Enter     Down
        L_BBLU,   L__OFF,   L_BRED,   L_BRED,   L__OFF,   L__OFF,   L_BRED,   L_BRED,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF  
    },

    // RGB LAYER TODO match leds
    [2] = {
    //  ESC       `         Tab       Caps      L_SHIFT   L_CTL     F1        1         Q         A         Z         L_WIN     
        L_BGRE,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_BBLU,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   
    //  F2        2         W         S         X         L_ALT     F3        3         E         D         C         F4        4         R         F         V
        L__OFF,   L__OFF,   L__OFF,   L_BVIO,   L_BVIO,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,
    //  F5        5         T         G         B         SPACE     F6        6         Y         H         N         F7        7         U         J         M
        L__OFF,   L__OFF,   L_BBLU,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_BMAG,   L_BMAG,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_BBLU,  
    //  F8        8         I         K         ,         R_ALT     F9        9         O         L         .         FN
        L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,  
    //  F10       0         P         ;         /         F11       -         [         "         Ct_R      F12       \         L_LED1    R_LED1
        L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_BCYA,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_BGRE,   L_BGRE,   
    //  Print     L_LED2    R_LED2    Del       L_LED3    R_LED3    PgUp      L_LED4    R_LED4    =         Right     L_LED5    R_LED5    End       L_LED6    R_LED6
        L__OFF,   L_BGRE,   L_BGRE,   L__OFF,   L_BGRE,   L_BGRE,   L__OFF,   L_BGRE,   L_BGRE,   L_BCYA,   L_BBLU,   L_BGRE,   L_BGRE,   L__OFF,   L_BGRE,   L_BGRE,  
    //  BSpc      PgDn      L_LED7    L_LED7    ]         R_SHIFT   L_LED8    R_LED8    Up        #         Left      Enter     Down
        L__OFF,   L__OFF,   L_BGRE,   L_BGRE,   L__OFF,   L__OFF,   L_BGRE,   L_BGRE,   L_BAZU,   L__OFF,   L_BBLU,   L__OFF,   L_BAZU  
    },

    // ADVANCED LAYER
    [3] = {
    //  ESC       `         Tab       Caps      L_SHIFT   L_CTL     F1        1         Q         A         Z         L_WIN     
        L_BBLU,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   
    //  F2        2         W         S         X         L_ALT     F3        3         E         D         C         F4        4         R         F         V
        L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_BBLU,   L__OFF,   L__OFF,
    //  F5        5         T         G         B         SPACE     F6        6         Y         H         N         F7        7         U         J         M
        L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_DMAG,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,  
    //  F8        8         I         K         ,         R_ALT     F9        9         O         L         .         FN
        L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,  
    //  F10       0         P         ;         /         F11       -         [         "         Ct_R      F12       \         L_LED1    R_LED1
        L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L_BBLU,   L_BBLU,   
    //  Print     L_LED2    R_LED2    Del       L_LED3    R_LED3    PgUp      L_LED4    R_LED4    =         Right     L_LED5    R_LED5    End       L_LED6    R_LED6
        L__OFF,   L_BBLU,   L_BBLU,   L__OFF,   L_BBLU,   L_BBLU,   L__OFF,   L_BBLU,   L_BBLU,   L__OFF,   L__OFF,   L_BBLU,   L_BBLU,   L__OFF,   L_BBLU,   L_BBLU,  
    //  BSpc      PgDn      L_LED7    L_LED7    ]         R_SHIFT   L_LED8    R_LED8    Up        #         Left      Enter     Down
        L__OFF,   L__OFF,   L_BBLU,   L_BBLU,   L__OFF,   L__OFF,   L_BBLU,   L_BBLU,   L__OFF,   L__OFF,   L__OFF,   L__OFF,   L__OFF  
    },
};

// clang-format on

// TODO make encoder map per layer
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
    return true;
}
#endif

HSV get_hsv_color(uint8_t colorcode[]) {
    // TODO this fail compile, rm:
    /* HSV hsv = {.h=pgm_read_byte(colorcode[0]), .s=pgm_read_byte(colorcode[1]), .v=pgm_read_byte(colorcode[2])}; */
    // Adding & fixes it and seem to work.
    HSV hsv = {.h=pgm_read_byte(&colorcode[0]), .s=pgm_read_byte(&colorcode[1]), .v=pgm_read_byte(&colorcode[2])};
    return hsv;
}

void set_layer_color( uint8_t layer) {
    // effect cycle timer example using user config:
    // uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);

    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        uint8_t val = pgm_read_byte(&ledcolors[layer][i][2]);
        uint8_t breathe = pgm_read_byte(&ledcolors[layer][i][3]);

        // If RGB layer is enabled, skip all leds with brightness set to 0.
        // This is so that the rgb effect mode can be previewed in layer.
        if (layer == 2 && val == 0) continue;

        // For key leds (index 0-63), allow brightness to be set by user.
        // But for underglow, always use bragthness vaule set in map above.
        if (i < 64) {
            // if the brightness of the led is set to 0 in the map, the value is not overriden by matrix effect, 
            // allowing the led to appear turned off. Else, set brightness to current rgb matrix value.
            if (val != 0) {
                val = rgb_matrix_get_val();
            }
        } 

        // If breathe, set val based on time cycle
        // This is done by creating a per led breathing effect cycle timer.
        if (breathe > 0) {
            uint16_t time = scale16by8(g_rgb_timer, breathe);
            uint8_t hsv_breathe_val = abs8(sin8(time) - 128) * 2;
            val = scale8(hsv_breathe_val, val);
        }

        HSV hsv = { .h = pgm_read_byte(&ledcolors[layer][i][0]), .s = pgm_read_byte(&ledcolors[layer][i][1]), .v = val};
        RGB rgb = hsv_to_rgb( hsv );
        rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
    }
}

// LED INDICATORS
void rgb_matrix_indicators_user(void) {
    uint32_t mode = rgb_matrix_get_mode();

    // Assign custom layer colors if the rgb matrix is on.
    // For default layer only assign colors if mode is SOLID COLORS => No animations running.
    // For all other layers, always set custom colors.
    // For some layers, set an underglow breathing effect.
    if(rgb_matrix_is_enabled() == 1) {
        uint8_t layer = biton32(layer_state);
        switch (layer) {
            case 0:
                if (mode == 1) set_layer_color(0);
                break;
            case 1:
                set_layer_color(1);
                break;
            case 2:
                set_layer_color(2);
                break;
            case 3:
                set_layer_color(3);
                break;
        }
    }

    // Set led for Caps Lock
    if (host_keyboard_led_state().caps_lock) {
        uint8_t hsv_col[4] = L_DBLU;
        // TODO add get_rgb_color()!
        HSV hsv = get_hsv_color(hsv_col);
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(28, rgb.r, rgb.g, rgb.b);
    }
}


// TAPDANCE - Common. Determine the current tap dance state
// Double and triple tap is handled to make tapping more stable
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held.
        // Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } 
    else if (state->count == 2) return TD_DOUBLE_TAP;
    else if (state->count == 3) return TD_TRIPLE_TAP;
    else return TD_UNKNOWN;
}


// TAPDANCE - Tap to toggle layer 1. Hold to momentarily activate layer 1.
static td_tap_t td_lr1_tapstate = {.is_press_action = true, .state = TD_NONE};

// TODO use generic func that passes layer in user_data?
void td_lr1_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_lr1_tapstate.state = cur_dance(state);

    switch (td_lr1_tapstate.state) {
        // Toggle layer 1
        case TD_SINGLE_TAP:
            if (layer_state_is(1)) layer_off(1);
            else layer_on(1);
            break;
        // Momentarily turn on layer 1
        case TD_SINGLE_HOLD: layer_on(1); break;
        case TD_DOUBLE_TAP: break;
        case TD_TRIPLE_TAP: break;
        case TD_NONE: break;
        case TD_UNKNOWN: break;
    }
}

void td_lr1_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (td_lr1_tapstate.state == TD_SINGLE_HOLD) {
        layer_off(1);
    }
    td_lr1_tapstate.state = TD_NONE;
}


// TAPDANCE - Tap to send normal KC_X, hold to momentarily enable layer
// Func retreives current keycode and desired layer from user_data in custom tapdance action.
// See: https://github.com/qmk/qmk_firmware/blob/master/quantum/process_keycode/process_tap_dance.c
static td_tap_t td_lr_holdmo_tapstate = {.is_press_action = true, .state = TD_NONE};

void td_lr_holdmo_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_lr_holdmo_tapstate.state = cur_dance(state);
    qk_tap_dance_dual_role_t *pair = (qk_tap_dance_dual_role_t *)user_data;

    switch (td_lr_holdmo_tapstate.state) {
        case TD_SINGLE_TAP: register_code(pair->kc); break;
        case TD_SINGLE_HOLD: layer_on(pair->layer); break;
        case TD_DOUBLE_TAP: register_code(pair->kc); break;
        case TD_TRIPLE_TAP: register_code(pair->kc); break;
        case TD_NONE: break;
        case TD_UNKNOWN: break;
    }
}

void td_lr_holdmo_reset(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_dual_role_t *pair = (qk_tap_dance_dual_role_t *)user_data;

    switch (td_lr_holdmo_tapstate.state) {
        case TD_SINGLE_TAP: unregister_code(pair->kc); break;
        case TD_SINGLE_HOLD: layer_off(pair->layer); break;
        case TD_DOUBLE_TAP: unregister_code(pair->kc); break;
        case TD_TRIPLE_TAP: unregister_code(pair->kc); break;
        case TD_UNKNOWN: break;
        case TD_NONE: break; 
    }
    td_lr_holdmo_tapstate.state = TD_NONE;
}


// TAPDANCE - Tap sends kc. Hold to activate layer.
static td_tap_t td_lr_holdon_tapstate = {.is_press_action = true, .state = TD_NONE};

void td_lr_holdon_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_lr_holdon_tapstate.state = cur_dance(state);
    qk_tap_dance_dual_role_t *pair = (qk_tap_dance_dual_role_t *)user_data;

    switch (td_lr_holdon_tapstate.state) {
        case TD_SINGLE_TAP: register_code(pair->kc); break;
        case TD_SINGLE_HOLD: layer_on(pair->layer); break;
        /* case TD_SINGLE_HOLD: layer_move(pair->layer); break; */
        case TD_DOUBLE_TAP: register_code(pair->kc); break;
        case TD_TRIPLE_TAP: register_code(pair->kc); break;
        case TD_NONE: break;
        case TD_UNKNOWN: break;
    }
}

void td_lr_holdon_reset(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_dual_role_t *pair = (qk_tap_dance_dual_role_t *)user_data;

    switch (td_lr_holdmo_tapstate.state) {
        case TD_SINGLE_TAP: unregister_code(pair->kc); break;
        case TD_SINGLE_HOLD: break;
        case TD_DOUBLE_TAP: unregister_code(pair->kc); break;
        case TD_TRIPLE_TAP: unregister_code(pair->kc); break;
        case TD_UNKNOWN: break;
        case TD_NONE: break; 
    }
    td_lr_holdon_tapstate.state = TD_NONE;
}


// TAPDANCE - Tap for normal KC_X. Hold to send Alt+KC_X
// Func retreives current keycode from user_data in custom tapdance action.
// This means I can use this func for any keycodes.
// see: https://github.com/qmk/qmk_firmware/commit/ad7a5bdc4f2527f47ca22885e5d0b689fb8d4518
// and this one: https://www.reddit.com/r/olkb/comments/kcfs52/qmk_generic_handler_for_tap_dance/
static td_tap_t td_alt_tap_state = {.is_press_action = true, .state = TD_NONE};

void td_alt_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_alt_tap_state.state = cur_dance(state);
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;
    uint16_t keycode = pair->kc1;

    switch (td_alt_tap_state.state) {
        case TD_SINGLE_TAP: register_code(keycode); break;
        case TD_SINGLE_HOLD: register_code16(LALT(keycode)); break;
        case TD_DOUBLE_TAP: register_code(keycode); break;
        case TD_TRIPLE_TAP: register_code(keycode); break;
        case TD_UNKNOWN: break;
        case TD_NONE: break;
    }
}

void td_alt_reset(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;
    uint16_t keycode = pair->kc1;

    switch (td_alt_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(keycode); break;
        case TD_SINGLE_HOLD: unregister_code16(LALT(keycode)); break;
        case TD_DOUBLE_TAP: unregister_code(keycode); break;
        case TD_TRIPLE_TAP: unregister_code(keycode); break;
        case TD_UNKNOWN: break;
        case TD_NONE: break; 
    }
    td_alt_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    // Layer 1 activation for right FN
    [LR1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_lr1_finished, td_lr1_reset),
    // Layer 1 activation on left Super hold
    [LR1S] = ACTION_TAP_DANCE_FN_KEY_LAYER(NULL, td_lr_holdmo_finished, td_lr_holdmo_reset, KC_LGUI, 1),
    // Layer 1 activation on Caps hold
    [LR1C] = ACTION_TAP_DANCE_FN_KEY_LAYER(NULL, td_lr_holdmo_finished, td_lr_holdmo_reset, KC_CAPS, 1),
    // Layer 2 activation on left Alt hold
    [LR2] = ACTION_TAP_DANCE_FN_KEY_LAYER(NULL, td_lr_holdon_finished, td_lr_holdon_reset, KC_LALT, 2),
    // Layer 3 activation on right Alt hold
    [LR3] = ACTION_TAP_DANCE_FN_KEY_LAYER(NULL, td_lr_holdon_finished, td_lr_holdon_reset, KC_RALT, 3),
    // Hold to send ALT+KC_F1-12
    [AF1] = ACTION_TAP_DANCE_FN_KEY(NULL, td_alt_finished, td_alt_reset, KC_F1),
    [AF2] = ACTION_TAP_DANCE_FN_KEY(NULL, td_alt_finished, td_alt_reset, KC_F2),
    [AF3] = ACTION_TAP_DANCE_FN_KEY(NULL, td_alt_finished, td_alt_reset, KC_F3),
    [AF4] = ACTION_TAP_DANCE_FN_KEY(NULL, td_alt_finished, td_alt_reset, KC_F4),
    [AF5] = ACTION_TAP_DANCE_FN_KEY(NULL, td_alt_finished, td_alt_reset, KC_F5),
    [AF6] = ACTION_TAP_DANCE_FN_KEY(NULL, td_alt_finished, td_alt_reset, KC_F6),
    [AF7] = ACTION_TAP_DANCE_FN_KEY(NULL, td_alt_finished, td_alt_reset, KC_F7),
    [AF8] = ACTION_TAP_DANCE_FN_KEY(NULL, td_alt_finished, td_alt_reset, KC_F8),
    [AF9] = ACTION_TAP_DANCE_FN_KEY(NULL, td_alt_finished, td_alt_reset, KC_F9),
    [AF10] = ACTION_TAP_DANCE_FN_KEY(NULL, td_alt_finished, td_alt_reset, KC_F10),
    [AF11] = ACTION_TAP_DANCE_FN_KEY(NULL, td_alt_finished, td_alt_reset, KC_F11),
    [AF12] = ACTION_TAP_DANCE_FN_KEY(NULL, td_alt_finished, td_alt_reset, KC_F12)
};
