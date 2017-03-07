#ifndef GAME_H
#define GAME_H

#include <Adafruit_DotStar.h>

class game{
public:
        game(Adafruit_DotStar *strip){
                display = strip;
        };
        ~game();
        
        bool handleInput()=0;
        void runLogic()=0;
        void drawFrame()=0;
protected:
        Adafruit_DotStar *display;
};

#endif