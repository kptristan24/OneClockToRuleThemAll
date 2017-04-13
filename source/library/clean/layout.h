/*
 * Define the positions of the words in the grid
 * The first two sets of twelve are required
 * The third set is optional and has an array to describe which
 * words are present in your grid.
 *
 */

#ifndef LAYOUT_H
#define LAYOUT_H

#include <avr/pgmspace.h>

#define TIME24HOUR 0
#define NUM_WORDS  23
#define NUM_EXTRA  6

//Format {xStart, yStart, xEnd, yEnd, orientation, length}, orientation: 0 for horizontal word, 1 for vertical

//******* Times within the hour *******//
const uint8_t fiveM[6] PROGMEM= {0,0,0,0,0,0};

const uint8_t tenM[6] PROGMEM= {0,0,0,0,0,0};

const uint8_t fifteenM[6] PROGMEM= {6,0,0,0,0,0};

const uint8_t twentyM[6] PROGMEM= {6,0,0,0,0,0};

const uint8_t twentyfiveM[6] PROGMEM= {6,0,0,0,0,0};

const uint8_t thirtyM[6] PROGMEM= {6,0,0,0,0,0};

const uint8_t thirtyfiveM[6] PROGMEM= {6,0,0,0,0,0};

const uint8_t fourtyM[6] PROGMEM= {6,0,0,0,0,0};

const uint8_t fourtyfiveM[6] PROGMEM= {6,0,0,0,0,0};

const uint8_t fiftyM[6] PROGMEM= {6,0,0,0,0,0};

const uint8_t fiftyfiveM[6] PROGMEM= {6,0,0,0,0,0};


//******* Hour word positions *******//
const uint8_t one[6] PROGMEM= {0,0,0,0,0,0};

const uint8_t two[6] PROGMEM= {0,0,0,0,0,0};

const uint8_t three[6] PROGMEM= {6,0,0,0,0,0};

const uint8_t four[6] PROGMEM= {0,0,0,0,0,0};

const uint8_t five[6] PROGMEM= {0,0,0,0,0,0};

const uint8_t six[6] PROGMEM= {0,0,0,0,0,0};

const uint8_t seven[6] PROGMEM= {6,0,0,0,0,0};

const uint8_t eight[6] PROGMEM= {6,0,0,0,0,0};

const uint8_t nine[6] PROGMEM= {0,0,0,0,0,0};

const uint8_t ten[6] PROGMEM= {0,0,0,0,0,0};

const uint8_t eleven[6] PROGMEM= {0,0,0,0,0,0};

const uint8_t twelve[6] PROGMEM= {0,0,0,0,0,0};

//set the 24 hour time flag and include 13-23 if using "military" time


//******* Extra Words ********//

//This first array defines which of the extra words exist
const uint8_t extra[6] PROGMEM= {1,1,1,1,1,1};

//does the grid contain am/pm?
//FORMAT: {xStart, yStart, xEnd, yEnd, orientation, length}
const uint8_t amE[6] PROGMEM= {0, 0, 0, 0, 0, 2};

const uint8_t pmE[6] PROGMEM= {0, 0, 0, 0, 0, 2};

//are their words/symbols for minute incrememnts?
//FORMAT: {x,y}
const uint8_t minOne[2] PROGMEM= {2, 0};

const uint8_t minTwo[2] PROGMEM= {2, 0};

const uint8_t minThree[2] PROGMEM= {2, 0};

const uint8_t minFour[2] PROGMEM= {2, 0};



//Font library from https://github.com/agr00m/LedMatrix/blob/master/src/font_5x7_col.h
//Public Domain License

const uint8_t font_5x7_col[128][5] PROGMEM = {
   { 0x00, 0x00, 0x00, 0x00, 0x00 }, //
   { 0x00, 0x00, 0x00, 0x00, 0x00 }, //
   { 0x00, 0x00, 0x00, 0x00, 0x00 }, //
   { 0x00, 0x00, 0x00, 0x00, 0x00 }, //
   { 0x00, 0x00, 0x00, 0x00, 0x00 }, //
   { 0x00, 0x00, 0x00, 0x00, 0x00 }, //
   { 0x00, 0x00, 0x00, 0x00, 0x00 }, //
   { 0x00, 0x00, 0x00, 0x00, 0x00 }, //
   { 0x00, 0x00, 0x00, 0x00, 0x00 }, //
   { 0x03, 0x07, 0x7E, 0x20, 0x1C }, //
   { 0x60, 0x66, 0x09, 0x09, 0x09 }, //
   { 0x60, 0x6F, 0x0A, 0x0A, 0x08 }, //
   { 0x10, 0x18, 0x1C, 0x18, 0x10 }, //
   { 0x00, 0x3E, 0x1C, 0x08, 0x00 }, //
   { 0x00, 0x08, 0x1C, 0x3E, 0x00 }, //
   { 0x04, 0x0C, 0x1C, 0x0C, 0x04 }, //
   { 0x7F, 0x00, 0x00, 0x00, 0x00 }, // (1 col left)
   { 0x7F, 0x7F, 0x00, 0x00, 0x00 }, // (2 col left)
   { 0x7F, 0x7F, 0x7F, 0x00, 0x00 }, // (3 col left)
   { 0x7F, 0x7F, 0x7F, 0x7F, 0x00 }, // (4 col left)
   { 0x7F, 0x7F, 0x7F, 0x7F, 0x7F }, // (solid fill)
   { 0x00, 0x7F, 0x7F, 0x7F, 0x7F }, // (4 col right)
   { 0x00, 0x00, 0x7F, 0x7F, 0x7F }, // (3 col right)
   { 0x00, 0x00, 0x00, 0x7F, 0x7F }, // (2 col right)
   { 0x00, 0x00, 0x00, 0x00, 0x7F }, // (1 col right)
   { 0x03, 0x07, 0x7E, 0x20, 0x1C }, // (music note)
   { 0x60, 0x66, 0x09, 0x09, 0x09 }, // (deg c)
   { 0x60, 0x6F, 0x0A, 0x0A, 0x08 }, // (deg f)
   { 0x10, 0x18, 0x1C, 0x18, 0x10 }, // (triangle down)
   { 0x00, 0x3E, 0x1C, 0x08, 0x00 }, // (triangle right)
   { 0x00, 0x08, 0x1C, 0x3E, 0x00 }, // (triangle left)
   { 0x04, 0x0C, 0x1C, 0x0C, 0x04 }, // (triangle up)
   { 0x00, 0x00, 0x00, 0x00, 0x00 }, // (space)
   { 0x00, 0x7D, 0x00, 0x00, 0x00 }, // (!)
   { 0x00, 0x70, 0x00, 0x70, 0x00 }, // (")
   { 0x14, 0x7F, 0x14, 0x7F, 0x14 }, // (#)
   { 0x12, 0x2A, 0x7F, 0x2A, 0x24 }, // ($)
   { 0x62, 0x64, 0x08, 0x13, 0x23 }, // (%)
   { 0x36, 0x49, 0x35, 0x02, 0x05 }, // (&)
   { 0x00, 0x50, 0x60, 0x00, 0x00 }, // (')
   { 0x00, 0x1C, 0x22, 0x41, 0x00 }, // (()
   { 0x00, 0x41, 0x22, 0x1C, 0x00 }, // ())
   { 0x44, 0x28, 0x7C, 0x28, 0x44 }, // (*)
   { 0x08, 0x08, 0x7F, 0x08, 0x08 }, // (+)
   { 0x05, 0x06, 0x00, 0x00, 0x00 }, // (,)
   { 0x08, 0x08, 0x08, 0x00, 0x00 }, // (-)
   { 0x00, 0x03, 0x03, 0x00, 0x00 }, // (.)
   { 0x02, 0x04, 0x08, 0x10, 0x20 }, // (/)
   { 0x3E, 0x45, 0x49, 0x51, 0x3E }, // (0)
   { 0x00, 0x21, 0x7F, 0x01, 0x00 }, // (1)
   { 0x21, 0x43, 0x45, 0x49, 0x31 }, // (2)
   { 0x42, 0x41, 0x51, 0x69, 0x46 }, // (3)
   { 0x0C, 0x14, 0x24, 0x7F, 0x04 }, // (4)
   { 0x72, 0x51, 0x51, 0x51, 0x4E }, // (5)
   { 0x1E, 0x29, 0x49, 0x49, 0x06 }, // (6)
   { 0x43, 0x44, 0x48, 0x50, 0x60 }, // (7)
   { 0x36, 0x49, 0x49, 0x49, 0x36 }, // (8)
   { 0x30, 0x49, 0x49, 0x4A, 0x3C }, // (9)
   { 0x00, 0x36, 0x36, 0x00, 0x00 }, // (:)
   { 0x00, 0x35, 0x36, 0x00, 0x00 }, // (;)
   { 0x08, 0x14, 0x22, 0x41, 0x00 }, // (<)
   { 0x14, 0x14, 0x14, 0x14, 0x14 }, // (=)
   { 0x41, 0x22, 0x14, 0x08, 0x00 }, // (>)
   { 0x20, 0x40, 0x45, 0x48, 0x30 }, // (?)
   { 0x3E, 0x41, 0x4D, 0x51, 0x36 }, // (@)
   { 0x3F, 0x48, 0x48, 0x48, 0x3F }, // (A)
   { 0x7F, 0x49, 0x49, 0x49, 0x36 }, // (B)
   { 0x3E, 0x41, 0x41, 0x41, 0x22 }, // (C)
   { 0x7F, 0x41, 0x41, 0x41, 0x3E }, // (D)
   { 0x7F, 0x49, 0x49, 0x49, 0x41 }, // (E)
   { 0x7F, 0x48, 0x48, 0x48, 0x40 }, // (F)
   { 0x3E, 0x41, 0x49, 0x49, 0x2E }, // (G)
   { 0x7F, 0x08, 0x08, 0x08, 0x7F }, // (H)
   { 0x00, 0x41, 0x7F, 0x41, 0x00 }, // (I)
   { 0x02, 0x01, 0x41, 0x7E, 0x40 }, // (J)
   { 0x7F, 0x08, 0x14, 0x22, 0x41 }, // (K)
   { 0x7F, 0x01, 0x01, 0x01, 0x01 }, // (L)
   { 0x7F, 0x20, 0x18, 0x20, 0x7F }, // (M)
   { 0x7F, 0x10, 0x08, 0x04, 0x7F }, // (N)
   { 0x3E, 0x41, 0x41, 0x41, 0x3E }, // (O)
   { 0x7F, 0x48, 0x48, 0x48, 0x30 }, // (P)
   { 0x3E, 0x41, 0x45, 0x42, 0x3D }, // (Q)
   { 0x7F, 0x48, 0x4C, 0x4A, 0x31 }, // (R)
   { 0x31, 0x49, 0x49, 0x49, 0x46 }, // (S)
   { 0x40, 0x40, 0x7F, 0x40, 0x40 }, // (T)
   { 0x7E, 0x01, 0x01, 0x01, 0x7E }, // (U)
   { 0x7C, 0x02, 0x01, 0x02, 0x7C }, // (V)
   { 0x7E, 0x01, 0x06, 0x01, 0x7E }, // (W)
   { 0x63, 0x14, 0x08, 0x14, 0x63 }, // (X)
   { 0x70, 0x08, 0x07, 0x08, 0x70 }, // (Y)
   { 0x43, 0x45, 0x49, 0x51, 0x61 }, // (Z)
   { 0x00, 0x7F, 0x41, 0x41, 0x00 }, // ([)
   { 0x20, 0x10, 0x08, 0x04, 0x02 }, // (\)
   { 0x00, 0x41, 0x41, 0x7F, 0x00 }, // (])
   { 0x10, 0x20, 0x40, 0x20, 0x10 }, // (^)
   { 0x01, 0x01, 0x01, 0x01, 0x01 }, // (_)
   { 0x00, 0x40, 0x20, 0x10, 0x00 }, // (`)
   { 0x02, 0x15, 0x15, 0x15, 0x0F }, // (a)
   { 0x7F, 0x09, 0x11, 0x11, 0x0E }, // (b)
   { 0x0E, 0x11, 0x11, 0x11, 0x02 }, // (c)
   { 0x0E, 0x11, 0x11, 0x09, 0x7F }, // (d)
   { 0x0E, 0x15, 0x15, 0x15, 0x0C }, // (e)
   { 0x08, 0x3F, 0x48, 0x40, 0x20 }, // (f)
   { 0x18, 0x25, 0x25, 0x25, 0x3E }, // (g)
   { 0x7F, 0x08, 0x10, 0x10, 0x0F }, // (h)
   { 0x00, 0x11, 0x5F, 0x01, 0x00 }, // (i)
   { 0x02, 0x01, 0x11, 0x5E, 0x00 }, // (j)
   { 0x7F, 0x04, 0x0A, 0x11, 0x00 }, // (k)
   { 0x00, 0x41, 0x7F, 0x01, 0x00 }, // (l)
   { 0x1F, 0x10, 0x0C, 0x10, 0x0F }, // (m)
   { 0x1F, 0x08, 0x10, 0x10, 0x0F }, // (n)
   { 0x0E, 0x11, 0x11, 0x11, 0x0E }, // (o)
   { 0x1F, 0x14, 0x14, 0x14, 0x08 }, // (p)
   { 0x08, 0x14, 0x14, 0x14, 0x0F }, // (q)
   { 0x1F, 0x08, 0x10, 0x10, 0x08 }, // (r)
   { 0x09, 0x15, 0x15, 0x15, 0x02 }, // (s)
   { 0x10, 0x7E, 0x11, 0x01, 0x02 }, // (t)
   { 0x1E, 0x01, 0x01, 0x02, 0x1F }, // (u)
   { 0x1C, 0x02, 0x01, 0x02, 0x1C }, // (v)
   { 0x1E, 0x01, 0x02, 0x01, 0x1E }, // (w)
   { 0x11, 0x0A, 0x04, 0x0A, 0x11 }, // (x)
   { 0x18, 0x05, 0x05, 0x05, 0x1E }, // (y)
   { 0x11, 0x13, 0x15, 0x19, 0x11 }, // (z)
   { 0x08, 0x36, 0x41, 0x00, 0x00 }, // ({)
   { 0x00, 0x00, 0x7F, 0x00, 0x00 }, // (|)
   { 0x00, 0x00, 0x41, 0x36, 0x08 }, // (})
   { 0x08, 0x08, 0x2A, 0x1C, 0x08 }, // (arrow right)
   { 0x08, 0x1C, 0x2A, 0x08, 0x08 }, // (arrow left)

};


#endif