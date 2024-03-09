# Convert to Liatris MCU
CONVERT_TO=liatris

# TODO use info.json in keyboard folder?

# TODO disable?
MOUSEKEY_ENABLE = no

EXTRAKEY_ENABLE = yes

# TODO press lower and raise to activate adjust layer
# it does not seem to work well
# TRI_LAYER_ENABLE = yes

# do not need via
VIA_ENABLE = no

# Enable console for debugging
# CONSOLE_ENABLE = yes

ENCODER_ENABLE = no
LTO_ENABLE = yes
OLED_ENABLE = yes
OLED_DRIVER = ssd1306

# Track Pad
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c

# POINTING_DEVICE_DRIVER = pimoroni_trackball
# POINTING_DEVICE_DRIVER = azoteq_iqs5xx

# Haptic
HAPTIC_ENABLE = yes
HAPTIC_DRIVER = drv2605l

# Audio
AUDIO_ENABLE = yes
AUDIO_DRIVER = pwm_hardware
