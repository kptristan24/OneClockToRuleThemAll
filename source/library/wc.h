/*
 * Word clock control library
 * OneClockToRuleThemAll Team 2017
 *
 */

#ifndef WC_h
#define WC_h

#include <Arduino.h>
#include <Adafruit_DotStar.h>
#include "layout.h"

#define NUM_LEDS 196
#define ROW_LENGTH 14

class wordClock{
public:
        wordClock();
        ~wordClock();
        void testMe();
        void setupExtraWords(); //init function that associates optional words
        // Run once during setup function after the strip is initialized and the time is known
        void wordClockSetup(Adafruit_DotStar *,int,int); // hours (24 hour format), minutes
        uint32_t genTimeColor(int,int); // hours (24 hour format), minutes
        void updateGridFromTime(int, int); // hours (24 hour format), minutes
        void updateMinutes(int); // if the clock face has lights or words for increments of time less than five minutes
        void updateDisplayFromGrid(Adafruit_DotStar *);
        int getDisplaySize();
        int getLEDSPerRow();
        void writeLetter(char, int, int); //letter, row (0-1: top or bottom), column offset
        void showScrollingText(char *, int, int); //message, message length, row (0-1: top or bottom)
private:
        int test;
        uint32_t color;
        int **letters;
        int gridLEDs[NUM_LEDS];
        int letterPos[2][ROW_LENGTH];
};

#endif
