#ifndef BUTTONTEST_H
#define BUTTONTEST_H

#include "timekeeping.h"
#include "display.h"
#include "state.h"
#include "buttons.h"
#include "timeS.h"
#include "menu.h"

extern display disp;
extern clockLib clk;
extern Buttons buttons;
extern state *newState;
extern uint8_t signal;


class buttonTest : public state{
public:
        buttonTest();
        void handleInput();
        void runLogic();
        void drawFrame();
private:
        //menu <buttonTest>testMenu;
        uint8_t counter;
        uint8_t state;
};

#endif
