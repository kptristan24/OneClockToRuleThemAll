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

//Format {xStart, yStart, xEnd, yEnd, orientation}, orientation: 0 for horizontal word, 1 for vertical

//******* Times within the hour *******//
const uint8_t WordLayout[] PROGMEM= {
        //the numbers 1 through 12
        0,0,0,0,0, //one
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0, //twelve
        //phrases for 5-minute increments of time within the hour
        0,0,0,0,0, //five past
        0,0,0,0,0, //ten past
        0,0,0,0,0, //and so on
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0, //5 till (55 past)
        //am and pm
        0,0,0,0,0, //am
        0,0,0,0,0, //pm
        //minute increments
        0,0,0,0,0, //one
        0,0,0,0,0, //two
        0,0,0,0,0, //three
        0,0,0,0,0, //four
        //extra words
}

/*
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
*/
#endif
