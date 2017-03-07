#ifndef SNAKE_H
#define SNAKE_H

#include <Arduino.h>
#include "state.h"

struct point{
        point(){
                x = 0;
                y = 0;
        }
        point(int a, int b){
                x = a;
                y = b;
        }
        void set(int a, int b){
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

class snake : public state{
public:
        snake(Adafruit_DotStar *, wordClock *);
        ~snake();
        
        bool handleInput();
        void runLogic();
        void drawFrame();
        
        void paused();
        void gameOver();
        void newGame();
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
        
        bool isPaused;
        
};

#endif