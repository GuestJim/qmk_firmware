#include QMK_KEYBOARD_H


/* RGB LEDs
*	,-----------------------------------.
*	|	0	1	2	3	4	5	6	7	|
*	|									|
*	|	15	14	13	12	11	10	9	8	|
*	 `----------------------------------'
*/

const rgblight_segment_t PROGMEM layer_function[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, HSV_CYAN},
    {6, 1, HSV_CYAN},
    {9, 1, HSV_CYAN},
    {14, 1, HSV_CYAN}
);

const rgblight_segment_t PROGMEM layer_rgb[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 1, HSV_GREEN},
    {5, 1, HSV_GREEN},
    {10, 1, HSV_GREEN},
    {13, 1, HSV_GREEN}
);

const rgblight_segment_t PROGMEM layer_review[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, HSV_RED},
    {6, 4, HSV_RED},
    {14, 2, HSV_RED}
);

const rgblight_segment_t PROGMEM lock_caps[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_BLUE},
    {7, 2, HSV_BLUE},
    {15, 1, HSV_BLUE}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer_review,		//	0
    layer_function,		//	1
    layer_rgb,			//	2
    lock_caps			//	3
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(0, layer_state_cmp(state, 3));
    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(3, led_state.caps_lock);
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT_all(
					KC_ESC,		KC_1,		KC_2,		KC_3,		KC_4,		KC_5,		KC_6,		KC_7,		KC_8,		KC_9,		KC_0,		KC_MINS,	KC_EQL,		KC_BSPC,	KC_BSPC,
					KC_TAB,		KC_Q,		KC_W,		KC_E,		KC_R,		KC_T,		KC_Y,		KC_U,		KC_I,		KC_O,		KC_P,		KC_LBRC,	KC_RBRC,	KC_BSLS,
					KC_CAPS,	KC_A,		KC_S,		KC_D,		KC_F,		KC_G,		KC_H,		KC_J,		KC_K,		KC_L,		KC_SCLN,	KC_QUOT,				KC_ENT,		KC_ENT,
		KC_LSFT,	KC_LSFT,	KC_Z,		KC_X,		KC_C,		KC_V,		KC_B,		KC_N,		KC_M,		KC_COMM,	KC_DOT,		KC_SLSH,							KC_RSFT,	KC_RSFT,
					KC_LCTL,	KC_LGUI,	KC_LALT,													KC_SPC,								KC_RALT,	TT(1),		LT(1, KC_APP),		KC_RCTL),

	[1] = LAYOUT_all(
					KC_GRV,		KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_F5,		KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		KC_F11,		KC_F12,		KC_DEL,		KC_DEL,
					KC_TRNS,	KC_TRNS,	KC_UP,		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_PSCR,	KC_SLCK,	KC_PAUS,	KC_TRNS,
					KC_TRNS,	KC_LEFT,	KC_DOWN,	KC_RIGHT,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_INS,		KC_HOME,	KC_PGUP,				KC_TRNS,	KC_TRNS,
		KC_TRNS,	KC_TRNS,	KC_VOLU,	KC_VOLD,	KC_MUTE,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_DEL,		KC_END,		KC_PGDN,							KC_TRNS,	KC_TRNS,
					KC_TRNS,	KC_TRNS,	KC_TRNS,													KC_TRNS,							KC_TRNS,	KC_TRNS,	MO(2),		KC_TRNS),

	[2] = LAYOUT_all(
					KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
					BL_TOGG,	BL_DEC,		BL_INC,		BL_STEP,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
					RGB_TOG,	RGB_MOD,	RGB_HUI,	RGB_SAI,	RGB_VAI,	RGB_SPI,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,				KC_TRNS,	KC_TRNS,
		KC_TRNS,	KC_TRNS,	RGB_RMOD,	RGB_HUD,	RGB_SAD,	RGB_VAD,	RGB_SPD,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,							KC_TRNS,	KC_TRNS,
					KC_TRNS,	KC_TRNS,	KC_TRNS,													KC_TRNS,							KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS),

	[3] = LAYOUT_all(
					KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
					KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
					KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,				KC_TRNS,	KC_TRNS,
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,							KC_TRNS,	KC_TRNS,
					KC_TRNS,	KC_TRNS,	KC_TRNS,													KC_TRNS,							KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS),

};

