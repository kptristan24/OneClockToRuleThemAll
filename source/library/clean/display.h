#ifndef DISPLAY_H
#define DISPLAY_H

#include <FastLED.h>
#include <string.h>
#include "layout.h"

#define CHECKBIT(ADDRESS,BIT) (ADDRESS & (1<<BIT))

//hardware information
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
#define CHIPSET     DOTSTAR //Must be one of the chipsets above.
#define NUM_LEDS    144
#define ROW_LENGTH  12
#define DATA_PIN    7
#define CLOCK_PIN   8
#define HEADLESS    1  //Don't actually use LED's, just print screen state to serial monitor
#define TEXT_SPEED  10

class display{
public:
        display();

        void setupWords();
        void setupExtraWords();

        //accessors
        int getVertSize();
        int getHorizSize();
        CRGB **rawStrip();

        void update();
        void clear();
        void debugUpdateDisplay(); //Just prints display state to console
        void updateFromArray(int **, CRGB &, bool); //array, color to use, trigger screen drawing

        //Basic drawing Functions
        void setPixel(int, int, const CRGB & = CRGB::White); //at (x,y)
        void setPixel(int, const CRGB & = CRGB::White);              //at linear position
        void setWordBuiltin(int, const CRGB & = CRGB::White);
        void setFromTime(int, int, const CRGB & = CRGB::White); //hour, minute (in 24 hour time)
        void drawLine()

        //scrolling Text functions
        void clearScrollingText(int); //0 - top row, 1 - bot row, 2 - both rows
        void drawChar(char, int, int, const CRGB &); //character, x position, row, color
        //ScrollingText Parameters: message, length, row (0=top, 1=bot), and two colors
        void scrollingText(char *, int, const CRGB & = CRGB::White, const CRGB & = CRGB::Blue);

private:
        CRGB **dispArray; //abstraction for treating strip like an array
        CRGB LEDstrip[NUM_LEDS];
        uint8_t const **words;

        //scrolling text internal Functions
        void __updateTextVariables(int);

        //scrolling text position variables
        uint8_t text[2];
        uint16_t currentChar[2];
        uint16_t length[2];
        uint16_t offset[2];

        uint8_t frameCounter;
};

#endif
