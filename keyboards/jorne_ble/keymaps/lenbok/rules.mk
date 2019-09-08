
RGBLIGHT_ENABLE = yes
LED_ANIMATIONS = yes        # LED animations
OLED_ENABLE = yes           # OLED_ENABLE
LOCAL_GLCDFONT = yes        # use each keymaps "helixfont.h" insted of "common/glcdfont.c"

FLIPPED_NRFMICRO_MASTER = yes # Set to yes if master side uses a nrfmicro with jumpers on the reverse bridged
FLIPPED_NRFMICRO_SLAVE = yes  # Set to yes if slave side uses a nrfmicro with jumpers on the reverse bridged


ifeq ($(strip $(NRF_SEPARATE)), slave)
  ifeq ($(strip $(FLIPPED_NRFMICRO_SLAVE)), yes)
    OPT_DEFS += -DFLIPPED_NRFMICRO
  endif
else ifeq ($(strip $(NRF_SEPARATE)), master)
  ifeq ($(strip $(FLIPPED_NRFMICRO_MASTER)), yes)
    OPT_DEFS += -DFLIPPED_NRFMICRO
  endif
endif

ifeq ($(strip $(LED_ANIMATIONS)), yes)
    OPT_DEFS += -DRGBLIGHT_ANIMATIONS
endif

ifeq ($(strip $(LOCAL_GLCDFONT)), yes)
    OPT_DEFS += -DLOCAL_GLCDFONT
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
    OPT_DEFS += -DOLED_ENABLE
endif

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend

ifndef QUANTUM_DIR
	include ../../../../Makefile
endif

# If you want to change the display of OLED, you need to change here
SRC +=  ../../lib/glcdfont.c \
        ../../lib/rgb_state_reader.c \
        ../../lib/layer_state_reader.c \
        ../../lib/logo_reader.c \
        ../../lib/keylogger.c \
        # ./lib/mode_icon_reader.c \
        # ./lib/host_led_state_reader.c \
        ../../lib/timelogger.c \
