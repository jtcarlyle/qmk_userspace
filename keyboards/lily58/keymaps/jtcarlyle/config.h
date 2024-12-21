/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* Select hand configuration */

/* #define MASTER_LEFT */
#define MASTER_RIGHT
// #define EE_HANDS

#define QUICK_TAP_TERM 180 // tap term for tap then hold repeat
#define TAPPING_TERM 180
#define PERMISSIVE_HOLD
// #define TAPPING_FORCE_HOLD_PER_KEY

/* One shot modifier and layer keys */
#define ONESHOT_TAP_TOGGLE 5  /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 5000  /* Time (in ms) before the one shot key is released */

/* combo */
#define COMBO_TERM 50 // 80 default for mozc, gboards had 50

/* I don't even have rgb on this keyboard */
/* #undef RGBLED_NUM */
/* #define RGBLIGHT_EFFECT_BREATHING */
/* #define RGBLIGHT_EFFECT_RAINBOW_MOOD */
/* #define RGBLIGHT_EFFECT_RAINBOW_SWIRL */
/* #define RGBLIGHT_EFFECT_SNAKE */
/* #define RGBLIGHT_EFFECT_KNIGHT */
/* #define RGBLIGHT_EFFECT_CHRISTMAS */
/* #define RGBLIGHT_EFFECT_STATIC_GRADIENT */
/* #define RGBLIGHT_EFFECT_RGB_TEST */
/* #define RGBLIGHT_EFFECT_ALTERNATING */
/* #define RGBLIGHT_EFFECT_TWINKLE */
/* #define RGBLED_NUM 27 */
/* #define RGBLIGHT_LIMIT_VAL 120 */
/* #define RGBLIGHT_HUE_STEP 10 */
/* #define RGBLIGHT_SAT_STEP 17 */
/* #define RGBLIGHT_VAL_STEP 17 */
// steno stuff
// #define STENO_COMBINEDMAP

// Underglow
/*
  #undef RGBLED_NUM
  #define RGBLED_NUM 14    // Number of LEDs
  #define RGBLIGHT_SLEEP
*/