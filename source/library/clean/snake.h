#ifndef SNAKE_H
#define SNAKE_H

#include "timekeeping.h"
#include "display.h"
#include "state.h"
#include "buttons.h"
#include "menu.h"

extern display *disp;
extern clockLib *clk;
extern state *newState;
extern uint8_t signal;
extern Buttons *buttons;

struct point{
        point(){
                x = 0;
                y = 0;
        }
        point(uint8_t a, uint8_t b){
                x = a;
                y = b;
        }
        void set(uint8_t a, uint8_t b){
                x = a;
                y = b;
        }

        bool operator ==(const point &other) const{
                if(other.x == x && other.y == y){
                        return true;
                }
                return false;
        }
        uint8_t x;
        uint8_t y;
};

class snake : public state{
public:
        enum GameState {MENU, RUN, PAUSE, GOVER};
        snake();
        ~snake();

        void handleInput();
        void runLogic();
        void moveSnake(); //helper for runLogic movement processing
        void drawFrame();

        void moveFood();
        void updateTail();
        void gameOver();
        void newGame();
        void gameInput();
        void genLengthStr();

        void gameOverInput();
private:
        menu <snake>gameMenu;
        menu <snake>pauseMenu;
        int direction;
        point head;
        point tail;
        int length;

        uint8_t **grid;
        int xSize;
        int ySize;
        int input;
        int grow;
        uint8_t state; //0 mainMenu, 1 running, 2 paused, 3 game over
        char lengStr[3];
};

#endif
