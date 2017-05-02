#include "mainMenu.h"

mainMenu::mainMenu(){
        currentlySelected = 0;
        transition = 0;
}

void mainMenu::handleInput(){
        int input = buttons->getInput();

        if(input != -1){
                switch(input){
                case 0: currentlySelected--; //scroll up
                        if(currentlySelected < 0) currentlySelected = NUM_OPTIONS - 1;
                        disp->clearScrollingText(1);
                        break;
                case 1: currentlySelected++; //scroll down
                        if(currentlySelected == NUM_OPTIONS) currentlySelected = 0;
                        disp->clearScrollingText(1);
                        break;
                case 2: transition = 1; //an option was selected
                        break;
                }
        }
}

void mainMenu::runLogic(){
        if(transition){
                switch(currentlySelected){
                case 0: signal = 3; //show an alarm for demo purposes
                        newState = new alarmState(clk->getCurrentTime());
                        break;
                case 1: signal = 3; //launch led grid demo
                        newState = new demo;
                        break;
                case 2: signal = 3; //launch snake game
                        newState = new snake;
                        break;
                case 3: signal = 3;
                        newState = new editAlarms;
                        break;
                case 4: signal = 2; //exit
                        break;
                }
        }
}

void mainMenu::drawFrame(){
        disp->scrollingText("Menu: ", 0, CRGB::Green, CRGB::Lime);
        switch(currentlySelected){
        case 0: disp->scrollingText("New Alarm ", 1, CRGB::Blue, CRGB::Aqua);
                break;
        case 1: disp->scrollingText("Grid Demo ", 1, CRGB::Blue, CRGB::Aqua);
                break;
        case 2: disp->scrollingText("Snake Game ", 1, CRGB::Blue, CRGB::Aqua);
                break;
        case 3: disp->scrollingText("Edit Alarms ", 1, CRGB::Blue, CRGB::Aqua);
                break;
        case 4: disp->scrollingText("Exit ", 1, CRGB::Blue, CRGB::Aqua);
                break;
        }
}
