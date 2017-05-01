#include "alarmState.h"

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

        alarmTime[2] = ':';

        String(t.minute).toCharArray(temp, 2);
        if(t.hour < 10){
                alarmTime[3] = '0';
                alarmTime[4] = temp[0];
        }
        else{
                alarmTime[3] = temp[0];
                alarmTime[4] = temp[1];
        }

        alarmTime[5] = ' ';
        alarmTime[6] = '\n';
}

void alarmState::handleInput(){
        int input = buttons->getInput();

        if(input != -1){ //if user hits anything, close the alarm
                signal = 2;
        }
}

void alarmState::runLogic(){

}

void alarmState::drawFrame(){
        disp->scrollingText("Alarm! ", 0, CRGB::Red, CRGB::Fuchsia);
        disp->scrollingText(alarmTime, 1, CRGB::Blue, CRGB::Aqua);
}
