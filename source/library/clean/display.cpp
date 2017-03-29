#include "display.h"

display::display(){
#if !HEADLESS
        FastLED.addLeds<CHIPSET, DATA_PIN, CLOCK_PIN>(LEDstrip, NUM_LEDS);
#endif
}

void display::updateDisplay(){
#if !HEADLESS

        FastLED.show();
#else
        debugUpdateDisplay();
#endif
}

void display::debugUpdateDisplay(){
        int rows;
        unsigned char rowContents;

        rows = NUM_LEDS / ROW_LENGTH;
        for(int i = 0; i < rows; i++){
                rowContents = 0;
                for(int j = 0; j < ROW_LENGTH; j++){
                        if(LEDstrip[j + (i*ROW_LENGTH)])
                                rowContents |= 1 << j;
                }
                Serial.print(rowContents, BIN);
        }
}

CRBG *display::rawStrip(){
        return LEDstrip;
}
