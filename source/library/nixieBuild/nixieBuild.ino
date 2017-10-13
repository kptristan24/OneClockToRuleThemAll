
#include <SPI.h>
#include "timekeeping.h"
#include "display.h"
#include "state.h"
#include "stateStack.h"

#include "nixieState.h"


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
        stk.push(new nixieClock);
        top = stk.accessStack();

        newState = NULL;
        signal = 0;
}

void loop() {

        (*top)->curState->handleInput();
        (*top)->curState->runLogic();
        (*top)->curState->drawFrame();

}
