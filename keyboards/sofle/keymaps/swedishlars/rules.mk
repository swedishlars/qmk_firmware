# Convert to Liatris MCU
CONVERT_TO=liatris

MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = yes

# Enable console for debugging
# CONSOLE_ENABLE = yes

RGBLIGHT_ENABLE = yes
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
