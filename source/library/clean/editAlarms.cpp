#include "editAlarms.h"

editAlarms::editAlarms(){
        currentState = MENU;

        mainMenu.setupMenu(F("Alarm Menu "), this);
        mainMenu.addOption(F("Exit "), &signal, SET, stateStack::EXIT);
        mainMenu.addOption(F("New Alarm "), &changeToAdd);
        mainMenu.addOption(F("Delete Alarm "), &changeToDelete);

        deleteAlarm.setupMenu(F("Delete "), this);
        deleteAlarm.addOption(F("Exit "), &currentState, SET, 0);
        deleteAlarm.addOption(F("Next Alarm "), &deleteGetNextAlarm);
        deleteAlarm.addOption(F("Delete "), &deleteAlarmResponse);
}

void editAlarms::changeToAdd(){
        currentState = NEW;
        currentlySelected = 0;
        alarmTime = clk.getCurrentTime();
        updateTimeString();
        addUpdateColors();
}

void editAlarms::changeToDelete(){
        if(clk.getAlarmTime(0, alarmTime)){
                deleteAlarm.setMenuName(timeStr);
                currentlySelected = 0;
                currentState = DELETE;
                updateTimeString();
        }
        else{ //no alarms currently set, return to menu
                currentState = MENU;
        }
}

void editAlarms::handleInput(){
        switch(currentState){
        case MENU  : mainMenu.update();
                     break;
        case NEW   : addAlarmInput();
                     break;
        case DELETE: deleteAlarm.update();
                     break;
        }
}

void editAlarms::addAlarmInput(){
        int input = buttons.getInput();
        if(input == 2){
                currentlySelected++;
                if(currentlySelected == 3){
                        currentState = MENU;
                        clk.addAlarm(alarmTime);
                }
        }
        else if(input == 1 || input == 0){
                addInputHelper(input);
                updateTimeString();
        }
}

void editAlarms::addInputHelper(uint8_t input){
        switch(currentlySelected){
        case 0: amPm = !amPm;
                break;
        case 1: if(!input){
                        alarmTime.hour++;
                        if(alarmTime.hour > 12)
                                alarmTime.hour = 1;
                }
                else{
                        if(alarmTime.hour == 1)
                                alarmTime.hour = 12;
                        else
                                alarmTime.hour--;
                }
                updateTimeString();
                break;
        case 2: if(!input){
                        alarmTime.minute++;
                        if(alarmTime.minute > 59)
                                alarmTime.minute = 0;
                }
                else{
                        if(alarmTime.minute == 0)
                                alarmTime.minute = 59;
                        else
                                alarmTime.minute--;
                }
                updateTimeString();
                break;
        }
}

void editAlarms::deleteAlarmResponse(){
        clk.removeAlarm(alarmTime);
        currentlySelected--;
        deleteGetNextAlarm();
}

void editAlarms::deleteGetNextAlarm(){
        currentlySelected++;
        if(!clk.getAlarmTime(currentlySelected, alarmTime)){
                currentlySelected = 0;
                if(!clk.getAlarmTime(currentlySelected, alarmTime)){
                        currentState = MENU;
                }
        }
        deleteAlarm.setMenuName(timeStr);
        updateTimeString();
}

void editAlarms::updateTimeString(){
        if(alarmTime.hour > 9){
                timeStr[0] = '1';
                timeStr[1] = (alarmTime.hour - 10) + 48;
        }
        else{
                timeStr[0] = '0';
                timeStr[1] = alarmTime.hour + 48;
        }

        if(alarmTime.minute > 9){
                uint8_t temp = alarmTime.minute / 10;
                timeStr[2] = temp + 48;
                timeStr[3] = (alarmTime.minute - temp * 10) + 48;
        }
}


void editAlarms::runLogic(){

}

void editAlarms::drawFrame(){
        switch(currentState){
        case MENU  : mainMenu.draw();
                     break;
        case NEW   : addDrawTime();
                     break;
        case DELETE: deleteAlarm.draw();
                     break;
        }
}

void editAlarms::addUpdateColors(){
        switch(currentlySelected){ //hours
        case 0: hourCol = CRGB::Red;
                minCol  = CRGB::Green;
                amPmCol = CRGB::Green;
                break;
        case 1: hourCol = CRGB::Green; //minutes
                minCol  = CRGB::Red;
                amPmCol = CRGB::Green;
                break;
        case 2: hourCol = CRGB::Green; //ampm
                minCol  = CRGB::Green;
                amPmCol = CRGB::Red;
                break;
        }
}

void editAlarms::addDrawTime(){
        disp.staticText(timeStr, display::TOP, 4, hourCol, hourCol, minCol, minCol);

        if(amPm)
                disp.staticText(F("PM "), display::BOT, 2, amPmCol, amPmCol);
        else
                disp.staticText(F("AM "), display::BOT, 2, amPmCol, amPmCol);
}
