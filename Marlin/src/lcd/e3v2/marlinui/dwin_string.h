/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2021 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <stdint.h>


#include "../../fontutils.h"
#include "../../marlinui.h"

typedef struct _dwin_charmap_t {
  wchar_t uchar; // the unicode char
  uint8_t idx;   // the glyph of the char in the ROM
  uint8_t idx2;  // the char used to be combined with the idx to simulate a single char
} dwin_charmap_t;

#define MAX_STRING_LENGTH   64

#define S(V) (char*)(V)

class DWIN_String {
  private:
    //static glyph_t *glyphs[256];
    //static font_t *font_header;

    static uint8_t data[MAX_STRING_LENGTH + 1];
    static uint16_t span;   // in pixels
    static uint8_t len;  // in characters

    static void add_character(uint8_t character);
    static void eol() { data[len] = 0x00; }

  public:
    //static void set_font(const uint8_t *font);
    //static void add_glyphs(const uint8_t *font);

    //static font_t *font() { return font_header; };
    //static uint16_t font_height() { return font_header->FontAscent - font_header->FontDescent; }
    //static glyph_t *glyph(uint8_t character) { return glyphs[character] ?: glyphs[0x3F]; }  /* Use '?' for unknown glyphs */
    //static inline glyph_t *glyph(uint8_t *character) { return glyph(*character); }

    static void set();
    //static void add(uint8_t character) { add_character(character); eol(); }
    static void add(wchar_t character);
    static void add(uint8_t *string, uint8_t max_len=MAX_STRING_LENGTH);
    static void add(uint8_t *string, int8_t index, uint8_t *itemString=nullptr);
    static void set(uint8_t *string)   { set(); add(string); }
    static void set(wchar_t character) { set(); add(character); }
    static void set(uint8_t *string, int8_t index, const char *itemString=nullptr) { set(); add(string, index, (uint8_t *)itemString); }
    static inline void set(const __FlashStringHelper *fstring) { set((uint8_t *)fstring); }
    static inline void set(const char *string) { set((uint8_t *)string); }
    static inline void set(const char *string, int8_t index, const char *itemString=nullptr) { set((uint8_t *)string, index, itemString); }
    static inline void add(const char *string) { add((uint8_t *)string); }

    static void trim(uint8_t character=0x20);
    static void rtrim(uint8_t character=0x20);
    static void ltrim(uint8_t character=0x20);

    static void truncate(uint8_t maxlen) { if (len > maxlen) { len = maxlen; eol(); } }

    static uint8_t length() { return len; }
    static uint16_t width() { return span; }
    static uint8_t *string() { return data; }
    static uint16_t center(uint16_t width) { return span > width ? 0 : (width - span) / 2; }
};

int dwin_charmap_compare(dwin_charmap_t *v1, dwin_charmap_t *v2);
int pf_bsearch_cb_comp_dwinmap_pgm(void *userdata, size_t idx, void * data_pin);

extern DWIN_String dwin_string;

#ifdef __AVR__
  #define IV(a) U##a
#else
  #define IV(a) L##a
#endif

const dwin_charmap_t g_dwin_charmap_device[] PROGMEM = {
  // sorted by uchar:
  #if DISPLAY_CHARSET_HD44780 == JAPANESE

    {IV('??'), 0xEC, 0}, // A2
    {IV('??'), 0xDF, 0}, // B0, Marlin special: '??'  LCD_STR_DEGREE (0x09)
    {IV('??'), 0xE1, 0}, // E4
    {IV('??'), 0xEF, 0}, // F6
    {IV('??'), 0xFD, 0}, // 00F7
    {IV('??'), 0xF5, 0}, // 00FC
    {IV('??'), 0xEB, 0}, // 02E3

    {IV('??'), 0xA5, 0}, // 0387
    {IV('??'), 0xF4, 0}, // 038F
    {IV('??'), 0xF2, 0}, // 0398, Theta
    {IV('??'), 0xE3, 0}, // 039E, Xi
    {IV('??'), 0xF6, 0}, // 03A3, Sigma
    {IV('??'), 0xF4, 0}, // 03A9, Omega
    {IV('??'), 0xE0, 0}, // 03AC
    {IV('??'), 0xE3, 0}, // 03AD
    {IV('??'), 0xE0, 0}, // 03B1, alpha
    {IV('??'), 0xE2, 0}, // 03B2, beta
    {IV('??'), 0xE3, 0}, // 03B5, epsilon
    {IV('??'), 0xF2, 0}, // 03B8, theta
    {IV('??'), 0xE4, 0}, // 03BC, mu
    {IV('??'), 0xE3, 0}, // 03BE, xi
    {IV('??'), 0xF7, 0}, // 03C0, pi
    {IV('??'), 0xE6, 0}, // 03C1, rho
    {IV('??'), 0xE5, 0}, // 03C3, sigma

    {IV('???'), 0x7F, 0}, // 2190
    {IV('???'), 0x7E, 0}, // 2192, Marlin special: '??????????????????' LCD_STR_ARROW_RIGHT (0x03)
    {IV('???'), 0xE8, 0}, // 221A
    {IV('???'), 0xF3, 0}, // 221E
    {IV('???'), 0xFF, 0}, // 2588

    //{IV(''), 0xA0, 0},
    {IV('???'), 0xA1, 0},
    {IV('???'), 0xA2, 0},
    {IV('???'), 0xA3, 0},
    {IV('???'), 0xDE, 0}, // ???
    {IV('???'), 0xDF, 0}, // '???'
    {IV('???'), '=', 0},
    {IV('???'), 0xA7, 0},
    {IV('???'), 0xB1, 0},
    {IV('???'), 0xA8, 0},
    {IV('???'), 0xB2, 0},
    {IV('???'), 0xA9, 0},
    {IV('???'), 0xB3, 0},
    {IV('???'), 0xAA, 0},
    {IV('???'), 0xB4, 0},
    {IV('???'), 0xAB, 0},

    {IV('???'), 0xB5, 0},
    {IV('???'), 0xB6, 0},
    {IV('???'), 0xB6, 0xDE},
    {IV('???'), 0xB7, 0},
    {IV('???'), 0xB7, 0xDE},
    {IV('???'), 0xB8, 0},
    {IV('???'), 0xB8, 0xDE},
    {IV('???'), 0xB9, 0},
    {IV('???'), 0xB9, 0xDE},
    {IV('???'), 0xBA, 0},
    {IV('???'), 0xBA, 0xDE},
    {IV('???'), 0xBB, 0},
    {IV('???'), 0xBB, 0xDE},
    {IV('???'), 0xBC, 0},
    {IV('???'), 0xBC, 0xDE},
    {IV('???'), 0xBD, 0},
    {IV('???'), 0xBD, 0xDE},
    {IV('???'), 0xBE, 0},
    {IV('???'), 0xBE, 0xDE},
    {IV('???'), 0xBF, 0},
    {IV('???'), 0xBF, 0xDE},

    {IV('???'), 0xC0, 0},
    {IV('???'), 0xC0, 0xDE},
    {IV('???'), 0xC1, 0},
    {IV('???'), 0xC1, 0xDE},
    {IV('???'), 0xAF, 0},
    {IV('???'), 0xC2, 0},
    {IV('???'), 0xC2, 0xDE},
    {IV('???'), 0xC3, 0},
    {IV('???'), 0xC3, 0xDE},
    {IV('???'), 0xC4, 0},
    {IV('???'), 0xC4, 0xDE},
    {IV('???'), 0xC5, 0},
    {IV('???'), 0xC6, 0},
    {IV('???'), 0xC7, 0},
    {IV('???'), 0xC8, 0},
    {IV('???'), 0xC9, 0},
    {IV('???'), 0xCA, 0},
    {IV('???'), 0xCA, 0xDE},
    {IV('???'), 0xCA, 0xDF},
    {IV('???'), 0xCB, 0},
    {IV('???'), 0xCB, 0xDE},
    {IV('???'), 0xCB, 0xDF},
    {IV('???'), 0xCC, 0},
    {IV('???'), 0xCC, 0xDE},
    {IV('???'), 0xCC, 0xDF},
    {IV('???'), 0xCD, 0},
    {IV('???'), 0xCD, 0xDE},
    {IV('???'), 0xCD, 0xDF},
    {IV('???'), 0xCE, 0},
    {IV('???'), 0xCE, 0xDE},
    {IV('???'), 0xCE, 0xDF},
    {IV('???'), 0xCF, 0},

    {IV('???'), 0xD0, 0},
    {IV('???'), 0xD1, 0},
    {IV('???'), 0xD2, 0},
    {IV('???'), 0xD3, 0},
    {IV('???'), 0xAC, 0},
    {IV('???'), 0xD4, 0},
    {IV('???'), 0xAD, 0},
    {IV('???'), 0xD5, 0},
    {IV('???'), 0xAE, 0},
    {IV('???'), 0xD6, 0},
    {IV('???'), 0xD7, 0},
    {IV('???'), 0xD8, 0},
    {IV('???'), 0xD9, 0},
    {IV('???'), 0xDA, 0},
    {IV('???'), 0xDB, 0},
    {IV('???'), 0xDC, 0},
    {IV('???'), 0xA6, 0},
    {IV('???'), 0xDD, 0},
    {IV('???'), 0xB3, 0xDE},
    {IV('???'), 0xDC, 0xDE},
    {IV('???'), 0xA6, 0xDE},
    {IV('???'), 0xA5, 0},
    {IV('???'), 0xB0, 0},
    {IV('???'), 0xA4, 0},

    //{IV('g'), 0xE7, 0}, // error
    //{IV(''), 0xE9, 0},
    //{IV('j'), 0xEA, 0}, // error
    //{IV(''), 0xED, 0},
    //{IV(''), 0xEE, 0},

    //{IV('p'), 0xF0, 0}, // error
    //{IV('q'), 0xF1, 0}, // error
    //{IV(''), 0xF8, 0},
    //{IV('y'), 0xF9, 0}, // error
    {IV('???'), 0xFB, 0},
    {IV('???'), 0xFC, 0},
    {IV('???'), 0xFA, 0},
    //{IV(''), 0xFE, 0},

    //???????????????????????????????????????
    {IV('???'), 0xA4, 0}, //???
    {IV('???'), 0xA5, 0}, //???
    {IV('???'), 0xA6, 0}, //???
    {IV('???'), 0xA7, 0}, //???
    {IV('???'), 0xA8, 0}, //???
    {IV('???'), 0xA9, 0}, //???
    {IV('???'), 0xAA, 0}, //???
    {IV('???'), 0xAB, 0}, //???
    {IV('???'), 0xAC, 0}, //???
    {IV('???'), 0xAD, 0}, //???
    {IV('???'), 0xAE, 0}, //???
    {IV('???'), 0xAF, 0}, //???
    {IV('???'), 0xB0, 0}, //???

    //??????????????????????????????????????????
    {IV('???'), 0xB1, 0}, //???
    {IV('???'), 0xB2, 0}, //???
    {IV('???'), 0xB3, 0}, //???
    {IV('???'), 0xB4, 0}, //???
    {IV('???'), 0xB5, 0}, //???
    {IV('???'), 0xB6, 0}, //???
    {IV('???'), 0xB7, 0}, //???
    {IV('???'), 0xB8, 0}, //???
    {IV('???'), 0xB9, 0}, //???
    {IV('???'), 0xBA, 0}, //???
    {IV('???'), 0xBB, 0}, //???
    {IV('???'), 0xBC, 0}, //???
    {IV('???'), 0xBD, 0}, //???
    {IV('???'), 0xBE, 0}, //???

    //??????????????????????????????????????????
    {IV('???'), 0xBF, 0}, //???
    {IV('???'), 0xC0, 0}, //???
    {IV('???'), 0xC1, 0}, //???
    {IV('???'), 0xC2, 0}, //???
    {IV('???'), 0xC3, 0}, //???
    {IV('???'), 0xC4, 0}, //???
    {IV('???'), 0xC5, 0}, //???
    {IV('???'), 0xC6, 0}, //???
    {IV('???'), 0xC7, 0}, //???
    {IV('???'), 0xC8, 0}, //???
    {IV('???'), 0xC9, 0}, //???
    {IV('???'), 0xCA, 0}, //???
    {IV('???'), 0xCB, 0}, //???
    {IV('???'), 0xCC, 0}, //???

    //?????????????????????????????????????????????????????????
    {IV('???'), 0xCD, 0}, //???
    {IV('???'), 0xCE, 0}, //???
    {IV('???'), 0xCF, 0}, //???
    {IV('???'), 0xD0, 0}, //???
    {IV('???'), 0xD1, 0}, //???
    {IV('???'), 0xD2, 0}, //???
    {IV('???'), 0xD3, 0}, //???
    {IV('???'), 0xD4, 0}, //???
    {IV('???'), 0xD5, 0}, //???
    {IV('???'), 0xD6, 0}, //???
    {IV('???'), 0xD7, 0}, //???
    {IV('???'), 0xD8, 0}, //???
    {IV('???'), 0xD9, 0}, //???
    {IV('???'), 0xDA, 0}, //???
    {IV('???'), 0xDB, 0}, //???
    {IV('???'), 0xDC, 0}, //???
    {IV('???'), 0xDD, 0}, //???
    {IV('???'), 0xDE, 0}, // ???
    {IV('???'), 0xDF, 0}, // ???

    {IV('???'), 0x5C, 0},

  #elif DISPLAY_CHARSET_HD44780 == WESTERN
    // 0x10 -- 0x1F (except 0x1C)
    // 0x80 -- 0xFF (except 0xA7,0xB0,0xB1,0xB3,0xB4,0xBF,0xD1,0xF8,0xFA,0xFC-0xFF)

    {IV('??'), 0xA9, 0},
    {IV('??'), 0xA4, 0},
    {IV('??'), 0xA5, 0},
    {IV('??'), 0xA6, 0},
    {IV('??'), 0xD2, 0}, // section sign
    {IV('??'), 0xCF, 0},

    {IV('??'), 0x9D, 0},
    {IV('??'), 0xBB, 0},
    {IV('??'), 0xCE, 0},

    {IV('??'), 0xB2, 0}, // Marlin special: '??'  LCD_STR_DEGREE (0x09)
    //{IV(''), 0xD1, 0},
    {IV('??'), 0x10, 0}, //?????
    //{'='), 0x1C, 0}, // error
    {IV('??'), 0x1E, 0},
    {IV('??'), 0x1F, 0},
    {IV('??'), 0xD3, 0}, // pilcrow sign
    {IV('??'), 0x9E, 0},
    {IV('??'), 0xBC, 0}, // 00BB
    //{IV(''), 0xB3, 0}, // error
    //{IV(''), 0xB4, 0}, // error
    {IV('??'), 0xB6, 0}, // 00BC
    {IV('??'), 0xB5, 0}, // 00BD
    //{IV('??'), '3', 0}, // 00BE
    {IV('??'), 0x9F, 0}, // 00BF

    {IV('??'), 0x8F, 0},
    {IV('??'), 0xAA, 0},
    {IV('??'), 0x8E, 0},
    {IV('??'), 0x92, 0},
    {IV('??'), 0x80, 0},
    {IV('??'), 0x90, 0},
    {IV('??'), 0x9C, 0},
    {IV('??'), 0xAC, 0},
    {IV('??'), 0x99, 0},
    {IV('??'), 0xB7, 0},
    {IV('??'), 0xAE, 0},
    {IV('??'), 0x9A, 0},
    {IV('??'), 0x85, 0},
    {IV('??'), 0xA0, 0},
    {IV('??'), 0x83, 0},
    {IV('??'), 0xAB, 0},
    {IV('??'), 0x84, 0},
    {IV('??'), 0x86, 0},
    {IV('??'), 0x91, 0},
    {IV('??'), 0x87, 0},
    {IV('??'), 0x8A, 0},
    {IV('??'), 0x82, 0},
    {IV('??'), 0x88, 0},
    {IV('??'), 0x89, 0},
    {IV('??'), 0x8D, 0},
    {IV('??'), 0xA1, 0},
    {IV('??'), 0x8C, 0},
    {IV('??'), 0x8B, 0},

    {IV('??'), 0x9B, 0},
    {IV('??'), 0x95, 0},
    {IV('??'), 0xA2, 0},
    {IV('??'), 0x93, 0},
    {IV('??'), 0xAD, 0},
    {IV('??'), 0x94, 0},
    {IV('??'), 0xB8, 0},
    {IV('??'), 0xAF, 0},
    {IV('??'), 0x97, 0},
    {IV('??'), 0xA3, 0},
    {IV('??'), 0x96, 0},
    {IV('??'), 0x81, 0},
    {IV('??'), 0x98, 0},

    //{IV(''), 0xB0, 0}, // error
    //{IV(''), 0xB1, 0}, // error
    {IV('??'), 0xA8, 0}, // 0192

    {IV('??'), 0xDB, 0}, // 038E
    {IV('??'), 0xDE, 0}, // 038F
    {IV('??'), 0xE7, 0}, // 0390

    {IV('??'), 0xD4, 0}, // 0393, Gamma
    {IV('??'), 0xD5, 0}, // 0394, Delta, ???
    {IV('??'), 0xD6, 0}, // 0398, Theta
    {IV('??'), 0xD7, 0}, // 039B, Lambda
    {IV('??'), 0xD8, 0}, // 039E, Xi
    {IV('??'), 0xD9, 0}, // Pi
    {IV('??'), 0xDA, 0}, // Sigma
    {IV('??'), 0xDB, 0}, // Upsilon
    {IV('??'), 0xDC, 0}, // Phi
    {IV('??'), 0xDD, 0}, // Psi
    {IV('??'), 0xDE, 0}, // Omega

    {IV('??'), 0xDF, 0}, // 03AC
    {IV('??'), 0xE3, 0}, // 03AD
    {IV('??'), 0xE5, 0}, // 03AE
    {IV('??'), 0xE7, 0}, // 03AF
    {IV('??'), 0xF1, 0}, // 03B0

    {IV('??'), 0xDF, 0}, // alpha
    {IV('??'), 0xE0, 0}, // beta
    {IV('??'), 0xE1, 0}, // gamma
    {IV('??'), 0xE2, 0}, // delta
    {IV('??'), 0xE3, 0}, // epsilon
    {IV('??'), 0xE4, 0}, // zeta
    {IV('??'), 0xE5, 0}, // eta
    {IV('??'), 0xE6, 0}, // theta
    {IV('??'), 0xE7, 0}, // lota
    {IV('??'), 0xE8, 0}, // kappa
    {IV('??'), 0xE9, 0}, // lambda
    {IV('??'), 0xEA, 0}, // mu
    {IV('??'), 0xEB, 0}, // nu
    {IV('??'), 0xEC, 0}, // xi
    {IV('??'), 0xED, 0}, // pi
    {IV('??'), 0xEE, 0}, // rho
    {IV('??'), 0xEF, 0}, // sigma

    {IV('??'), 0xF0, 0}, // tau
    {IV('??'), 0xF1, 0}, // upsilon
    {IV('??'), 0xF2, 0}, // chi
    {IV('??'), 0xF3, 0}, // psi
    {IV('??'), 0xF4, 0}, // 03C9, omega
    {IV('??'), 0xE7, 0}, // 03CA
    {IV('??'), 0xF1, 0}, // 03CB
    {IV('??'), 0xF1, 0}, // 03CD
    {IV('??'), 0xF4, 0}, // 03CE

    {IV('???'), 0xCD, 0}, // ??
    {IV('???'), 0xA7, 0}, // ??? Pt ASCII 158
    {IV('???'), 0xD0, 0},
    {IV('???'), 0xF9, 0}, // ???
    {IV('???'), 0xC4, 0},
    {IV('???'), 0x04, 0}, // Marlin special: '????????????'  LCD_STR_REFRESH (0x01)
    {IV('???'), 0xFB, 0},
    {IV('???'), 0xBE, 0}, // ???
    {IV('???'), 0xC2, 0}, // infinity
    {IV('???'), 0x1B, 0},
    {IV('???'), 0x1D, 0},
    {IV('???'), 0x1A, 0},
    {IV('???'), 0xBD, 0},
    {IV('???'), 0x11, 0},
    {IV('???'), 0xB9, 0},// ?????? ??????
    {IV('???'), 0xBA, 0},
    //{IV(''), 0xBF, 0}, // error

    {IV('???'), 0xC0, 0},
    {IV('???'), 0xC1, 0},

    {IV('???'), 0x14, 0},
    {IV('???'), 0x15, 0},
    {IV('???'), 0x16, 0},
    {IV('???'), 0x17, 0},
    {IV('???'), 0x18, 0},
    {IV('???'), 0x19, 0},

    {IV('???'), 0x12, 0},
    {IV('???'), 0x13, 0},

    {IV('???'), 0x07, 0}, // Marlin special: '???????????????????????????????????????????????????????????????????????????????????????????????? ?????????????????????'  LCD_STR_CLOCK (0x05)
    {IV('???'), 0xC9, 0},
    {IV('???'), 0xCA, 0},
    {IV('???'), 0xCB, 0},
    {IV('???'), 0xCC, 0},
    {IV('???'), 0xC3, 0}, // ???
    {IV('???'), 0xC8, 0},
    {IV('???'), 0xC5, 0},
    {IV('???'), 0xC7, 0},
    {IV('???'), 0xC6, 0},


    {IV('???'), 0xF5, 0},
    {IV('???'), 0xF7, 0}, // ???
    {IV('???'), 0xF6, 0},
    //{IV(''), 0xF8, 0}, // error
    //{IV(''), 0xFA, 0}, // error
    //{IV(''), 0xFC, 0}, // error
    //{IV(''), 0xFD, 0}, // error
    //{IV(''), 0xFE, 0}, // error
    //{IV(''), 0xFF, 0}, // error

  #elif DISPLAY_CHARSET_HD44780 == CYRILLIC

    {IV('??'), 0x5C, 0}, // 00A2
    {IV('??'), 0xCF, 0}, // 00A3
    {IV('??'), 0x01, 0}, // 00B0, Marlin special: '??'  LCD_STR_DEGREE (0x09)

    //{IV(''), 0x80, 0},
    //{IV(''), 0x81, 0},
    //{IV(''), 0x82, 0},
    //{IV(''), 0x83, 0},
    //{IV(''), 0x84, 0},
    //{IV(''), 0x85, 0},
    //{IV(''), 0x86, 0},
    //{IV(''), 0x87, 0},
    //{IV(''), 0x88, 0},
    //{IV(''), 0x89, 0},
    //{IV(''), 0x8A, 0},
    //{IV(''), 0x8B, 0},
    //{IV(''), 0x8C, 0},
    //{IV(''), 0x8D, 0},
    //{IV(''), 0x8E, 0},
    //{IV(''), 0x8F, 0},

    //{IV(''), 0x90, 0},
    //{IV(''), 0x91, 0},
    //{IV(''), 0x92, 0},
    //{IV(''), 0x93, 0},
    //{IV(''), 0x94, 0},
    //{IV(''), 0x95, 0},
    //{IV(''), 0x96, 0},
    //{IV(''), 0x97, 0},
    //{IV(''), 0x98, 0},
    //{IV(''), 0x99, 0},
    //{IV(''), 0x9A, 0},
    //{IV(''), 0x9B, 0},
    //{IV(''), 0x9C, 0},
    //{IV(''), 0x9D, 0},
    //{IV(''), 0x9E, 0},
    //{IV(''), 0x9F, 0},


    {IV('??'), 0xF0, 0}, // 00BC
    {IV('???'), 0xF1, 0},
    {IV('??'), 0xF2, 0}, // 00BD
    {IV('??'), 0xF3, 0}, // 00BE
    {IV('??'), 0xCD, 0}, // 00BF

    #if ENABLED(DISPLAY_CHARSET_ISO10646_5)

      // Map Cyrillic to HD44780 extended CYRILLIC where possible
      {IV('??'), 0xA2, 0}, // 0401
      {IV('??'), 'A', 0}, // 0410
      {IV('??'), 0xA0, 0},
      {IV('??'), 'B', 0},
      {IV('??'), 0xA1, 0},
      {IV('??'), 0xE0, 0},
      {IV('??'), 'E', 0},
      {IV('??'), 0xA3, 0},
      {IV('??'), 0xA4, 0},
      {IV('??'), 0xA5, 0},
      {IV('??'), 0xA6, 0},
      {IV('??'), 'K', 0},
      {IV('??'), 0xA7, 0},
      {IV('??'), 'M', 0},
      {IV('??'), 'H', 0},
      {IV('??'), 'O', 0},
      {IV('??'), 0xA8, 0},
      {IV('??'), 'P', 0},
      {IV('??'), 'C', 0},
      {IV('??'), 'T', 0},
      {IV('??'), 0xA9, 0},
      {IV('??'), 0xAA, 0},
      {IV('??'), 'X', 0},
      {IV('??'), 0xE1, 0},
      {IV('??'), 0xAB, 0},
      {IV('??'), 0xAC, 0},
      {IV('??'), 0xE2, 0},
      {IV('??'), 0xAD, 0},
      {IV('??'), 0xAE, 0},
      {IV('??'), 'b', 0},
      {IV('??'), 0xAF, 0},
      {IV('??'), 0xB0, 0},
      {IV('??'), 0xB1, 0},
      {IV('??'), 'a', 0},

      {IV('??'), 0xB2, 0},
      {IV('??'), 0xB3, 0},
      {IV('??'), 0xB4, 0},
      {IV('??'), 0xE3, 0},
      {IV('??'), 'e', 0},
      {IV('??'), 0xB6, 0},
      {IV('??'), 0xB7, 0},
      {IV('??'), 0xB8, 0},
      {IV('??'), 0xB9, 0},
      {IV('??'), 0xBA, 0}, //????????????
      {IV('??'), 0xBB, 0},
      {IV('??'), 0xBC, 0},
      {IV('??'), 0xBD, 0},
      {IV('??'), 'o', 0},
      {IV('??'), 0xBE, 0},
      {IV('??'), 'p', 0},
      {IV('??'), 'c', 0},
      {IV('??'), 0xBF, 0},

      {IV('??'), 'y', 0},
      {IV('??'), 0xE4, 0},
      {IV('??'), 'x', 0},
      {IV('??'), 0xE5, 0},
      {IV('??'), 0xC0, 0},
      {IV('??'), 0xC1, 0},
      {IV('??'), 0xE6, 0},
      {IV('??'), 0xC2, 0},
      {IV('??'), 0xC3, 0},
      {IV('??'), 0xC4, 0},
      {IV('??'), 0xC5, 0},
      {IV('??'), 0xC6, 0},
      {IV('??'), 0xC7, 0}, // 044F
      {IV('??'), 0xB5, 0}, // 0451
      //{IV(''), 0xC8, 0},
      //{IV(''), 0xC9, 0},
      //{IV(''), 0xCA, 0},
      //{IV(''), 0xCB, 0},
      //{IV(''), 0xCC, 0},
      //{IV(''), 0xCD, 0},
      //{IV(''), 0xCE, 0},

      //{IV(''), 0xD0, 0},
      //{IV(''), 0xD1, 0},
      //{IV(''), 0xD2, 0},
      //{IV(''), 0xD3, 0},
      //{IV(''), 0xD4, 0},
      //{IV(''), 0xD5, 0},
      //{IV(''), 0xD6, 0},
      //{IV(''), 0xD7, 0},
      //{IV(''), 0xD8, 0},
      //{IV(''), 0xDB, 0},
      //{IV(''), 0xDC, 0},
      //{IV(''), 0xDD, 0},
      //{IV(''), 0xDE, 0},
      //{IV(''), 0xDF, 0},

      //{IV(''), 0xE7, 0},
      //{IV(''), 0xE8, 0},
      //{IV(''), 0xE9, 0},
      //{IV(''), 0xEA, 0},
      //{IV(''), 0xEB, 0},
      //{IV(''), 0xEC, 0},
      //{IV(''), 0xED, 0},
      //{IV(''), 0xEE, 0},
      //{IV(''), 0xEF, 0},

      //{IV(''), 0xF4, 0},
      //{IV(''), 0xF5, 0},
      //{IV(''), 0xF6, 0},
      //{IV(''), 0xF7, 0},
      //{IV(''), 0xF8, 0},
      //{IV(''), 0xF9, 0},
      //{IV(''), 0xFA, 0},
      //{IV(''), 0xFB, 0},
      //{IV(''), 0xFC, 0},
      //{IV(''), 0xFD, 0},
      //{IV(''), 0xFE, 0},
      //{IV(''), 0xFF, 0},

    #endif

    {IV('???'), 0xD9, 0}, // 2191 ????????????
    {IV('???'), 0xDA, 0}, // 2193
  #endif
};

// the plain ASCII replacement for various char
const dwin_charmap_t g_dwin_charmap_common[] PROGMEM = {
  {IV('??'), 'i', 0}, // A1
  {IV('??'), 'c', 0}, // A2
  {IV('??'), 0x09, 0}, // B0 Marlin special: '??'  LCD_STR_DEGREE (0x09)

  // Map WESTERN code to plain ASCII
  {IV('??'), 'A', 0}, // C1
  {IV('??'), 'A', 0}, // C2
  {IV('??'), 'A', 0}, // C3
  {IV('??'), 'A', 0}, // C4
  {IV('??'), 'A', 0}, // C5
  {IV('??'), 'A', 'E'}, // C6
  {IV('??'), 'C', 0}, // C7
  {IV('??'), 'E', 0}, // C8
  {IV('??'), 'E', 0}, // C9
  {IV('??'), 'I', 0}, // CD
  {IV('??'), 'N', 0}, // D1
  {IV('??'), 'O', 0}, // D5
  {IV('??'), 'O', 0}, // D6
  {IV('??'), 'x', 0}, // D7
  {IV('??'), 'U', 0}, // DC
  {IV('??'), 'Y', 0}, // DD
  {IV('??'), 'a', 0}, // E0
  {IV('??'), 'a', 0},
  {IV('??'), 'a', 0},
  {IV('??'), 'a', 0},
  {IV('??'), 'a', 0},
  {IV('??'), 'a', 0},
  {IV('??'), 'a', 'e'},
  {IV('??'), 'c', 0},
  {IV('??'), 'e', 0}, // 00E8
  {IV('??'), 'e', 0},
  {IV('??'), 'e', 0},
  {IV('??'), 'e', 0},
  {IV('??'), 'i', 0}, // 00EC
  {IV('??'), 'i', 0},
  {IV('??'), 'i', 0},
  {IV('??'), 'i', 0}, // 00EF

  {IV('??'), 'n', 0}, // 00F1
  {IV('??'), 'o', 0},
  {IV('??'), 'o', 0},
  {IV('??'), 'o', 0},
  {IV('??'), 'o', 0},
  {IV('??'), 'o', 0},
  //{IV('??'), 0xB8, 0},
  {IV('??'), 'o', 0},
  {IV('??'), 'u', 0},
  {IV('??'), 'u', 0},
  {IV('??'), 'u', 0},
  {IV('??'), 'u', 0}, // FC
  {IV('??'), 'y', 0}, // FD
  {IV('??'), 'y', 0}, // FF

  {IV('??'), 'A', 0}, // 0104
  {IV('??'), 'a', 0}, // 0105
  {IV('??'), 'C', 0}, // 0106
  {IV('??'), 'c', 0}, // 0107
  {IV('??'), 'C', 0}, // 010C
  {IV('??'), 'c', 0}, // 010D
  {IV('??'), 'D', 0}, // 010E
  {IV('??'), 'd', 0}, // 010F
  {IV('??'), 'd', 0}, // 0111
  {IV('??'), 'e', 0}, // 0119
  {IV('??'), 'E', 0}, // 011A
  {IV('??'), 'e', 0}, // 011B
  {IV('??'), 'g', 0}, // 011F
  {IV('??'), 'I', 0}, // 0130
  {IV('??'), 'i', 0}, // 0131

  {IV('??'), 'L', 0}, // 0141
  {IV('??'), 'l', 0}, // 0142
  {IV('??'), 'N', 0}, // 0143
  {IV('??'), 'n', 0}, // 0144
  {IV('??'), 'n', 0}, // 0148

  {IV('??'), 'R', 0}, // 0158
  {IV('??'), 'r', 0}, // 0159
  {IV('??'), 'S', 0}, // 015A
  {IV('??'), 's', 0}, // 015B
  {IV('??'), 's', 0}, // 015F
  {IV('??'), 'S', 0}, // 0160
  {IV('??'), 's', 0}, // 0161
  {IV('??'), 't', 0}, // 0165
  {IV('??'), 'u', 0}, // 016F
  {IV('??'), 'z', 0}, // 017C
  {IV('??'), 'Z', 0}, // 017D
  {IV('??'), 'z', 0}, // 017E
  {IV('??'), 'f', 0}, // 0192

  {IV('??'), 'x', 0}, // 02E3

  #if ENABLED(DISPLAY_CHARSET_ISO10646_VI)

    // Map Vietnamese phonetics

    //{IV('??'), 'a', 0}, {IV('??'), 'A', 0},
    {IV('???'), 'a', 0}, {IV('???'), 'A', 0},
    {IV('???'), 'a', 0}, {IV('???'), 'A', 0},
    //{IV('??'), 'a', 0}, {IV('??'), 'A', 0},
    //{IV('??'), '??', 0}, {IV('??'), 'A', 0},
    {IV('???'), 'A', 0},
    {IV('??'), 'a', 0}, {IV('??'), 'A', 0},
    {IV('???'), 'a', 0}, {IV('???'), 'A', 0},
    {IV('???'), 'a', 0}, {IV('???'), 'A', 0},
    {IV('???'), 'a', 0}, {IV('???'), 'A', 0},
    {IV('???'), 'a', 0}, {IV('???'), 'A', 0},
    {IV('???'), 'a', 0}, {IV('???'), 'A', 0},
    {IV('??'), 'a', 0}, {IV('??'), 'A', 0},
    {IV('???'), 'a', 0}, {IV('???'), 'A', 0},
    {IV('???'), 'a', 0}, {IV('???'), 'A', 0},
    {IV('???'), 'a', 0}, {IV('???'), 'A', 0},
    {IV('???'), 'a', 0}, {IV('???'), 'A', 0},
    {IV('???'), 'a', 0}, {IV('???'), 'A', 0},
    //{IV('??'), 'd', 0},
                       {IV('??'), 'D', 0},
    {IV('e'), 'e', 0}, {IV('E'), 'E', 0},
    {IV('??'), 'e', 0}, {IV('??'), 'E', 0},
    {IV('???'), 'e', 0}, {IV('???'), 'E', 0},
    {IV('???'), 'e', 0}, {IV('???'), 'E', 0},
    {IV('??'), 'e', 0}, {IV('??'), 'E', 0},
    {IV('???'), 'e', 0}, {IV('???'), 'E', 0},
    {IV('??'), 'e', 0}, {IV('??'), 'E', 0},
    {IV('???'), 'e', 0}, {IV('???'), 'E', 0},
    {IV('???'), 'e', 0}, {IV('???'), 'E', 0},
    {IV('???'), 'e', 0}, {IV('???'), 'E', 0},
    {IV('???'), 'e', 0}, {IV('???'), 'E', 0},
    {IV('???'), 'e', 0}, {IV('???'), 'E', 0},
    {IV('i'), 'i', 0}, {IV('I'), 'I', 0},
    //{IV('??'), '??', 0}, {IV('??'), '??', 0},
    {IV('???'), '???', 0}, {IV('???'), '???', 0},
    {IV('??'), '??', 0}, {IV('??'), '??', 0},
    {IV('??'), '??', 0}, {IV('??'), '??', 0},
    {IV('???'), '???', 0}, {IV('???'), '???', 0},
    {IV('o'), 'o', 0}, {IV('O'), 'O', 0},
    {IV('??'), 'o', 0}, {IV('??'), 'O', 0},
    {IV('???'), 'o', 0}, {IV('???'), 'O', 0},
    {IV('??'), 'o', 0}, {IV('??'), 'O', 0},
    {IV('??'), 'o', 0}, {IV('??'), 'O', 0},
    {IV('???'), 'o', 0}, {IV('???'), 'O', 0},
    {IV('??'), 'o', 0}, {IV('??'), 'O', 0},
    {IV('???'), 'o', 0}, {IV('???'), 'O', 0},
    {IV('???'), 'o', 0}, {IV('???'), 'O', 0},
    {IV('???'), 'o', 0}, {IV('???'), 'O', 0},
    {IV('???'), 'o', 0}, {IV('???'), 'O', 0},
    {IV('???'), 'o', 0}, {IV('???'), 'O', 0},
    {IV('??'), 'o', 0}, {IV('??'), 'O', 0},
    {IV('???'), 'o', 0}, {IV('???'), 'O', 0},
    {IV('???'), 'o', 0}, {IV('???'), 'O', 0},
    {IV('???'), 'o', 0}, {IV('???'), 'O', 0},
    {IV('???'), 'o', 0}, {IV('???'), 'O', 0},
    {IV('???'), 'o', 0}, {IV('???'), 'O', 0},
    {IV('??'), 'u', 0}, {IV('??'), 'U', 0},
    {IV('???'), 'u', 0}, {IV('???'), 'U', 0},
    {IV('??'), 'u', 0}, {IV('??'), 'U', 0},
    //{IV('??'), 'u', 0}, {IV('??'), 'U', 0},
    {IV('???'), 'u', 0}, {IV('???'), 'U', 0},
    {IV('??'), 'u', 0}, {IV('??'), 'U', 0},
    {IV('???'), 'u', 0}, {IV('???'), 'U', 0},
    {IV('???'), 'u', 0}, {IV('???'), 'U', 0},
    {IV('???'), 'u', 0}, {IV('???'), 'U', 0},
    {IV('???'), 'u', 0}, {IV('???'), 'U', 0},
    {IV('???'), 'u', 0}, {IV('???'), 'U', 0},
    {IV('y'), 'y', 0}, {IV('Y'), 'Y', 0},

  #endif

  #if ENABLED(DISPLAY_CHARSET_ISO10646_GREEK)

    {IV('??'), '\'', 0}, // 0384
    {IV('??'), '\'', 0}, // 0385
    {IV('??'), 'A', 0}, // 0386
    {IV('??'), '.', 0}, // 0387
    {IV('??'), 'E', 0}, // 0388
    {IV('??'), 'H', 0}, // 0389
    {IV('??'), 'I', 0}, // 038A
    {IV('??'), 'O', 0}, // 038C
    {IV('??'), 'Y', 0}, // 038E
    {IV('??'), 'O', 0}, // 038F
    {IV('??'), 'i', 0}, // 0390
    {IV('??'), 'A', 0}, // 0391
    {IV('??'), 'B', 0}, // 0392
    {IV('??'), 'T', 0}, // 0393, Gamma
    {IV('??'), '4', 0}, // 0394, Delta, ???
    {IV('??'), 'E', 0}, // 0395
    {IV('??'), 'Z', 0}, // 0396
    {IV('??'), 'H', 0}, // 0397
    {IV('??'), '0', 0}, // 0398, Theta
    {IV('??'), 'I', 0}, // 0399
    {IV('??'), 'K', 0}, // 039A
    {IV('??'), '^', 0}, // 039B, Lambda
    {IV('??'), 'M', 0}, // 039C
    {IV('??'), 'N', 0}, // 039D
    {IV('??'), '3', 0}, // 039E, Xi
    {IV('??'), 'O', 0}, // 039F
    {IV('??'), 'n', 0}, // 03A0, Pi
    {IV('??'), 'P', 0}, // 03A1
    {IV('??'), 'E', 0}, // 03A3, Sigma
    {IV('??'), 'T', 0}, // 03A4
    {IV('??'), 'Y', 0}, // 03A5, Upsilon
    {IV('??'), 'p', 0}, // 03A6, Phi
    {IV('??'), 'X', 0}, // 03A7
    {IV('??'), 'P', 0}, // 03A8, Psi
    {IV('??'), 'O', 0}, // 03A9, Omega
    {IV('??'), 'I', 0}, // 03AA
    {IV('??'), 'Y', 0}, // 03AB
    {IV('??'), 'a', 0}, // 03AC
    {IV('??'), 'e', 0}, // 03AD
    {IV('??'), 'n', 0}, // 03AE
    {IV('??'), 'i', 0}, // 03AF
    {IV('??'), 'v', 0}, // 03B0
    {IV('??'), 'a', 0}, // 03B1, alpha
    {IV('??'), 'B', 0}, // 03B2, beta
    {IV('??'), 'v', 0}, // 03B3, gamma
    {IV('??'), 'd', 0}, // 03B4, delta
    {IV('??'), 'e', 0}, // 03B5, epsilon
    {IV('??'), 'Z', 0}, // 03B6, zeta
    {IV('??'), 'n', 0}, // 03B7, eta
    {IV('??'), '0', 0}, // 03B8, theta
    {IV('??'), 'i', 0}, // 03B9, lota
    {IV('??'), 'k', 0}, // 03BA, kappa
    {IV('??'), 'L', 0}, // 03BB, lambda
    {IV('??'), 'u', 0}, // 03BC, mu
    {IV('??'), 'v', 0}, // 03BD, nu
    {IV('??'), 'e', 0}, // 03BE, xi
    {IV('??'), 'o', 0}, // 03BF
    {IV('??'), 'n', 0}, // 03C0, pi
    {IV('??'), 'p', 0}, // 03C1, rho
    {IV('??'), 'c', 0}, // 03C2
    {IV('??'), 'o', 0}, // 03C3, sigma
    {IV('??'), 't', 0}, // 03C4, tau
    {IV('??'), 'v', 0}, // 03C5, upsilon
    {IV('??'), 'p', 0}, // 03C6
    {IV('??'), 'X', 0}, // 03C7, chi
    {IV('??'), 'W', 0}, // 03C8, psi
    {IV('??'), 'w', 0}, // 03C9, omega
    {IV('??'), 'i', 0}, // 03CA
    {IV('??'), 'v', 0}, // 03CB
    {IV('??'), 'o', 0}, // 03CC
    {IV('??'), 'v', 0}, // 03CD
    {IV('??'), 'w', 0}, // 03CE

  #endif

  #if ENABLED(DISPLAY_CHARSET_ISO10646_5)
    // Map CYRILLIC code to plain ASCII
    {IV('??'), 'E', 0}, // 0401
    {IV('??'), 'A', 0}, // 0410
    {IV('??'), 'b', 0}, // 0411
    {IV('??'), 'B', 0}, // 0412
    {IV('??'), 'T', 0}, // 0413
    {IV('??'), 'Q', 0}, // 0414
    {IV('??'), 'E', 0}, // 0415
    {IV('??'), '*', 0}, // 0416
    {IV('??'), 'E', 0}, // 0417
    {IV('??'), 'N', 0}, // 0418
    {IV('??'), 'N', 0}, // 0419
    {IV('??'), 'K', 0}, // 041A
    {IV('??'), 'T', 0}, // 041B
    {IV('??'), 'M', 0}, // 041C
    {IV('??'), 'H', 0}, // 041D
    {IV('??'), 'O', 0}, // 041E
    {IV('??'), 'n', 0}, // 041F
    {IV('??'), 'P', 0}, // 0420
    {IV('??'), 'C', 0}, // 0421
    {IV('??'), 'T', 0}, // 0422
    {IV('??'), 'Y', 0},
    {IV('??'), 'o', 0},
    {IV('??'), 'X', 0},
    {IV('??'), 'U', 0},
    {IV('??'), 'y', 0},
    {IV('??'), 'W', 0},
    {IV('??'), 'W', 0},
    {IV('??'), 'b', 0},
    {IV('??'), 'b', '|'},
    {IV('??'), 'b'},
    {IV('??'), 'e'},
    {IV('??'), '|', 'O'},
    {IV('??'), '9', '|'}, // 042F

    {IV('??'), 'a', 0}, // 0430
    {IV('??'), '6', 0}, // 0431
    {IV('??'), 'B', 0}, // 0432,
    {IV('??'), 'r', 0}, // 0433
    {IV('??'), 'a', 0}, // 0434,
    {IV('??'), 'e', 0}, // 0435
    {IV('??'), '*', 0}, // 0436
    {IV('??'), 'e', 0}, // 0437,
    {IV('??'), 'u', 0}, // 0438
    {IV('??'), 'u', 0}, // 0439,
    {IV('??'), 'k', 0}, // 043A
    {IV('??'), 'n', 0},
    {IV('??'), 'm', 0},
    {IV('??'), 'H', 0},
    {IV('??'), 'o', 0},
    {IV('??'), 'n', 0},
    {IV('??'), 'p', 0},
    {IV('??'), 'c', 0},
    {IV('??'), 't', 0},
    {IV('??'), 'y', 0},
    {IV('??'), 'q', 'p'},
    {IV('??'), 'x', 0},
    {IV('??'), 'u', 0},
    {IV('??'), 'y', 0},
    {IV('??'), 'w', 0},
    {IV('??'), 'w', 0},
    {IV('??'), 'b', 0},
    {IV('??'), 'b', '|'},
    {IV('??'), 'b', 0},
    {IV('??'), 'e', 0},
    {IV('??'), '|', 'o'},
    {IV('??'), 'g', 0}, // 044F
    {IV('??'), 'e', 0}, // 0451
  #endif

  {IV('???'), '.', 0}, // 2022 ??
  {IV('???'), 'P', 'x'}, // 211E ??? Pt ASCII 158
  {IV('???'), 'T', 'M'}, // 2122
  {IV('???'), '<', '-'}, // 2190
  {IV('???'), '-', '>'}, // 2192, Marlin special: '??????????????????????????????' LCD_STR_ARROW_RIGHT (0x03)
  //{IV('???'), '<', 0}, // 21B0, Marlin special: '?????????????????????'  LCD_STR_UPLEVEL (0x04)
  {IV('???'), 0x03, 0}, // 21B0, Marlin special: '?????????????????????'  LCD_STR_UPLEVEL (0x04)
  {IV('???'), 0x04, 0}, // 21BB Marlin special: '????????????'  LCD_STR_REFRESH (0x01)
  {IV('???'), '~', 0}, // 223C
  {IV('???'), '~', '='}, // 2248
  {IV('???'), '!', '='}, // 2260
  {IV('???'), '=', 0}, // 2261
  {IV('???'), '<', '='},// 2264, ?????? ??????
  {IV('???'), '>', '='}, // 2265
  {IV('???'), 0x07, 0}, // 23F1, Marlin special: '???????????????????????????????????????????????????????????????????????????????????????????????? ?????????????????????'  LCD_STR_CLOCK (0x05)

  {IV('???'), '=', 0}, // 30A0

  // ????????????????????????
  // ????????????
  //{IV(''), 0x00, 0}, // Marlin special: ''  LCD_STR_BEDTEMP (0x07)
  {IV('????'), 0x02, 0}, // D83CDF21 Marlin special: '????'  LCD_STR_THERMOMETER (0x08)
  {IV('????'), 0x05, 0}, // D83DDCC2 Marlin special: '????????'  LCD_STR_FOLDER (0x02)
  //{IV(''), 0x06, 0}, // Marlin special: ''  LCD_STR_FEEDRATE (0x06)
};
