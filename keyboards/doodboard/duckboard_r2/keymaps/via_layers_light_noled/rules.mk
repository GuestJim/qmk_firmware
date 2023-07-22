#BOOTLOADER = qmk-dfu
BOOTLOADER = atmel-dfu
#	the Elite-C uses a different boot loader, making the above line necessary
#	https://old.reddit.com/r/olkb/comments/mujcfm/elitec_reset_key_not_working_dfu_qmk/

VIA_ENABLE = yes
LTO_ENABLE = yes
RGBLIGHT_ENABLE = yes
# KEY_LOCK_ENABLE = yes
OLED_DRIVER_ENABLE = no