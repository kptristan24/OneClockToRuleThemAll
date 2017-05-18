#include "snake.h"

snake::snake(){
        disp->clearScrollingText(display::ALL);
        xSize = disp->getHorizSize();
        ySize = disp->getVertSize();

        grid = new uint8_t*[ySize];
        for(uint8_t i = 0; i < ySize; i++){
                grid[i] = new uint8_t[xSize];
        }

        state = MENU;

        gameMenu.setupMenu("Sssnake ", this);
        gameMenu.addOption("Exit", &signal, SET, stateStack::EXIT);
        gameMenu.addOption("New Game ", &newGame);

        pauseMenu.setupMenu("Paused ", this);
        pauseMenu.addOption("Continue ", &state, SET, RUN);
        pauseMenu.addOption("Quit", &state, SET, GOVER);
}

snake::~snake(){
        if(!grid)
                return;

        for(int i = 0; i < ySize; i++){
                delete [] grid[i];
        }
        delete [] grid;
}

void snake::handleInput(){
        switch(state){
        case MENU : gameMenu.update();
                    break;
        case RUN  : gameInput();
                    break;
        case PAUSE: pauseMenu.update();
                    break;
        case GOVER: gameOverInput();
                    break;
        }
}

void snake::gameOverInput(){
        const int input = buttons->getInput();
        if(input > -1){
                state = MENU;
                disp->clearScrollingText(display::ALL);
        }
}

void snake::gameInput(){
        const int input = buttons->getInput();

        switch(input){
        case 0: direction++;
                if(direction == 4)
                        direction = 0;
                break;
        case 1: direction--;
                if(direction == -1)
                        direction = 4;
                break;
        case 2: state = PAUSE;
                disp->clearScrollingText(display::ALL);
                break;
        }
}

void snake::runLogic(){
        if(state != RUN)
                return;

        //update position, check for out of bounds head, check for food
        moveSnake();

        //check if food found
        /*
        if(head == food){
                moveFood();
                length++;
        }
        else{ //shrink tail
                updateTail();
        }
        */
        //check if out of bounds
        if(head.x < 0 || head.x >= xSize){
                state = 2;
        }
        else if(head.y < 0 || head.y >= ySize){
                state = 2;
        }

        grid[head.y][head.x] = 1;
}

//will get very slow as board gets full, should fix this at some point
void snake::moveFood(){
        uint8_t x, y;

        do{
                x = random(xSize);
                y = random(ySize);
        }while(grid[y][x]);

        grid[y][x] = 2;
}

void snake::updateTail(){

}

void snake::moveSnake(){
        switch(direction){
        case 0: head.x += 1;
                break;
        case 1: head.y -= 1;
                break;
        case 2: head.x -= 1;
                break;
        case 3: head.y += 1;
                break;
        }
}

void snake::drawFrame(){
        switch(state){
        case MENU : gameMenu.draw();
                    break;
        case RUN  : gameInput();
                    break;
        case PAUSE: pauseMenu.draw();
                    break;
        case GOVER: gameOver();
                    break;
        }
}

void snake::genLengthStr(){
        lengStr[0] = '0';
        lengStr[1] = '0';
        lengStr[2] = '0';

        if(length > 100)
                lengStr[0] = '1';

        length -= 100;
        if(length > 9){
                uint8_t temp = length - 100;
                length -= temp;
                lengStr[1] = (temp / 10) + 48;
        }

        if(length != 0)
                lengStr[2] = length + 48;
}

void snake::gameOver(){
        CRGB temp[4] = {CRGB::Blue, CRGB::Green, CRGB::Blue};

        disp->scrollingText("Game Over ", display::TOP, CRGB::Red, CRGB::Blue);
        disp->staticText(lengStr, display::BOT, 3, temp);
}

void snake::newGame(){
        //create clean game state
        int i, j;

        for(i = 0; i < ySize; i++){
                for(j = 0; j < xSize; j++){
                        grid[i][j] = 0;
                }
        }

        head.set(1, 1);
        tail.set(1, 1);

        direction = 0;
        length = 1;
        state = RUN;
        grow = 0;
}
