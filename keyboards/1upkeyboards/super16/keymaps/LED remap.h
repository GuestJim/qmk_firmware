/* Copyright 2018 MechMerlin
 * Copyright 2018 Logan Huskins
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
This file was made by GuestJim of Overclockers Club based on the original files the above covers.
While it works for him, there is no warranty or guarantee it will for anyone else
His article creating such custom keymap files:
	http://www.overclockersclub.com/reviews/cmk_qmk_via
 */

#pragma once

// place overrides here
#undef RGBLIGHT_ANIMATIONS
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_STATIC_GRADIENT

#define RGBLIGHT_LAYERS
#define RGBLIGHT_MAX_LAYERS 5
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF

	/* RGB LEDs
	*	,-------------------.
	*	|	0	1	2	3	|
	*	|					|
	*	|	7	6	5	4	|
	*	|					|
	*	|	8	9	10	11	|
	*	|					|
	*	|	15	14	13	12	|
	*	 `------------------'
	*/
#define RGB_LED_MAP	{0, 1, 2, 3,   7, 6, 5, 4,   8, 9, 10, 11,   15, 14, 13, 12}