/* Copyright 2021 Shulin Huang <mumu@x-bows.com>
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
 */
#include QMK_KEYBOARD_H

enum layer_number {
  _DVORAK = 0,
  _QWERTY,
  _KANA,
  _NAV,
  _SYM,
  _FN,
};

enum custom_keycodes {
  // Unnamed kana layout
  // top row
  KN_JO = SAFE_RANGE,
  KN_NI,
  KN_HA,
  KN_TEN, // 、
  KN_JU,
  KN_TI,
  KN_SE,
  KN_KU,
  KN_KO,
  KN_O,

  // homerow
  KN_TA,
  KN_TE,
  KN_KA,
  KN_TO,
  KN_SA,
  KN_SU,
  KN_SI,
  KN_U,
  KN_I,
  KN_N, // ん

  // bottom row
  KN_RU,
  KN_WO,
  KN_MA,
  KN_MARU, // 。
  KN_NO,
  KN_RI,
  KN_NA,
  KN_KI,
  KN_TU,
  KN_Q, // っ
};


/* dual purpose mod/layer-tap keys */
#define ST_SPC  LSFT_T(KC_SPC)
#define ST_ENT  RSFT_T(KC_ENT)
#define NAV_TAB LT(_NAV, KC_TAB)
#define NAV_SPC LT(_NAV, KC_SPC)
#define SM_BSPC LT(_SYM, KC_BSPC)
#define AT_ESC  LALT_T(KC_ESC)
#define AT_MINS RALT_T(KC_MINS)

/* one shot modifiers */
#define OS_LSFT OSM(MOD_LSFT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_LALT OSM(MOD_LALT)
#define OS_LGUI OSM(MOD_LGUI)

/* combo definition marcos */
#include "g/keymap_combo.h" // must come after dual purpose definitions

/* base layer change */
#define DVORAK  DF(_DVORAK)
#define QWERTY  DF(_QWERTY)
#define KANA    DF(_KANA)

/* others, make some macros later */
#define DELWORD C(KC_BSPC)
#define NXTWORD C(KC_RGHT)
#define PRVWORD C(KC_LEFT)
#define NXTPARA C(KC_DOWN)
#define PRVPARA C(KC_UP)
#define ZOOMIN  C(KC_EQL)
#define ZOOMOUT C(KC_MINS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap VANILLA: (Base Layer) Default Layer
   *
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * | Esc |  F1  |  F2  |  F3  |  F4  |      F5  |  F6  |  F7  |  F8  |      F9  |  F10 |  F11 |  F12 |   Delete   |    Prtsc    |
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * |  ~  |     1   |   2   |   3   |   4   |    5      |       6    |    7    |    8   |   9  |   0  |   -  |  =  |  Backspace  |
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * | Tab |   Q    |    W   |   E  |   R  |   T  |            |    Y   |    U   |    I  |   O  |   P  |   [  |  ]  |   \  | PgUp |
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * | Ctl |   A   |   S   |   D  |   F  |   G  |      Bksp      |    H  |    J   |   K  |   L  |   ;  |  '"  |    Enter   | PgDn |
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * |Shift|   Z  |   X  |   C  |   V  |   B  |       Enter       |    N  |    M   |  ,  |   .  |  /?  | Shift|      |  Up |
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * |Ctrl | GUI |     Alter   |    Space   |   Ctrl   |   Shift   |     Space     |    Alter   |  FN  | Ctrl | Lft  |  Dn |  Rig |
   * |---------------------------------------------------------------------------------------------------------------------------------|
   */
  [_DVORAK] = LAYOUT(
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,   KC_F6,   KC_F7,   KC_F8,  KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,           KC_PSCR,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,                      KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,  KC_LBRC, KC_BSPC,
    KC_BSLS, KC_QUOT, KC_COMM, KC_DOT,  KC_P,   KC_Y,                      KC_F,   KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, KC_RBRC, KC_BSLS, KC_PGUP,
    AT_ESC,  KC_A,    KC_O,    KC_E,    KC_U,   KC_I,         KC_BSPC,     KC_D,   KC_H,    KC_T,    KC_N,    KC_S,    AT_MINS, KC_ENT,  KC_PGDN,
    KC_LGUI, KC_SCLN, KC_Q,    KC_J,    KC_K,   KC_X,         KC_ENT,      KC_B,   KC_M,    KC_W,    KC_V,    KC_Z,    KC_RGUI,          KC_UP,
    KC_LCTL, KC_LGUI, KC_LCTL,          ST_SPC,          NAV_TAB, SM_BSPC, ST_ENT,          KC_RCTL,          MO(_FN), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),
  [_QWERTY] = LAYOUT(
    KC_ESC,  KC_F1,   KC_F2, KC_F3,  KC_F4,  KC_F5, KC_F6,   KC_F7,   KC_F8,  KC_F9,  KC_F10, KC_F11,  KC_F12,   KC_DEL,           KC_PSCR,
    KC_GRV,  KC_1,    KC_2,  KC_3,   KC_4,   KC_5,                    KC_6,   KC_7,   KC_8,    KC_9,   KC_0,     KC_MINS, KC_EQL,  KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,  KC_E,   KC_R,   KC_T,                    KC_Y,   KC_U,   KC_I,    KC_O,   KC_P,     KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
    KC_CAPS, KC_A,    KC_S,  KC_D,   KC_F,   KC_G,       KC_BSPC,     KC_H,   KC_J,   KC_K,    KC_L,   KC_SCLN,  KC_QUOT, KC_ENT,  KC_PGDN,
    KC_LSFT, KC_Z,    KC_X,  KC_C,   KC_V,   KC_B,       KC_ENT,      KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLSH,  KC_RSFT,          KC_UP,
    KC_LCTL, KC_LGUI, KC_LALT,       KC_SPC,        KC_LCTL, KC_LSFT,  NAV_SPC,       KC_RALT,         MO(_FN),  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),
  [_KANA] = LAYOUT(
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,   KC_F6,   KC_F7,   KC_F8,  KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,           KC_PSCR,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,                      KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,  KC_LBRC, KC_BSPC,
    KC_BSLS, KN_JO,   KN_NI,   KN_HA,   KN_TEN, KN_JU,                     KN_TI,  KN_SE,   KN_KU,   KN_KO,   KN_O,    KC_SLSH, KC_RBRC, KC_BSLS, KC_PGUP,
    AT_ESC,  KN_TA,   KN_TE,   KN_KA,   KN_TO,  KN_SA,        KC_BSPC,     KN_SU,  KN_SI,   KN_U,    KN_I,    KN_N,    AT_MINS, KC_ENT,  KC_PGDN,
    KC_LGUI, KN_RU,   KN_WO,   KN_MA,   KN_NO,  KN_MARU,       KC_ENT,     KN_RI,  KN_NA,   KN_KI,   KN_TU,   KN_Q,    KC_RGUI,          KC_UP,
    KC_LCTL, KC_LGUI, KC_LCTL,          ST_SPC,          NAV_TAB, SM_BSPC, ST_ENT,          KC_RCTL,          MO(_FN), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),
  [_NAV] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______, _______,
    QWERTY,  KC_MPRV, KC_MPLY, DELWORD, KC_MNXT, _______,                   C(KC_Z), PRVWORD, KC_UP,   NXTWORD, C(KC_Y), ZOOMIN,  _______, _______, _______,
    DVORAK,  OS_LGUI, OS_LALT, OS_LCTL, OS_LSFT, _______,      _______,     KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  ZOOMOUT, _______, _______,
    KANA,    DVORAK,  C(KC_X), C(KC_C), C(KC_V), _______,      _______,     C(KC_F), NXTPARA, KC_PGUP, KC_PGDN, PRVPARA, KANA,             _______,
    _______, _______, _______,          _______,          _______, _______, KC_DEL,           _______,          _______, _______, _______, _______, _______),
  [_SYM] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, KC_LABK, KC_RABK, KC_ASTR, _______,                   KC_AMPR, KC_AT  , KC_LBRC, KC_RBRC, KC_CIRC, _______, _______, _______, _______,
    _______, KC_PLUS, KC_SLSH, KC_MINS, KC_EQL , KC_HASH,      _______,     KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_BSLS, _______, _______, _______,
    _______, KC_EXLM, KC_MUTE, KC_VOLD, KC_VOLU, _______,      _______,     KC_TILD, KC_DLR , KC_LCBR, KC_RCBR, _______, _______,          _______,
    _______, _______, _______,          KC_UNDS,          _______, _______, _______,          _______,          _______, _______, _______, _______, _______),
  [_FN] = LAYOUT(
    QK_BOOT,   KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_CALC,   KC_MYCM,  KC_MSEL,   KC_MAIL,   NK_TOGG,   EE_CLR,
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,             KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_NUM,
    RGB_TOG,   RGB_MOD, RGB_VAI, RGB_HUI,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_HOME,
    KC_TRNS,   RGB_SPD, RGB_VAD, RGB_SPI,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_END,
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_MUTE,   KC_VOLU,
    KC_TRNS,   KC_TRNS, KC_TRNS,           KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,            KC_TRNS,   KC_TRNS,  KC_MPLY,   KC_MPRV,   KC_VOLD,   KC_MNXT)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    // set_timelog();
    switch (keycode) {
      // kana macros
      case KN_MARU:    SEND_STRING(".");  break;
      case KN_SA:      SEND_STRING("sa"); break;
      case KN_TE:      SEND_STRING("te"); break;
      case KN_SE:      SEND_STRING("se"); break;
      case KN_RI:      SEND_STRING("ri"); break;
      case KN_TEN:     SEND_STRING(",");  break;
      case KN_JO:      SEND_STRING("xyo"); break;
      case KN_N:       SEND_STRING("nn"); break;
      case KN_KO:      SEND_STRING("ko"); break;
      case KN_O:       SEND_STRING("o");  break;
      case KN_KI:      SEND_STRING("ki"); break;
      case KN_KA:      SEND_STRING("ka"); break;
      case KN_NO:      SEND_STRING("no"); break;
      case KN_SI:      SEND_STRING("si"); break;
      case KN_TO:      SEND_STRING("to"); break;
      case KN_SU:      SEND_STRING("su"); break;
      case KN_TA:      SEND_STRING("ta"); break;
      case KN_U:       SEND_STRING("u");  break;
      case KN_I:       SEND_STRING("i");  break;
      case KN_KU:      SEND_STRING("ku"); break;
      case KN_TI:      SEND_STRING("ti"); break;
      case KN_HA:      SEND_STRING("ha"); break;
      case KN_NI:      SEND_STRING("ni"); break;
      case KN_MA:      SEND_STRING("ma"); break;
      case KN_WO:      SEND_STRING("wo"); break;
      case KN_JU:      SEND_STRING("xyu"); break;
      case KN_NA:      SEND_STRING("na"); break;
      case KN_Q:       SEND_STRING("xtu"); break;
      case KN_TU:      SEND_STRING("tu"); break;
      case KN_RU:      SEND_STRING("ru"); break;
    }
  }
  return true;
}
