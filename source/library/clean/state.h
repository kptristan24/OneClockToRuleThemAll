#ifndef STATE_H
#define STATE_H

#include "timekeeping.h"
#include "display.h"

struct node;
class state;

extern display *disp;
extern class clockLib *clk;
extern state *newState;
extern uint8_t signal;

class state{
public:
        state(){

        };
        ~state(){

        };

        virtual void handleInput()=0;
        virtual void runLogic()=0;
        virtual void drawFrame()=0;
protected:
};


class showTime : public state{
public:
        showTime(){

        };
        ~showTime(){

        };

        void handleInput(){
                //handle buttons
        };
        void runLogic(){
                // show the time
        };
        void drawFrame(){
                 //update time: does all the work
        };


};

#endif
