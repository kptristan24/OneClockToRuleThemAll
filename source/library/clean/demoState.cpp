#include "demoState.h"

demo::demo(){
        frameCounter = 0;
        curState = 1;
        curTest = 0;
}

void demo::handleInput(){
        const int8_t input = buttons.getInput();

        switch(input){
        case 0:
        case 1: curTest = 0;
                curState = 1;
                frameCounter = 0;
                break;
        case 2: signal = stateStack::EXIT;
                break;
        }

}

void demo::runLogic(){

}

void demo::drawFrame(){

        switch(curState){
        case 1: testEachPosition();
                break;
        case 2: testRows();
                break;
        case 3: testColumns();
                break;
        case 4: testText();
                break;
        default:
                curState = 1;
        }

        frameCounter++;
}

void demo::testEachPosition(){
        const uint8_t row = curTest / disp.getHorizSize();

        if(frameCounter > 100){
                frameCounter = 0;
                disp.clear();
                disp.setPixel(curTest, CRGB::White);
                disp.update();
                curTest++;
        }
        else{
                return;
        }


        if(curTest >= NUM_LEDS){
                curState++;
                curTest = 0;
        }
}

void demo::testRows(){
        const uint8_t numRows = disp.getVertSize();

        if(frameCounter > 2000){
                frameCounter = 0;
                disp.clear();
                const uint8_t numCols = disp.getHorizSize();
                for(uint8_t i = 0; i < numCols; i++)
                        disp.setPixel(curTest, i, CRGB::Red);
                disp.update();
                curTest++;
        }
        else{
                return;
        }

        if(curTest == numRows){
                curState++;
                curTest = 0;
        }
}

void demo::testColumns(){
        const uint8_t numCols = disp.getHorizSize();

        if(frameCounter > 2000){
                frameCounter = 0;
                disp.clear();
                const uint8_t numRows = disp.getVertSize();
                for(int i = 0; i < numRows; i++)
                        disp.setPixel(i, curTest, CRGB::Red);
                disp.update();
                curTest++;
        }
        else{
                return;
        }

        if(curTest == numCols){
                curState++;
                curTest = 0;
        }
}

void demo::testText(){
        if(frameCounter > 700){
                curState++;
                curTest = 0;
        }
        disp.clear();
        disp.scrollingText("Hello! ", 0, CRGB::Red, CRGB::Blue);
        disp->scrollingText("World ", 1, CRGB::Blue, CRGB::Green);
        disp.update();
}
