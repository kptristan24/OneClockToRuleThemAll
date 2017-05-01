#ifndef DISPLAY_H
#define DISPLAY_H

#include <FastLED.h>
#include <string.h>
#include "layout.h"
#include "Wendy3x5.h"

#define CHECKBIT(ADDRESS,BIT) (ADDRESS & (1<<BIT))

extern CRGB LEDstrip[13];

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
#define NUM_LEDS    13
#define ROW_LENGTH  13
#define ALT_DIR     1 //are the strips wired in alternating directions
#define DATA_PIN    4
#define CLOCK_PIN   5
#define HEADLESS    0  //Don't actually use LED's, just print screen state to serial monitor
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
        void setPixel(int, int, const CRGB &); //at (x,y)
        void setPixel(int, const CRGB &);              //at linear position
        void setWordBuiltin(int, const CRGB & = CRGB::White);
        void setFromTime(int, int, const CRGB & = CRGB::White); //hour, minute (in 24 hour time)
        //void drawLine();

        //scrolling Text functions
        void clearScrollingText(int); //0 - top row, 1 - bot row, 2 - both rows
        void drawChar(char, int, int, const CRGB &); //character, x position, row, color
        //ScrollingText Parameters: message, length, row (0=top, 1=bot), and two colors
        void scrollingText(char *, int, const CRGB & = CRGB::White, const CRGB & = CRGB::Blue);

private:
        CRGB **dispArray; //abstraction for treating strip like an array
        uint8_t const **words;

        void __arrayAccessFunction(int, int, const CRGB &);
        //scrolling text internal Functions
        void __updateTextVariables(int);
        void __bufferChar(uint8_t *, int);

        //scrolling text position variables
        uint8_t text[2];
        uint16_t currentChar[2];
        uint16_t length[2];
        uint16_t offset[2];

        uint8_t frameCounter;
};

#endif
