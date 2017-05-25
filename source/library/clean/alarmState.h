#ifndef ALARMSTATE_H
#define ALARMSTATE_H

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

class alarmState : public state{
public:
        alarmState();
        alarmState(const timeS &);
        void handleInput();
        void runLogic();
        void drawFrame();
private:
        char alarmTime[4];
};

#endif
