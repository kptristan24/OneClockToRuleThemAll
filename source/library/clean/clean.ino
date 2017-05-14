
#include <SPI.h>
//hardware abstraction libraries
#include "timekeeping.h"
#include "display.h"
#include "buttons.h"

//state abstraction code
#include "state.h"
#include "stateStack.h"
#include "basicTime.h"

//hardware interfaces
display *disp;
clockLib *clk;
stateStack *stk;
Buttons *buttons;

node **top;
state *newState;
uint8_t signal;

void setup() {
        Serial.begin(9600);

        disp = new display;
        clk = new clockLib;
        stk = new stateStack;
        buttons = new Buttons;

        randomSeed(analogRead(0));

        //setup initial state: basic timekeeping
        stk->push(new basicTime);
        top = stk->accessStack();

        newState = NULL;
        signal = stateStack::NOTHING;
}

void loop() {
        //Run hardware interaction updates
        clk->update();
        buttons->update();

        //check for alarms and then run the current state
        if(!clk->checkAlarms()){ //can generate a state transistion if an alarm goes off
                (*top)->curState->handleInput();
                (*top)->curState->runLogic();
                (*top)->curState->drawFrame();
        }

        //Statemachine manager
        switch(signal){
        case stateStack::NOTHING: break;                  //nothing requested
        case stateStack::NEW    : stk->push(newState);     //add new state requested.
                                  break;
        case stateStack::EXIT   : stk->pop();              //exit top state
                                  break;
        case stateStack::REPLACE: stk->pop();              //replace top state
                                  stk->push(newState);
                                  break;
        default: Serial.print("State change requested with unknown signal: ");
                 Serial.print(signal);
        }

        //things that need to be cleaned up if a state change occured
        if(signal){
                top = stk->accessStack();
                signal = stateStack::NOTHING;
                newState = nullptr;
                disp->clearScrollingText(2);
        }
}
