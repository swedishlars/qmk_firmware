#pragma once

#include "quantum.h"

// Modify these values to adjust the scrolling speed
#define SCROLL_DIVISOR_H 20.0
#define SCROLL_DIVISOR_V 15.0

report_mouse_t pointing_device_set_scroll(report_mouse_t mouse_report);
