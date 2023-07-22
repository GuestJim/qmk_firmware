#pragma once

#define DYNAMIC_KEYMAP_LAYER_COUNT 16

// place overrides here
#define TAPPING_TOGGLE 2
//	changes the number of taps necessary for toggling such as with TT
//		default is 5

#undef RGBLIGHT_ANIMATIONS
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_STATIC_GRADIENT

#define RGBLIGHT_LAYERS
#define RGBLIGHT_MAX_LAYERS 16
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF

#undef RGBLIGHT_LIMIT_VAL
#define RGBLIGHT_LIMIT_VAL 127
//	Lowers maximum brightness by half (normally 255)

#undef RGBLED_NUM
#define RGBLED_NUM 8
// LEDs above 10 are not working correctly, so cutting it down to 8 LEDs