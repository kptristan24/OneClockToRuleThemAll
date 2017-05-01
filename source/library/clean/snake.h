#ifndef SNAKE_H
#define SNAKE_H

#include "timekeeping.h"
#include "display.h"
#include "state.h"
#include "buttons.h"

extern display *disp;
extern clockLib *clk;
extern state *newState;
extern uint8_t signal;
extern Buttons buttons;

struct point{
        point(){
                x = 0;
                y = 0;
        }
        point(const int &a, const int &b){
                x = a;
                y = b;
        }
        void set(const int &a, const int &b){
                x = a;
                y = b;
        }

        bool operator ==(const point &other) const{
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

        void handleInput();
        void runLogic();
        void moveSnake(); //helper for runLogic movement processing
        void drawFrame();

        void moveFood();
        void updateTail();
        void paused();
        void gameOver();
        void newGame();
private:
        int direction;
        point head;
        point tail;
        point food;
        int length;

        int **grid;
        int xSize;
        int ySize;
        int input;
        int grow;
        int state; //0 running, 1 paused, 2 score screen
        bool isPaused;
};

#endif
