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


// TODO KB freezes after a few minutes!!!
//
/* Select hand configuration */
// TODO test usb detect - it does not seem to work
// Enabling this option changes the startup behavior to listen for an
// // active USB communication to delegate which part is master and which
// // is slave. With this option enabled and theres’s USB communication,
// // then that half assumes it is the master, otherwise it assumes it
// // is the slave.
// //
// // I've found this helps with some ProMicros where the slave does not boot
/* #define SPLIT_USB_DETECT */

// TODO orig:
#define MASTER_LEFT

// TODO what I orig used:
/* #define MASTER_RIGHT */

// TODO required for rgb matrix
#define SPLIT_TRANSPORT_MIRROR

// TODO test for rgb, these are not causing the freeze
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_MODS_ENABLE

// TODO what is this?
#define CUSTOM_FONT

// TODO orig enabled
/* #define CUSTOM_LAYER_READ //if you remove this it causes issues - needs better guarding */


// Oled
#ifdef OLED_ENABLE
#   define SPLIT_OLED_ENABLE
#endif

#ifdef POINTING_DEVICE_ENABLE
/* #   define POINTING_DEVICE_DEBUG */
#   define SPLIT_POINTING_ENABLE
#   define POINTING_DEVICE_COMBINED

//  Pimoroni trackball - works
/* #   define PIMORONI_TRACKBALL_SCALE 10 */
/* #   define POINTING_DEVICE_TASK_THROTTLE_MS 8 */
/* #   define POINTING_DEVICE_ROTATION_180 */

// Cirque trackpad - works
#   define CIRQUE_PINNACLE_DIAMETER_MM 40
#   define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_ABSOLUTE_MODE
#   define CIRQUE_PINNACLE_TAP_ENABLE

// TODO test Azoteq iqs -tps65
/* #   define AZOTEQ_IQS5XX_TPS65 */
/* #   define AZOTEQ_IQS5XX_WIDTH_MM 65 */
/* #   define AZOTEQ_IQS5XX_HEIGHT_MM 49 */
/* #   define AZOTEQ_IQS5XX_RESOLUTION_X 5120 */
/* #   define AZOTEQ_IQS5XX_RESOLUTION_Y 2048 */
// Common
/* #   define  */
#   define POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE
// TODO test:
/* #define POINTING_DEVICE_TASK_THROTTLE_MS 10 */
#endif

// Haptic Feedback. Works!
#ifdef HAPTIC_ENABLE
//  TODO test
#   define SPLIT_HAPTIC_ENABLE

#   define DRV2605L_FB_ERM_LRA 1
    // TODO orig:
/* #   define DRV2605L_FB_BRAKEFACTOR 3 /1* For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable Braking:7 *1/ */
#   define DRV2605L_FB_BRAKEFACTOR 2 // For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable Braking:7
#   define DRV2605L_FB_LOOPGAIN 1 /* For  Low:0, Medium:1, High:2, Very High:3 */
#   define DRV2605L_RATED_VOLTAGE 2 //2Vrms per ELV1411A datasheet, which is the LRA used for the Pimoroni Haptic Bzzz driver DRV2605.
#   define DRV2605L_V_PEAK 2.8 //Per QMK docs.
#   define DRV2605L_V_RMS 2.0 //Per ELV1411A datasheet.
#   define DRV2605L_F_LRA 150 //Resonant frequency per ELV1411A datasheet.
/* #   define DRV2605L_GREETING alert_1000ms */
/* #   define DRV2605L_DEFAULT_MODE strong_click */
#   define DRV2605L_DEFAULT_MODE 1
#endif

// AUDIO
// TODO Liatris pin conversions. Use Liatris pins (13U for example)
// F4 = 29U - Works. Encoder top left pin. Use PWMD6, channel B
#ifdef AUDIO_ENABLE
#   undef AUDIO_PIN
#   define AUDIO_PIN 29U
#   define AUDIO_PWM_DRIVER PWMD6
#   define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_B
/* #   define AUDIO_CLICKY */
#   define STARTUP_SONG SONG(STARTUP_SOUND)
/* #   define AUDIO_INIT_DELAY 200 */
/* #   define NO_MUSIC_MODE */
#endif

// Quick Tap TODO what is this?
#define QUICK_TAP_TERM 0
#ifdef TAPPING_TERM
    #undef TAPPING_TERM
    #define TAPPING_TERM 200
#endif


// TODO do I have to correct driver in info.json?
#ifdef RGB_MATRIX_ENABLE
    // TODO this is specced in info.json
    #define RGB_MATRIX_SPLIT { 29, 29 }
    
    #define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended

    #define ENABLE_RGB_MATRIX_SOLID_COLOR

    // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.
    // NOTE: EE prom needs to be reset for this to thake effect!
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
    #define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS

    #define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR

    #define RGB_MATRIX_HUE_STEP 8
    #define RGB_MATRIX_SAT_STEP 8
    #define RGB_MATRIX_VAL_STEP 8
    #define RGB_MATRIX_SPD_STEP 10

    // Disable the animations you don't want/need.  You will need to disable a good number of these
    //  because they take up a lot of space.  Disable until you can successfully compile your firmware.
    // #   undef ENABLE_RGB_MATRIX_ALPHAS_MODS
    // #   undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
    // #   undef ENABLE_RGB_MATRIX_BREATHING
    #   undef ENABLE_RGB_MATRIX_CYCLE_ALL
    #   undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
    #   undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
    #   undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
    #   undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
    #   undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
    // #   undef ENABLE_RGB_MATRIX_DUAL_BEACON
    // #   undef ENABLE_RGB_MATRIX_RAINBOW_BEACON
    // #   undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
    // #   undef ENABLE_RGB_MATRIX_RAINDROPS
    // #   undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
    // #   undef ENABLE_RGB_MATRIX_TYPING_HEATMAP
    // #   undef ENABLE_RGB_MATRIX_DIGITAL_RAIN
    // #   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE
    // #   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
    // #   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
    // #   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
    // #   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
    // #   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
    // #   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
    // #   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
    // #   undef ENABLE_RGB_MATRIX_SPLASH
    // #   undef ENABLE_RGB_MATRIX_MULTISPLASH
    // #   undef ENABLE_RGB_MATRIX_SOLID_SPLASH
    // #   undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#endif
