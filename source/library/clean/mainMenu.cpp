#include "mainMenu.h"

mainMenu::mainMenu(){
        currentlySelected = 0;
        transition = 0;

        clockMenu.setMenuName("Main Menu: ");
        clockMenu.addOption("Edit Alarms: ", &transition, option::SET, 0);
        clockMenu.addOption("Grid Demo ", &transition, option::SET, 1);
        clockMenu.addOption("Snake Game ", &transition, option::SET, 2);
        clockMenu.addOption("Show Alarm ", &transition, option::SET, 3);
        clockMenu.addOption("Exit", &signal, option::SET, stateStack::EXIT);
}

void mainMenu::handleInput(){
        clockMenu.update();
}

void mainMenu::runLogic(){
        if(transition){
                switch(currentlySelected){
                case 0: signal = stateStack::REPLACE; //show an alarm for demo purposes
                        newState = new editAlarms();
                        break;
                case 1: signal = stateStack::REPLACE; //launch led grid demo
                        newState = new demo;
                        break;
                case 2: signal = stateStack::REPLACE; //launch snake game
                        newState = new snake;
                        break;
                case 3: signal = stateStack::REPLACE
                        newState = new alarmState(clk->getCurrentTime());
                        break;
                }
        }
}

void mainMenu::drawFrame(){
        clockMenu.draw();
}
