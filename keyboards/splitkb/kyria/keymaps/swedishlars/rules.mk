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

RGB_MATRIX_ENABLE = yes     # Disable keyboard RGB matrix, as it is enabled by default on rev3
RGBLIGHT_ENABLE = no      # Enable keyboard RGB underglow

# enable caps word
CAPS_WORD_ENABLE = yes

# enable auto shift
AUTO_SHIFT_ENABLE = yes

# Using LIB_SRC as per docs
LIB_SRC += lib/rgb.c
LIB_SRC += lib/oled.c
