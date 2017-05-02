#ifndef EDITALARMS_H
#define EDITALARMS_H

#include "timekeeping.h"
#include "display.h"
#include "state.h"
#include "buttons.h"

extern display *disp;
extern clockLib *clk;
extern state *newState;
extern uint8_t signal;
extern Buttons *buttons;

class editAlarms : public state{
public:
        editAlarms();
        void handleInput();
        void runLogic();
        void drawFrame();

        void showMenu();
        void addAlarm();
        void deleteAlarm();
private:
        uint8_t currentlySelected;
        uint8_t currentState;
        uint8_t subState;
        timeS alarmTime;
};


#endif
