 /* Copyright 2021 Dane Evans
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
  #pragma once

// NOTE can I use another automatic option?
// Does not work: SPLIT_USB_DETECT, SPLIT_HAND_PIN B6

// NOTE left is default
/* #define MASTER_LEFT */

// required for rgb matrix
#define SPLIT_TRANSPORT_MIRROR

#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_MODS_ENABLE

// activity timestamp synching
#define SPLIT_ACTIVITY_ENABLE

// TODO test if this fixes oled timeout
#define SPLIT_WATCHDOG_ENABLE


#ifdef OLED_ENABLE
    #define SPLIT_OLED_ENABLE
    #define OLED_UPDATE_INTERVAL 50

    // standard sofle 128x32 oled
    /* #define OLED_DISPLAY_128X64 */

    // bigger 64x128 sh1107 oled
    #define OLED_DISPLAY_64X128
    #define OLED_IC OLED_IC_SH1107

    // set default brightness
    #define OLED_BRIGHTNESS 128

    #define OLED_TIMEOUT 0
#endif


#ifdef POINTING_DEVICE_ENABLE
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
#endif


#ifdef HAPTIC_ENABLE
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
#endif


#ifdef AUDIO_ENABLE
    // Liatris pin conversions. Use Liatris pins (13U for example)
    // F4 = 29U - Works. Encoder top left pin. Use PWMD6, channel B
    #undef AUDIO_PIN
    #define AUDIO_PIN 29U
    #define AUDIO_PWM_DRIVER PWMD6
    #define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_B
    #define NO_MUSIC_MODE
    #define STARTUP_SONG SONG(STARTUP_SOUND)
#endif

// Remove the auto-repeat ability of tapping and activate the hold function instead. 
#define QUICK_TAP_TERM 0

// tap-hold threshold, default is 200
#ifdef TAPPING_TERM
    #undef TAPPING_TERM
    #define TAPPING_TERM 140
#endif


#ifdef RGB_MATRIX_ENABLE
    #define ENABLE_RGB_MATRIX_SOLID_COLOR

    // turn off effects when suspended
    #define RGB_MATRIX_SLEEP 
    //  Diasble rgb after 5 minutes of inactivity. Configured in milliseconds
    #define RGB_MATRIX_TIMEOUT 300000

    // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.
    // NOTE: EE prom needs to be reset for this to thake effect!
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150

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

