/* 
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
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

  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSPC,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                         KC_M,    KC_N,    KC_E,    KC_I,    KC_O, KC_ENT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, LGUI_T(KC_Z), LALT_T(KC_X), KC_C, KC_D, KC_K,                        KC_V,    KC_H, KC_COMM,  KC_DOT, KC_SLSH, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                      LCTL_T(KC_TAB), KC_SPC, MO(2),  MO(3), OSM(MOD_LSFT), OSL(1)
                                      //`--------------------------'  `--------------------------'

  ),

  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_CIRC, KC_TILD, KC_PLUS, KC_PIPE,  CBRACE,                      KC_RCBR, KC_UNDS, KC_EQL,  _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_PERC, KC_EXLM, KC_BSLS, KC_QUOT,  PARENS,                      KC_RPRN, KC_DQUO, KC_MINS, KC_HASH,   KC_AT, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_DLR,   KC_GRV, _______, KC_SCLN, BRACKETS,                     KC_RBRC, KC_COLN, KC_AMPR, KC_ASTR, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     _______, SGUI(KC_4), LGUI(KC_LBRC), KC_UP, LGUI(KC_RBRC), KC_HOME,            RESET, _______, _______, _______, _______, TBACKTICK,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_RSFT, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_LGUI, LALT(KC_LEFT), KC_DOWN, LALT(KC_RGHT), _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______, _______, _______, _______, _______,                      _______,    KC_7,    KC_8,    KC_9, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                         KC_0,    KC_4,    KC_5,    KC_6, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______,    KC_1,    KC_2,    KC_3, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [4] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC, S(KC_Q), S(KC_W), S(KC_F), S(KC_P), S(KC_B),                      S(KC_J), S(KC_L), S(KC_U), S(KC_Y), _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSPC, S(KC_A), S(KC_R), S(KC_S), S(KC_T), S(KC_G),                      S(KC_M), S(KC_N), S(KC_E), S(KC_I), S(KC_O), _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, S(KC_Z), S(KC_X), S(KC_C), S(KC_D), S(KC_V),                      S(KC_K), S(KC_H), S(KC_COMM), S(KC_DOT), S(KC_SLSH), _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                      _______, _______, _______,        _______, _______, _______
                                      //`--------------------------'  `--------------------------'

  ),
};
