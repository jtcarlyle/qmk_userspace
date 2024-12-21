#include QMK_KEYBOARD_H

#include "features/select_word.h"
// japanese map is poorly implemented
// #include "keymap_japanese.h"
#include "layout.h"

enum layer_number {
  _DVORAK = 0,
  _QWERTY,
  _KOUME,
  _NAV,
  _SYM,
};

enum custom_keycodes {
  SELWORD = SAFE_RANGE,
  // koume homerow
  KN_KO,
  KN_TA,
  KN_KA,
  KN_RU,
  KN_HA,
  KN_BIKI, // ー
  KN_N, // ん
  KN_I,
  KN_SI,
  KN_TO,
  // koume top row
  KN_TEN, // 。
  KN_NA,
  KN_TE,
  KN_SE,
  KN_SO,
  KN_MI,
  KN_O,
  KN_NO,
  KN_NI,
  KN_TOU, // 、
  // koume bottom row
  KN_YU,
  KN_XYU,
  KN_XYO,
  KN_RO,
  KN_XYA,
  KN_Q, // っ
  KN_U,
  KN_SU,
  KN_RA,
  KN_E
};

/* dual purpose mod/layer-tap keys */
#define ST_SPC  LSFT_T(KC_SPC)
#define ST_ENT  RSFT_T(KC_ENT)
// #define DV_SPC  LT(_DVORAK, KC_SPC)
// #define DV_ENT  LT(_DVORAK, KC_ENT)
#define NAV_TAB LT(_NAV, KC_TAB)
#define NAV_ENT LT(_NAV, KC_ENT)
#define SM_BSPC LT(_SYM, KC_BSPC)
#define AT_ESC  LALT_T(KC_ESC)
#define AT_MINS RALT_T(KC_MINS)
#define CT_RGHT LCTL_T(KC_RGHT)
#define CT_DOWN RCTL_T(KC_DOWN)
// #define GT_KANA LGUI_T(KC_F8)

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
#define KOUME   TO(_KOUME)

/* others, make some macros later */
#define DELWORD C(KC_BSPC)
#define NXTWORD C(KC_RGHT)
#define PRVWORD C(KC_LEFT)
#define HOME    KC_HOME
#define END     KC_END
#define NXTPARA C(KC_DOWN)
#define PRVPARA C(KC_UP)
#define REDO    C(KC_Y)
#define ZOOMIN  C(KC_EQL)
#define ZOOMOUT C(KC_MINS)
#define SFT_ENT S(KC_ENT)
#define SELLINE S(SELWORD)

/* language specific stuff */
// none of the language-specific keys work on Mac
// have to use other janky key bindings
// used for toggling IME, might need to change for Mac
// #define ZENHAN   KC_LNG5 // Zenkaku ↔ Hankaku ↔ Kanji (半角 ↔ 全角 ↔ 漢字)
// #define KANA     KC_INT2 // Katakana ↔ Hiragana ↔ Rōmaji (カタカナ ↔ ひらがな ↔ ローマ字)
// using F13 and F7 for input change and katakana since they are default in MS-IME and I'm lazy
// okay maybe F13 is not default
bool is_zh_active = false; // Chinese input is active

/* Tap dance */
// Tap Dance keycodes
enum td_keycodes {
    GEZ, // toggle English/Chinese on tap, right gui on hold
    GJK  // toggle Japanese/switch kana type on tap, left gui on hold
};

// Define a type containing as many tapdance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_SINGLE_TAP
} td_state_t;

// Create a global instance of the tapdance state type
static td_state_t td_state;

// Declare your tapdance functions:

// Function to determine the current tapdance state
td_state_t cur_dance(tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void altlp_finished(tap_dance_state_t *state, void *user_data);
void altlp_reset(tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base Layer DVORAK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   7  |   8  |   9  |   0  |   5  |                    |   6  |   1  |   2  |   3  |   4  |  =   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  \   |   "  |   ,  |   .  |   P  |   Y  |                    |   F  |   G  |   C  |   R  |   L  |  /   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  ESC |   A  |   O  |   E  |   U  |   I  |-------.    ,-------|   D  |   H  |   T  |   N  |   S  |  -   |
 * |------+------+------+------+------+------|  F11  |    |  F12  |------+------+------+------+------+------|
 * |  [   |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   B  |   M  |   W  |   V  |   Z  |  ]   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | Down |  Up  | Tab  | /  RET  /       \ SPC  \  | BKSPC |  <-  |  ->  |
 *                   |      | GUI  | EXT  |/ Shift /         \ Shift\ | EXT   | GUI  |      |
 *                   `----------------------------'           '------''--------------------'
 */
    [_DVORAK] = LAYOUT_LR(
      KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,
      KC_BSLS, KC_QUOT, KC_COMM, KC_DOT , KC_P   , KC_Y   ,
      AT_ESC , KC_A   , KC_O   , KC_E   , KC_U   , KC_I   ,
      TD(GJK), KC_SCLN, KC_Q   , KC_J   , KC_K   , KC_X   , KC_LBRC,
                                 KC_LEFT, CT_RGHT, ST_SPC , NAV_TAB,

               KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_EQL ,
               KC_F   , KC_G   , KC_C   , KC_R   , KC_L   , KC_SLSH,
               KC_D   , KC_H   , KC_T   , KC_N   , KC_S   , AT_MINS,
      KC_RBRC, KC_B   , KC_M   , KC_W   , KC_V   , KC_Z   , TD(GEZ),
      SM_BSPC, ST_ENT , CT_DOWN, KC_UP
    ),

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  [   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | CAPS |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   \   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | GUI  | LALT | Space | /CTRL  /       \ ESC  \  | Enter | RALT |  =  |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 *
 * For gaming and lending to others
 * Full keyboard functionality in a semi-sane usable layout
 * Note that ESC is where Capslock normally is. I hope that this
 * can be reprogrammed in games
 * need to change the tab layer-tap at some point
 *
 */
    [_QWERTY] = LAYOUT_LR(
      KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,
      KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,
      KC_CAPS, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,
      KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_BSLS,
                              KC_LGUI , KC_LALT  , KC_SPC , KC_LCTL,

               KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS,
               KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC,
               KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
      KC_RBRC, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
      SM_BSPC, NAV_ENT, KC_RALT, KC_EQL
    ),

/* Japanese layout
 * Trying out koume for now
 */

    [_KOUME] = LAYOUT_LR(
      KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,
      KC_BSLS, KN_TEN , KN_NA  , KN_TE  , KN_SE  , KN_SO  ,
      AT_ESC , KN_KO  , KN_TA  , KN_KA  , KN_RU  , KN_HA  ,
      TD(GJK), KN_YU  , KN_XYU , KN_XYO , KN_RO  , KN_XYA , KC_LBRC,
                                 KC_LEFT, CT_RGHT, ST_SPC , NAV_TAB,

               KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_EQL ,
               KN_MI  , KN_O   , KN_NO  , KN_NI  , KN_TOU , KN_NAKA,
               KN_BIKI, KN_N   , KN_I   , KN_SI  , KN_TO  , AT_MINS,
      KC_RBRC, KN_Q   , KN_U   , KN_SU  , KN_RA  , KN_E   , TD(GEZ),
      SM_BSPC, ST_ENT , CT_DOWN, KC_UP
    ),

/* NAV - Text editing/navigation layer
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |dmenu | IME  | ⌫w  |  ⌦w |      |                    | undo |  ←w  |   ↑  |  →w  | redo | zoom+|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | GUI  | Alt  | Ctrl |Shift |      |-------.    ,-------|  |←  |   ←  |   ↓  |   →  |  →|  | zoom-|
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |  cut | copy | paste|      |-------|    |-------| find | ←¶  | PgDn  | PgUp |  →¶  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \←find \  | find→ | Del |      |
 *                   |      |      |      |/       /         \      \ |       |     |      |
 *                   `----------------------------'           '------''--------------------'
 */
    [_NAV] = LAYOUT_LR(
      _______, _______, _______, _______, _______, _______,
      QWERTY , KC_MPRV, KC_MPLY, DELWORD, KC_MNXT, _______,
      DVORAK , OS_LGUI, OS_LALT, OS_LCTL, OS_LSFT, _______,
      KOUME  , _______, C(KC_X), C(KC_C), C(KC_V), _______, _______,
                                 _______, _______, _______, _______,

               _______, _______, SELWORD, _______, _______, _______,
               C(KC_Z), PRVWORD, KC_UP  , NXTWORD, REDO   , ZOOMIN ,
               HOME   , KC_LEFT, KC_DOWN, KC_RGHT, END    , ZOOMOUT,
      _______, C(KC_F), NXTPARA, KC_PGUP, KC_PGDN, PRVPARA, _______,
      KC_DEL , SELLINE, KC_PGDN, KC_PGUP
    ),

/* SYML - function keys and symbols on the left hand (intended for cross hand use)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |  F6  |  F1  | F2   |  F3   | F4   |     |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |   &  |   %  |  [   |   ]  |   ^  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | GUI  | ALT  | CTRL | SHIFT|      |-------.    ,-------|   |  |   :  |  (   |   )  |   \  |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      | UNDO | CUT  | COPY | PASTE|      |-------|    |-------|   ~  |  $   |  {   |  }   |  @  |       |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |       |     | /       /       \   _  \  |  DEL | HOME | END  |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
    [_SYM] = LAYOUT_LR(
       _______, KC_F1  , KC_F2  , KC_F3  , KC_F4 , KC_F5  ,
       _______, _______, KC_LABK, KC_RABK, KC_ASTR, _______,
       _______, KC_PLUS, KC_SLSH, KC_MINS, KC_EQL , KC_HASH,
       _______, KC_EXLM, KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_F11 ,
                                  HOME   , END    , SELWORD, KC_UNDS,

                         KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , _______,
                         KC_AMPR, KC_AT  , KC_LBRC, KC_RBRC, KC_CIRC, _______,
                         KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_BSLS, _______,
                KC_F12 , KC_TILD, KC_DLR , KC_LCBR, KC_RCBR, _______, _______,
                _______ , _______, _______, _______
    ),

/* SYMR - function keys and symbols on the left hand (intended for cross hand use)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |       |     |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |  <   |  >   |  *   |      |                    |      |      |  DVO | QWE  |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  +   |  /   |  -   |  =   |      |-------.    ,-------|      | SHIFT| CTRL |  ALT | GUI  |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |  !   | Mute | Vol- | Vol+ |      |-------|    |-------|      | Prev | Play | Stop | Next |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | PgDn  | PgUp |     | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

};

// Determine the tapdance state to return
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }

    if (state->count == 2) return TD_DOUBLE_SINGLE_TAP;
    else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

// Handle the possible states for each tapdance keycode you define:
void enzh_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            // switch to EN from ZH or JA
            if (is_zh_active || IS_LAYER_ON(_KOUME)) {
                is_zh_active = false;
                register_code16(S(KC_F5));
            }
            // otherwise switch to ZH from EN
            else {
                is_zh_active = true;
                register_code16(S(KC_F6));
            }
            layer_move(_DVORAK);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_RGUI));
            break;
        case TD_DOUBLE_SINGLE_TAP: // Switch to ZH from JA/ZH
            // switch to ZH from JA
            if (IS_LAYER_ON(_KOUME)) {
                is_zh_active = true;
                register_code16(S(KC_F6));
                layer_move(_DVORAK);
            }
            // don't need to do anything from ZH and EN
            break;
        default:
            break;
    }
}

void enzh_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            if (is_zh_active) unregister_code16(S(KC_F6));
            else unregister_code16(S(KC_F5));
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_RGUI));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            if (is_zh_active) unregister_code16(S(KC_F6));
            break;
        default:
            break;
    }
}

void jakn_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            if (IS_LAYER_ON(_KOUME)) tap_code16(S(KC_F8));
            else {
                layer_move(_KOUME);
                tap_code16(S(KC_F7));
            }
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LGUI));
            break;
        case TD_DOUBLE_SINGLE_TAP: // Switch to JA and press kana key
            if (!IS_LAYER_ON(_KOUME)) {
                layer_move(_KOUME);
                tap_code16(S(KC_F7));
            }
            register_code16(S(KC_F8));
            break;
        default:
            break;
    }
}

void jakn_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LGUI));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(S(KC_F8));
            break;
        default:
            break;
    }
}

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
tap_dance_action_t tap_dance_actions[] = {
    [GEZ] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, enzh_finished, enzh_reset),
    [GJK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, jakn_finished, jakn_reset)
};

/* layer_state_t layer_state_set_user(layer_state_t state) {
 *   return update_tri_layer_state(state, _FUN, _NAV, _ADJUST);
 * }
 */

// I don't use any of this junk since my OLED's don't work
//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_select_word(keycode, record, SELWORD)) { return false; }
  if (record->event.pressed) {
#ifdef OLED_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
    switch (keycode) {
      // kana macros
      case KN_TEN:     SEND_STRING(".");  break;
      case KN_NA:      SEND_STRING("na"); break;
      case KN_TE:      SEND_STRING("te"); break;
      case KN_SE:      SEND_STRING("se"); break;
      case KN_SO:      SEND_STRING("so"); break;
      case KN_MI:      SEND_STRING("mi"); break;
      case KN_O:       SEND_STRING("o"); break;
      case KN_NO:      SEND_STRING("no"); break;
      case KN_NI:      SEND_STRING("ni"); break;
      case KN_TOU:     SEND_STRING(","); break;
      case KN_KO:      SEND_STRING("ko"); break;
      case KN_TA:      SEND_STRING("ta"); break;
      case KN_KA:      SEND_STRING("ka"); break;
      case KN_RU:      SEND_STRING("ru"); break;
      case KN_HA:      SEND_STRING("ha"); break;
      case KN_BIKI:    SEND_STRING("-"); break;
      case KN_N:       SEND_STRING("nn"); break;
      case KN_I:       SEND_STRING("i"); break;
      case KN_SI:      SEND_STRING("si"); break;
      case KN_TO:      SEND_STRING("to"); break;
      case KN_YU:      SEND_STRING("yu"); break;
      case KN_XYU:     SEND_STRING("xyu"); break;
      case KN_XYO:     SEND_STRING("xyo"); break;
      case KN_RO:      SEND_STRING("ro"); break;
      case KN_XYA:     SEND_STRING("xya"); break;
      case KN_Q:       SEND_STRING("xtu"); break;
      case KN_U:       SEND_STRING("u"); break;
      case KN_SU:      SEND_STRING("su"); break;
      case KN_RA:      SEND_STRING("ra"); break;
      case KN_E:       SEND_STRING("e"); break;
    }
  }
  return true;
}

void matrix_scan_user(void) {
  select_word_task();
}
