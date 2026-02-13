#include QMK_KEYBOARD_H
#include "enums.h"
#include "lufa.h"

// homerow mod-taps (aliases for readability + re-use in combo definitions)
#define HM_A    LALT_T(KC_A)
#define HM_S    LGUI_T(KC_S)
#define HM_D    LSFT_T(KC_D)
#define HM_F    LCTL_T(KC_F)
#define HM_J    RCTL_T(KC_J)
#define HM_K    RSFT_T(KC_K)
#define HM_L    RGUI_T(KC_L)
#define HM_SCLN LALT_T(KC_SCLN)

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT(
    'L', 'L', 'L', 'L', 'L', 'L',                    'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L',                    'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L',                    'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L', 'L',      'R',     'R', 'R', 'R', 'R', 'R', 'R',
              '*', '*', '*', '*',                   '*', '*', '*', '*'
);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      | ESC  |LOWER | /TAB    /       \Enter \  | RAISE  | Del  |      |
 *                   |      |      |Space |/Shift  /         \Ralt  \ | BackSp |      |      |
 *                   `----------------------------'           '------''----------------------'
 */
[_QWERTY] = LAYOUT(
  XXXXXXX,  XXXXXXX,   XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX,                      XXXXXXX,   XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX,     TG(_GAMING),
  XXXXXXX,  KC_Q,   KC_W,   KC_E,    KC_R,    KC_T,                      KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,     XXXXXXX,
  XXXXXXX,  HM_A,   HM_S,   HM_D,    HM_F,    KC_G,                      KC_H,   HM_J,   HM_K,    HM_L,    HM_SCLN,  XXXXXXX,
  XXXXXXX,  KC_Z,   KC_X,   KC_C,    KC_V,    KC_B, XXXXXXX,    XXXXXXX, KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,  XXXXXXX,
    XXXXXXX, KC_ESC, LT(_NUM,KC_TAB), KC_SPC,             LT(_SYMBOL, KC_ENT), LT(_NAV,KC_BSPC), KC_DEL, XXXXXXX
),
[_GAMING] = LAYOUT(
KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
KC_LSFT, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
KC_LCTL,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, XXXXXXX,  XXXXXXX,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                    KC_LALT, KC_LGUI, MO(_NUM), KC_SPC, KC_ENT, MO(_NAV), KC_BSPC, TG(_GAMING)
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   -  |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |   _  |   +  |   {  |   }  |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      | ESC  |LOWER | /TAB    /       \Enter \  | RAISE  | Del  |      |
 *                   |      |      |Space |/Shift  /         \Ralt  \ | BackSp |      |      |
 *                   `----------------------------'           '------''----------------------'
 */
[_NUM] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_F10, KC_F7, KC_F8, KC_F9, XXXXXXX,                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_F11, KC_F4, KC_F5, KC_F6, XXXXXXX,                         KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_F12, KC_F1, KC_F2, KC_F3, XXXXXXX, XXXXXXX,       XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END, XXXXXXX, XXXXXXX,
                        _______, _______, _______,  _______,     KC_DEL,  LT(_NAV, KC_ENT), KC_BSPC, _______
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | PG_UP|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |-------.    ,-------| Left | Down |  Up  |Right |      |PG_DWN|
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |-------|    |-------|   +  |   -  |   =  |   [  |   ]  |   \  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      | ESC  |LOWER | /TAB    /       \Enter \  | RAISE  | Del  |      |
 *                   |      |      |Space |/Shift  /         \Ralt  \ | BackSp |      |      |
 *                   `----------------------------'           '------''----------------------'
 */

[_NAV] = LAYOUT(
  XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX,  KC_KP_EQUAL,    KC_7,    KC_8,    KC_9,    XXXXXXX,                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX,  KC_KP_PLUS,    KC_4,    KC_5,    KC_6,    XXXXXXX,                         KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, XXXXXXX, XXXXXXX,
  XXXXXXX,  KC_KP_MINUS,    KC_1,    KC_2,    KC_3,    KC_N, XXXXXXX,       XXXXXXX, KC_HOME, KC_PAGE_DOWN, KC_PAGE_UP, KC_END, XXXXXXX, XXXXXXX,
                                     _______, _______, LT(_NUM,KC_0),  _______,               _______,  _______, _______, _______
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | RESET|      |      |      |      |TG(_GAMING)|               |      |      |      |      |      |PRNTSC|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |TRCKPS|      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |BRTUP |-------.    ,-------| VOLUP|      |      |      |      |      |
 * |------+------+------+------+------+------|TRACKPR|    |TRACKFW|------+------+------+------+------+------|
 * |      |      |      |      |      |BRTDWN|-------|    |-------|VOLDWN| MUTE |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      | ESC  |LOWER | /TAB    /       \Enter \  | RAISE  | Del  |      |
 *                   |      |      |Space |/Shift  /         \Ralt  \ | BackSp |      |      |
 *                   `----------------------------'           '------''----------------------'
 */
[_MEDIA] = LAYOUT(
  QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                             XXXXXXX,           XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX,KC_PRINT_SCREEN,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                           XXXXXXX,           XXXXXXX,       XXXXXXX, XXXXXXX, KC_MEDIA_PLAY_PAUSE, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BRIGHTNESS_UP,                                           KC_AUDIO_VOL_UP,   XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX,             XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BRIGHTNESS_DOWN, KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK, KC_AUDIO_VOL_DOWN, KC_AUDIO_MUTE, XXXXXXX, XXXXXXX, XXXXXXX,             KC_PRINT_SCREEN,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  ),
[_SYMBOL] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                 XXXXXXX,XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,
    XXXXXXX,KC_CIRC, RALT(KC_W), RALT(KC_E), KC_DLR,  KC_PERC,             RALT(KC_Y),   KC_AMPR, KC_ASTR, KC_QUOT, KC_GRV,XXXXXXX,
    XXXXXXX,KC_LCBR, RALT(KC_S), RALT(KC_D), KC_RCBR, KC_EQUAL,                 KC_BSLS, KC_PLUS, RALT(KC_K), RALT(KC_L), KC_DQT,XXXXXXX,
    XXXXXXX,KC_TILD, KC_LBRC, KC_RBRC, KC_UNDS, RALT(KC_B),XXXXXXX,    XXXXXXX,KC_PIPE, RALT(KC_M), RALT(KC_COMM), RALT(KC_DOT), RALT(KC_SLASH),XXXXXXX,
                         _______, _______, _______, _______,        _______,  _______, _______, _______
  ),
};

uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t *record, uint16_t prev_keycode) {
    switch (keycode) {
        case HM_D:
        case HM_K:
            return 0;
    }

    if (is_flow_tap_key(keycode) && is_flow_tap_key(prev_keycode)) {
        return FLOW_TAP_TERM;
    }

    return 0;
}

/* uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t* record) {
  switch (keycode) {
    case HM_J:
    case HM_K:
    case HM_L:
    case HM_SCLN:
      return QUICK_TAP_TERM;  // Enable key repeating.
    default:
      return 0;  // Otherwise, force hold and disable key repeating.
  }
} */

/* uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(_NUM,KC_TAB):
        case LT(_NAV,KC_BTN2):
        case LT(_NAV,KC_BSPC):
            return TAPPING_TERM - 600;
        default:
            return TAPPING_TERM;
    }
} */
// Switch to ADJUST when layer LOWER and RAISE are on
layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _NUM, _NAV, _MEDIA);
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

static void print_logo_narrow(void) {
    oled_set_cursor(0, 14);
    oled_write("LILY58", false);
}

static void print_status_narrow(void) {
    /* Print current mode */
    // oled_set_cursor(0, 0);
    // oled_write_raw_P(tux_logo, sizeof(tux_logo));
    oled_set_cursor(0, 0);
    /* Print current layer */
    oled_write("LAYER", false);

    oled_set_cursor(0, 2);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write("Base ", false);
            break;
        case _NUM:
            oled_write("Num  ", false);
            break;
        case _NAV:
            oled_write("Nav  ", false);
            break;
        case _MEDIA:
            oled_write("Media", false);
            break;
        case _GAMING:
            oled_write("Game ", false);
            break;
        default:
            oled_write("Undef", false);
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_270;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        print_logo_narrow();
    }
    return false;
}
#endif // OLED_ENABLE
