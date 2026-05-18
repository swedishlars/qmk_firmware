// Copyright 2024 Lars Johansson (github.com/swedishlars)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define KEYLOG_LENGTH 11
#define KEYLOG_EMPTY_LINE "          "

// global used to check if keylogger is enabled
extern bool keylogger_enabled;

// Store current key code
extern char keylog_keycode[KEYLOG_LENGTH];

// Store current active modifiers
extern char keylog_keymod[KEYLOG_LENGTH];

// rename keylogger_keydesc
// Store current key description
extern char keylog_keydesc[KEYLOG_LENGTH];

void add_keylog(uint16_t keycode, keyrecord_t *record);

uint8_t process_record_keylogger(uint16_t keycode, keyrecord_t *record);

// Enum names for keycode description array index
enum keycode_desc_index {
    KEYCODE_DEFAULT,
    KEYCODE_SHIFT,
    KEYCODE_FUNC,
    KEYCODE_RAISE,
    KEYCODE_MACRO
};

// Key code descriptions - array index represents keycode
// NOTE: backslash does not count as a char
static const char PROGMEM keycode_to_desc[][256][KEYLOG_LENGTH] = {
//   0           1            2            3            4            5            6            7            8            9         Raw code
//  ------------ ------------ ------------ ------------ ------------ ------------ ------------ ------------ ------------ ------------
[KEYCODE_DEFAULT] = {
    "          ","          ","          ","          "," a        "," b        "," c        "," d        "," e        "," f        ",  // 0-9
    " g        "," h        "," i        "," j        "," k        "," l        "," m        "," n        "," o        "," p        ",  // 10-19
    " q        "," r        "," s        "," t        "," u        "," v        "," w        "," x        "," y        "," z        ",  // 20-29
    " 1        "," 2        "," 3        "," 4        "," 5        "," 6        "," 7        "," 8        "," 9        "," 0        ",  // 30-39
    "Enter     "," Escape   ","Back Space"," Tab      ","Space     "," -        "," =        "," [        "," ]        "," \\       ",  // 40-49
    " #        "," ;        "," \'       "," `        "," ,        "," .        "," /        ","128       "," F1       "," F2       ",  // 50-59
    " F3       "," F4       "," F5       "," F6       "," F7       "," F8       "," F9       "," F10      "," F11      "," F12      ",  // 60-69
    "Print Scrn","Scroll Lck","Play/Pause","Insert    "," Home     ","Page Up   "," Delete   "," End      ","Page Down ","Right     ",  // 70-79
    " Left     "," Down     "," Up       ","Num Lock  ","/         "," *        "," -        "," +        ","Enter     "," 1        ",  // 80-89
    " 2        "," 3        "," 4        "," 5        "," 6        "," 7        "," 8        "," 9        "," 0        "," .        ",  // 90-99
    " \\       ","App Menu  ","Mac Power "," =        "," F13      "," F14      "," F15      "," F16      "," F17      "," F18      ",  // 100-109
    " F19      "," F20      "," F21      "," F22      "," F23      "," F24      ","          ","          ","          ","          ",  // 110-119
    "          ","          ","          ","          ","          ","          ","          ","          ","          ","          ",  // 120-129
    "          ","          ","          ","          ","          ","          ","          ","          ","          ","          ",  // 130-139
    "          ","          ","          ","          ","          ","          ","          ","          ","          ","          ",  // 140-149
    "          ","          ","          ","          ","          ","          ","          ","          ","          ","          ",  // 150-159
    "          ","          ","          ","          ","          ","Sys Power ","Sys Sleep ","Sys Wake  ","Mute      ","Vol Up    ",  // 160-169
    "Vol Down  ","Next Track","Prev Track","          ","Play/Pause","          ","          ","          ","          ","          ",  // 170-179
    "          ","          ","          ","          ","          ","          ","          ","          ","          ","          ",  // 180-189
    "          ","          ","          ","MissionCtl","Launch Pad","          ","          ","          ","          ","          ",  // 190- 199
    "          ","          ","          ","          ","0x80      ","0x80      ","0x80      ","0x80      ","0x80      ","L MouseBtn",  // 200-209
    "R MouseBtn","M MouseBtn","MouseBtn 4","MouseBtn 5","0x80      ","0x80      ","0x80      ","Wheel Up  ","Wheel Down","Wheel Left",  // 210-219
    "Wheel Rght","MouseAcc 0","MouseAcc 1","MouseAcc 2","L Control ","L Shift   ","L Alt     ","L Gui     "," R Control","R Shift   ",  // 220-229
    "R Alt     ","R Gui     ","          ","          ","          ","          ","          "," 24       "," 26       "," 24       ",  // 230-239
    "25        ","          ","          ","          ","          ","          ","          ","          ","          "," 24       ",  // 240- 249
    "25        "," 27       "," 26       ","          ","          ","          "                                                       // 250-255
    },

// Shifted key code descriptions - array index represents keycode
//   0           1            2            3            4            5            6            7            8            9              Raw code
//  ----------   ------------ ------------ ------------ ------------ ------------ ------------ ------------ ------------ ------------
[KEYCODE_SHIFT] = {
    "          ","          ","          ","          "," A        "," B        "," C        "," D        "," E        "," F        ",  // 0-9
    " G        "," H        "," I        "," J        "," K        "," L        "," M        "," N        "," O        "," P        ",  // 10-19
    " Q        "," R        "," S        "," T        "," U        "," V        "," W        "," X        "," Y        "," Z        ",  // 20-29
    " !        "," \"       ","Pound     "," $        ","Percent   "," ^        "," &        "," *        "," (        "," )        ",  // 30-39
    "Enter     ","Escape    ","Back Space","Tab       ","Space     "," _        "," +        "," {        "," }        "," |        ",  // 40-49
    " ~        "," :        ","  @       ","Neg Symbol"," <        "," >        "," ?        "," Caps Lock"," F1       "," F2       ",  // 50-59
    " F3       "," F4       "," F5       "," F6       "," F7       "," F8       "," F9       "," F10      "," F11      "," F12      ",  // 60-69
    "Print Scrn","Scroll Lck","Play/Pause","Insert    "," Home     ","Page Up   ","Delete    "," End      ","Page Down ","Right     ",  // 70-79
    " Left     "," Down     "," Up       ","Num Lock  ","/         "," *        "," -        "," +        ","Enter     "," 1        ",  // 80-89
    " 2        "," 3        "," 4        "," 5        "," 6        "," 7        "," 8        "," 9        "," 0        "," .        ",  // 90-99
    " |        ",                                                                                                                       // 100
    },

// Key description overrides per layer
[KEYCODE_RAISE] = {
    [53] =  "(Neg Symb)"
    },

[KEYCODE_FUNC] = {
    [7]  =  "d (tmux)  ",
    [9]  =  "f (maxwin)",
    [23] =  "t (Term)  "
    },

[KEYCODE_MACRO] = {
    [9]  =  "@gmail.com",
    [68] =  "ileanastr ",
    [69] =  "Ileana    ",
    [73]  =  "gmail.com",
    [74]  =  "henrmanil",
    [75]  =  "Henry    ",
    [76]  =  "Emmanouil",
    [77]  =  "swedshlrs",
    [79]  =  "Gunnar   ",
    [80]  =  "Johansson"
    }
};
