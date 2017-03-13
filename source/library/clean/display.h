#ifndef DISPLAY_H
#define DISPLAY_H

#include <FastLED.h>

//hardware information
#define NUM_LEDS    144
#define DATA_PIN    7
#define CLOCK_PIN   8
#define HEADLESS    1  //Don't actually use LED's, just print screen state to serial monitor

class display{
public:
        display(); 
private:
        CRGB *LEDstrip;
};

#endif
