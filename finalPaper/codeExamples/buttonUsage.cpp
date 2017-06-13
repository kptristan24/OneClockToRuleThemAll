#include "simpleState.h"

simpleState::simpleState(){ //run once setup function
        brightness = 50; //0-255
}

void simpleState::handleInput(){
        //no input
}

void simpleState::runLogic(){
        const int8_t input = buttons.getInput();
        switch(input){
        case 0: FastLED.setBrightness(++brightness);
                break;
        case 1: FastLED.setBrightness(--brightness);
                break;
        }

        currentTime = clk.getCurrentTime();
}

void simpleState::drawFrame(){
        disp.setFromTime(currentTime, CRGB::Blue);
}
