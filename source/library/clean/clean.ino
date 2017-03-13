
#include <SPI.h>
#include "timekeeping.h"
#include "display.h"
#include "state.h"
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
        stk.push(new showTime);
        top = stk.accessStack();

        newState = NULL;
        signal = 0;
}

void loop() {
        (*top)->curState->handleInput();
        (*top)->curState->runLogic();
        (*top)->curState->drawFrame();

        if(signal){
                switch(signal){
                case 1: stk.push(newState); //new state construction requested.
                        break;
                case 2: stk.pop(); //exit top state
                        break;
                case 3: stk.pop(); stk.push(newState); //state replacement requested
                        break;
                default: Serial.print("State change requested with unknown signal: ");
                         Serial.print(signal);
                }
        }
}
