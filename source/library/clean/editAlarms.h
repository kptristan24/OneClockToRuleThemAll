#ifndef EDITALARMS_H
#define EDITALARMS_H

#include "timekeeping.h"
#include "display.h"
#include "state.h"
#include "buttons.h"
#include "menu.h"

extern display *disp;
extern clockLib *clk;
extern state *newState;
extern uint8_t signal;
extern Buttons *buttons;

class editAlarms : public state{
public:
        enum Mode {MENU, NEW, DELETE};
        editAlarms();
        void handleInput();
        void runLogic();
        void drawFrame();

private:
        void updateAlarmTime(uint8_t, uint8_t);
        void updateTimeString();

        void changeToDelete();
        void deleteGetNextAlarm();
        void deleteAlarmResponse();

        void changeToAdd();
        void addDrawTime();
        void addAlarmInput();
        void addUpdateColors();

        CRGB minCol, hourCol, amPmCol;
        menu mainMenu;
        menu addAlarm;
        menu deleteAlarm;
        uint8_t currentlySelected;
        uint8_t currentState;
        bool amPm;
        timeS alarmTime;
        char timeStr[6];
};


#endif
