
#include <SPI.h>
//hardware abstraction libraries
#include "timekeeping.h"
#include "display.h"
#include "buttons.h"

//state abstraction code
#include "state.h"
#include "stateStack.h"
#include "demoState.h"


//hardware interfaces
display disp = display();
clockLib clk = clockLib();
stateStack stk = stateStack();
Buttons buttons = Buttons();

node **top;
state *newState;
uint8_t signal;

void setup() {
        Serial.begin(9600);

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
        clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif

        randomSeed(analogRead(0));

        //setup initial state: basic timekeeping
        stk.push(new demo);
        top = stk.accessStack();

        newState = NULL;
        signal = 0;
}

void loop() {
        //Run hardware interaction updates
        rtc.update();
        buttons.update();

        //check for alarms and then run the current state
        if(!clk.checkAlarms()){ //can generate a state transistion if an alarm goes off
                (*top)->curState->handleInput();
                (*top)->curState->runLogic();
                (*top)->curState->drawFrame();
        }

        //Statemachine manager
        switch(signal){
        case 0: break;                  //nothing requested
        case 1: stk.push(newState);     //add new state requested.
                break;
        case 2: stk.pop();              //exit top state
                break;
        case 3: stk.pop();              //replace top state
                stk.push(newState);
                break;
        default: Serial.print("State change requested with unknown signal: ");
                 Serial.print(signal);
        }
        if(signal){
                disp.clearScrollingText(2);
        }
}
