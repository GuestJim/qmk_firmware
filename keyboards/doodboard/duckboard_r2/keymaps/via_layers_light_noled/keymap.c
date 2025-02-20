/* Copyright 2020-2021 doodboard
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#define OBS_REC RALT(KC_F9)
//	Alt + F9	OBS Studio start and stop recording hotkey
#define OBS_BUF RALT(KC_F10)
//	Alt + F10	OBS Studio replay buffer save
#define OBS_MUT	RSFT(KC_PAUS)

/* RGB LEDs
*	,-------------------.
*	|		7	6		|
*	|					|
*	|	0			5	|
*	|					|
*	|	1			4	|
*	|					|
*	|		2	3		|
*	 `------------------'
*/

const rgblight_segment_t PROGMEM layer_nav_sym[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 8, HSV_GREEN}	//	Nav
);

const rgblight_segment_t PROGMEM layer_review[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 8, HSV_RED}
);

const rgblight_segment_t PROGMEM layer_ahk[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 8, HSV_ORANGE}
);

const rgblight_segment_t PROGMEM layer_rgb[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, HSV_RED},
    {2, 2, HSV_GREEN},
    {4, 2, HSV_BLUE},
    {6, 2, HSV_WHITE}
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
	[0] = LAYOUT(	//	Base - Number Pad
					OSL(1),	KC_PSLS,	KC_PAST,	KC_PMNS,
					KC_P7,	KC_P8,		KC_P9,		KC_PPLS,
					KC_P4,	KC_P5,		KC_P6,		KC_PPLS,
		KC_BTN3,	KC_P1,	KC_P2,		KC_P3,		KC_PENT,
		TG(2),		KC_P0,	OSL(1),		KC_PDOT,	KC_PENT),

	[1] = LAYOUT(	//	Nav
					KC_NLCK,	KC_LPRN,	KC_RPRN,	KC_CIRC,
					KC_INS,		KC_HOME,	KC_PGUP,	KC_HASH,
					KC_DEL,		KC_END,		KC_PGDN,	KC_DLR,
		TO(1),		KC_LCTL,	KC_UP,		KC_LSFT,	KC_PERC,
		TG(1),		KC_LEFT,	KC_DOWN,	KC_RGHT,	KC_AMPR),

	[2] = LAYOUT(	//	Review
					KC_BTN1,	KC_BTN2,	KC_NO,		KC_F12,
					KC_NO,		KC_SPC,		KC_NO,		OBS_BUF,
					KC_NO,		KC_NO,		KC_NO,		KC_NO,
		KC_NO,		KC_NO,		KC_NO,		OBS_MUT,	KC_PSCR,
		TG(2),		TT(4),		MO(3),		KC_NO,		OBS_REC),

	[3] = LAYOUT(	//	RGB
					KC_NO,		RGB_TOG,	RGB_MOD,	KC_NO,
					RGB_HUI,	RGB_SAI,	RGB_VAI,	KC_NO,
					RGB_HUD,	RGB_SAD,	RGB_VAD,	KC_NO,
		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,
		RESET,		KC_NO,		KC_TRNS,	KC_NO,		KC_NO),
	[4] = LAYOUT(	//	Macro
					OBS_REC,	OBS_MUT,	OBS_BUF,	KC_F12,	// so this can be used when recording/reviewing games
					KC_F13,		KC_F14,		KC_F15,		KC_F16,
					KC_F17,		KC_F18,		KC_F19,		KC_F20,
		KC_NO,		KC_F21,		KC_F22,		KC_F23,		KC_F24,
		KC_NO,		TT(4),		OSM(MOD_RSFT),	OSM(MOD_RCTL),	OSM(MOD_RALT)),
};

void encoder_update_user(uint8_t index, bool clockwise) {
	if (index == 0) { /* First encoder */
		// if (IS_LAYER_ON(0))	{}		so it will change with layer
		if (clockwise) {
			tap_code(KC_WH_D);
		} else {
			tap_code(KC_WH_U);
		}
}
}


#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }


// WPM-responsive animation stuff here
#define IDLE_FRAMES 2
#define IDLE_SPEED 40 // below this wpm value your animation will idle

#define ANIM_FRAME_DURATION 200 // how long each frame lasts in ms
// #define SLEEP_TIMER 60000 // should sleep after this period of 0 wpm, needs fixing
#define ANIM_SIZE 636 // number of bytes in array, minimize for adequate firmware size, max is 1024

uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;
uint8_t current_idle_frame = 0;

// Credit to u/Pop-X- for the initial code. You can find his commit here https://github.com/qmk/qmk_firmware/pull/9264/files#diff-303f6e3a7a5ee54be0a9a13630842956R196-R333.
static void render_anim(void) {
	static const char PROGMEM idle[IDLE_FRAMES][ANIM_SIZE] = {
		{
		0,	0,192,192,192,192,192,192,192,248,248, 30, 30,254,254,248,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	3,	3,	3,	3,	3,255,255,255,255,255,255,255,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,127,127,255,255,255,255,255,159,159,135,135,129,129,129, 97, 97, 25, 25,	7,	7,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1, 97, 97,127,	1,	1, 97, 97,127,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0
		},
		{
		0,	0,128,128,128,128,128,128,128,240,240, 60, 60,252,252,240,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	7,	7,	7,	7,	7,255,255,254,254,255,255,255,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,255,255,255,255,255,255,255, 63, 63, 15, 15,	3,	3,	3,195,195, 51, 51, 15, 15,	3,	3,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	3,	3, 99, 99,127,	3,	3, 99, 99,127,	3,	3,	0,	0,	0,	0,	0,	0,	0,	0,	0
		}
	};

	//assumes 1 frame prep stage
	void animation_phase(void) {
			current_idle_frame = (current_idle_frame + 1) % IDLE_FRAMES;
			oled_write_raw_P(idle[abs((IDLE_FRAMES-1)-current_idle_frame)], ANIM_SIZE);
	}

		if(timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
			anim_timer = timer_read32();
			animation_phase();
		}
	}

void oled_task_user(void) {
		render_anim();
		oled_set_cursor(0,6);
		oled_write_P(PSTR("DUCK\nBOARD\n"), false);
	oled_write_P(PSTR("-----\n"), false);
	// Host Keyboard Layer Status
	oled_write_P(PSTR("MODE\n"), false);
	oled_write_P(PSTR("\n"), false);

	switch (get_highest_layer(layer_state)) {
		case 0:
			oled_write_P(PSTR("BASE\n"), false);
			break;
		case 1:
			oled_write_P(PSTR("NAV\n"), false);
			break;
		case 2:
			oled_write_P(PSTR("REVIEW\n"), false);
			break;
		case 3:
			oled_write_P(PSTR("RGB\n"), false);
			break;
		case 4:
			oled_write_P(PSTR("MACRO\n"), false);
			break;
	}
}
#endif
