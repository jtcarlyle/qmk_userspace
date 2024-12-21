SRC += features/select_word.c

VPATH += keyboards/gboards

BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.
SWAP_HANDS_ENABLE = no      # Enable one-hand typing
OLED_ENABLE = no            # OLED display
COMBO_ENABLE = yes          # for koume implementation
TAP_DANCE_ENABLE = yes      # for complex dual purpose keys
REPEAT_KEY_ENABLE = no      # cool, but probably overkill
STENO_ENABLE = no			# not using for now
STENO_LAYERS = no			# not using for now

# If you want to change the display of OLED, you need to change here
# SRC +=  ./lib/rgb_state_reader.c \
        # ./lib/layer_state_reader.c \
        # ./lib/logo_reader.c \
        # ./lib/keylogger.c \
# below previously commented out
        # ./lib/mode_icon_reader.c \
        # ./lib/host_led_state_reader.c \
        # ./lib/timelogger.c \
