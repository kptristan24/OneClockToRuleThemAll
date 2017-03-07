#ifndef SNAKE_H
#define SNAKE_H

#include <Arduino.h>
#include "game.h"

struct point{
        point(int a, int b){
                x = a;
                y = b;
        }
        void setPoint(int a, int b){
                x = a;
                y = b;
        }
        
        bool checkEquals(const point &other){
                if(other.x == x && other.y == y){
                        return true;
                }
                return false;
        }
        int x;
        int y;
};

class snake : public game{
public:
        snake(Adafruit_DotStar *);
        ~snake();
        
        bool handleInput();
        void runLogic();
        void drawFrame();
private:
        int **grid;
        int xSize;
        int ySize;
        
        int input;
        
        int direction;
        int length;
        point head;
        point tail;
        
        point food;
        
};

#endif