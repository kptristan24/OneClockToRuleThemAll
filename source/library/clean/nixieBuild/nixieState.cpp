#include "nixieState.h"

nixieClock::nixieClock(){
        numbers[0] = nixieZero;
        numbers[1] = nixieOne;
        numbers[2] = nixieTwo;
        numbers[3] = nixieThree;
        numbers[4] = nixieFour;
        numbers[5] = nixieFive;
        numbers[6] = nixieSix;
        numbers[7] = nixieSeven;
        numbers[8] = nixieEight;
        numbers[9] = nixieNine;

        //set initial time
        drawFrame();
}

void nixieClock::handleInput(){
        //basic nixie clock has no input
}

void nixieClock::runLogic(){
        //no logic besides drawing the frame
}

void nixieClock::drawFrame(){
        uint8_t hour = rtc.hour();
        uint8_t min = rtc.minute();
        uint8_t sec = rtc.second();

        __setTube(0, sec % 10);
        __setTube(1, sec / 10);
        __setTube(2, min % 10);
        __setTube(3, min / 10);
        __setTube(4, hour % 10);
        __setTube(5, hour / 10);
}

void nixieClock::__setTube(const uint8_t &pinNum, const uint8_t &data){
        //sanity checks
        if((data > 9) || (pinNum > 5))
                return;

        //set the select pins for the tube to be changed
        for(int i = 0; i < 6; i++){
                if(i != pinNum)
                        digitalWrite(select_pins[i], LOW);
                else
                        digitalWrite(select_pins[i], HIGH);
        }

        //set the time on the tube
        for(int i = 0; i < 4; i++){
                if(numbers[data][i])
                        digitalWrite(data_pins[i], HIGH);
                else
                        digitalWrite(data_pins[i], LOW);
        }
}
