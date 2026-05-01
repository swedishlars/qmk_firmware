# NOTE I get strange behaviours (kb sending volume decrease etc)
# with info.json config, so keeping my configurations here.

# Convert to Liatris MCU
CONVERT_TO=liatris

VIA_ENABLE = no
ENCODER_ENABLE = no

LTO_ENABLE = no  # check that this does not cause compile issues, I turned it off for Kyria
EXTRAKEY_ENABLE = yes

MOUSEKEY_ENABLE = yes

OLED_ENABLE = yes

RGB_MATRIX_ENABLE = yes
RGBLIGHT_ENABLE = no

TAP_DANCE_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
CAPS_WORD_ENABLE = yes
AUTO_SHIFT_ENABLE = yes

# Key override to convert swedish layout to english
KEY_OVERRIDE_ENABLE = yes

# Unicode for swedish letters
UNICODE_ENABLE = yes

# enable deferred execution of callbacks
DEFERRED_EXEC_ENABLE = yes

# Track Pad
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c

# Haptic
HAPTIC_ENABLE = yes
HAPTIC_DRIVER = drv2605l

# Audio
AUDIO_ENABLE = yes
AUDIO_DRIVER = pwm_hardware

# Using LIB_SRC as per docs
LIB_SRC += lib/rgb.c
LIB_SRC += lib/oled.c
LIB_SRC += lib/pointing_device.c
LIB_SRC += lib/tapdance.c
LIB_SRC += lib/keylogger.c
