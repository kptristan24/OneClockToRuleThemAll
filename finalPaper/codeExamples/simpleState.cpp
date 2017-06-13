#include "simpleState.h"

void simpleState::handleInput(){
        //no input
}

void simpleState::runLogic(){
        currentTime = clk.getCurrentTime();
}

void simpleState::drawFrame(){
        disp.setFromTime(currentTime, CRGB::Blue);
}