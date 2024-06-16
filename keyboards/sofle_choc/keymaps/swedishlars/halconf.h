// Copyright 2024 Lars Johansson (github.com/swedishlars)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <halconf.h>

// This is for audio driver
#undef HAL_USE_PWM
#define HAL_USE_PWM TRUE
