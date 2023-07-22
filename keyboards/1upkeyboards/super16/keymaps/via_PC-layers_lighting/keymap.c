#include QMK_KEYBOARD_H

#define OBS_REC RALT(KC_F9)
//	Alt + F9	OBS Studio start and stop recording hotkey
#define OBS_BUF RALT(KC_F10)
//	Alt + F10	OBS Studio replay buffer save
#define OBS_MUT	RSFT(KC_PAUS)

	/* RGB LEDs
	*	,-------------------.
	*	|	0	1	2	3	|
	*	|					|
	*	|	7	6	5	4	|
	*	|					|
	*	|	x	x	x	x	|
	*	|					|
	*	|	x	x	x	x	|
	*	 `------------------'
	*/


const rgblight_segment_t PROGMEM layer_nav_sym[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_GREEN},	//	Nav
    {3, 1, HSV_GREEN},	//	Nav
    {4, 1, HSV_GREEN},	//	Nav
    {7, 1, HSV_GREEN}	//	Nav
);

const rgblight_segment_t PROGMEM layer_review[] = RGBLIGHT_LAYER_SEGMENTS(
	{0, 1, HSV_RED},
	{3, 1, HSV_RED},
	{4, 1, HSV_RED},
	{7, 1, HSV_RED}
);

const rgblight_segment_t PROGMEM layer_ahk[] = RGBLIGHT_LAYER_SEGMENTS(
	{0, 1, HSV_ORANGE},
	{3, 1, HSV_ORANGE},
	{4, 1, HSV_ORANGE},
	{7, 1, HSV_ORANGE}
);

const rgblight_segment_t PROGMEM layer_rgb[] = RGBLIGHT_LAYER_SEGMENTS(
	{0, 1, HSV_RED},
	{3, 1, HSV_GREEN},
	{4, 1, HSV_BLUE},
	{7, 1, HSV_WHITE}
);


const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
	// lock_num,			//	0
	layer_nav_sym,		//	1
	layer_review,		//	2
	layer_rgb,			//	3
	layer_ahk			//	4
);

void keyboard_post_init_user(void) {
//    Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
	//	first number is lighting layer (as shown above)
	//	second number is the keymap layer number
    rgblight_set_layer_state(0, layer_state_cmp(state, 1));
    rgblight_set_layer_state(1, layer_state_cmp(state, 2));
    rgblight_set_layer_state(2, layer_state_cmp(state, 3));
    rgblight_set_layer_state(3, layer_state_cmp(state, 4));
    return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    //	Number Pad
	[0] = LAYOUT_ortho_4x4(
        KC_7,	KC_8,	KC_9,	KC_PSLS,
        KC_4,	KC_5,	KC_6,	KC_PAST,
        KC_1,	KC_2,	KC_3,	KC_PMNS,
        KC_0,	OSL(1),	KC_DOT,	KC_PPLS
    ),

	//	Navigation and Symbols
    [1] = LAYOUT_ortho_4x4(
        KC_INS,		KC_HOME,	KC_PGUP,	KC_HASH,
        KC_DEL,		KC_END,		KC_PGDN,	KC_DLR,
        KC_NO,		KC_NO,		KC_NO,		KC_PERC,
        KC_NO,		KC_PENT,	TG(2),		KC_AMPR
    ),

	//	Review Macros
    [2] = LAYOUT_ortho_4x4(
        KC_BTN1,	KC_BTN2,	KC_NO,		KC_F12,
        KC_NO,		KC_SPC,		KC_NO,		OBS_BUF,
        KC_NO,		KC_NO,		OBS_MUT,	KC_PSCR,
        TT(4),		MO(3),		TG(2),		OBS_REC
    ),

	//	RGB Controls
    [3] = LAYOUT_ortho_4x4(
        RGB_MOD,	RGB_SPI,	RGB_HUI,	RGB_VAI,
        RGB_RMOD,	RGB_SPD,	RGB_HUD,	RGB_VAD,
        RESET,		KC_NO,		RGB_SAI,	KC_NO,
        RGB_TOG,	KC_TRNS,	RGB_SAD,	KC_NO
    ),

	//	AHK Macros through F13-F24 with OSM Modifiers
    [4] = LAYOUT_ortho_4x4(
        KC_F13,		KC_F14,		KC_F15,		KC_F16,
        KC_F17,		KC_F18,		KC_F19,		KC_F20,
        KC_F21,		KC_F22,		KC_F23,		KC_F24,
        TT(4),		OSM(MOD_RSFT),	OSM(MOD_RCTL),	OSM(MOD_RALT)
    ),

    [5] = LAYOUT_ortho_4x4(
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS
    ),

    [6] = LAYOUT_ortho_4x4(
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS
    ),

    [7] = LAYOUT_ortho_4x4(
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS
    ),

    [8] = LAYOUT_ortho_4x4(
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS
    ),

    [9] = LAYOUT_ortho_4x4(
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS
    ),

    [10] = LAYOUT_ortho_4x4(
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS
    ),

    [11] = LAYOUT_ortho_4x4(
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS
    ),

    [12] = LAYOUT_ortho_4x4(
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS
    ),

    [13] = LAYOUT_ortho_4x4(
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS
    ),

    [14] = LAYOUT_ortho_4x4(
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS
    ),

    [15] = LAYOUT_ortho_4x4(
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS
    ),

};


