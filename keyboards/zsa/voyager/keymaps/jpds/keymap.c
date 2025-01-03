// Copyright 2023 ZSA Technology Labs, Inc <@zsa>
// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
  BASE,
  SYM,
  NAV,
  STENO,
  MOUSE
};

// Combos
const uint16_t PROGMEM semicolon_combo[] = {KC_COMMA, KC_DOT, COMBO_END};
combo_t key_combos[] = {
    COMBO(semicolon_combo, KC_SCLN),
};

// Tap Dance declarations
enum {
    TD_ESC_EQL,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for equal sign
    [TD_ESC_EQL] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_EQL),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        TD(TD_ESC_EQL), KC_1, KC_2, KC_3,   KC_4,    KC_5,                                                    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        CW_TOGG, KC_W,    KC_L,    KC_Y,    KC_P,    KC_B,                                                    KC_Z,    KC_F,    KC_O,    KC_U,    KC_QUOT, KC_BSLS,
        OSM(MOD_LSFT), MT(MOD_LGUI, KC_C), MT(MOD_LALT, KC_R), MT(MOD_LSFT, KC_S), MT(MOD_LCTL, KC_T), KC_G,  KC_M,    MT(MOD_RCTL, KC_N),    MT(MOD_RSFT, KC_E),    MT(MOD_RALT, KC_I), MT(MOD_RGUI, KC_A), RSFT_T(KC_SCLN),
        KC_LGUI, ALT_T(KC_Q), KC_J, KC_V,   KC_D,    KC_K,                                                    KC_X,    KC_H,    KC_SLSH, KC_COMMA, KC_DOT, KC_HYPR,
                                LT(SYM,KC_ENT), CTL_T(KC_TAB),                                             SFT_T(KC_BSPC), LT(NAV,KC_SPC)
    ),
    [SYM] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                      KC_7,    KC_8,    KC_9,    KC_MINS, KC_SLSH, KC_F12,
        _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,                      KC_4,    KC_5,    KC_6,    KC_PLUS, KC_ASTR, KC_BSPC,
        TO(STENO), _______, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR,                    KC_1,    KC_2,    KC_3,    KC_DOT,  KC_EQL,  KC_ENT,
                                                     _______, _______,    _______, KC_0
    ),
    [NAV] = LAYOUT(
        RGB_TOG, QK_KB,   RGB_MOD, RGB_M_P, RGB_VAD, RGB_VAI,                      KC_BRID, KC_BRIU, _______, _______, _______, QK_BOOT,
        RM_HUEU, _______, KC_VOLD, KC_VOLU, KC_MUTE, _______,                      KC_PGUP, KC_HOME, KC_DEL,  KC_END,  _______, _______,
        _______, KC_MPRV, KC_MNXT, KC_MSTP, KC_MPLY, _______,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
        _______, _______, _______, _______, _______, _______,                      _______, C(S(KC_TAB)), C(KC_TAB), KC_PSCR, _______, TO(MOUSE),
                                                     _______, _______,    _______, _______
    ),
    [STENO] = LAYOUT(
        _______, STN_N1, STN_N2, STN_N3, STN_N4, STN_N5,                           STN_N6,  STN_N7, STN_N8, STN_N9, STN_NA, STN_NB,
        _______, STN_S1, STN_TL, STN_PL, STN_HL, STN_ST1,                          STN_ST1, STN_FR, STN_PR, STN_LR, STN_TR, STN_DR,
        _______, STN_S2, STN_KL, STN_WL, STN_RL, STN_ST2,                          STN_ST4, STN_RR, STN_BR, STN_GR, STN_SR, STN_ZR,
        TO(BASE), _______, _______, _______, STN_NC, QK_STENO_BOLT,                QK_STENO_GEMINI, STN_NC, STN_FN, STN_RES1, STN_RES2, STN_PWR,
                                                     STN_A, STN_O,        STN_E, STN_U
    ),
    [MOUSE] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                      _______,  _______, _______, _______, _______, _______,
        _______, _______, _______, MS_WHLD, _______, _______,                      _______,  _______, MS_UP,   _______,  _______, _______,
        _______, _______, MS_BTN1, MS_WHLU, MS_BTN2, _______,                      _______,  MS_LEFT, MS_DOWN, MS_RGHT, _______, _______,
        TO(BASE), _______, _______, _______, _______, _______,                      _______,  _______, _______, _______, _______, _______,
                                                     _______, _______,    _______, _______
    ),
};

extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [SYM]   =   { {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_BLUE}, {HSV_BLUE}, {HSV_WHITE}, {HSV_OFF}, {HSV_YELLOW}, {HSV_YELLOW}, {HSV_CYAN}, {HSV_CYAN}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_GREEN}, {HSV_GREEN}, {HSV_GREEN}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_GREEN}, {HSV_GREEN}, {HSV_GREEN}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_GREEN}, {HSV_GREEN}, {HSV_GREEN}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_GREEN} },
    [NAV]   =   { {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_GREEN}, {HSV_GREEN}, {HSV_RED}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_GREEN}, {HSV_GREEN}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_RED}, {HSV_OFF}, {HSV_OFF}, {HSV_RED}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_SPRINGGREEN}, {HSV_SPRINGGREEN}, {HSV_SPRINGGREEN}, {HSV_SPRINGGREEN}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_MAGENTA}, {HSV_OFF}, {HSV_OFF} },
    [STENO] =   { {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_CYAN}, {HSV_CYAN}, {HSV_CYAN}, {HSV_CYAN}, {HSV_CYAN}, {HSV_OFF}, {HSV_CYAN}, {HSV_CYAN}, {HSV_CYAN}, {HSV_CYAN}, {HSV_CYAN}, {HSV_WHITE}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_CYAN}, {HSV_CYAN}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_CYAN}, {HSV_CYAN}, {HSV_CYAN}, {HSV_CYAN}, {HSV_CYAN}, {HSV_CYAN}, {HSV_CYAN}, {HSV_CYAN}, {HSV_CYAN}, {HSV_CYAN}, {HSV_CYAN}, {HSV_CYAN}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_CYAN}, {HSV_CYAN} },
    [MOUSE]   = { {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_GREEN}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_AZURE}, {HSV_GREEN}, {HSV_AZURE}, {HSV_OFF}, {HSV_WHITE}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_MAGENTA}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_MAGENTA}, {HSV_MAGENTA}, {HSV_MAGENTA}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF} },
};

void set_layer_color(int layer) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, HSV_OFF );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

bool rgb_matrix_indicators_user(void) {
  if (keyboard_config.disable_layer_led) { return false; }
  switch (biton32(layer_state)) {
    // case 0:
    //   set_layer_color(0);
    //   break;
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 3:
      set_layer_color(3);
      break;
    case 4:
      set_layer_color(4);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(HSV_OFF);
    break;
  }
  return true;
}
