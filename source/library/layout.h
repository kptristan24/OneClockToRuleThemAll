/*
 * Define the positions of the words in the grid
 * The first two sets of twelve are required
 * The third set is optional and has an array to describe which
 * words are present in your grid.
 *
 */

#ifndef LAYOUT_H
#define LAYOUT_H

#define TIME24HOUR 0

//******* Times within the hour *******//
static int fiveM[6] = {6,0,0,0,0,0};

static int tenM[6] = {6,0,0,0,0,0};

static int fifteenM[6] = {6,0,0,0,0,0};

static int twentyM[6] = {6,0,0,0,0,0};

static int twentyfiveM[6] = {6,0,0,0,0,0};

static int thirtyM[6] = {6,0,0,0,0,0};

static int thirtyfiveM[6] = {6,0,0,0,0,0};

static int fourtyM[6] = {6,0,0,0,0,0};

static int fourtyfiveM[6] = {6,0,0,0,0,0};

static int fiftyM[6] = {6,0,0,0,0,0};

static int fiftyfiveM[6] = {6,0,0,0,0,0};


//******* Hour word positions *******//
static int one[4] = {4,0,0,0};

static int two[4] = {4,0,0,0};

static int three[6] = {6,0,0,0,0,0};

static int four[5] = {5,0,0,0,0};

static int five[5] = {5,0,0,0,0};

static int six[4] = {4,0,0,0};

static int seven[6] = {6,0,0,0,0,0};

static int eight[6] = {6,0,0,0,0,0};

static int nine[5] = {5,0,0,0,0};

static int ten[4] = {4,0,0,0};

static int eleven[7] = {7,0,0,0,0,0,0};

static int twelve[7] = {7,0,0,0,0,0,0};

//set the 24 hour time flag and include 13-23 if using "military" time


//******* Extra Words ********//

//This first array defines which of the extra words exist
static int extra[6] = {1,1,1,1,1,1};

//does the grid contain am/pm?
static int amE[3] = {3, 0 , 0};

static int pmE[3] = {3, 0 , 0};

//are their words/symbols for minute incrememnts?
static int minOne[2] = {2, 0};

static int minTwo[2] = {2, 0};

static int minThree[2] = {2, 0};

static int minFour[2] = {2, 0};


#endif
