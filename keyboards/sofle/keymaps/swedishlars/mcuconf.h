#pragma once

#include_next <mcuconf.h>

/* #undef RP_PWM_USE_PWM0 */
/* #define RP_PWM_USE_PWM0 TRUE */

/* #undef RP_PWM_USE_PWM1 */
/* #define RP_PWM_USE_PWM1 TRUE */


// AUDIO THIS WORKS!
#undef RP_PWM_USE_PWM6
#define RP_PWM_USE_PWM6 TRUE


/* #undef RP_PWM_USE_TIM1 */
/* #define RP_PWM_USE_TIM1 TRUE */

/* #undef RP_PWM_USE_TIM6 */
/* #define RP_PWM_USE_TIM6 TRUE */
