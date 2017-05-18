#include "demoState.h"
demo::demo(){}
void demo::handleInput(){}
void demo::runLogic(){}
void demo::drawFrame(){
        disp->scrollingText("Hello ", 0, CRGB::Red, CRGB::Blue);
        disp->scrollingText("World! ", 1, CRGB::Blue, CRGB::Green);
}
