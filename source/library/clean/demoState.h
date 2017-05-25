#ifndef DEMOSTATE_H
#define DEMOSTATE_H

#include "timekeeping.h"
#include "display.h"
#include "state.h"
#include "buttons.h"

extern display disp;
extern clockLib clk;
extern Buttons buttons;
extern state *newState;
extern uint8_t signal;

class demo : public state{
public:
        demo();
        void handleInput();
        void runLogic();
        void drawFrame();

        void testEachPosition();
        void testRows();
        void testColumns();
        void testText();
private:
        int frameCounter;
        uint8_t curState;
        int curTest;
};


#endif
