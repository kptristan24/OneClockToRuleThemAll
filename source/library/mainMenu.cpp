#include "mainMenu.h"

mainMenu::mainMenu(){
        Serial.print(F("mainMenu\n"));
        transition = -1;

        clockMenu.setupMenu(F("Menu"), this);
        clockMenu.addOption(F("Edit Alarms: "), &transition, SET, 0);
        clockMenu.addOption(F("Snake "), &transition, SET, 2);
        clockMenu.addOption(F("Text"), &transition, SET, 4);
        clockMenu.addOption(F("Grid Demo "), &transition, SET, 1);
        clockMenu.addOption(F("Alarm "), &transition, SET, 3);
        clockMenu.addOption(F("Exit"), &signal, SET, stateStack::EXIT);
}

mainMenu::~mainMenu(){} //exists so that menu gets cleaned up

void mainMenu::handleInput(){
        clockMenu.update();
}

void mainMenu::runLogic(){
        if(transition != -1){
                Serial.print(F("runlogic: "));
                Serial.println(transition);
        }

        switch(transition){
        case 0: signal = stateStack::REPLACE; //show an alarm for demo purposes
                newState = new editAlarms;
                break;
        case 1: signal = stateStack::REPLACE; //launch led grid demo
                newState = new demo;
                break;
        case 2: signal = stateStack::REPLACE; //launch snake game
                newState = new snake;
                break;
        case 3: signal = stateStack::REPLACE;
                newState = new alarmState(clk.getCurrentTime());
                break;
        case 4: signal = stateStack::REPLACE;
                newState = new buttonTest;
                break;
        }

        transition = -1;
}

void mainMenu::drawFrame(){
        clockMenu.draw();
        disp.update();
}
