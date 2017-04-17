
#include <SPI.h>
#include "timekeeping.h"
#include "display.h"
#include "state.h"
#include "demoState.h"
#include "stateStack.h"


//hardware interfaces
display disp = display();
clockLib clk = clockLib();
stateStack stk = stateStack();

node **top;
state *newState;
uint8_t signal;

void setup() {
        Serial.begin(9600);
        #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
          clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
        #endif

        //setup initial state: basic timekeeping
        stk.push(new demo);
        top = stk.accessStack();

        newState = NULL;
        signal = 0;
}

void loop() {
        //rtc.update();
        //if(!clk.checkAlarms()){ //can generate a state transistion if an alarm goes off
                (*top)->curState->handleInput();
                (*top)->curState->runLogic();
                (*top)->curState->drawFrame();
        //}

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
