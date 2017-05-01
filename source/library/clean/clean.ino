
#include <SPI.h>
//hardware abstraction libraries
#include "timekeeping.h"
#include "display.h"
#include "buttons.h"

//state abstraction code
#include "state.h"
#include "stateStack.h"
#include "demoState.h"

CRGB LEDstrip[NUM_LEDS];

//hardware interfaces
display *disp; // = display();
clockLib *clk;
stateStack *stk;
Buttons *buttons;

node **top;
state *newState;
uint8_t signal;

int freeRam ()
{
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void setup() {
        Serial.begin(9600);
        Serial.print("contents in constructor:");
        Serial.print((int)LEDstrip[2], BIN);
        Serial.print("\n");

        disp = new display;
        clk = new clockLib;
        stk = new stateStack;
        buttons = new Buttons;

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
        case 1: stk->push(newState);     //add new state requested.
                break;
        case 2: stk->pop();              //exit top state
                break;
        case 3: stk->pop();              //replace top state
                stk->push(newState);
                break;
        default: Serial.print("State change requested with unknown signal: ");
                 Serial.print(signal);
        }
        if(signal){
                disp->clearScrollingText(2);
        }
}
