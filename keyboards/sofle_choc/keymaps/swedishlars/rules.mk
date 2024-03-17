# Convert to Liatris MCU
CONVERT_TO=liatris

# TODO use info.json in keyboard folder?

MOUSEKEY_ENABLE = no
EXTRAKEY_ENABLE = yes
VIA_ENABLE = no

ENCODER_ENABLE = no
LTO_ENABLE = yes

# Oled
OLED_ENABLE = yes
OLED_DRIVER = ssd1306

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
