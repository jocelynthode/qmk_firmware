#include QMK_KEYBOARD_H
#include "enums.h"
#include "keymap_ergol.h"

// homerow mod-taps (aliases for readability + re-use in combo definitions)
#define HM_A LALT_T(EL_A)
#define HM_S LGUI_T(EL_S)
#define HM_E LSFT_T(EL_E)
#define HM_N LCTL_T(EL_N)
#define HM_R RCTL_T(EL_R)
#define HM_T RSFT_T(EL_T)
#define HM_I RGUI_T(EL_I)
#define HM_U LALT_T(EL_U)


const uint16_t PROGMEM rt_combo[] = {HM_R, HM_T, COMBO_END};
const uint16_t PROGMEM cv_combo[] = {EL_C, EL_V, COMBO_END};
/*CW_TOGG*/
combo_t key_combos[] = {
    COMBO(rt_combo, KC_ESC),
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
        EL_Q, EL_C, EL_O, EL_P, EL_W,       EL_J, EL_M, EL_D,   EL_1DK, EL_Y,
        HM_A, HM_S, HM_E, HM_N, EL_F,       EL_L, HM_R, HM_T,   HM_I,   HM_U,
        EL_Z, EL_X, EL_MINS, EL_V, EL_B,    EL_DOT, EL_H, EL_G, EL_COMM, EL_K,
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
        QK_BOOTLOADER, QK_REBOOT, XXXXXXX, XXXXXXX,  KC_MPRV,                  KC_MNXT,           XXXXXXX,             XXXXXXX, XXXXXXX, KC_PRINT_SCREEN,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BRIGHTNESS_UP,         KC_AUDIO_VOL_UP,   KC_MEDIA_PLAY_PAUSE, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BRIGHTNESS_DOWN,       KC_AUDIO_VOL_DOWN, KC_AUDIO_MUTE,       XXXXXXX, XXXXXXX, XXXXXXX,
                                                _______, _______,   _______,_______
    ),
	[_SYMBOL] = LAYOUT(
        EL_CIRC, EL_LABK, EL_RABK, EL_DLR,  EL_PERC,       EL_AT,   EL_AMPR, EL_ASTR, EL_QUOT, EL_GRV,
        EL_LCBR, EL_LPRN, EL_RPRN, EL_RCBR, EL_EQL,  EL_BSLS, EL_PLUS, EL_MINS, EL_SLSH, EL_DQUO,
        EL_TILD, EL_LBRC, EL_RBRC, EL_UNDS, EL_HASH,       EL_PIPE, EL_EXLM, EL_SCLN, EL_COLN, EL_QUES,
                                                 _______, _______,   _______,_______
    ),
};
// clang-format on

uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t *record, uint16_t prev_keycode) {
    switch (keycode) {
        case HM_E:
        case HM_N:
        case HM_R:
        case HM_T:
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
            return TAPPING_TERM + 300;
        default:
            return TAPPING_TERM;
    }
}

// Switch to ADJUST when layer LOWER and RAISE are on
layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _NUM, _NAV, _MEDIA);
}
