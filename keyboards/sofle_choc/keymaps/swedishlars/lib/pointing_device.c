#include "pointing_device.h"


// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

// Function to handle mouse reports and perform drag scrolling
report_mouse_t pointing_device_set_scroll(report_mouse_t mouse_report) {

    // limit haptic buzz based on amount of movement
    if ( (mouse_report.y > 3 && mouse_report.y < 10) ||
        (mouse_report.y < -3 && mouse_report.y > -10) ) {
        //  mode 13 , 9 are ok
        haptic_set_mode(9);
        haptic_play();
    }

    // Calculate and accumulate scroll values based on mouse movement and divisors
    // ---------------------------------------------------------------------------
    scroll_accumulated_h += (float)mouse_report.x / SCROLL_DIVISOR_H;
    scroll_accumulated_v += (float)mouse_report.y / SCROLL_DIVISOR_V;

    // Assign integer parts of accumulated scroll values to the mouse report
    mouse_report.h = (int8_t)scroll_accumulated_h;
    mouse_report.v = (int8_t)scroll_accumulated_v;

    // Update accumulated scroll values by subtracting the integer parts
    scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
    scroll_accumulated_v -= (int8_t)scroll_accumulated_v;
    // ---------------------------------------------------------------------------

    // Clear the X and Y values of the mouse report
    mouse_report.x = 0;
    mouse_report.y = 0;

    // disable any button reports (tapping the trackpad)
    mouse_report.buttons = 0;

    return mouse_report;
}

