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
        6,10,11,10,0,
        0,5,2,5,0, //one
        4,5,6,5,0,
        7,5,11,5,0,
        0,6,3,6,0,
        6,6,8,6,0, //five
        1,7,3,7,0,
        5,7,9,7,0,
        0,8,4,8,0,
        7,8,10,8,0,
        2,9,4,9,0,
        0,10,5,10,0,
        //6,10,11,10,0, //twelve
        //phrases for 5-minute increments of time within the hour
        7,1,10,1,0, //five
        0,3,2,3,0, //ten
        5,2,11,2,0, //quarter
        0,1,5,1,0, //twenty
        0,2,3,2,0, //half
        7,4,10,4,0, //past
        0,4,1,4,0, //to
        4,3,10,3,0, //minutes
        2,0,3,0,0, // it
        5,0,6,0,0, // is
        //am and pm
        2,11,3,11,0, //am
        5,11,6,11,0, //pm
        //minute increments

        //0,0,0,0,0, //one
        //0,11,0,11,0, //two
        //11,0,11,0,0, //three
        //11,11,11,11,0, //four

        //extra words
}; //0-11, 12-21, 22-23, 24-27

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
