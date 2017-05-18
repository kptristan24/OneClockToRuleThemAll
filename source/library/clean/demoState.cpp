#include "demoState.h"

demo::demo(){
        frameCounter = 0;
        curState = 1;
        curTest = 0;
        FastLED.clear();
        FastLED.show();
        Serial.print("Constructor for demo run...\n");
}

void demo::handleInput(){

        const int input  = -1; //= buttons->getInput();

        switch(input){
        case 0: //first or second button exits the demo
        case 1: signal = 2;
                break;
        case 2: curTest = 0;
                curState = 1;
                frameCounter = 0;
                break;
        default: //no button input
                break;
        }

}

void demo::runLogic(){

}

void demo::drawFrame(){
        //testEachPosition();
        //testText();

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
        const int row = curTest / disp->getHorizSize();

        if(frameCounter > 2){
                frameCounter = 0;
                disp->clear();
                disp->setPixel(curTest, CRGB::White);
                disp->update();
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
        const int numRows = disp->getVertSize();

        if(frameCounter > 1000){
                frameCounter = 0;
                disp->clear();
                const int numCols = disp->getHorizSize();
                for(uint8_t i = 0; i < numCols; i++)
                        disp->setPixel(curTest, i, CRGB::Red);
                disp->update();
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
        const int numCols = disp->getHorizSize();

        if(frameCounter > 1000){
                frameCounter = 0;
                disp->clear();
                const int numRows = disp->getVertSize();
                for(int i = 0; i < numRows; i++)
                        disp->setPixel(i, curTest, CRGB::Red);
                disp->update();
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
        disp->clear();
        //delay(100);
        disp->scrollingText("Hello ", 0, CRGB::Red, CRGB::Blue);
        disp->scrollingText("World ", 1, CRGB::Blue, CRGB::Green);
        disp->update();
}
