/*
 * Word clock control library
 * OneClockToRuleThemAll Team 2017
 *
 */

#ifndef LIBRARY_h
#define LIBRARY_h

#include <Arduino.h>
#include <Adafruit_DotStar.h>
#include "layout.h"

#define NUM_LEDS 144
#define ROW_LENGTH 12

class wordClock{
public:
        wordClock();
        ~wordClock();
        void testMe();

        // Run once during setup function after the strip is initialized and the time is known
        void wordClockSetup(Adafruit_DotStar *,int,int); // hours (24 hour format), minutes
        uint32_t genTimeColor(int,int); // hours (24 hour format), minutes
        void updateGridFromTime(int, int); // hours (24 hour format), minutes
        void updateDisplayFromGrid(Adafruit_DotStar *);
private:
        int test;
        uint32_t color;
        int **letters;
        int gridLEDs[NUM_LEDS];
};

#endif
