// default rgb mode
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_COLOR

// TODO test suspend rgb. Does not work unfortunately.
#define RGB_DISABLE_WHEN_USB_SUSPENDED true

//  Diasble rgb after 10 minutes of inactivity. Configured in milliseconds
#define RGB_DISABLE_TIMEOUT 600000

// Disable unwanted RGB effects
#define DISABLE_RGB_MATRIX_ALPHAS_MODS
#define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#define DISABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define DISABLE_RGB_MATRIX_BREATHING
#define DISABLE_RGB_MATRIX_BAND_SAT
#define DISABLE_RGB_MATRIX_BAND_VAL
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#define DISABLE_RGB_MATRIX_CYCLE_ALL
#define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
#define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN	
#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#define DISABLE_RGB_MATRIX_CYCLE_PINWHEEL
#define DISABLE_RGB_MATRIX_CYCLE_SPIRAL	
#define DISABLE_RGB_MATRIX_DUAL_BEACON
#define DISABLE_RGB_MATRIX_RAINBOW_BEACON
#define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#define DISABLE_RGB_MATRIX_RAINDROPS
#define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#define DISABLE_RGB_MATRIX_HUE_PENDULUM
#define DISABLE_RGB_MATRIX_HUE_WAVE 
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#define DISABLE_RGB_MATRIX_MULTISPLASH
#define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH

// Set tap dance timeout limit in milliseconds
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY

//Sets the delay between register_code and unregister_code, default is 100 ms
/* #define TAP_CODE_DELAY 20 */

// Mouse keys
// Accelerated mode settings
#define MOUSEKEY_DELAY 0                            // Delay between pressing a movement key and cursor movement, default 300.
#define MOUSEKEY_INTERVAL 1                         // Time between cursor movements in milliseconds, default 50 for accelerated mode, 8 for kinetic.
#define MOUSEKEY_MOVE_DELTA 1                       // Step size for accelerating from initial to base speed, default 25.
#define MOUSEKEY_MAX_SPEED 80
#define MOUSEKEY_TIME_TO_MAX 140

#define MOUSEKEY_WHEEL_DELAY 0                      // Delay between pressing a wheel key and wheel movement, default 300.
#define MOUSEKEY_WHEEL_INTERVAL 1                   // Time between wheel movements, default 100.
#define MOUSEKEY_WHEEL_MAX_SPEED 8
#define MOUSEKEY_WHEEL_TIME_TO_MAX 250

// Kinetic mode settings
// TODO does not seem to work well
/* #define MK_KINETIC_SPEED */
/* #define MOUSEKEY_DELAY 0                         // Delay between pressing a movement key and cursor movement, default 300. */
/* #define MOUSEKEY_INTERVAL 1                      // Time between cursor movements in milliseconds, default 50 for accelerated mode, 8 for kinetic. */
/* #define MOUSEKEY_MOVE_DELTA 2                    // Step size for accelerating from initial to base speed, default 25 */
/* #define MOUSEKEY_INITIAL_SPEED 1                 // Initial speed of the cursor in pixel per second, default 100 */
/* #define MOUSEKEY_BASE_SPEED 100                  // Maximum cursor speed at which acceleration stops, default 1000 */
/* #define MOUSEKEY_DECELERATED_SPEED 40            // Decelerated cursor speed, default 400 */
/* #define MOUSEKEY_ACCELERATED_SPEED 100           // Accelerated cursor speed, default 3000. */

/* #define MOUSEKEY_WHEEL_DELAY 0                   // Delay between pressing a wheel key and wheel movement, default 300. */
/* #define MOUSEKEY_WHEEL_INTERVAL 2                // Time between wheel movements, default 100. */
/* #define MOUSEKEY_WHEEL_INITIAL_MOVEMENTS 1       // Initial number of movements of the mouse wheel, default 16. */ 
/* #define MOUSEKEY_WHEEL_BASE_MOVEMENTS 300        // Maximum number of movements at which acceleration stops, default 32 */
/* #define MOUSEKEY_WHEEL_DECELERATED_MOVEMENTS 1   //Decelerated wheel movements, default 8 */
/* #define MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS 300 // Accelerated wheel movements, default 48 */


// Custom tapdance advanced action. Pass keycode in user_data
#define ACTION_TAP_DANCE_FN_KEY(user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset, kc) { \
    .fn = {user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset}, \
    .user_data = (void *)&((qk_tap_dance_pair_t) { kc, 0 }) \
}

// Custom tapdance advanced action. Pass keycode and layer in user_data.
#define ACTION_TAP_DANCE_FN_KEY_LAYER(user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset, kc, layer) { \
    .fn = {user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset}, \
    .user_data = (void *)&((qk_tap_dance_dual_role_t) {kc, layer, NULL}) \
}
