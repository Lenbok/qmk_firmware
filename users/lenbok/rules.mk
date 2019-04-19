RGB_IDLE = yes   # If yes do something with the rgblight/rgb_matrix after inactivity timeout

SRC += lenbok.c

EXTRAFLAGS += -flto

ifeq ($(strip $(RGB_IDLE)), yes)
    OPT_DEFS += -DRGB_IDLE
endif
