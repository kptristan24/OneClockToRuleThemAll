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
        snake();
        ~snake();

        bool handleInput();
        void runLogic();
        point moveSnake(); //helper for runLogic movement processing
        void drawFrame();

        void paused();
        void gameOver();
        void newGame();
private:
        int direction;
        point head;
        point tail;
        point food;

        int **grid;
        int xSize;
        int ySize;
        int input;
        int grow;
        int state; //0 running, 1 paused, 2 score screen
};

#endif
