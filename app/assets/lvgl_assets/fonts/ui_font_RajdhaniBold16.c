/*******************************************************************************
 * Size: 16 px
 * Bpp: 4
 * Opts: --bpp 4 --size 16 --font F:/newshit/phoebe/lvgl_shit/assets/Rajdhani-Bold.ttf -o F:/newshit/phoebe/lvgl_shit/assets\ui_font_RajdhaniBold16.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "../ui.h"

#ifndef UI_FONT_RAJDHANIBOLD16
#define UI_FONT_RAJDHANIBOLD16 1
#endif

#if UI_FONT_RAJDHANIBOLD16

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0021 "!" */
    0x2f, 0xf3, 0xff, 0x3f, 0xf2, 0xff, 0x1f, 0xe0,
    0xfc, 0x7, 0x50, 0x88, 0x1f, 0xf1, 0xfe,

    /* U+0022 "\"" */
    0x5f, 0x5a, 0xf0, 0x3f, 0x38, 0xe0, 0x1f, 0x16,
    0xb0, 0x7, 0x2, 0x50,

    /* U+0023 "#" */
    0x0, 0x0, 0xf9, 0x8, 0xf0, 0x0, 0x0, 0x4f,
    0x50, 0xdc, 0x0, 0xa, 0xff, 0xff, 0xff, 0xff,
    0x10, 0x59, 0xfe, 0x9c, 0xfa, 0x90, 0x0, 0xf,
    0x90, 0x9f, 0x0, 0x0, 0x4, 0xf5, 0xd, 0xc0,
    0x0, 0x6f, 0xff, 0xff, 0xff, 0xf5, 0x3, 0x9f,
    0xe9, 0xcf, 0xa9, 0x30, 0x0, 0xf9, 0x9, 0xf0,
    0x0, 0x0, 0x3f, 0x50, 0xcc, 0x0, 0x0,

    /* U+0024 "$" */
    0x0, 0x8, 0xf0, 0x0, 0x0, 0x9, 0xf1, 0x0,
    0x5, 0xdf, 0xfe, 0x80, 0x1f, 0xf5, 0x5d, 0xf5,
    0x3f, 0xc0, 0x7, 0xf8, 0x3f, 0xf5, 0x32, 0x31,
    0xf, 0xff, 0xff, 0xa0, 0x3, 0xbe, 0xff, 0xf7,
    0x2, 0x10, 0x9, 0xfa, 0x3f, 0xd0, 0x6, 0xfa,
    0x1f, 0xfc, 0xbf, 0xf7, 0x5, 0xdf, 0xfe, 0x90,
    0x0, 0x9, 0xf1, 0x0, 0x0, 0x4, 0x70, 0x0,

    /* U+0025 "%" */
    0xa, 0xff, 0x90, 0xe, 0x70, 0x0, 0x2f, 0x56,
    0xf1, 0x6f, 0x10, 0x0, 0x3f, 0x23, 0xf2, 0xcb,
    0x0, 0x0, 0x2f, 0x34, 0xf5, 0xf4, 0x0, 0x0,
    0xb, 0xff, 0xa9, 0xd0, 0x0, 0x0, 0x0, 0x0,
    0x1f, 0x7b, 0xfe, 0x80, 0x0, 0x0, 0x7f, 0x5f,
    0x47, 0xf0, 0x0, 0x0, 0xda, 0x4f, 0x15, 0xf0,
    0x0, 0x4, 0xf3, 0x4f, 0x47, 0xf0, 0x0, 0xa,
    0xc0, 0xb, 0xff, 0x80,

    /* U+0026 "&" */
    0x0, 0x6d, 0xfe, 0x80, 0x0, 0x2, 0xff, 0xbf,
    0xf4, 0x0, 0x5, 0xfb, 0x8, 0xf8, 0x0, 0x4,
    0xfe, 0x2, 0x63, 0x0, 0x2, 0xff, 0xb0, 0x0,
    0x0, 0x1f, 0xfe, 0xff, 0xff, 0xf0, 0x5f, 0x92,
    0xef, 0xeb, 0xb0, 0x5f, 0x90, 0x3f, 0xf4, 0x0,
    0x2f, 0xfc, 0xdf, 0xff, 0x30, 0x7, 0xef, 0xfb,
    0x6f, 0xe1,

    /* U+0027 "'" */
    0x28, 0x23, 0xf3, 0xe, 0x0,

    /* U+0028 "(" */
    0x3, 0xcf, 0x0, 0xee, 0x70, 0x3f, 0x60, 0x4,
    0xf5, 0x0, 0x5f, 0x50, 0x5, 0xf5, 0x0, 0x5f,
    0x50, 0x4, 0xf5, 0x0, 0x3f, 0x50, 0x1, 0xfb,
    0x20, 0x6, 0xff, 0x0, 0x1, 0x30,

    /* U+0029 ")" */
    0x4e, 0xa1, 0x1, 0x8f, 0x90, 0x0, 0xbe, 0x0,
    0x9, 0xf0, 0x0, 0x9f, 0x0, 0x9, 0xf0, 0x0,
    0x9f, 0x0, 0x9, 0xf0, 0x0, 0xaf, 0x0, 0x3e,
    0xb0, 0x4f, 0xe3, 0x1, 0x30, 0x0,

    /* U+002A "*" */
    0x0, 0x8d, 0x0, 0x2a, 0x7b, 0x98, 0x2a, 0xbd,
    0xa5, 0x5, 0xfa, 0xc0, 0x5, 0x82, 0x90,

    /* U+002B "+" */
    0x0, 0x4f, 0x50, 0x0, 0x5, 0xf6, 0x0, 0x8a,
    0xcf, 0xca, 0x8d, 0xff, 0xff, 0xfe, 0x0, 0x5f,
    0x60, 0x0, 0x5, 0xf6, 0x0, 0x0, 0x3a, 0x30,
    0x0,

    /* U+002C "," */
    0x13, 0x26, 0xfa, 0x6f, 0x96, 0xf2, 0x56, 0x0,

    /* U+002D "-" */
    0x39, 0x99, 0x35, 0xff, 0xf5,

    /* U+002E "." */
    0x39, 0x56, 0xfa, 0x5f, 0xa0,

    /* U+002F "/" */
    0x0, 0x0, 0xef, 0x0, 0x0, 0x5f, 0x90, 0x0,
    0xb, 0xf3, 0x0, 0x1, 0xfd, 0x0, 0x0, 0x7f,
    0x60, 0x0, 0xd, 0xf1, 0x0, 0x4, 0xfa, 0x0,
    0x0, 0xaf, 0x40, 0x0, 0x1f, 0xd0, 0x0, 0x6,
    0xf7, 0x0, 0x0,

    /* U+0030 "0" */
    0x4, 0xdf, 0xfe, 0xa0, 0xe, 0xfc, 0xbe, 0xf7,
    0x2f, 0xe0, 0x5, 0xfb, 0x2f, 0xe0, 0x4, 0xfb,
    0x2f, 0xe0, 0x4, 0xfb, 0x2f, 0xe0, 0x4, 0xfb,
    0x2f, 0xe0, 0x4, 0xfb, 0x2f, 0xe0, 0x5, 0xfb,
    0xe, 0xfc, 0xbe, 0xf8, 0x4, 0xdf, 0xff, 0xa0,

    /* U+0031 "1" */
    0x7, 0xef, 0x48, 0xff, 0xf4, 0x98, 0xcf, 0x40,
    0xb, 0xf4, 0x0, 0xbf, 0x40, 0xb, 0xf4, 0x0,
    0xbf, 0x40, 0xb, 0xf4, 0x0, 0xbf, 0x40, 0xb,
    0xf4,

    /* U+0032 "2" */
    0x5, 0xdf, 0xfd, 0x40, 0x1f, 0xfb, 0xbf, 0xf0,
    0x4f, 0xb0, 0xd, 0xf2, 0x16, 0x40, 0xe, 0xf1,
    0x0, 0x1, 0xbf, 0xb0, 0x0, 0x2d, 0xfb, 0x0,
    0x4, 0xff, 0x80, 0x0, 0x1f, 0xf6, 0x0, 0x0,
    0x3f, 0xfc, 0xcc, 0xb1, 0x3f, 0xff, 0xff, 0xf2,

    /* U+0033 "3" */
    0x7, 0xef, 0xfd, 0x50, 0x3f, 0xfb, 0xbf, 0xf1,
    0x6f, 0xa0, 0xb, 0xf4, 0x2, 0x10, 0xd, 0xf3,
    0x0, 0xc, 0xff, 0x90, 0x0, 0x7, 0xaf, 0xe1,
    0x26, 0x30, 0xb, 0xf4, 0x6f, 0xa0, 0xb, 0xf4,
    0x2f, 0xfa, 0xbf, 0xf1, 0x6, 0xef, 0xfd, 0x50,

    /* U+0034 "4" */
    0x0, 0x2, 0xff, 0xe0, 0x0, 0x0, 0xbf, 0xff,
    0x0, 0x0, 0x4f, 0x9e, 0xf0, 0x0, 0xd, 0xf1,
    0xef, 0x0, 0x6, 0xf7, 0xe, 0xf0, 0x0, 0xee,
    0x0, 0xef, 0x0, 0x6f, 0xeb, 0xbf, 0xfb, 0x46,
    0xff, 0xff, 0xff, 0xf7, 0x0, 0x0, 0xe, 0xf0,
    0x0, 0x0, 0x0, 0xef, 0x0,

    /* U+0035 "5" */
    0x1f, 0xff, 0xff, 0xf1, 0x2f, 0xfd, 0xdd, 0xd1,
    0x2f, 0xe0, 0x0, 0x0, 0x2f, 0xe5, 0x98, 0x20,
    0x2f, 0xff, 0xff, 0xf1, 0x1a, 0x91, 0xb, 0xf5,
    0x2, 0x10, 0x9, 0xf6, 0x4f, 0xc0, 0xa, 0xf5,
    0x1f, 0xfb, 0xaf, 0xf2, 0x5, 0xdf, 0xfe, 0x70,

    /* U+0036 "6" */
    0x4, 0xdf, 0xff, 0xf0, 0xe, 0xfc, 0xbb, 0xb0,
    0x2f, 0xe0, 0x0, 0x0, 0x2f, 0xfb, 0xba, 0x50,
    0x2f, 0xff, 0xff, 0xf4, 0x2f, 0xd0, 0x8, 0xf9,
    0x2f, 0xd0, 0x5, 0xfb, 0x2f, 0xe0, 0x6, 0xfa,
    0xf, 0xfc, 0xbe, 0xf6, 0x4, 0xdf, 0xfe, 0x90,

    /* U+0037 "7" */
    0xaf, 0xff, 0xff, 0x88, 0xdd, 0xde, 0xf8, 0x0,
    0x0, 0xdf, 0x50, 0x0, 0x5f, 0xe0, 0x0, 0xb,
    0xf7, 0x0, 0x2, 0xff, 0x10, 0x0, 0x9f, 0xa0,
    0x0, 0x1f, 0xf3, 0x0, 0x7, 0xfc, 0x0, 0x0,
    0xdf, 0x50, 0x0,

    /* U+0038 "8" */
    0x5, 0xdf, 0xff, 0xb1, 0xf, 0xfc, 0xbd, 0xfa,
    0x2f, 0xe0, 0x3, 0xfc, 0x1f, 0xf1, 0x5, 0xfb,
    0x8, 0xff, 0xff, 0xf3, 0xd, 0xfa, 0x9c, 0xf7,
    0x2f, 0xe0, 0x3, 0xfc, 0x2f, 0xe0, 0x3, 0xfc,
    0xf, 0xfc, 0xbd, 0xf9, 0x4, 0xdf, 0xff, 0xb1,

    /* U+0039 "9" */
    0x5, 0xdf, 0xfe, 0x80, 0x1f, 0xfc, 0xbf, 0xf5,
    0x4f, 0xc0, 0x8, 0xf8, 0x5f, 0xb0, 0x7, 0xf8,
    0x4f, 0xd0, 0x7, 0xf8, 0xe, 0xff, 0xff, 0xf8,
    0x2, 0x9b, 0xbd, 0xf8, 0x0, 0x0, 0x8, 0xf8,
    0x9, 0xbb, 0xbf, 0xf5, 0xc, 0xff, 0xfe, 0x80,

    /* U+003A ":" */
    0x5f, 0xa6, 0xfa, 0x28, 0x50, 0x0, 0x0, 0x3,
    0x95, 0x6f, 0xa5, 0xfa,

    /* U+003B ";" */
    0x5f, 0xa6, 0xfa, 0x28, 0x50, 0x0, 0x0, 0x1,
    0x32, 0x6f, 0xa6, 0xf9, 0x6f, 0x25, 0x60,

    /* U+003C "<" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x27, 0xce, 0x27,
    0xcf, 0xfe, 0x9d, 0xfb, 0x62, 0x0, 0xcf, 0xea,
    0x62, 0x0, 0x38, 0xdf, 0xfc, 0x0, 0x0, 0x27,
    0xa0,

    /* U+003D "=" */
    0x79, 0x99, 0x99, 0x8d, 0xff, 0xff, 0xfe, 0x0,
    0x0, 0x0, 0x7, 0x99, 0x99, 0x98, 0xdf, 0xff,
    0xff, 0xe0,

    /* U+003E ">" */
    0x0, 0x0, 0x0, 0xd, 0xc7, 0x20, 0x0, 0x8e,
    0xff, 0xd8, 0x20, 0x2, 0x6b, 0xfe, 0x2, 0x6a,
    0xef, 0xcc, 0xff, 0xd8, 0x30, 0xa8, 0x30, 0x0,
    0x0,

    /* U+003F "?" */
    0x6, 0xef, 0xfb, 0x12, 0xff, 0xbd, 0xf9, 0x5f,
    0xa0, 0x3f, 0xc1, 0x31, 0xa, 0xf8, 0x0, 0xc,
    0xf9, 0x0, 0x4, 0xfb, 0x0, 0x0, 0x16, 0x30,
    0x0, 0x3, 0x95, 0x0, 0x0, 0x6f, 0xa0, 0x0,
    0x6, 0xf9, 0x0,

    /* U+0040 "@" */
    0x0, 0x4c, 0xff, 0xff, 0xe9, 0x10, 0x5, 0xf7,
    0x34, 0x44, 0x5c, 0xb0, 0xd, 0x62, 0xdf, 0xff,
    0xa1, 0xf1, 0x1f, 0x19, 0xf7, 0x5f, 0xa0, 0xf2,
    0x1f, 0x1c, 0xf0, 0xf, 0xa0, 0xf2, 0x1f, 0x1c,
    0xf0, 0xf, 0xa0, 0xf2, 0x1f, 0x1a, 0xf6, 0x8f,
    0xa3, 0xf1, 0xf, 0x53, 0xef, 0xce, 0xff, 0x90,
    0x8, 0xe4, 0x12, 0x0, 0x21, 0x0, 0x0, 0x6e,
    0xff, 0xff, 0x20, 0x0, 0x0, 0x0, 0x12, 0x22,
    0x0, 0x0,

    /* U+0041 "A" */
    0x0, 0x2f, 0xff, 0x0, 0x0, 0x6, 0xff, 0xf5,
    0x0, 0x0, 0xaf, 0x9f, 0x90, 0x0, 0xe, 0xf2,
    0xfd, 0x0, 0x3, 0xfc, 0xd, 0xf2, 0x0, 0x7f,
    0x80, 0x9f, 0x60, 0xc, 0xfb, 0x9c, 0xfa, 0x0,
    0xff, 0xff, 0xff, 0xe0, 0x4f, 0xc0, 0x0, 0xdf,
    0x38, 0xf7, 0x0, 0x9, 0xf7,

    /* U+0042 "B" */
    0xef, 0xff, 0xfb, 0x1f, 0xfb, 0xad, 0xfa, 0xff,
    0x10, 0x2f, 0xdf, 0xf1, 0x4, 0xfc, 0xff, 0xff,
    0xfe, 0x4f, 0xfa, 0xab, 0xfa, 0xff, 0x10, 0xf,
    0xff, 0xf1, 0x0, 0xff, 0xff, 0xba, 0xcf, 0xce,
    0xff, 0xff, 0xc2,

    /* U+0043 "C" */
    0x3, 0xdf, 0xff, 0xb1, 0xe, 0xfd, 0xbe, 0xfa,
    0x1f, 0xf0, 0x2, 0xfe, 0x2f, 0xe0, 0x0, 0x98,
    0x2f, 0xe0, 0x0, 0x0, 0x2f, 0xe0, 0x0, 0x0,
    0x2f, 0xe0, 0x0, 0x98, 0x1f, 0xe0, 0x2, 0xfe,
    0xe, 0xfc, 0xbd, 0xfa, 0x4, 0xdf, 0xff, 0xb1,

    /* U+0044 "D" */
    0xef, 0xff, 0xfb, 0x2f, 0xfc, 0xbd, 0xfb, 0xff,
    0x10, 0x1f, 0xff, 0xf1, 0x1, 0xff, 0xff, 0x10,
    0x1f, 0xff, 0xf1, 0x1, 0xff, 0xff, 0x10, 0x1f,
    0xff, 0xf1, 0x1, 0xff, 0xff, 0xcb, 0xdf, 0xbe,
    0xff, 0xff, 0xc2,

    /* U+0045 "E" */
    0xef, 0xff, 0xfe, 0xff, 0xcb, 0xba, 0xff, 0x10,
    0x0, 0xff, 0x10, 0x0, 0xff, 0xff, 0xf5, 0xff,
    0xcb, 0xb3, 0xff, 0x10, 0x0, 0xff, 0x10, 0x0,
    0xff, 0xcb, 0xba, 0xef, 0xff, 0xfe,

    /* U+0046 "F" */
    0xef, 0xff, 0xfc, 0xff, 0xcb, 0xb8, 0xff, 0x10,
    0x0, 0xff, 0x10, 0x0, 0xff, 0xcb, 0xb3, 0xff,
    0xff, 0xf5, 0xff, 0x10, 0x0, 0xff, 0x10, 0x0,
    0xff, 0x10, 0x0, 0xef, 0x0, 0x0,

    /* U+0047 "G" */
    0x3, 0xdf, 0xff, 0xb1, 0xe, 0xfd, 0xbe, 0xfa,
    0x1f, 0xf0, 0x3, 0xfd, 0x2f, 0xe0, 0x0, 0x32,
    0x2f, 0xe0, 0x7b, 0xb9, 0x2f, 0xe0, 0xaf, 0xfd,
    0x2f, 0xe0, 0x3, 0xfd, 0x1f, 0xe0, 0x3, 0xfc,
    0xe, 0xfc, 0xbe, 0xf9, 0x4, 0xdf, 0xff, 0xb1,

    /* U+0048 "H" */
    0xef, 0x0, 0xd, 0xf2, 0xff, 0x10, 0xd, 0xf2,
    0xff, 0x10, 0xd, 0xf2, 0xff, 0x10, 0xd, 0xf2,
    0xff, 0xff, 0xff, 0xf2, 0xff, 0xcb, 0xbf, 0xf2,
    0xff, 0x10, 0xd, 0xf2, 0xff, 0x10, 0xd, 0xf2,
    0xff, 0x10, 0xd, 0xf2, 0xef, 0x0, 0xd, 0xf2,

    /* U+0049 "I" */
    0xdf, 0x2e, 0xf2, 0xef, 0x2e, 0xf2, 0xef, 0x2e,
    0xf2, 0xef, 0x2e, 0xf2, 0xef, 0x2d, 0xf2,

    /* U+004A "J" */
    0x0, 0x0, 0xa, 0xf5, 0x0, 0x0, 0xa, 0xf6,
    0x0, 0x0, 0xa, 0xf6, 0x0, 0x0, 0xa, 0xf6,
    0x0, 0x0, 0xa, 0xf6, 0x25, 0x20, 0xa, 0xf6,
    0x7f, 0x80, 0xa, 0xf6, 0x7f, 0x90, 0xb, 0xf5,
    0x4f, 0xfb, 0xbf, 0xf2, 0x8, 0xef, 0xfe, 0x60,

    /* U+004B "K" */
    0xef, 0x0, 0x2e, 0xf3, 0xff, 0x10, 0xcf, 0x80,
    0xff, 0x17, 0xfc, 0x0, 0xff, 0x4f, 0xe1, 0x0,
    0xff, 0xdf, 0x70, 0x0, 0xff, 0xff, 0xe1, 0x0,
    0xff, 0x88, 0xfa, 0x0, 0xff, 0x10, 0xdf, 0x50,
    0xff, 0x10, 0x3f, 0xe1, 0xef, 0x0, 0x8, 0xf9,

    /* U+004C "L" */
    0xef, 0x0, 0x0, 0xff, 0x10, 0x0, 0xff, 0x10,
    0x0, 0xff, 0x10, 0x0, 0xff, 0x10, 0x0, 0xff,
    0x10, 0x0, 0xff, 0x10, 0x0, 0xff, 0x10, 0x0,
    0xff, 0xcb, 0xba, 0xef, 0xff, 0xfe,

    /* U+004D "M" */
    0xef, 0xf2, 0x0, 0x7f, 0xf8, 0xff, 0xf7, 0x0,
    0xdf, 0xf9, 0xff, 0xdc, 0x2, 0xfe, 0xf9, 0xff,
    0x8f, 0x17, 0xf8, 0xf9, 0xff, 0x3f, 0x6c, 0xd6,
    0xf9, 0xff, 0xe, 0xcf, 0x86, 0xf9, 0xff, 0x9,
    0xff, 0x36, 0xf9, 0xff, 0x3, 0xcb, 0x6, 0xf9,
    0xff, 0x0, 0x0, 0x6, 0xf9, 0xef, 0x0, 0x0,
    0x6, 0xf8,

    /* U+004E "N" */
    0xef, 0x30, 0xa, 0xf4, 0xff, 0xb0, 0xb, 0xf5,
    0xff, 0xf4, 0xb, 0xf5, 0xff, 0xfd, 0xb, 0xf5,
    0xff, 0x9f, 0x5b, 0xf5, 0xff, 0x1f, 0xeb, 0xf5,
    0xff, 0x7, 0xff, 0xf5, 0xff, 0x0, 0xef, 0xf5,
    0xff, 0x0, 0x5f, 0xf5, 0xef, 0x0, 0xc, 0xf4,

    /* U+004F "O" */
    0x3, 0xdf, 0xff, 0xc2, 0xe, 0xfd, 0xbd, 0xfb,
    0x1f, 0xe0, 0x1, 0xfe, 0x2f, 0xe0, 0x1, 0xff,
    0x2f, 0xe0, 0x1, 0xff, 0x2f, 0xe0, 0x1, 0xff,
    0x2f, 0xe0, 0x1, 0xff, 0x1f, 0xe0, 0x1, 0xfe,
    0xe, 0xfc, 0xbd, 0xfb, 0x4, 0xdf, 0xff, 0xc2,

    /* U+0050 "P" */
    0xef, 0xff, 0xfb, 0x1f, 0xfc, 0xbe, 0xfa, 0xff,
    0x10, 0x2f, 0xef, 0xf1, 0x2, 0xfe, 0xff, 0x10,
    0x4f, 0xdf, 0xff, 0xff, 0xf8, 0xff, 0xcb, 0xb7,
    0xf, 0xf1, 0x0, 0x0, 0xff, 0x10, 0x0, 0xe,
    0xf0, 0x0, 0x0,

    /* U+0051 "Q" */
    0x2c, 0xff, 0xfc, 0x30, 0xcf, 0xdb, 0xdf, 0xd0,
    0xff, 0x10, 0xf, 0xf0, 0xff, 0x10, 0xf, 0xf1,
    0xff, 0x10, 0xf, 0xf1, 0xff, 0x10, 0xf, 0xf1,
    0xff, 0x10, 0xf, 0xf1, 0xff, 0x10, 0xf, 0xf0,
    0xcf, 0xdb, 0xdf, 0xd0, 0x2c, 0xff, 0xfd, 0x30,
    0x0, 0x9, 0xf7, 0x0, 0x0, 0x1, 0xef, 0x10,

    /* U+0052 "R" */
    0xef, 0xff, 0xfb, 0x10, 0xff, 0xcb, 0xef, 0xa0,
    0xff, 0x10, 0x3f, 0xd0, 0xff, 0x10, 0x3f, 0xd0,
    0xff, 0xa9, 0xcf, 0xa0, 0xff, 0xff, 0xfc, 0x10,
    0xff, 0x17, 0xfb, 0x0, 0xff, 0x10, 0xff, 0x20,
    0xff, 0x10, 0x9f, 0xa0, 0xef, 0x0, 0x2f, 0xf0,

    /* U+0053 "S" */
    0x4, 0xdf, 0xfe, 0x90, 0xf, 0xfd, 0xbf, 0xf7,
    0x3f, 0xd0, 0x6, 0xfa, 0x3f, 0xe1, 0x0, 0x31,
    0xe, 0xff, 0xeb, 0x60, 0x2, 0x9d, 0xff, 0xf7,
    0x3, 0x20, 0x7, 0xfc, 0x3f, 0xd0, 0x3, 0xfd,
    0xf, 0xfc, 0xbe, 0xf9, 0x4, 0xdf, 0xff, 0xb1,

    /* U+0054 "T" */
    0xcf, 0xff, 0xff, 0xe9, 0xbd, 0xfe, 0xba, 0x0,
    0x7f, 0x90, 0x0, 0x7, 0xf9, 0x0, 0x0, 0x7f,
    0x90, 0x0, 0x7, 0xf9, 0x0, 0x0, 0x7f, 0x90,
    0x0, 0x7, 0xf9, 0x0, 0x0, 0x7f, 0x90, 0x0,
    0x7, 0xf8, 0x0,

    /* U+0055 "U" */
    0xf, 0xf0, 0x0, 0xff, 0xf, 0xf0, 0x0, 0xff,
    0xf, 0xf0, 0x0, 0xff, 0xf, 0xf0, 0x0, 0xff,
    0xf, 0xf0, 0x0, 0xff, 0xf, 0xf0, 0x0, 0xff,
    0xf, 0xf0, 0x0, 0xff, 0xf, 0xf0, 0x1, 0xff,
    0xd, 0xfd, 0xbd, 0xfc, 0x3, 0xcf, 0xff, 0xc2,

    /* U+0056 "V" */
    0xaf, 0x70, 0x2, 0xff, 0x7, 0xfb, 0x0, 0x5f,
    0xc0, 0x2f, 0xe0, 0x9, 0xf8, 0x0, 0xef, 0x20,
    0xcf, 0x40, 0xa, 0xf6, 0xf, 0xf0, 0x0, 0x6f,
    0x94, 0xfb, 0x0, 0x1, 0xfd, 0x7f, 0x70, 0x0,
    0xd, 0xfb, 0xf3, 0x0, 0x0, 0x9f, 0xfe, 0x0,
    0x0, 0x4, 0xff, 0xa0, 0x0,

    /* U+0057 "W" */
    0xbf, 0x90, 0xd, 0xfb, 0x0, 0xbf, 0x98, 0xfc,
    0x0, 0xff, 0xe0, 0xd, 0xf7, 0x5f, 0xe0, 0x3f,
    0xef, 0x20, 0xff, 0x42, 0xff, 0x7, 0xf7, 0xf5,
    0x1f, 0xf1, 0xf, 0xf1, 0xaf, 0x1f, 0x83, 0xfe,
    0x0, 0xdf, 0x3d, 0xc0, 0xeb, 0x5f, 0xb0, 0xa,
    0xf6, 0xf9, 0xb, 0xf7, 0xf8, 0x0, 0x7f, 0xbf,
    0x60, 0x7f, 0xbf, 0x50, 0x4, 0xff, 0xf3, 0x4,
    0xff, 0xf2, 0x0, 0x1f, 0xff, 0x0, 0x1f, 0xfe,
    0x0,

    /* U+0058 "X" */
    0x6f, 0xc0, 0x3, 0xff, 0x10, 0xef, 0x40, 0xaf,
    0x80, 0x6, 0xfb, 0x2f, 0xf1, 0x0, 0xd, 0xfb,
    0xf7, 0x0, 0x0, 0x5f, 0xfe, 0x0, 0x0, 0x7,
    0xff, 0xf1, 0x0, 0x0, 0xef, 0xbf, 0x90, 0x0,
    0x7f, 0xb1, 0xff, 0x20, 0xe, 0xf3, 0x9, 0xf9,
    0x7, 0xfc, 0x0, 0x2f, 0xf1,

    /* U+0059 "Y" */
    0xbf, 0x80, 0x4, 0xfe, 0x3, 0xff, 0x0, 0xbf,
    0x80, 0xc, 0xf6, 0x2f, 0xf1, 0x0, 0x4f, 0xd8,
    0xf8, 0x0, 0x0, 0xcf, 0xff, 0x10, 0x0, 0x4,
    0xff, 0x90, 0x0, 0x0, 0xe, 0xf2, 0x0, 0x0,
    0x0, 0xef, 0x20, 0x0, 0x0, 0xe, 0xf2, 0x0,
    0x0, 0x0, 0xdf, 0x20, 0x0,

    /* U+005A "Z" */
    0xe, 0xff, 0xff, 0xf5, 0xc, 0xee, 0xef, 0xf5,
    0x0, 0x0, 0x3f, 0xf2, 0x0, 0x0, 0xdf, 0x60,
    0x0, 0x9, 0xfb, 0x0, 0x0, 0x4f, 0xe1, 0x0,
    0x1, 0xef, 0x50, 0x0, 0xb, 0xf9, 0x0, 0x0,
    0x2f, 0xfe, 0xee, 0xe7, 0x3f, 0xff, 0xff, 0xf8,

    /* U+005B "[" */
    0xbf, 0xf2, 0xce, 0x50, 0xcd, 0x0, 0xcd, 0x0,
    0xcd, 0x0, 0xcd, 0x0, 0xcd, 0x0, 0xcd, 0x0,
    0xcd, 0x0, 0xce, 0x0, 0xcf, 0xf2, 0x24, 0x30,

    /* U+005C "\\" */
    0x6f, 0x70, 0x0, 0x1, 0xfd, 0x0, 0x0, 0xa,
    0xf4, 0x0, 0x0, 0x4f, 0xa0, 0x0, 0x0, 0xdf,
    0x10, 0x0, 0x7, 0xf6, 0x0, 0x0, 0x1f, 0xc0,
    0x0, 0x0, 0xbf, 0x30, 0x0, 0x5, 0xf9, 0x0,
    0x0, 0xe, 0xf0,

    /* U+005D "]" */
    0xf, 0xfe, 0x5, 0xde, 0x0, 0xbe, 0x0, 0xbe,
    0x0, 0xbe, 0x0, 0xbe, 0x0, 0xbe, 0x0, 0xbe,
    0x0, 0xbe, 0x0, 0xce, 0xf, 0xfe, 0x3, 0x43,

    /* U+005E "^" */
    0x0, 0x17, 0x72, 0x0, 0x0, 0x9f, 0xfc, 0x0,
    0x2, 0xfb, 0x9f, 0x40, 0xa, 0xf3, 0x1f, 0xc0,
    0x2f, 0xb0, 0x8, 0xf4,

    /* U+005F "_" */
    0xef, 0xff, 0xfd, 0x12, 0x22, 0x21,

    /* U+0060 "`" */
    0x0, 0x0, 0x0, 0xdf, 0x40, 0x2, 0xeb, 0x0,

    /* U+0061 "a" */
    0x5, 0xdf, 0xff, 0xf6, 0x1f, 0xfc, 0xbe, 0xf6,
    0x4f, 0xc0, 0xa, 0xf6, 0x4f, 0xc0, 0xa, 0xf6,
    0x4f, 0xc0, 0xa, 0xf6, 0x4f, 0xc0, 0xb, 0xf6,
    0x1f, 0xfc, 0xcf, 0xf6, 0x5, 0xdf, 0xdb, 0xf6,

    /* U+0062 "b" */
    0x1f, 0xe0, 0x0, 0x0, 0x2f, 0xe0, 0x0, 0x0,
    0x2f, 0xe0, 0x0, 0x0, 0x2f, 0xe9, 0xfe, 0xa0,
    0x2f, 0xfd, 0xbe, 0xf7, 0x2f, 0xf0, 0x6, 0xfa,
    0x2f, 0xe0, 0x5, 0xfb, 0x2f, 0xe0, 0x5, 0xfb,
    0x2f, 0xe0, 0x6, 0xfa, 0x2f, 0xfb, 0xbe, 0xf7,
    0x1f, 0xff, 0xfe, 0xa0,

    /* U+0063 "c" */
    0x5, 0xdf, 0xff, 0x1, 0xff, 0xcb, 0xb0, 0x4f,
    0xc0, 0x0, 0x4, 0xfc, 0x0, 0x0, 0x4f, 0xc0,
    0x0, 0x4, 0xfc, 0x0, 0x0, 0x1f, 0xfc, 0xbb,
    0x0, 0x5d, 0xff, 0xf1,

    /* U+0064 "d" */
    0x0, 0x0, 0x7, 0xf8, 0x0, 0x0, 0x8, 0xf8,
    0x0, 0x0, 0x8, 0xf8, 0x6, 0xef, 0xdb, 0xf8,
    0x1f, 0xfc, 0xcf, 0xf8, 0x4f, 0xc0, 0x9, 0xf8,
    0x4f, 0xc0, 0x8, 0xf8, 0x4f, 0xc0, 0x8, 0xf8,
    0x4f, 0xc0, 0x9, 0xf8, 0x1f, 0xfc, 0xbf, 0xf8,
    0x6, 0xef, 0xda, 0xf8,

    /* U+0065 "e" */
    0x5, 0xdf, 0xfd, 0x40, 0x1f, 0xfb, 0xbf, 0xf0,
    0x4f, 0xc0, 0xc, 0xf3, 0x4f, 0xc1, 0x1c, 0xf4,
    0x4f, 0xff, 0xff, 0xf4, 0x4f, 0xd4, 0x44, 0x30,
    0x1f, 0xfb, 0xbb, 0xa2, 0x5, 0xdf, 0xff, 0xf3,

    /* U+0066 "f" */
    0x0, 0x7e, 0xf6, 0x2, 0xff, 0xb4, 0x5, 0xfb,
    0x0, 0x9f, 0xff, 0xf6, 0x6d, 0xfe, 0xb4, 0x6,
    0xfa, 0x0, 0x6, 0xfa, 0x0, 0x6, 0xfa, 0x0,
    0x6, 0xfa, 0x0, 0x6, 0xfa, 0x0, 0x5, 0xfa,
    0x0,

    /* U+0067 "g" */
    0x5, 0xdf, 0xff, 0xf6, 0x1f, 0xfc, 0xbe, 0xf6,
    0x3f, 0xc0, 0x9, 0xf6, 0x4f, 0xc0, 0x9, 0xf6,
    0x4f, 0xc0, 0x9, 0xf6, 0x3f, 0xc0, 0xb, 0xf6,
    0x1f, 0xfc, 0xcf, 0xf6, 0x5, 0xef, 0xcb, 0xf6,
    0x0, 0x0, 0xa, 0xf6, 0x6, 0xbb, 0xcf, 0xf2,
    0x9, 0xff, 0xfe, 0x60,

    /* U+0068 "h" */
    0x1f, 0xe0, 0x0, 0x0, 0x2f, 0xe0, 0x0, 0x0,
    0x2f, 0xe0, 0x0, 0x0, 0x2f, 0xea, 0xfe, 0x90,
    0x2f, 0xfd, 0xbf, 0xf5, 0x2f, 0xf0, 0x8, 0xf8,
    0x2f, 0xe0, 0x7, 0xf9, 0x2f, 0xe0, 0x7, 0xf9,
    0x2f, 0xe0, 0x7, 0xf9, 0x2f, 0xe0, 0x7, 0xf9,
    0x1f, 0xe0, 0x7, 0xf8,

    /* U+0069 "i" */
    0xf, 0xf0, 0xff, 0x0, 0x0, 0xff, 0xf, 0xf0,
    0xff, 0xf, 0xf0, 0xff, 0xf, 0xf0, 0xff, 0xf,
    0xf0,

    /* U+006A "j" */
    0x0, 0xf, 0xf0, 0x0, 0xff, 0x0, 0x0, 0x0,
    0x0, 0xff, 0x0, 0xf, 0xf0, 0x0, 0xff, 0x0,
    0xf, 0xf0, 0x0, 0xff, 0x0, 0xf, 0xf0, 0x0,
    0xff, 0x0, 0x1f, 0xf0, 0xbe, 0xfc, 0xf, 0xfc,
    0x20,

    /* U+006B "k" */
    0x1f, 0xe0, 0x0, 0x0, 0x2f, 0xe0, 0x0, 0x0,
    0x2f, 0xe0, 0x0, 0x0, 0x2f, 0xe0, 0x2f, 0xf3,
    0x2f, 0xe0, 0xaf, 0xa0, 0x2f, 0xe3, 0xfe, 0x10,
    0x2f, 0xec, 0xf6, 0x0, 0x2f, 0xeb, 0xf8, 0x0,
    0x2f, 0xe2, 0xff, 0x20, 0x2f, 0xe0, 0x8f, 0xb0,
    0x1f, 0xe0, 0xe, 0xf4,

    /* U+006C "l" */
    0xf, 0xf0, 0xff, 0xf, 0xf0, 0xff, 0xf, 0xf0,
    0xff, 0xf, 0xf0, 0xff, 0xf, 0xf0, 0xff, 0xf,
    0xf0,

    /* U+006D "m" */
    0x1f, 0xe9, 0xfe, 0x86, 0xef, 0xc2, 0x2f, 0xfd,
    0xbf, 0xff, 0xbd, 0xfc, 0x2f, 0xf0, 0x9, 0xf9,
    0x1, 0xfe, 0x2f, 0xe0, 0x8, 0xf7, 0x1, 0xff,
    0x2f, 0xe0, 0x8, 0xf7, 0x1, 0xff, 0x2f, 0xe0,
    0x8, 0xf7, 0x1, 0xff, 0x2f, 0xe0, 0x8, 0xf7,
    0x1, 0xff, 0x1f, 0xe0, 0x8, 0xf7, 0x0, 0xfe,

    /* U+006E "n" */
    0x1f, 0xea, 0xfe, 0x90, 0x2f, 0xfd, 0xbf, 0xf5,
    0x2f, 0xf0, 0x8, 0xf8, 0x2f, 0xe0, 0x7, 0xf9,
    0x2f, 0xe0, 0x7, 0xf9, 0x2f, 0xe0, 0x7, 0xf9,
    0x2f, 0xe0, 0x7, 0xf9, 0x1f, 0xe0, 0x7, 0xf8,

    /* U+006F "o" */
    0x5, 0xdf, 0xfe, 0x60, 0x1f, 0xfb, 0xbf, 0xf3,
    0x4f, 0xc0, 0x9, 0xf6, 0x4f, 0xb0, 0x9, 0xf6,
    0x4f, 0xb0, 0x9, 0xf6, 0x4f, 0xc0, 0x9, 0xf6,
    0x1f, 0xfb, 0xbf, 0xf3, 0x5, 0xdf, 0xfe, 0x70,

    /* U+0070 "p" */
    0x1f, 0xe9, 0xff, 0xa0, 0x2f, 0xfd, 0xbe, 0xf8,
    0x2f, 0xf0, 0x6, 0xfa, 0x2f, 0xe0, 0x5, 0xfb,
    0x2f, 0xe0, 0x5, 0xfb, 0x2f, 0xf0, 0x6, 0xfa,
    0x2f, 0xfd, 0xbe, 0xf8, 0x2f, 0xea, 0xff, 0xa0,
    0x2f, 0xe0, 0x0, 0x0, 0x1f, 0xe0, 0x0, 0x0,

    /* U+0071 "q" */
    0x5, 0xdf, 0xff, 0xf6, 0x1f, 0xfc, 0xbe, 0xf6,
    0x4f, 0xc0, 0xa, 0xf6, 0x4f, 0xc0, 0xa, 0xf6,
    0x4f, 0xc0, 0xa, 0xf6, 0x4f, 0xc0, 0xb, 0xf6,
    0x1f, 0xfc, 0xcf, 0xf6, 0x5, 0xdf, 0xcb, 0xf6,
    0x0, 0x0, 0xa, 0xf6, 0x0, 0x0, 0x9, 0xf6,

    /* U+0072 "r" */
    0x1f, 0xe9, 0xf6, 0x2f, 0xfd, 0xb4, 0x2f, 0xf0,
    0x0, 0x2f, 0xe0, 0x0, 0x2f, 0xe0, 0x0, 0x2f,
    0xe0, 0x0, 0x2f, 0xe0, 0x0, 0x1f, 0xe0, 0x0,

    /* U+0073 "s" */
    0xa, 0xff, 0xff, 0x5, 0xff, 0xaa, 0xa0, 0x6f,
    0xd1, 0x0, 0x0, 0xcf, 0xf7, 0x0, 0x0, 0x6e,
    0xfd, 0x10, 0x0, 0xc, 0xf6, 0x3a, 0xaa, 0xef,
    0x55, 0xff, 0xff, 0xa0,

    /* U+0074 "t" */
    0xb, 0xf3, 0x0, 0xc, 0xf4, 0x0, 0xef, 0xff,
    0xf0, 0xaf, 0xfc, 0xb0, 0xc, 0xf4, 0x0, 0xc,
    0xf4, 0x0, 0xc, 0xf4, 0x0, 0xb, 0xf4, 0x0,
    0x8, 0xfe, 0xb1, 0x1, 0xaf, 0xf2,

    /* U+0075 "u" */
    0x2f, 0xc0, 0x8, 0xf7, 0x3f, 0xd0, 0x8, 0xf7,
    0x3f, 0xd0, 0x8, 0xf7, 0x3f, 0xd0, 0x8, 0xf7,
    0x3f, 0xd0, 0x8, 0xf7, 0x2f, 0xd0, 0xa, 0xf7,
    0xf, 0xfc, 0xcf, 0xf7, 0x5, 0xdf, 0xdb, 0xf7,

    /* U+0076 "v" */
    0xaf, 0x50, 0xd, 0xf2, 0x6f, 0x90, 0x1f, 0xe0,
    0x2f, 0xd0, 0x5f, 0x90, 0xd, 0xf1, 0x9f, 0x50,
    0x9, 0xf4, 0xcf, 0x10, 0x4, 0xf9, 0xfc, 0x0,
    0x0, 0xff, 0xf8, 0x0, 0x0, 0xbf, 0xf3, 0x0,

    /* U+0077 "w" */
    0x9f, 0x70, 0x8f, 0xa0, 0x5f, 0xb6, 0xfa, 0xc,
    0xfe, 0x8, 0xf8, 0x3f, 0xc0, 0xfd, 0xf1, 0xaf,
    0x40, 0xfe, 0x3f, 0x7f, 0x4c, 0xf1, 0xc, 0xf7,
    0xf1, 0xf8, 0xfd, 0x0, 0x8f, 0xde, 0xd, 0xdf,
    0xa0, 0x5, 0xff, 0xb0, 0xaf, 0xf7, 0x0, 0x1f,
    0xf8, 0x6, 0xff, 0x30,

    /* U+0078 "x" */
    0x8f, 0xb0, 0x6f, 0xc0, 0x1e, 0xf2, 0xcf, 0x40,
    0x6, 0xfb, 0xfc, 0x0, 0x0, 0xdf, 0xf3, 0x0,
    0x0, 0xef, 0xf5, 0x0, 0x7, 0xfb, 0xfd, 0x0,
    0x1f, 0xf2, 0xbf, 0x60, 0x8f, 0xb0, 0x4f, 0xe0,

    /* U+0079 "y" */
    0x9f, 0x60, 0xd, 0xf2, 0x5f, 0xb0, 0x1f, 0xe0,
    0xf, 0xf0, 0x5f, 0xa0, 0xc, 0xf3, 0xaf, 0x60,
    0x7, 0xf7, 0xef, 0x10, 0x2, 0xfd, 0xfd, 0x0,
    0x0, 0xdf, 0xf9, 0x0, 0x0, 0xc, 0xf4, 0x0,
    0x1c, 0xef, 0xd0, 0x0, 0x1f, 0xfb, 0x20, 0x0,

    /* U+007A "z" */
    0x5f, 0xff, 0xff, 0x83, 0xbb, 0xbf, 0xf7, 0x0,
    0x6, 0xfe, 0x10, 0x2, 0xff, 0x30, 0x0, 0xdf,
    0x70, 0x0, 0xaf, 0xb0, 0x0, 0x5f, 0xfc, 0xbb,
    0x77, 0xff, 0xff, 0xfa,

    /* U+007B "{" */
    0x0, 0xaf, 0x20, 0x7f, 0x80, 0x9, 0xf0, 0x0,
    0xaf, 0x0, 0xb, 0xf0, 0x9, 0xf8, 0x0, 0x7f,
    0xa0, 0x0, 0xaf, 0x0, 0x9, 0xf0, 0x0, 0x8f,
    0x30, 0x2, 0xef, 0x30, 0x0, 0x30,

    /* U+007C "|" */
    0xc8, 0xd8, 0xd8, 0xd8, 0xd8, 0xd8, 0xd8, 0xd8,
    0xd8, 0xc8,

    /* U+007D "}" */
    0x9e, 0x50, 0x3, 0xcf, 0x0, 0x6, 0xf3, 0x0,
    0x6f, 0x30, 0x5, 0xf5, 0x0, 0x1c, 0xf2, 0x2,
    0xfd, 0x10, 0x6f, 0x30, 0x6, 0xf3, 0x0, 0x9f,
    0x20, 0x9f, 0xb0, 0x2, 0x20, 0x0,

    /* U+007E "~" */
    0x37, 0x74, 0x23, 0x5d, 0xff, 0xff, 0xfe, 0x31,
    0x2, 0x44, 0x10
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 56, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 61, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 90, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 27, .adv_w = 171, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 82, .adv_w = 135, .box_w = 8, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 138, .adv_w = 190, .box_w = 12, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 198, .adv_w = 158, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 248, .adv_w = 48, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 253, .adv_w = 78, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 283, .adv_w = 78, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 313, .adv_w = 102, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 328, .adv_w = 145, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 353, .adv_w = 52, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 361, .adv_w = 80, .box_w = 5, .box_h = 2, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 366, .adv_w = 52, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 371, .adv_w = 105, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 406, .adv_w = 137, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 446, .adv_w = 86, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 471, .adv_w = 126, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 511, .adv_w = 130, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 551, .adv_w = 138, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 596, .adv_w = 130, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 636, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 676, .adv_w = 110, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 711, .adv_w = 139, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 751, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 791, .adv_w = 52, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 803, .adv_w = 52, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 818, .adv_w = 144, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 843, .adv_w = 145, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 861, .adv_w = 145, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 886, .adv_w = 119, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 921, .adv_w = 191, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 987, .adv_w = 143, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1032, .adv_w = 142, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1067, .adv_w = 138, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1107, .adv_w = 142, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1142, .adv_w = 123, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1172, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1202, .adv_w = 140, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1242, .adv_w = 147, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1282, .adv_w = 68, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1297, .adv_w = 133, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1337, .adv_w = 143, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1377, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1407, .adv_w = 186, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1457, .adv_w = 150, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1497, .adv_w = 141, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1537, .adv_w = 136, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1572, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1620, .adv_w = 140, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1660, .adv_w = 138, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1700, .adv_w = 113, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1735, .adv_w = 143, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1775, .adv_w = 133, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1820, .adv_w = 207, .box_w = 13, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1885, .adv_w = 138, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1930, .adv_w = 132, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1975, .adv_w = 133, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2015, .adv_w = 83, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2039, .adv_w = 105, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2074, .adv_w = 83, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2098, .adv_w = 131, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 2118, .adv_w = 95, .box_w = 6, .box_h = 2, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2124, .adv_w = 76, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 9},
    {.bitmap_index = 2132, .adv_w = 133, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2164, .adv_w = 135, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2208, .adv_w = 105, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2236, .adv_w = 135, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2280, .adv_w = 126, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2312, .adv_w = 91, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2345, .adv_w = 133, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2389, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2433, .adv_w = 63, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2450, .adv_w = 63, .box_w = 5, .box_h = 13, .ofs_x = -2, .ofs_y = -2},
    {.bitmap_index = 2483, .adv_w = 121, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2527, .adv_w = 63, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2544, .adv_w = 204, .box_w = 12, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2592, .adv_w = 134, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2624, .adv_w = 130, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2656, .adv_w = 135, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2696, .adv_w = 133, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2736, .adv_w = 89, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2760, .adv_w = 112, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2788, .adv_w = 90, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2818, .adv_w = 134, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2850, .adv_w = 120, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2882, .adv_w = 178, .box_w = 11, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2926, .adv_w = 118, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2958, .adv_w = 121, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2998, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3026, .adv_w = 81, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 3056, .adv_w = 59, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3066, .adv_w = 81, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 3096, .adv_w = 145, .box_w = 7, .box_h = 3, .ofs_x = 1, .ofs_y = 3}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t ui_font_RajdhaniBold16 = {
#else
lv_font_t ui_font_RajdhaniBold16 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_FONT_RAJDHANIBOLD16*/

