#include "keylogger.h"
#include "swedishlars.h"


// Get a description of keycode that can be rendered on oled.
// First check if there is a layer enabled which has a description override.
// Then check if shift is held and there is a shifted keycode description.
// If none of the above is true, return a default keycode description.
const char* get_keycode_desc(uint16_t keycode, uint8_t key_desc_mod) {
    // Set keycode description override for layer
    uint8_t key_desc_layer = KEYCODE_DEFAULT;

    switch (get_highest_layer(layer_state)) {
        case _RAISE:
            key_desc_layer = KEYCODE_RAISE;
            break;
        case _FUNC:
            key_desc_layer = KEYCODE_FUNC;
            break;
        case _MACRO:
            key_desc_layer = KEYCODE_MACRO;
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
    return KEYLOG_EMPTY_LINE;
}


// Store current key code
char keylog_keycode[KEYLOG_LENGTH] = {0};
// TODO not long enough to store > 2 modifiers on one line!
// Store current active modifiers
char keylog_keymod[KEYLOG_LENGTH] = {0};
// Store current key description
char keylog_keydesc[KEYLOG_LENGTH] = {0};


void add_keylog(uint16_t keycode, keyrecord_t *record) {
    // Set keycode description array override for modifier
    uint8_t key_desc_mod = KEYCODE_DEFAULT;

    // temp store any active modifiers
    char active_mods[KEYLOG_LENGTH] = {0};

    // Get active real modifiers (actual mod keys pressed)
    const uint8_t mods = get_mods();

    // Get quantum mods that are part of macros & modifier keycodes
    // examples: LALT(kc), KC_PERC
    uint8_t qk_mods = 0;

    // Set keycode - if code is is in a higher 16 bit range,
    // convert it to basic 256 range by splitting into
    // lowest 8 bits or highest 8 bits.
    // See keycodes.h for IS KEYCODE macros
    // See quantum_keycodes.h for GET keycode macros
    if (IS_QK_MODS(keycode)) {
        qk_mods = QK_MODS_GET_MODS(keycode);
        keycode = QK_MODS_GET_BASIC_KEYCODE(keycode);
    }
    else if (IS_QK_MOD_TAP(keycode) && record->tap.count) {
        qk_mods = QK_MODS_GET_MODS(keycode);
        keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
    }
    else if (IS_QK_LAYER_TAP(keycode) && record->tap.count) {
        keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    }
    // activate layer (TO) - convert to highest 8 bits
    else if (IS_QK_TO(keycode)) {
        keycode = ((keycode) >> 8);
    }
    // layer toggle (TG) - convert to lowest 8 bits
    else if (IS_QK_TOGGLE_LAYER(keycode)) {
        keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    }
    // one shot layer (TD) - convert to lowest 8 bits
    else if (IS_QK_ONE_SHOT_LAYER(keycode)) {
        keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    }
    // quantum range - convert to lowest 8 bits
    // NOTE this results with reboot code index 0, so let's offset
    else if (IS_QK_QUANTUM(keycode)) {
        keycode = QK_MODS_GET_BASIC_KEYCODE(keycode) + 1;
    }
    // rgb matrix range
    else if (IS_QK_LIGHTING(keycode)) {
        keycode = QK_MODS_GET_BASIC_KEYCODE(keycode);
    }
    // user range keycode
    else if (IS_QK_USER(keycode)) {
        keycode = QK_MODS_GET_BASIC_KEYCODE(keycode);
    }
    // tapdance keycode - return tap dance index starting at 0 + offset so start is at 240.
    else if (IS_QK_TAP_DANCE(keycode)) {
        keycode = QK_TAP_DANCE_GET_INDEX(keycode) + 240;
    }

    // store description for shift mod
    if ((mods | qk_mods) & MOD_MASK_SHIFT) {
        strcat(active_mods, "Shift+");
        key_desc_mod = KEYCODE_SHIFT;
    }
    // store description for alt mod
    if ((mods | qk_mods) & MOD_MASK_ALT) {
        strcat(active_mods, "Alt+");
    }
    // store description for ctrl mod
    if ((mods | qk_mods) & MOD_MASK_CTRL) {
        strcat(active_mods, "Ctrl+");
    }
    // Store all current active modifier descriptions.
    if (sizeof(active_mods)) {
        snprintf(keylog_keymod, KEYLOG_LENGTH, active_mods);
    }
    else {
        snprintf(keylog_keymod, KEYLOG_LENGTH, KEYLOG_EMPTY_LINE);
    }

    // store keycode
    snprintf(keylog_keycode, KEYLOG_LENGTH, "key: %3d", keycode);

    // store key description
    snprintf(keylog_keydesc, KEYLOG_LENGTH, get_keycode_desc(keycode, key_desc_mod));
}


// Key logger that will display key function on Oled display.
// Do not send key to host if keylogger help is enabled, with a few exceptions.
// Allow normal process (return true) of:
//   1. Modifiers
//   2. Dedicated layer change keys.
//   3. Tapdances
// Otherwise the consectutive key press will not be handled.
// Active modifiers will be checked by keylogger and displayed on oled.
// Return should tell what caller (calling function) should do:
// 0 - continue
// 1 - return false
// 2 - return true (allow normal process)
uint8_t process_record_keylogger(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Allow normal process of layer change keys.
        case QK_LAYER_TAP ... QK_LAYER_TAP_TOGGLE_MAX:
            // Except explicit layer changes done from a layer.
            // Those should be checked by keylogger and displayed on oled.
            if (keycode == TG(_GAME) || keycode == TO(_BASE)) {
                break;
            } else {
                return 2;
            }

        // Allow normal process of tap dances.
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            return 2;

        // Allow normal process of real mods.
        case MODIFIER_KEYCODE_RANGE:
            return 2;

        // Allow normal process of mod combos like  S(KC_LCTL) = shift+ctrl
        // NOTE this works but is hardcoded. Have not found a dynamic way.
        case S(KC_LCTL):
            return 2;
    }
    // Display key log on oled and do not send key press to host (return false).
    // But first, make sure key is not the keylog toggler.
    if (keycode != KL_TOGL) {
        add_keylog(keycode, record);
        return 1;
    }
    return 0;
}
