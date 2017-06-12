#include <SPI.h>
//hardware abstraction libraries
#include "timekeeping.h"
#include "display.h"
#include "buttons.h"
#include "stateStack.h"

//example programs
#include "state.h"
#include "basicTime.h"

//hardware interfaces
display disp;
clockLib clk;
stateStack stk;
Buttons buttons;

state *runningState;
state *newState;
uint8_t signal;

void setup() {
        Serial.begin(9600);

        randomSeed(analogRead(0));

        //setup initial state: basic timekeeping
        stk.push(new basicTime);
        runningState = stk.accessStack()->curState;

        newState = nullptr;
        signal = stateStack::NOTHING;
}

void loop() {
        //Run hardware interaction updates
        clk.update();
        buttons.update();

        //check for alarms and then run the current state
        if(!clk.checkAlarms()){
                runningState->handleInput();
                runningState->runLogic();
                runningState->drawFrame();
        }
        else{ //an alarm went off!
                newState = new alarmState(getCurrentTime());
                signal = stateStack::NEW;
        }

        //Statemachine manager
        switch(signal){
        case stateStack::NEW    : stk.push(newState);     //add new state requested.
                                  break;
        case stateStack::EXIT   : stk.pop();              //exit top state
                                  break;
        case stateStack::REPLACE: stk.pop();              //replace top state
                                  stk.push(newState);
                                  break;
        }

        //things that need to be cleaned up if a state change occured
        if(signal){
                runningState = stk.accessStack()->curState;
                signal = stateStack::NOTHING;
                newState = nullptr;
                disp.clearScrollingText(display::ALL);
                disp.clear();
        }
}
