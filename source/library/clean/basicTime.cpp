#include "basicTime.h"

basicTime::basicTime(){
        currentTime = clk->getCurrentTime();
}

void basicTime::handleInput(){
        int input = buttons->getInput();

        if(input == 2){ //menu button pressed
                signal = 1;
                newState = new mainMenu;
        }
}

void basicTime::runLogic(){
        currentTime = clk->getCurrentTime();
}

void basicTime::drawFrame(){
        disp->setFromTime(currentTime, CRGB::White);
}
