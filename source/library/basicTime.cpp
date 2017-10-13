#include "basicTime.h"

basicTime::basicTime(){
        Serial.print(F("Time\n"));
        currentTime = clk.getCurrentTime();
}

void basicTime::handleInput(){
        const int8_t input = buttons.getInput();

        if(input == 2){ //menu button pressed
                signal = stateStack::NEW;
                newState = new mainMenu;
        }
}

void basicTime::runLogic(){
        if(currentTime.minute != clk.curMinute())
            currentTime = clk.getCurrentTime();
}

void basicTime::drawFrame(){
        disp.clear();
        disp.setFromTime(currentTime.hour, currentTime.minute, CRGB::Red);
        disp.update();
}
