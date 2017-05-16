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
void mainMenu::runLogic(){}
void mainMenu::drawFrame(){
        clockMenu.draw();
}
