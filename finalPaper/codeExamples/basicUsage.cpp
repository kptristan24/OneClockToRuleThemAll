#include "timekeeping.h"
#include "display.h"

display disp;
clockLib clk;

void setup() {
        Serial.begin(9600);
}

void loop() {
        //Run hardware interaction updates
        clk.update();
        
        disp.setFromTime(clk.getCurrentTime(), CRGB::Blue);
}
