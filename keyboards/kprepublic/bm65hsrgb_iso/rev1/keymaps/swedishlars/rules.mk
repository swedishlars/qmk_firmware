# Enable VIA NOTE: VIA breaks key mapping and compiler. Leave Off.
VIA_ENABLE = no
ENCODER_ENABLE = no

# Enables Link Time Optimization (LTO) when compiling the keyboard
LTO_ENABLE = yes
EXTRAKEY_ENABLE = yes

MOUSEKEY_ENABLE = yes

TAP_DANCE_ENABLE = yes
CAPS_WORD_ENABLE = yes
AUTO_SHIFT_ENABLE = yes

# Key override to convert swedish layout to english
#KEY_OVERRIDE_ENABLE = yes

# Key override to convert swedish layout to english
#KEY_OVERRIDE_ENABLE = yes

# Unicode for swedish letters
#UNICODE_ENABLE = yes

# enable deferred execution of callbacks
#DEFERRED_EXEC_ENABLE = yes

# Using LIB_SRC as per docs
LIB_SRC += lib/rgb.c
LIB_SRC += lib/tapdance.c
