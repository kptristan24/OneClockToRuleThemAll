#ifndef BASICTIME_H
#define BASICTIME_H

#include "timekeeping.h"
#include "display.h"
#include "state.h"
#include "buttons.h"
#include "timeS.h"
#include "mainMenu.h"

extern display disp;
extern clockLib clk;
extern Buttons buttons;
extern state *newState;
extern uint8_t signal;


class basicTime : public state{
public:
        basicTime();
        void handleInput();
        void runLogic();
        void drawFrame();
private:
        timeS currentTime;
};

#endif
