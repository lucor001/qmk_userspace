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

// Define custom keycodes for the home row mods
enum custom_keycodes {
    SMTD_KEYCODES_BEGIN = SAFE_RANGE,
    // reads as C(ustom) + KC_A, but you may give any name here
    //Colmak-DH Home row mods
    CKC_AC,
    CKC_RC,
    CKC_SC,
    CKC_TC,
    CKC_NC,
    CKC_EC,
    CKC_IC,
    CKC_OC,
    //QWERTY Home row mods
    CKC_AQ,
    CKC_SQ,
    CKC_DQ,
    CKC_FQ,
    CKC_JQ,
    CKC_KQ,
    CKC_LQ,
    CKC_SCLNQ,
    //Dvorak Home row mods
    CKC_AD,
    CKC_OD,
    CKC_ED,
    CKC_UD,
    CKC_HD,
    CKC_TD,
    CKC_ND,
    CKC_SD,
    //non-homerow keys colmak
    CKC_ZC,
    CKC_XC,
    CKC_DOTC,
    CKC_SLSHC,
    //non-homerow keys colmak
    CKC_ZQ,
    CKC_XQ,
    CKC_DOTQ,
    CKC_SLSHQ,
    //non-homerow keys dvorak
    CKC_SCLND,
    CKC_QD,
    CKC_VD,
    CKC_ZD,
    //thumb keys //Not Used
//    CKC_ESC,
//    CKC_TAB,
//    CKC_ENT,
//    CKC_SPC,
//    CKC_BSPC,
//    CKC_DEL,
    SMTD_KEYCODES_END,
};

//This doesn't match their instructions for v0.5.4, but I couldn't get it to compile as process_smtd is now defined in the c file not the header file.
//Something seems fishy about this but I couldn't sort it out without just including the c file instead (header usually should be sufficient).
//#include "sm_td.h"
//bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//  if (!process_smtd(keycode, record)) return false;
//
//  //Attempt to make SM_TD_LT compatible with QK_LLCK, but this doesn't work
////  switch (keycode) {
////    case QK_LLCK:
////        if (record->event.pressed) {
////          // Toggle the lock on the highest layer.
////          layer_lock_invert(get_highest_layer(layer_state));
////          return false;
////        }
////      break;
////    }
//
//
//  return true;
//}

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

// SM Tap Dance feature to implement the home row mods
smtd_resolution on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
// void on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
  switch (keycode) {
    // Here is another attempt to get layer lock working with SM_TD, currently unconfirmed:
//    case QK_LLCK: {
//      switch (action) {
//          case SMTD_ACTION_TOUCH:
//              break; // Not used
//          case SMTD_ACTION_TAP:
//              layer_lock_invert(get_highest_layer(layer_state));
//              break;
//          case SMTD_ACTION_HOLD:
//              break; // Not used
//          case SMTD_ACTION_RELEASE:
//              break; // Not used
//      } // end of switch (action)
//        return SMTD_RESOLUTION_DETERMINED;
//    } // end of case CUSTOM_KEYCODE_1

    //COLMAK-DH Home Row Mods
    SMTD_MT_ON_MKEY(CKC_AC, KC_A, KC_LEFT_GUI, 2)
    SMTD_MT_ON_MKEY(CKC_RC, KC_R, KC_LEFT_ALT, 2)
    SMTD_MT_ON_MKEY(CKC_SC, KC_S, KC_LEFT_CTRL, 2)
    SMTD_MT_ON_MKEY(CKC_TC, KC_T, KC_LSFT, 2)
    SMTD_MT_ON_MKEY(CKC_NC, KC_N, KC_LSFT, 2)
    SMTD_MT_ON_MKEY(CKC_EC, KC_E, KC_LEFT_CTRL, 2)
    SMTD_MT_ON_MKEY(CKC_IC, KC_I, KC_ALGR, 2)
    SMTD_MT_ON_MKEY(CKC_OC, KC_O, KC_LEFT_GUI, 2)
    //QWERTY Home Row Mods
//        SMTD_MT(CKC_A, KC_A, KC_LEFT_GUI)
    SMTD_MT_ON_MKEY(CKC_AQ, KC_A, KC_LEFT_GUI, 2)
    SMTD_MT_ON_MKEY(CKC_SQ, KC_S, KC_LEFT_ALT, 2)
    SMTD_MT_ON_MKEY(CKC_DQ, KC_D, KC_LEFT_CTRL, 2)
    SMTD_MT_ON_MKEY(CKC_FQ, KC_F, KC_LSFT, 2)
    SMTD_MT_ON_MKEY(CKC_JQ, KC_J, KC_LSFT, 2)
    SMTD_MT_ON_MKEY(CKC_KQ, KC_K, KC_LEFT_CTRL, 2)
    SMTD_MT_ON_MKEY(CKC_LQ, KC_L, KC_ALGR, 2)
    SMTD_MT_ON_MKEY(CKC_SCLNQ, KC_SCLN, KC_LEFT_GUI, 2)
    //Dvorak Home Row Mods
//      SMTD_MT(CKC_A, KC_A, KC_LEFT_GUI, 2)
    SMTD_MT_ON_MKEY(CKC_AD, KC_A, KC_LEFT_GUI, 2)
    SMTD_MT_ON_MKEY(CKC_OD, KC_O, KC_LEFT_ALT, 2)
    SMTD_MT_ON_MKEY(CKC_ED, KC_E, KC_LEFT_CTRL, 2)
    SMTD_MT_ON_MKEY(CKC_UD, KC_U, KC_LSFT, 2)
    SMTD_MT_ON_MKEY(CKC_HD, KC_H, KC_LSFT, 2)
    SMTD_MT_ON_MKEY(CKC_TD, KC_T, KC_LEFT_CTRL, 2)
    SMTD_MT_ON_MKEY(CKC_ND, KC_N, KC_ALGR, 2)
    SMTD_MT_ON_MKEY(CKC_SD, KC_S, KC_LEFT_GUI, 2)
    //Non homerow keys colmak
    SMTD_LT_ON_MKEY(CKC_ZC, KC_Z, U_BUTTON, 2)
    SMTD_LT_ON_MKEY(CKC_XC, KC_X, KC_RIGHT_ALT, 2)
    SMTD_LT_ON_MKEY(CKC_DOTC, KC_DOT, KC_RIGHT_ALT, 2)
    SMTD_LT_ON_MKEY(CKC_SLSHC, KC_SLSH, U_BUTTON, 2)
    //Non homerow keys qwerty
    SMTD_LT_ON_MKEY(CKC_ZQ, KC_Z, U_BUTTON, 2)
    SMTD_LT_ON_MKEY(CKC_XQ, KC_X, KC_RIGHT_ALT, 2)
    SMTD_LT_ON_MKEY(CKC_DOTQ, KC_DOT, KC_RIGHT_ALT, 2)
    SMTD_LT_ON_MKEY(CKC_SLSHQ, KC_SLSH, U_BUTTON, 2)
    //Non homerow keys dvorak
    SMTD_LT_ON_MKEY(CKC_SCLND, KC_SCLN, U_BUTTON, 2)
    SMTD_LT_ON_MKEY(CKC_QD, KC_Q, KC_RIGHT_ALT, 2)
    SMTD_LT_ON_MKEY(CKC_VD, KC_V, KC_RIGHT_ALT, 2)
    SMTD_LT_ON_MKEY(CKC_ZD, KC_Z, U_BUTTON, 2)
    //Thumb keys (Not Used because these are not compatible with Layer Lock function)
//    SMTD_LT_ON_MKEY(CKC_ESC, KC_ESC, U_SYM, 2)
//    SMTD_LT_ON_MKEY(CKC_TAB, KC_TAB, U_NAV, 2)
//    SMTD_LT_ON_MKEY(CKC_ENT, KC_ENT, U_NUM, 2)
//    SMTD_LT_ON_MKEY(CKC_SPC, KC_SPC, U_MOUSE, 2)
//    SMTD_LT_ON_MKEY(CKC_BSPC, KC_BSPC, U_MEDIA, 2)
//    SMTD_LT_ON_MKEY(CKC_DEL, KC_DEL, U_FUN, 2)
  }
    return SMTD_RESOLUTION_UNHANDLED;
}

// Map the redo/paste/copy/cut/undo functions
#define U_RDO C(KC_Y)
#define U_PST C(KC_V)
#define U_CPY C(KC_C)
#define U_CUT C(KC_X)
#define U_UND C(KC_Z)

// Keymap, leveraged Miryoku heavily but swapped action hand to right hand, updated for a Corne v4.1 3x6+2 keyboard
// Visualization perma-link: https://caksoylar.github.io/keymap-drawer?keymap_yaml=H4sIAAAAAAACA9VXaW_bRhD97l-xRdOyTegosh0nkVGgFA9RNi-TuzqcuqpSC2gg2UpkJYiRpr-9c5DUSmJZJ3aA1gAfh8Od3Zk3b1f0bHwzf7dsiY9vL6ej6eTm1Xy8uGiJ3xfTVxeNxeT9wajZuF6Ory7AbYoZjR5djS8nLRFYw1jJ0fWb2evlaP_D4Wh_NPmw92kHBk0W160dIez57HI83XV8fNgVpyei42Y224R9Qo8wIWwXI4PAPtmyjwkDQkU4JDzi2CzhyaXF03yEwixT_AG5dlT3U-lL2WcFcuXL2GfLYOWT7Mu8fFynTCjWkivssIyLKC4t49Dnsm9t_i75rKCTrnwxjyvzNeCPq4bpylFnNKqtpIyjVeyAY8u6mA2HsEfImfo8s2mUkY83ItHX2Foj1VPIhiENgI6uYiKrR07ogOZU-chImz2MVcacQNc0t-t0uWXtNb-nmFTHJf5O-24qh_WycjlnVkStrIaaoLqEsS7J28oqq5CVUyEr77Nk5ZdxxxWyOqmQVVAhq6N7l1VP26-RtgH-z7Jy3s8X4-m2rEq2iuIea_oY1mrL01psa4oMPk9bcYW23AptqQ1tdWu15ZRxfoW2ZIW2ogptZRvaamwL66hSWKcb8jjWzqiBJq9Q29UY16uQ1dl_WFaweEu8zAVlCumIdhxLMqSV0J0PNDLtOAitE8enB6cXpxZs8lxSmmG8NAC-R3gI8IMpfjQpDRPrMUk_JiwuSDUm6cSkrkCEYRY60Axo0gN49x28_NUUj0ySvR6CbaesqD64E6v4xvgL4RuEnxG-RfgTIC2D84sy4mRH5_AAPbh_broRaNKPQ2iZgjncCI7hpIPmnQiy-0LGnQ4McnGQE_eBhrTjS5zdiWoIy4UCFmkO39nL2aMh33p8s_k24KTQPKsgEIVZ1AH6Ig7VV9PXM4TnCC8Qzo07Umi0cJoDhKcIhwg_GXXU8dZD6lShtt8Qmgh7CPsAv2hUUUYFXfAbZDxBe9dArmi6r8AWrBBmou8HARmoNX5OC0NxXpv03Z46XoK1BwbLDwxWIC_i1DBJ_K0YXYmw1NumENdFCCu0ZbRfGM3C2NP1SRyj2u-f4zTMtx8YkTuQZPjKVWRkliSDihGiZwHhdyQ7SYGQXoykAsJ0YTSQdQTj3l7tdnwXK2EpGa9LkoLsopicW4mKSQJgJFTS3aQUTlydUK8JpHvP4HoO1ws4fzI7reLsS5hn0mwryXChJufuHcDDU7gOTQFrBf9EGpeTEsFMTErE66R5zScIcGEVIKjEUlndz8vqELQSqAHzo6SosetEQZE6UfCJ0TfxixvP_u2SmRv4sIZsob9D-hHURANdhJQgNxjV2SSv4AuShHyhZVBmnFfKhyKlDfsHd5KJ_wuAPiAA1oYPSTqaGkVxvE9wTTrfKYW1Q54_bfTa1NXFHCZ-twSYv7mBGsfXywlMOEF_xf4hfz6IIyiY5_nSrVIq-zadr0-5PsF_PYQ2jFy4ecD5zt-unYP16xAAAA%3D%3D

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//COLMAK-DH layout with home row special keys
    //Expanded Miryoku for this keyboard, adds outside columns and 4 keys in the middle
  [U_COLMAKDH] = LAYOUT_split_3x6_3_ex2(
  QK_GESC,   KC_Q,   KC_W,   KC_F,             KC_P,             KC_B,          QK_LLCK,            QK_LLCK,                KC_J,             KC_L,    KC_U,     KC_Y,   KC_SCLN, KC_BSPC,
   KC_TAB, CKC_AC, CKC_RC, CKC_SC,           CKC_TC,             KC_G,          QK_LOCK,            QK_LOCK,                KC_M,           CKC_NC,  CKC_EC,   CKC_IC,    CKC_OC, KC_QUOT,
  KC_LSFT, CKC_ZC, CKC_XC,   KC_C,             KC_D,             KC_V,                                                      KC_K,             KC_H, KC_COMM, CKC_DOTC, CKC_SLSHC, KC_RSFT,
//                                 CKC_ESC, CKC_TAB, CKC_ENT, CKC_SPC, CKC_BSPC, CKC_DEL
                                   LT(U_SYM,KC_ESC), LT(U_NAV,KC_TAB), LT(U_NUM,KC_ENT), LT(U_MOUSE,KC_SPC), LT(U_MEDIA,KC_BSPC), LT(U_FUN,KC_DEL)
  ),
  [U_QWERTY] = LAYOUT_split_3x6_3_ex2(
  QK_GESC,   KC_Q,   KC_W,   KC_E,    KC_R,              KC_T,          QK_LLCK,            QK_LLCK,                 KC_Y,             KC_U,    KC_I,     KC_O,      KC_P, KC_BSPC,
   KC_TAB, CKC_AQ, CKC_SQ, CKC_DQ,  CKC_FQ,              KC_G,          QK_LOCK,            QK_LOCK,                 KC_H,           CKC_JQ,  CKC_KQ,   CKC_LQ, CKC_SCLNQ, KC_QUOT,
  KC_LSFT, CKC_ZQ, CKC_XQ,   KC_C,    KC_V,              KC_B,                                                       KC_N,             KC_M, KC_COMM, CKC_DOTQ, CKC_SLSHQ, KC_RSFT,
//                                 CKC_ESC, CKC_TAB, CKC_ENT, CKC_SPC, CKC_BSPC, CKC_DEL
                          LT(U_SYM,KC_ESC),  LT(U_NAV,KC_TAB), LT(U_NUM,KC_ENT), LT(U_MOUSE,KC_SPC),  LT(U_MEDIA,KC_BSPC), LT(U_FUN,KC_DEL)
  ),
  [U_DVORAK] = LAYOUT_split_3x6_3_ex2(
   QK_GESC,   KC_QUOT, KC_COMM, KC_DOT,    KC_P,              KC_Y,          QK_LLCK,            QK_LLCK,                 KC_F,            KC_G,   KC_C,   KC_R,   KC_L, KC_BSPC,
    KC_TAB,    CKC_AD,  CKC_OD, CKC_ED,  CKC_UD,              KC_I,          QK_LOCK,            QK_LOCK,                 KC_D,          CKC_HD, CKC_TD, CKC_ND, CKC_SD, KC_SLSH,
   KC_LSFT, CKC_SCLND,  CKC_QD,   KC_J,    KC_K,              KC_X,                                                       KC_B,            KC_M,   KC_W, CKC_VD, CKC_ZD, KC_RSFT,
//                                        CKC_ESC, CKC_TAB, CKC_ENT, CKC_SPC, CKC_BSPC, CKC_DEL
                               LT(U_SYM,KC_ESC),  LT(U_NAV,KC_TAB), LT(U_NUM,KC_ENT), LT(U_MOUSE,KC_SPC),  LT(U_MEDIA,KC_BSPC), LT(U_FUN,KC_DEL)
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

  uint8_t layer = get_highest_layer(layer_state|default_layer_state);

  for (uint8_t i = led_min; i < led_max; i++) {
    switch(layer) {
        case U_QWERTY:
          rgb_matrix_set_color(i, rgb_g.r, rgb_g.g, rgb_g.b);
          break;
        case U_DVORAK:
          rgb_matrix_set_color(i, rgb_b.r, rgb_b.g, rgb_b.b);
          break;
        default:
            break;
    }
  }
  switch(layer) {
          case U_NUM:
          RGB_MATRIX_INDICATOR_SET_COLOR(0, rgb_w.r, rgb_w.g, rgb_w.b); // Turn Num key white
          break;
        case U_NAV:
          RGB_MATRIX_INDICATOR_SET_COLOR(7, rgb_w.r, rgb_w.g, rgb_w.b); // Turn Nav key white
          break;
        case U_SYM:
          RGB_MATRIX_INDICATOR_SET_COLOR(8, rgb_w.r, rgb_w.g, rgb_w.b); // Turn Sym key white
          break;
        case U_MOUSE:
          RGB_MATRIX_INDICATOR_SET_COLOR(23, rgb_w.r, rgb_w.g, rgb_w.b); // Turn Mouse key white
          break;
        case U_MEDIA:
          RGB_MATRIX_INDICATOR_SET_COLOR(30, rgb_w.r, rgb_w.g, rgb_w.b); // Turn Media key white
          break;
        case U_FUN:
          RGB_MATRIX_INDICATOR_SET_COLOR(31, rgb_w.r, rgb_w.g, rgb_w.b); // Turn Fun key white
          break;
        case U_BUTTON:
          RGB_MATRIX_INDICATOR_SET_COLOR(15, rgb_w.r, rgb_w.g, rgb_w.b); // Turn Number key white
          RGB_MATRIX_INDICATOR_SET_COLOR(38, rgb_w.r, rgb_w.g, rgb_w.b); // Turn Number key white
          break;
        case U_COLMAKDH:
        case U_TAP:
        default:
            break;
  }

  if (host_keyboard_led_state().caps_lock) {
    RGB_MATRIX_INDICATOR_SET_COLOR(19, rgb_w.r, rgb_w.g, rgb_w.b); // Turn Caps Lock key white
  }
  if (host_keyboard_led_state().scroll_lock) {
    RGB_MATRIX_INDICATOR_SET_COLOR(2, rgb_w.r, rgb_w.g, rgb_w.b); // Turn Scroll Lock key white
  }
  //This requires the USB cable to be plugged into the left half.
  // Try as I might I haven't found a way to make it sync this information across halves.  Probably need to write my own transport routine to pass autocorrect across.
  // For now, if plugged into the right half it will light the backspace key, normally it lights the escape key.
  if (autocorrect_is_enabled()==true) {
    rgb_matrix_set_color(18, rgb_w.r, rgb_w.g, rgb_w.b); // Turn ESC key white as indicator
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
