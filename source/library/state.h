#ifndef STATE_H
#define STATE_H

#include <Adafruit_DotStar.h>
#include "library.h"

class state{
public:
        state(Adafruit_DotStar *strip, wordClock *wc){
                display = strip;
                this->wc = wc;
        };
        ~state();
        
        virtual bool handleInput()=0;
        virtual void runLogic()=0;
        virtual void drawFrame()=0;
protected:
        Adafruit_DotStar *display;
        wordClock *wc;
};

#endif