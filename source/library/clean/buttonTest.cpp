#include "buttonTest.h"

buttonTest::buttonTest(){
        Serial.print(F("buttonTest\n"));
        state = 0;
        /*
        testMenu.setupMenu("Hello ", this);
        testMenu.addOption("option3 ", &counter, SET, 3);
        testMenu.addOption("option2 ", &counter, SET, 2);
        testMenu.addOption("option1 ", &counter, SET, 1);
        testMenu.addOption("option4 ", &state, SET, 1);
        counter = 1;
        */

}

void buttonTest::handleInput(){
        int input = buttons.getInput();

        if(input != -1){ //if user hits anything, close the alarm
                signal = stateStack::EXIT;
        }
}

void buttonTest::runLogic(){

}

void buttonTest::drawFrame(){
        disp.clear();
        disp.scrollingText("Hello ", display::TOP, CRGB::Green, CRGB::Blue);
        disp.scrollingText("World ", display::BOT, CRGB::Blue, CRGB::Red);

        //disp->staticText("", display::TOP, 4, CRGB::Green, CRGB::Red);
        //disp->staticText("", display::BOT, 3, CRGB::Green, CRGB::Red);

        disp.update();
}
