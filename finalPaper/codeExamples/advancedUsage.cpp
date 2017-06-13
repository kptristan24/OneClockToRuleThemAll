#include "timekeeping.h"
#include "display.h"
#include "buttons.h"
#include "stateStack.h"
#include "simpleState.h" //our basic program

display disp;
clockLib clk;
stateStack stk;
Buttons buttons;

state *runningState;
state *newState;
uint8_t signal;

void setup() {
        //the following 2 lines are only necessary if serial or random are being used
        Serial.begin(9600);
        randomSeed(analogRead(0));

        //setup initial state: the simpleState example
        stk.push(new simpleState);
        runningState = stk.accessStack()->curState;

        newState = nullptr;
        signal = stateStack::NOTHING;
}

void loop() {
        clk.update(); //update the clock abstraction
        buttons.update();

        if(!clk.checkAlarms()){ //run top program unless alarm happened
                runningState->handleInput();
                runningState->runLogic();
                runningState->drawFrame();
        }
        else{ //an alarm went off!
                newState = new alarmState(getCurrentTime());
                signal = stateStack::NEW;
        }

        switch(signal){ //Statemachine manager: changes running program
        case stateStack::NEW    : stk.push(newState);
                                  break;
        case stateStack::EXIT   : stk.pop();
                                  break;
        case stateStack::REPLACE: stk.pop();
                                  stk.push(newState);
                                  break;
        }

        if(signal){ //cleanup necessary after a state change
                runningState = stk.accessStack()->curState;
                signal = stateStack::NOTHING;
                newState = nullptr;
                disp.clearScrollingText(display::ALL);
                disp.clear();
        }
}
