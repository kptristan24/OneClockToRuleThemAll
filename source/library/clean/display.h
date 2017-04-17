#ifndef DISPLAY_H
#define DISPLAY_H

#include <FastLED.h>
#include <string.h>
#include "layout.h"

/* Chipset options (from fast LED)
	LPD8806,
	WS2801,
	WS2803,
	SM16716,
	P9813,
	APA102,
	SK9822,
	DOTSTAR
*/

//hardware information
#define CHIPSET     DOTSTAR //Must be one of the chipsets above.
#define NUM_LEDS    144
#define ROW_LENGTH  12
#define DATA_PIN    7
#define CLOCK_PIN   8
#define HEADLESS    1  //Don't actually use LED's, just print screen state to serial monitor


class display{
public:
        display();
        void setupWords();
        void setupExtraWords();

        int getVertSize();
        int getHorizSize();

        void update();
        void clear();
        void debugUpdateDisplay(); //Just prints display state to console
        void updateFromArray(int **, CRGB &, bool); //array, color to use, trigger screen drawing

        //Basic control Functions
        void setPixel(const int &, const int &, const CRGB & = defaultCol); //at (x,y)
        void setPixel(const int &, const CRGB & = defaultCol);              //at linear position
        void setWordBuiltin(const int &, const CRGB & = defaultCol);
        void setFromTime(const int &, const int &, const CRGB & = defaultCol); //hour, minute (in 24 hour time)

        CRGB **rawStrip();
        void clearScrollingText(const int &); //0 - top row, 1 - bot row, 2 - both rows

        /*To-Do
                * Scrolling text interface
                * Specific point access
        */
        void setScrollingText(const char *, const int &); //message, (0 or 1) - top or bottom row
        void updateMessage(const char *, const int &);
private:

        CRGB defaultCol;
        CRGB **dispArray; //abstraction for treating strip like an array
        CRGB LEDstrip[NUM_LEDS];
        uint8_t **words;

        uint8_t botText;
        uint8_t topText;
        uint16_t botLength;
        uint16_t topLength;
        int botPosition;
        int topPosition;
};

#endif
