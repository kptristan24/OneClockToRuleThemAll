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

#define NUM_OPTIONS 5

extern display *disp;
extern clockLib *clk;
extern state *newState;
extern uint8_t signal;
extern Buttons *buttons;

class mainMenu : public state{
public:
        mainMenu();
        void handleInput();
        void runLogic();
        void drawFrame();
private:
        menu clockMenu;
        uint8_t transition;
};

#endif
