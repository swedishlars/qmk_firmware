/* Copyright 2024 Lars Johansson (github.com/swedishlars)
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

// required for rgb matrix
#define SPLIT_TRANSPORT_MIRROR

#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_MODS_ENABLE

// activity timestamp synching
#define SPLIT_ACTIVITY_ENABLE

// Reboot slave side if no communication from master within timeout
#define SPLIT_WATCHDOG_ENABLE

// Remove the auto-repeat ability of tapping and activate the hold function instead.
#define QUICK_TAP_TERM 0

// tap-hold threshold, default is 200
#define TAPPING_TERM 140

// use per key tap-hold thresholds
#define TAPPING_TERM_PER_KEY

// Toggle layer with 1 tap
#define TAPPING_TOGGLE 1

// Caps word
/* #define BOTH_SHIFTS_TURNS_ON_CAPS_WORDS */
/* #define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD */
#define CAPS_WORD_INVERT_ON_SHIFT

// Auto shift
#define AUTO_SHIFT_TIMEOUT 200

// Oled
#define SPLIT_OLED_ENABLE

// default oled size needs to be unset
#undef OLED_DISPLAY_128X32
#define OLED_DISPLAY_64X128

#define OLED_IC OLED_IC_SH1107
#define OLED_UPDATE_INTERVAL 50
#define OLED_BRIGHTNESS 92

// Note: oled timeout is incompatible with oled off.
#define OLED_TIMEOUT 0


// RGB
// turn off effects when suspended
#define RGB_MATRIX_SLEEP
//  Diasble rgb after 5 minutes of inactivity. Configured in milliseconds
#define RGB_MATRIX_TIMEOUT 300000

// limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.
// NOTE: EE prom needs to be reset for this to thake effect!
// NOTE: Max brightness is already set to 128 on kb level
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150

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

// Unicode for linux for swedish letters
#define UNICODE_SELECTED_MODES UNICODE_MODE_LINUX


// POINTING DEVICE
#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_COMBINED
#define POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE

// Cirque trackpad
#define CIRQUE_PINNACLE_DIAMETER_MM 40
#define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_ABSOLUTE_MODE
/* #define CIRQUE_PINNACLE_TAP_ENABLE */

// NOTE: Azoteq iqs -tps65. It works
/* #   define AZOTEQ_IQS5XX_TPS65 */
/* #   define AZOTEQ_IQS5XX_WIDTH_MM 65 */
/* #   define AZOTEQ_IQS5XX_HEIGHT_MM 49 */
/* #   define AZOTEQ_IQS5XX_RESOLUTION_X 5120 */
/* #   define AZOTEQ_IQS5XX_RESOLUTION_Y 2048 */

// HAPTIC
#define SPLIT_HAPTIC_ENABLE
#define DRV2605L_FB_ERM_LRA 1
#define DRV2605L_FB_BRAKEFACTOR 3 /* For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable Braking:7 */
#define DRV2605L_FB_LOOPGAIN 1 /* For  Low:0, Medium:1, High:2, Very High:3 */
#define DRV2605L_RATED_VOLTAGE 2 //2Vrms per ELV1411A datasheet, which is the LRA used for the Pimoroni Haptic Bzzz driver DRV2605.
#define DRV2605L_V_PEAK 2.8 //Per QMK docs.
#define DRV2605L_V_RMS 2.0 //Per ELV1411A datasheet.
#define DRV2605L_F_LRA 150 //Resonant frequency per ELV1411A datasheet.

// medium click
#define DRV2605L_DEFAULT_MODE DRV2605L_EFFECT_MEDIUM_CLICK_1_100

// supposedly turns off haptic while suspended
#define HAPTIC_OFF_IN_LOW_POWER 1

#define NO_HAPTIC_ALPHA
#define NO_HAPTIC_NUMERIC
#define NO_HAPTIC_PUNCTUATION
/* #define NO_HAPTIC_NAV */

// AUDIO
// Liatris pin conversions. Use Liatris pins (13U for example)
// F4 = 29U - Works. Encoder top left pin. Use PWMD6, channel B
#undef AUDIO_PIN
#define AUDIO_PIN 29U
#define AUDIO_PWM_DRIVER PWMD6
#define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_B
#define NO_MUSIC_MODE
#define STARTUP_SONG SONG(STARTUP_SOUND)
// #define STARTUP_SONG SONG(CLOSE_ENCOUNTERS_SONG)




