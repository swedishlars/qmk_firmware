// default rgb mode
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_COLOR

// TODO test suspend rgb. Does not work unfortunately
#define RGB_DISABLE_WHEN_USB_SUSPENDED true

//  Diasble rgb after 10 minutes of inactivity. Configured in milliseconds
//  TODO increase to 20 mins?
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

// custom tapdance definition, adds user_data so I can pass on keycode to tapdance function.
#define ACTION_TAP_DANCE_FN_ADVANCED_KEYCODE(user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset, kc) { \
    .fn = {user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset}, \
    .user_data = (void *)&((qk_tap_dance_pair_t) { kc, 0 }) \
}

//Sets the delay between register_code and unregister_code, default is 100 ms
/* #define TAP_CODE_DELAY 20 */

// Mouse keys
/* #define MOUSEKEY_INTERVAL 20 */
/* #define MOUSEKEY_WHEEL_INTERVAL 50 */

// Use test Kinetic mode
// TODO make inital movements slower
#define MK_KINETIC_SPEED
#define MOUSEKEY_MOVE_DELTA 4
#define MOUSEKEY_INITIAL_SPEED 1
#define MOUSEKEY_BASE_SPEED 6000
#define MOUSEKEY_DECELERATED_SPEED 1000
#define MOUSEKEY_ACCELERATED_SPEED 8000

#define MOUSEKEY_WHEEL_INITIAL_MOVEMENTS 8
#define MOUSEKEY_WHEEL_BASE_MOVEMENTS 300
#define MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS 400
