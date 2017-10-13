#ifndef EDITALARMS_H
#define EDITALARMS_H

#include "timekeeping.h"
#include "display.h"
#include "state.h"
#include "buttons.h"
#include "menu.h"
#include "timeS.h"

extern display disp;
extern clockLib clk;
extern Buttons buttons;
extern state *newState;
extern uint8_t signal;

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
        void addInputHelper(uint8_t input);

        CRGB minCol, hourCol, amPmCol;
        menu <editAlarms>mainMenu;
        menu <editAlarms>deleteAlarm;
        uint8_t currentlySelected;
        uint8_t currentState;
        bool amPm;
        timeS alarmTime;
        char timeStr[4];
};


#endif
