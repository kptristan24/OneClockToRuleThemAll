/*
 * Word clock control library
 * OneClockToRuleThemAll Team 2017
 *
 */

#ifndef LIBRARY_h
#define LIBRARY_h

#include <Arduino.h>
#include "layout.h"

#define NUM_LEDS 144
#define ROW_LENGTH 12

class wordClock{
public:
        wordClock();
        ~wordClock();
        void testMe();
        void updateGrid(int, int); // hours, minutes
private:
        int test;
        int **letters;
        int gridLEDs[NUM_LEDS];
};

#endif
