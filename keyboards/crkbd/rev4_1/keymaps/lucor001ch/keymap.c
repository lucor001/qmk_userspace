/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

#include QMK_KEYBOARD_H
#include "layers.h"

//Chordal Hold handedness definition:
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
// 'L' = left hand, 'R' = right hand, '*' = exempt (e.g., thumb keys)
    LAYOUT_split_3x6_3_ex2(
        'L','L','L','L','L','L','L', 'R','R','R','R','R','R','R',
        'L','L','L','L','L','L','L', 'R','R','R','R','R','R','R',
        'L','L','L','L','L','L',         'R','R','R','R','R','R',
                        '*','*','*', '*','*','*' // thumbs exempt
    );

bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record,
                      uint16_t other_keycode, keyrecord_t* other_record) {
    // Exceptionally allow some one-handed chords for hotkeys.
    switch (tap_hold_keycode) {
        case LCTL_T(KC_Z):
            if (other_keycode == KC_C || other_keycode == KC_V) {
                return true;
            }
            break;

        case RCTL_T(KC_SLSH):
            if (other_keycode == KC_N) {
                return true;
            }
            break;
    }
    // Otherwise defer to the opposite hands rule.
    return get_chordal_hold_default(tap_hold_record, other_record);
}

// Enumerate all of the tap dance keys
enum {
  U_TD_BOOT,
#define KEYBOARD_X(LAYER, STRING) U_TD_U_##LAYER,
KEYBOARD_LAYER_LIST
#undef KEYBOARD_X
};

// Implement the boot tap dance
void u_td_fn_boot(tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    reset_keyboard();
  }
};

// Implement the remaining tap dances
#define KEYBOARD_X(LAYER, STRING) \
void u_td_fn_U_##LAYER(tap_dance_state_t *state, void *user_data) { \
if (state->count == 2) { \
  default_layer_set((layer_state_t)1 << U_##LAYER); \
} \
}
KEYBOARD_LAYER_LIST
#undef KEYBOARD_X

// Create the array of tap dance functions
tap_dance_action_t tap_dance_actions[] = {
  [U_TD_BOOT] = ACTION_TAP_DANCE_FN(u_td_fn_boot),
#define KEYBOARD_X(LAYER, STRING) [U_TD_U_##LAYER] = ACTION_TAP_DANCE_FN(u_td_fn_U_##LAYER),
KEYBOARD_LAYER_LIST
#undef KEYBOARD_X
};

// Map the redo/paste/copy/cut/undo functions
#define U_RDO C(KC_Y)
#define U_PST C(KC_V)
#define U_CPY C(KC_C)
#define U_CUT C(KC_X)
#define U_UND C(KC_Z)

// Keymap, leveraged Miryoku heavily but swapped action hand to right hand, updated for a Corne v4.1 3x6+2 keyboard

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//COLMAK-DH layout with home row special keys
    //Expanded Miryoku for this keyboard, adds outside columns and 4 keys in the middle
  [U_COLMAKDH] = LAYOUT_split_3x6_3_ex2(
  QK_GESC,               KC_Q,         KC_W,         KC_F,         KC_P,             KC_B,          QK_LLCK,            QK_LLCK,                KC_J,             KC_L,         KC_U,           KC_Y,               KC_SCLN, KC_BSPC,
   KC_TAB,       LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T),             KC_G,          QK_LOCK,            QK_LOCK,                KC_M,     RSFT_T(KC_N), RCTL_T(KC_E),   ALGR_T(KC_I),          RGUI_T(KC_O), KC_QUOT,
  KC_LSFT, MT(U_BUTTON, KC_Z), RALT_T(KC_X),         KC_C,         KC_D,             KC_V,                                                      KC_K,             KC_H,      KC_COMM, RALT_T(KC_DOT), MT(U_BUTTON, KC_SLSH), KC_RSFT,
//                                 CKC_ESC, CKC_TAB, CKC_ENT, CKC_SPC, CKC_BSPC, CKC_DEL
                                                       LT(U_SYM,KC_ESC), LT(U_NAV,KC_TAB), LT(U_NUM,KC_ENT), LT(U_MOUSE,KC_SPC), LT(U_MEDIA,KC_BSPC), LT(U_FUN,KC_DEL)
  ),
  [U_QWERTY] = LAYOUT_split_3x6_3_ex2(
  QK_GESC,                KC_Q,         KC_W,         KC_E,             KC_R,             KC_T,          QK_LLCK,            QK_LLCK,                 KC_Y,             KC_U,         KC_I,           KC_O,                  KC_P, KC_BSPC,
   KC_TAB,        LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D),     LSFT_T(KC_F),             KC_G,          QK_LOCK,            QK_LOCK,                 KC_H,     RSFT_T(KC_J), RCTL_T(KC_K),   ALGR_T(KC_L),       RGUI_T(KC_SCLN), KC_QUOT,
  KC_LSFT,  MT(U_BUTTON, KC_Z), RALT_T(KC_X),         KC_C,             KC_V,             KC_B,                                                       KC_N,             KC_M,      KC_COMM, RALT_T(KC_DOT), MT(U_BUTTON, KC_SLSH), KC_RSFT,
//                                 CKC_ESC, CKC_TAB, CKC_ENT, CKC_SPC, CKC_BSPC, CKC_DEL
                                                            LT(U_SYM,KC_ESC), LT(U_NAV,KC_TAB), LT(U_NUM,KC_ENT), LT(U_MOUSE,KC_SPC),  LT(U_MEDIA,KC_BSPC), LT(U_FUN,KC_DEL)
  ),
  [U_DVORAK] = LAYOUT_split_3x6_3_ex2(
   QK_GESC,               KC_QUOT,      KC_COMM,       KC_DOT,             KC_P,             KC_Y,          QK_LLCK,            QK_LLCK,                 KC_F,            KC_G,         KC_C,         KC_R,               KC_L, KC_BSPC,
    KC_TAB,          LGUI_T(KC_A), LALT_T(KC_O), LCTL_T(KC_E),     LSFT_T(KC_U),             KC_I,          QK_LOCK,            QK_LOCK,                 KC_D,    RSFT_T(KC_H), RCTL_T(KC_T), ALGR_T(KC_N),       RGUI_T(KC_S), KC_SLSH,
   KC_LSFT, MT(U_BUTTON, KC_SCLN), RALT_T(KC_Q),         KC_J,             KC_K,             KC_X,                                                       KC_B,            KC_M,         KC_W, RALT_T(KC_V), MT(U_BUTTON, KC_Z), KC_RSFT,
//                                        CKC_ESC, CKC_TAB, CKC_ENT, CKC_SPC, CKC_BSPC, CKC_DEL
                                                               LT(U_SYM,KC_ESC), LT(U_NAV,KC_TAB), LT(U_NUM,KC_ENT), LT(U_MOUSE,KC_SPC),  LT(U_MEDIA,KC_BSPC), LT(U_FUN,KC_DEL)
  ),
  [U_SYM] = LAYOUT_split_3x6_3_ex2(
  QK_GESC, TD(U_TD_BOOT), TD(U_TD_U_TAP), TD(U_TD_U_QWERTY), TD(U_TD_U_COLMAKDH), TD(U_TD_U_DVORAK), QK_LLCK, QK_LLCK, KC_LBRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
   KC_TAB,       KC_LGUI,        KC_LALT,           KC_LCTL,             KC_LSFT,             KC_NO, QK_LOCK, QK_LOCK, KC_SCLN,  KC_DLR, KC_PERC, KC_CIRC, KC_PLUS, KC_QUOT,
  KC_LSFT,         KC_NO,        KC_ALGR,    TD(U_TD_U_FUN),      TD(U_TD_U_SYM),             KC_NO,                   KC_TILD, KC_EXLM,   KC_AT, KC_HASH, KC_PIPE, KC_RSFT,
                                                                           KC_NO,             KC_NO,   KC_NO, KC_LPRN, KC_RPRN, KC_UNDS
  ),
  [U_NAV] = LAYOUT_split_3x6_3_ex2(
   QK_GESC, TD(U_TD_BOOT), TD(U_TD_U_TAP), TD(U_TD_U_QWERTY), TD(U_TD_U_COLMAKDH), TD(U_TD_U_DVORAK), QK_LLCK, QK_LLCK,  KC_INS, KC_HOME,   KC_UP,  KC_END, KC_PGUP, KC_BSPC,
    KC_TAB,       KC_LGUI,        KC_LALT,           KC_LCTL,             KC_LSFT,             KC_NO, QK_LOCK, QK_LOCK, CW_TOGG, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_QUOT,
   KC_LSFT,         KC_NO,        KC_ALGR,  TD(U_TD_U_MEDIA),      TD(U_TD_U_NAV),             KC_NO,                     U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND, KC_RSFT,
                                                                            KC_NO,             KC_NO,   KC_NO,  KC_ENT, KC_BSPC,  KC_DEL
  ),
  [U_NUM] = LAYOUT_split_3x6_3_ex2(
  QK_GESC, TD(U_TD_BOOT), TD(U_TD_U_TAP), TD(U_TD_U_QWERTY), TD(U_TD_U_COLMAKDH), TD(U_TD_U_DVORAK), QK_LLCK, QK_LLCK, KC_LBRC,    KC_7, KC_8, KC_9, KC_RBRC, KC_BSPC,
   KC_TAB,       KC_LGUI,        KC_LALT,           KC_LCTL,             KC_LSFT,             KC_NO, QK_LOCK, QK_LOCK, KC_COLN,    KC_4, KC_5, KC_6,  KC_EQL, KC_QUOT,
  KC_LSFT,         KC_NO,        KC_ALGR,  TD(U_TD_U_MOUSE),      TD(U_TD_U_NUM),             KC_NO,                    KC_GRV,    KC_1, KC_2, KC_3, KC_BSLS, KC_RSFT,
                                                                           KC_NO,             KC_NO,   KC_NO,  KC_DOT,    KC_0, KC_MINS
  ),
  [U_MOUSE] = LAYOUT_split_3x6_3_ex2(
   QK_GESC, TD(U_TD_BOOT), TD(U_TD_U_TAP), TD(U_TD_U_QWERTY),  TD(U_TD_U_COLMAKDH), TD(U_TD_U_DVORAK), QK_LLCK, QK_LLCK,   KC_NO, MS_WHLL,   MS_UP, MS_WHLR, MS_WHLU, KC_BSPC,
    KC_TAB,       KC_LGUI,        KC_LALT,           KC_LCTL,              KC_LSFT,             KC_NO, QK_LOCK, QK_LOCK,   KC_NO, MS_LEFT, MS_DOWN, MS_RGHT, MS_WHLD, KC_QUOT,
   KC_LSFT,         KC_NO,        KC_ALGR,    TD(U_TD_U_NUM),     TD(U_TD_U_MOUSE),             KC_NO,                     U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND, KC_RSFT,
                                                                           MS_BTN3,           MS_BTN1, MS_BTN2,   KC_NO,   KC_NO,   KC_NO
  ),

  [U_MEDIA] = LAYOUT_split_3x6_3_ex2(
  QK_GESC, TD(U_TD_BOOT), TD(U_TD_U_TAP), TD(U_TD_U_QWERTY),  TD(U_TD_U_COLMAKDH), TD(U_TD_U_DVORAK), QK_LLCK, QK_LLCK, RM_TOGG, RM_NEXT, RM_HUEU, RM_SATU, RM_VALU, KC_BSPC,
   KC_TAB,       KC_LGUI,        KC_LALT,           KC_LCTL,              KC_LSFT,             KC_NO, QK_LOCK, QK_LOCK,   KC_NO, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_QUOT,
  KC_LSFT,         KC_NO,        KC_ALGR,    TD(U_TD_U_NAV),     TD(U_TD_U_MEDIA),             KC_NO,                   OU_AUTO,   KC_NO,   KC_NO,   KC_NO, AC_TOGG, KC_RSFT,
                                                                          KC_MSTP,           KC_MPLY, KC_MUTE,   KC_NO,   KC_NO,   KC_NO
  ),
  [U_FUN] = LAYOUT_split_3x6_3_ex2(
  QK_GESC, KC_F12, KC_F7, KC_F8,  KC_F9, KC_PSCR, QK_LLCK, QK_LLCK, TD(U_TD_BOOT), TD(U_TD_U_TAP), TD(U_TD_U_QWERTY), TD(U_TD_U_COLMAKDH), TD(U_TD_U_DVORAK), KC_BSPC,
  KC_CAPS, KC_F11, KC_F4, KC_F5,  KC_F6, KC_SCRL, QK_LOCK, QK_LOCK,         KC_NO,        KC_RSFT,          KC_RCTL,              KC_ALGR,           KC_RGUI, KC_QUOT,
  KC_LSFT, KC_F10, KC_F1, KC_F2,  KC_F3, KC_PAUS,                         KC_ALGR, TD(U_TD_U_FUN),   TD(U_TD_U_SYM),                KC_NO,           KC_RSFT,   KC_NO,
                                 KC_APP,  KC_SPC,  KC_TAB,   KC_NO,         KC_NO,          KC_NO
  ),
  [U_TAP] = LAYOUT_split_3x6_3_ex2(
  QK_GESC, KC_Q, KC_W, KC_F,   KC_P,   KC_B,  TD(U_TD_U_COLMAKDH),     TD(U_TD_BOOT),    KC_J,   KC_L,    KC_U,   KC_Y, KC_SCLN, KC_BSPC,
   KC_TAB, KC_A, KC_R, KC_S,   KC_T,   KC_G,    TD(U_TD_U_QWERTY), TD(U_TD_U_DVORAK),    KC_M,   KC_N,    KC_E,   KC_I,    KC_O, KC_QUOT,
  KC_LSFT, KC_Z, KC_X, KC_C,   KC_D,   KC_V,                                             KC_K,   KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                             KC_ESC, KC_TAB,               KC_ENT,            KC_SPC, KC_BSPC, KC_DEL
  ),
  [U_BUTTON] = LAYOUT_split_3x6_3_ex2(
  QK_GESC,   U_UND,   U_CUT,   U_CPY,   U_PST,   U_RDO, QK_LLCK, QK_LLCK,   U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND, KC_BSPC,
   KC_TAB, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,   KC_NO, QK_LOCK, QK_LOCK,   KC_NO, KC_RSFT, KC_RCTL, KC_ALGR, KC_RGUI, KC_QUOT,
  KC_LSFT,   U_UND,   U_CUT,   U_CPY,   U_PST,   U_RDO,                     U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND, KC_RSFT,
                                      MS_BTN3, MS_BTN1, MS_BTN2, MS_BTN2, MS_BTN1, MS_BTN3
  ),
};

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
  hsv_t hsv_g = {85, 255, 128}; //Green, max saturation, 50% brightness
  hsv_t hsv_b = {169, 255, 128}; //Blue, max saturation, 50% brightness
  hsv_t hsv_w = {0, 0, 255}; //White, max saturation, 100% brightness
  if (hsv_g.v > rgb_matrix_get_val()) {
    hsv_g.v = rgb_matrix_get_val();
  }
  if (hsv_b.v > rgb_matrix_get_val()) {
    hsv_b.v = rgb_matrix_get_val();
  }
  if (hsv_w.v > rgb_matrix_get_val()) {
    hsv_w.v = rgb_matrix_get_val();
  }
  rgb_t rgb_g = hsv_to_rgb(hsv_g);
  rgb_t rgb_b = hsv_to_rgb(hsv_b);
  rgb_t rgb_w = hsv_to_rgb(hsv_w);


  for (uint8_t i = led_min; i < led_max; i++) {
    uint8_t layer = get_highest_layer(layer_state|default_layer_state);
    switch(layer) {
        case U_QWERTY:
          rgb_matrix_set_color(i, rgb_g.r, rgb_g.g, rgb_g.b);
          break;
        case U_DVORAK:
          rgb_matrix_set_color(i, rgb_b.r, rgb_b.g, rgb_b.b);
          break;
        case U_NUM:
          RGB_MATRIX_INDICATOR_SET_COLOR(0, rgb_w.r, rgb_w.g, rgb_w.b); // Turn Number key white
          break;
        case U_NAV:
          RGB_MATRIX_INDICATOR_SET_COLOR(7, rgb_w.r, rgb_w.g, rgb_w.b); // Turn Number key white
          break;
        case U_SYM:
          RGB_MATRIX_INDICATOR_SET_COLOR(8, rgb_w.r, rgb_w.g, rgb_w.b); // Turn Number key white
          break;
        case U_MOUSE:
          RGB_MATRIX_INDICATOR_SET_COLOR(23, rgb_w.r, rgb_w.g, rgb_w.b); // Turn Number key white
          break;
        case U_MEDIA:
          RGB_MATRIX_INDICATOR_SET_COLOR(30, rgb_w.r, rgb_w.g, rgb_w.b); // Turn Number key white
          break;
        case U_FUN:
          RGB_MATRIX_INDICATOR_SET_COLOR(31, rgb_w.r, rgb_w.g, rgb_w.b); // Turn Number key white
          break;
        case U_BUTTON:
        //NOTE: This layer is implemented by SMTD which means it does not work with Layer Lock (QK_LLCK)
          RGB_MATRIX_INDICATOR_SET_COLOR(15, rgb_w.r, rgb_w.g, rgb_w.b); // Turn Number key white
          RGB_MATRIX_INDICATOR_SET_COLOR(38, rgb_w.r, rgb_w.g, rgb_w.b); // Turn Number key white
          break;
        case U_COLMAKDH:
        case U_TAP:
        default:
            break;
    }
  }
  if (host_keyboard_led_state().caps_lock) {
    RGB_MATRIX_INDICATOR_SET_COLOR(19, rgb_w.r, rgb_w.g, rgb_w.b); // Turn Caps Lock key white
  }
  if (host_keyboard_led_state().scroll_lock) {
    RGB_MATRIX_INDICATOR_SET_COLOR(2, rgb_w.r, rgb_w.g, rgb_w.b); // Turn Scroll Lock key white
  }
  return false;
}

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
};
#endif

// OLED
#ifdef OLED_ENABLE

// Rotate OLED
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_90;
}

//oled_rotation_t oled_init_user(oled_rotation_t rotation) {
//  if (!is_keyboard_master()) {
//      return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
//  }
//
//  return rotation;
//}

// Draw to OLED
bool oled_task_user() {
  if (is_keyboard_master()) {
    // Set cursor position
    oled_set_cursor(0, 1);

    // Switch on current active layer
    switch (get_highest_layer(layer_state)) {
        case U_COLMAKDH :
            oled_write("COLMAKDH Layer", false);
            break;
        case U_NUM :
            oled_write("Number Layer", false);
            break;
        case U_NAV :
            oled_write("Navigation Layer", false);
            break;
        case U_SYM :
            oled_write("Symbol Layer", false);
            break;
        case U_MOUSE :
            oled_write("Mouse Layer", false);
            break;
        case U_MEDIA :
            oled_write("Media Layer", false);
            break;
        case U_BUTTON :
            oled_write("Button Layer", false);
            break;
        case U_TAP :
            oled_write("Tap Layer", false);
            break;
        case U_QWERTY :
            oled_write("QWERTY Layer", false);
            break;
        case U_DVORAK :
            oled_write("DVORAK Layer", false);
            break;
    }
  }

  return false;
}

#endif

// Saving for later, how to change all keys to a specific color when a layer is selected
//case U_SYM:
//RGB_MATRIX_INDICATOR_SET_COLOR(8, 255, 255, 255); // Turn Number key white
////          for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
////              for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
////                  uint8_t index = g_led_config.matrix_co[row][col];
////
////                  if (index >= led_min && index < led_max && index != NO_LED &&
////                  keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
////                    rgb_matrix_set_color(index, RGB_GOLDENROD);
////                  }
////                  else if (index >= led_min && index < led_max && index != NO_LED &&
////                    keymap_key_to_keycode(layer, (keypos_t){col,row}) == KC_NO) {
////                    rgb_matrix_set_color(index, RGB_BLACK);
////                  }
////              }
////          }
//break;

//case U_BUTTON:
//for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
//  for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
//      uint8_t index = g_led_config.matrix_co[row][col];
//
//      if (index >= led_min && index < led_max && index != NO_LED &&
//      keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
//          rgb_matrix_set_color(index, RGB_PINK);
//      }
//      else if (index >= led_min && index < led_max && index != NO_LED &&
//        keymap_key_to_keycode(layer, (keypos_t){col,row}) == KC_NO) {
//        rgb_matrix_set_color(index, RGB_BLACK);
//      }
//  }
//}
//break;
