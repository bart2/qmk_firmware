/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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

enum custom_keycodes {
    PARENS = SAFE_RANGE,
    CBRACE,
    BRACKETS,
    DQUOT,
    FREDIRECT,
    FBLOGS,
    BACKTICK,
    TBACKTICK,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case PARENS:
        if (record->event.pressed) {
            SEND_STRING("()"SS_TAP(X_LEFT));
        }
        break;
    case CBRACE:
        if (record->event.pressed) {
            SEND_STRING("{}"SS_TAP(X_LEFT));
        }
        break;
    case BRACKETS:
        if (record->event.pressed) {
            SEND_STRING("[]"SS_TAP(X_LEFT));
        }
        break;
    case TBACKTICK:
        if (record->event.pressed) {
            SEND_STRING("```");
            register_code(KC_LALT);
            SEND_STRING(SS_TAP(X_ENT));
            SEND_STRING(SS_TAP(X_ENT));
            unregister_code(KC_LALT);
            SEND_STRING("```" SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT));
        }
        break;
    }
    return true;
};

bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LGUI_T(KC_Z):
            return false;
        default:
            return true;
    }
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                                      KC_Y,    KC_U,    KC_I,    KC_O, _______, _______,
      KC_BSPC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                                      KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_ENT,				
      _______, LGUI_T(KC_B), LALT_T(KC_Z), KC_X, KC_C, KC_V, _______, _______,              _______, _______,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, _______,
                              _______, _______, LCTL_T(KC_TAB), KC_SPC, MO(2),                MO(3), OSM(MOD_LSFT), OSL(1), _______, _______
    ),

    [1] = LAYOUT(
      _______, KC_CIRC, KC_TILD, KC_PLUS, KC_PIPE,  CBRACE,                                                   KC_RCBR, KC_UNDS, KC_EQL,  _______, _______, _______,
      _______, KC_PERC, KC_EXLM, KC_BSLS, KC_QUOT,  PARENS,                                                   KC_RPRN, KC_DQUO, KC_MINS, KC_HASH,   KC_AT, _______,
      _______,  KC_DLR,  KC_GRV, _______, KC_P, BRACKETS, _______, _______,              _______, _______, KC_RBRC, LSFT(KC_P), KC_AMPR, KC_ASTR, _______, _______,
                                  _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______
    ),

    [2] = LAYOUT(
_______, SGUI(KC_4), LGUI(KC_LBRC), KC_UP, LGUI(KC_RBRC), KC_HOME,                                            _______, _______, _______, _______, _______, TBACKTICK,
LGUI(KC_Z), KC_RSFT, KC_LEFT, KC_DOWN, KC_RGHT,  KC_END,                                                      _______, _______, _______, _______, _______, _______,
_______, KC_LGUI, LALT(KC_LEFT), KC_DOWN, LALT(KC_RGHT), _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______,
                                       _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______
    ),

    [3] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                                   _______,    KC_7,    KC_8,    KC_9, _______, _______,
      _______, _______, _______, _______, _______, _______,                                                      KC_0,    KC_4,    KC_5,    KC_6, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______,               _______, _______, KC_LALT,    KC_1,    KC_2,    KC_3, KC_LGUI, _______,
                                 _______, _______, _______, _______, _______,               _______, _______, _______, _______, _______
    ),       
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};