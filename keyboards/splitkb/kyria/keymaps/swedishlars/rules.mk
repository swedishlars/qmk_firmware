# NOTE I get strange behaviours (kb sending volume decrease etc)
# with info.json config, so keeping my configurations here.

# Convert to Liatris MCU
CONVERT_TO=liatris

VIA_ENABLE = no
ENCODER_ENABLE = no

LTO_ENABLE = no
EXTRAKEY_ENABLE = yes

MOUSEKEY_ENABLE = yes

OLED_ENABLE = yes

RGB_MATRIX_ENABLE = yes
RGBLIGHT_ENABLE = no

TAP_DANCE_ENABLE = yes

CAPS_WORD_ENABLE = yes

AUTO_SHIFT_ENABLE = yes

# Using LIB_SRC as per docs
LIB_SRC += lib/rgb.c
LIB_SRC += lib/oled.c

# Unicode for swedish letters
UNICODE_ENABLE = yes
