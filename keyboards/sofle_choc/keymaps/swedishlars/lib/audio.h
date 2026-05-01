/* Copyright 2024 Lars Johansson (github.com/swedishlars)
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include "quantum.h"

// custom sounds
float click_sound[][2] = SONG(TERMINAL_SOUND);
float caps_on_sound[][2] = SONG(CAPS_LOCK_ON_SOUND);
float caps_off_sound[][2] = SONG(CAPS_LOCK_OFF_SOUND);
float oled_on_sound[][2] = SONG(SCROLL_LOCK_ON_SOUND);
float oled_off_sound[][2] = SONG(SCROLL_LOCK_OFF_SOUND);
float oledsleep_on_sound[][2] = SONG(AUDIO_ON_SOUND);
float oledsleep_off_sound[][2] = SONG(AUDIO_OFF_SOUND);
float keylogger_on_sound[][2] = SONG(AG_SWAP_SOUND);
float keylogger_off_sound[][2] = SONG(AG_NORM_SOUND);
float haptic_on_sound[][2] = SONG(NUM_LOCK_ON_SOUND);
float haptic_off_sound[][2] = SONG(NUM_LOCK_OFF_SOUND);
