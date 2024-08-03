/* Copyright 2024 Lars Johansson (github.com/swedishlars)
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

// required for rgb matrix
#define SPLIT_TRANSPORT_MIRROR

#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_MODS_ENABLE

// TODO what is SPLIT_ST7565?

// activity timestamp synching
#define SPLIT_ACTIVITY_ENABLE

// Reboot slave side if no communication from master within timeout
// TODO should I enable?
/* #define SPLIT_WATCHDOG_ENABLE */

// Remove the auto-repeat ability of tapping and activate the hold function instead. 
#define QUICK_TAP_TERM 0

// tap-hold threshold, default is 200
#define TAPPING_TERM 200

// use per key tap-hold thresholds
#define TAPPING_TERM_PER_KEY

// Toggle layer with 1 tap
#define TAPPING_TOGGLE 1

// TODO testing caps word
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORDS
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

// TODO auto shift
#define AUTO_SHIFT_TIMEOUT 200


#ifdef OLED_ENABLE
    // default oled size needs to be unset
    #undef OLED_DISPLAY_128X64

    #define OLED_DISPLAY_128X128
    #define OLED_IC OLED_IC_SH1107
    #define OLED_UPDATE_INTERVAL 50
    #define OLED_BRIGHTNESS 92

    // Note: oled timeout is incompatible with oled off.
    #define OLED_TIMEOUT 0
#endif

#ifdef RGB_MATRIX_ENABLE
    // turn off effects when suspended
    #define RGB_MATRIX_SLEEP 
    //  Diasble rgb after 5 minutes of inactivity. Configured in milliseconds
    #define RGB_MATRIX_TIMEOUT 300000

    // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.
    // NOTE: EE prom needs to be reset for this to thake effect!
    // TODO this is already set to 128 on kb level
    /* #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150 */

    #define ENABLE_RGB_MATRIX_SOLID_COLOR
    #define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR

    // Disable the animations you don't want/need.  You will need to disable a good number of these
    //  because they take up a lot of space.  Disable until you can successfully compile your firmware.
    #undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
    #undef ENABLE_RGB_MATRIX_BREATHING
    #undef ENABLE_RGB_MATRIX_CYCLE_ALL
    #undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
    #undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
    #undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
    #undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
    #undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
    #undef ENABLE_RGB_MATRIX_DUAL_BEACON
    #undef ENABLE_RGB_MATRIX_RAINBOW_BEACON
    #undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
    #undef ENABLE_RGB_MATRIX_RAINDROPS
    #undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
    #undef ENABLE_RGB_MATRIX_TYPING_HEATMAP
    #undef ENABLE_RGB_MATRIX_DIGITAL_RAIN
    #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE
    #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
    #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
    #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
    #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
    #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
    #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
    #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
    #undef ENABLE_RGB_MATRIX_SPLASH
    #undef ENABLE_RGB_MATRIX_MULTISPLASH
    #undef ENABLE_RGB_MATRIX_SOLID_SPLASH
    #undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#endif


