#ifndef DISPLAY_H
#define DISPLAY_H

#include <FastLED.h>

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

        void updateDisplay();
        void debugUpdateDisplay(); //Just prints display state to console

        CRBG *rawStrip();
private:
        CRGB LEDstrip[NUM_LEDS];
};

#endif
