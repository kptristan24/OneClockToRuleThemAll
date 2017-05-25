#ifndef MAINMENU_H
#define MAINMENU_H

#include "timekeeping.h"
#include "display.h"
#include "state.h"
#include "buttons.h"
#include "timeS.h"
#include "snake.h"
#include "demoState.h"
#include "editAlarms.h"
#include "buttonTest.h"

extern display disp;
extern clockLib clk;
extern Buttons buttons;
extern state *newState;
extern uint8_t signal;

class mainMenu : public state{
public:
        mainMenu();
        ~mainMenu();
        void handleInput();
        void runLogic();
        void drawFrame();
private:
        menu <mainMenu>clockMenu;
        int8_t transition;
};

#endif
