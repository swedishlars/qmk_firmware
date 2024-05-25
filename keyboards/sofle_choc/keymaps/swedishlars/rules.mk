# Convert to Liatris MCU
CONVERT_TO=liatris

# NOTE I get strange behaviours (kb sending volume decrease etc)
# with info.json config, so keeping my configurations here.
VIA_ENABLE = no
ENCODER_ENABLE = no

LTO_ENABLE = yes
EXTRAKEY_ENABLE = yes

# mouse keys needed for track pad
MOUSEKEY_ENABLE = yes

# enable deferred execution of callbacks
DEFERRED_EXEC_ENABLE = yes

# Oled
OLED_ENABLE = yes

# Track Pad
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c

# Haptic
HAPTIC_ENABLE = yes
HAPTIC_DRIVER = drv2605l

# Audio
AUDIO_ENABLE = yes
AUDIO_DRIVER = pwm_hardware

# Enable console for debugging
# CONSOLE_ENABLE = yes

# Using LIB_SRC as per docs
LIB_SRC += lib/rgb.c
LIB_SRC += lib/oled.c
LIB_SRC += lib/pointing_device.c
