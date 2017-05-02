#include "editAlarms.h"

editAlarms::editAlarms(){
        currentlySelected = 0;
        currentState = 0;
        subState = 0;
}

void editAlarms::handleInput(){
        int input = buttons->getInput();
        switch(currentState){
        case 0: switch(input){ //control alarm menu
                case 0: currentlySelected--; //scroll up
                        if(currentlySelected < 0) currentlySelected = 2;
                        disp->clearScrollingText(1);
                case 1: currentlySelected++; //scroll down
                        if(currentlySelected == 3) currentlySelected = 0;
                        disp->clearScrollingText(1);
                        break;
                case 2: signal = 2; //exit alarm settings menu
                }
                break;
        /* todo, add and delete control code
        case 1: switch(input){ //control add menu
                case 0:
                case 1:
                case 2:
                }
                break;
        case 2: switch(input){ //control delete menu
                case 0:
                case 1:
                case 2:
                }
                break;
        */
        }
}

void editAlarms::runLogic(){

}

void editAlarms::drawFrame(){
        switch(currentState){
        case 0: showMenu();
                break;
        case 1: addAlarm();
                break;
        case 2: deleteAlarm();
                break;
        }
}

void editAlarms::showMenu(){
        disp->scrollingText("Edit Alarms: ", 0, CRGB::Red, CRGB::Blue);
        switch(currentState){
        case 0: disp->scrollingText("Add Alarm ", 1, CRGB::Red, CRGB::Blue);
                break;
        case 1: disp->scrollingText("Delete Alarm ", 1, CRGB::Red, CRGB::Blue);
                break;
        case 2: disp->scrollingText("Exit ", 1, CRGB::Red, CRGB::Blue);
        }
}

void editAlarms::addAlarm(){
        disp->scrollingText("Time: ", 0, CRGB::Red, CRGB::Blue);
        //Display temp time of alarm
}

void editAlarms::deleteAlarm(){
        disp->scrollingText("Delete: ", 0, CRGB::Red, CRGB::Blue);
        //Display temp time of currently selected alarm.
}
