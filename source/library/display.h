#ifndef DISPLAY_H
#define DISPLAY_H

#include <FastLED.h>
#include <string.h>
#include "layout.h"
#include "timeS.h"
#include "Wendy3x5.h"

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
#define TEXT_ROWS   (NUM_LEDS/ROW_LENGTH)/6
#define ALT_DIR     1 //are the strips wired in alternating directions
#define DATA_PIN    4
#define CLOCK_PIN   5
#define TEXT_SPEED  25

class display{
public:
        enum TextRow {TOP, BOT, ALL};
        display();

        //accessors
        int getVertSize();
        int getHorizSize();

        void update();
        void clear();
        void debugUpdateDisplay(); //Just prints display state to console
        void updateFromArray(int **, CRGB &, bool); //array, color to use, trigger screen drawing

        //Basic drawing Functions
        void setPixel(int, int, const CRGB &); //at (y,x)
        void setPixel(int, const CRGB &);              //at linear position
        void setWordBuiltin(uint8_t, const CRGB & = CRGB::White);
        void setFromTime(uint8_t, uint8_t, const CRGB & = CRGB::White); //hour, minute (in 24 hour time)
        void setFromTime(const timeS &, const CRGB & = CRGB::White);
        void setMinutePhrase(uint8_t m, const CRGB &);
        CRGB getColorFromTime(const timeS &);
        //void drawLine();

        /**     Text functions     **/
        void clearScrollingText(uint8_t); //0 - top row, 1 - bot row, 2 - both rows
        void drawChar(char, int, uint8_t, const CRGB &); //character, x position, row, color

        //Text Parameters: message, row (0=top, 1=bot), and two colors
        void scrollingText(const char *, uint8_t, const CRGB & = CRGB::White, const CRGB & = CRGB::Blue);
        void scrollingText(const __FlashStringHelper *, uint8_t, const CRGB & = CRGB::White, const CRGB & = CRGB::Blue);
        /* Parameters: message, row (0=top, 1=bot), length, and a color
         * Only displays up to ROW_LENGTH / 3 characters
         * The second versions expects an array of colors the same length as the characters
         */
        void staticText(const char *, uint8_t, uint8_t, const CRGB &, const CRGB &);
        void staticText(const char *, uint8_t, uint8_t, const CRGB *);
        void staticText(const char *, uint8_t, uint8_t, const CRGB &, const CRGB &, const CRGB &, const CRGB &);
        void staticText(const __FlashStringHelper *, uint8_t, uint8_t,
                        const CRGB & = CRGB::White, const CRGB & = CRGB::White,
                        const CRGB & = CRGB::White, const CRGB & = CRGB::White);
private:
        CRGB LEDstrip[NUM_LEDS]; //large ram usage: NUM_LEDS * 3 bytes

        void __arrayAccessFunction(uint16_t, uint16_t, const CRGB &);
        //scrolling text internal Functions
        void __updateTextVariables(uint8_t);
        void __bufferChar(uint8_t *, uint8_t);
        void __bufferWordPos(uint8_t *, uint8_t);

        //scrolling text position variables
        char *tempStr[TEXT_ROWS];
        uint8_t text[TEXT_ROWS];
        uint8_t currentChar[TEXT_ROWS];
        uint8_t length[TEXT_ROWS];
        uint16_t offset[TEXT_ROWS];
        uint16_t frameCounter[TEXT_ROWS];
};

#endif
