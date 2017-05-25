#include "alarmState.h"

alarmState::alarmState(){
        alarmTime[0] = '0';
        alarmTime[1] = '0';
        alarmTime[2] = '0';
        alarmTime[3] = '0';
}

alarmState::alarmState(const timeS &t){
        //build a char array out of the time for use as a scrolling text
        char temp[2];
        String(t.hour).toCharArray(temp, 2);
        if(t.hour < 10){
                alarmTime[0] = '0';
                alarmTime[1] = temp[0];
        }
        else{
                alarmTime[0] = temp[0];
                alarmTime[1] = temp[1];
        }
        String(t.minute).toCharArray(temp, 2);
        if(t.hour < 10){
                alarmTime[2] = '0';
                alarmTime[3] = temp[0];
        }
        else{
                alarmTime[2] = temp[0];
                alarmTime[3] = temp[1];
        }
}

void alarmState::handleInput(){
        int8_t input = buttons.getInput();

        if(input != -1){ //if user hits anything, close the alarm
                signal = stateStack::EXIT;
        }
}

void alarmState::runLogic(){

}

void alarmState::drawFrame(){
        disp.clear();
        disp.scrollingText("ALARM! ", display::TOP, CRGB::Red, CRGB::Crimson);
        disp.staticText(alarmTime, display::BOT, 4, CRGB::Blue, CRGB::Green, CRGB::Blue, CRGB::Green);
        disp.update();
}
