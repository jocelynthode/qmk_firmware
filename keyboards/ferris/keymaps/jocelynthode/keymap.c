#include QMK_KEYBOARD_H
#include "enums.h"

// homerow mod-taps (aliases for readability + re-use in combo definitions)
#define HM_A    LALT_T(KC_A)
#define HM_S    LGUI_T(KC_S)
#define HM_D    LSFT_T(KC_D)
#define HM_F    LCTL_T(KC_F)
#define HM_J    RCTL_T(KC_J)
#define HM_K    RSFT_T(KC_K)
#define HM_L    RGUI_T(KC_L)
#define HM_SCLN LALT_T(KC_SCLN)


const uint16_t PROGMEM jk_combo[] = {HM_J, HM_K, COMBO_END};
const uint16_t PROGMEM cv_combo[] = {KC_C, KC_V, COMBO_END};
/*CW_TOGG*/
combo_t key_combos[] = {
    COMBO(jk_combo, KC_ESC),
    COMBO(cv_combo, KC_CAPS),
};

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT(
    'L', 'L', 'L', 'L', 'L',       'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L',       'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L',       'R', 'R', 'R', 'R', 'R',
                       '*', '*',  '*', '*'
);

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_BASE] = LAYOUT(
        KC_Q, KC_W, KC_E, KC_R, KC_T,       KC_Y, KC_U, KC_I,    KC_O,   KC_P,
        HM_A, HM_S, HM_D, HM_F, KC_G,       KC_H, HM_J, HM_K,    HM_L,   HM_SCLN,
        KC_Z, KC_X, KC_C, KC_V, KC_B,       KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
        LT(_NUM,KC_TAB), KC_SPC,  LT(_SYMBOL,KC_ENT), LT(_NAV,KC_BSPC)
    ),

	[_NUM] = LAYOUT(
        KC_F10, KC_F7, KC_F8, KC_F9, XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,     XXXXXXX,        XXXXXXX,
        KC_F11, KC_F4, KC_F5, KC_F6, XXXXXXX,       MS_LEFT,    MS_DOWN,    MS_UP,    MS_RGHT,    XXXXXXX,
        KC_F12, KC_F1, KC_F2, KC_F3, XXXXXXX,       MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, XXXXXXX,
                              _______, _______,   MS_BTN1, _______
    ),

	[_NAV] = LAYOUT(
        KC_KP_EQUAL, KC_7, KC_8, KC_9, XXXXXXX,      XXXXXXX, XXXXXXX,      XXXXXXX,    XXXXXXX,  XXXXXXX,
        KC_KP_PLUS,  KC_4, KC_5, KC_6, XXXXXXX,      KC_LEFT, KC_DOWN,      KC_UP,      KC_RIGHT, XXXXXXX,
        KC_KP_MINUS, KC_1, KC_2, KC_3, KC_N,       KC_HOME, KC_PAGE_DOWN, KC_PAGE_UP, KC_END,   XXXXXXX,
                                  _______, KC_0,    _______,_______
    ),

	[_MEDIA] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_MPRV,                  KC_MNXT,           XXXXXXX,             XXXXXXX, XXXXXXX, KC_PRINT_SCREEN,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BRIGHTNESS_UP,         KC_AUDIO_VOL_UP,   KC_MEDIA_PLAY_PAUSE, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BRIGHTNESS_DOWN,       KC_AUDIO_VOL_DOWN, KC_AUDIO_MUTE,       XXXXXXX, XXXXXXX, XXXXXXX,
                                                _______, _______,   _______,_______
    ),
	[_SYMBOL] = LAYOUT(
        KC_CIRC, RALT(KC_W), RALT(KC_E), KC_DLR,  KC_PERC,       RALT(KC_Y), KC_AMPR,    KC_ASTR,       KC_QUOT,      KC_GRV,
        KC_LCBR, RALT(KC_S), RALT(KC_D), KC_RCBR, KC_EQUAL,      KC_BSLS,    KC_PLUS,    RALT(KC_K),    RALT(KC_L),   KC_DQT,
        KC_TILD, KC_LBRC,    KC_RBRC,    KC_UNDS, RALT(KC_B),    KC_PIPE,    RALT(KC_M), RALT(KC_COMM), RALT(KC_DOT), RALT(KC_SLASH),
                                                 _______, _______,   _______,_______
    ),
};
// clang-format on

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

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HM_A:
        case HM_S:
        case HM_E:
        case HM_N:
        case HM_R:
        case HM_T:
        case HM_I:
        case HM_U:
            // Prevent accidental hold on same hand
            return TAPPING_TERM + 1250;
        default:
            return TAPPING_TERM;
    }
}

// Switch to ADJUST when layer LOWER and RAISE are on
layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _NUM, _NAV, _MEDIA);
}
