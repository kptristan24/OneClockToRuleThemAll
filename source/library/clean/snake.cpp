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
        else if(frameCounter){
                frameCounter--;
                return;
        }

        moveSnake();
        frameCounter = GAMESPEED;
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
        for(int8_t y = tail.y - 1; y < tail.y + 2; y++){
                if(y < 0 || y >= ySize)
                        continue;
                for(int8_t x = tail.x - 1; x < tail.x + 2; x++){
                        if(x < 0 || x >= xSize)
                                continue;

                        if(grid[y][x] == 1 && x != tail.x && y != tail.y){
                                tail.set(y, x);
                                grid[tail.y][tail.x] = 0;
                                return;
                        }
                }
        }
}

void snake::moveSnake(){
        uint8_t tempX = head.x;
        uint8_t tempY = head.y;

        switch(direction){
        case 0: tempX += 1;
                break;
        case 1: tempY -= 1;
                break;
        case 2: tempX -= 1;
                break;
        case 3: tempY += 1;
                break;
        }

        if(tempX < 0 || tempX >= xSize)
                state = GOVER;
        else if(tempY < 0 || tempY >= ySize)
                state = GOVER;
        else if(grid[tempY][tempX] == 1)
                state = GOVER;

        if(grid[tempY][tempX] != 2){
                updateTail();
                grid[tempY][tempX] = 1;
                head.set(tempY, tempX);
        }
        else{
                length++;
                grid[tempY][tempX] = 1;
                head.set(tempY, tempX);
                moveFood();
        }
}

void snake::drawFrame(){
        switch(state){
        case MENU : gameMenu.draw();
                    break;
        case RUN  : drawGame();
                    break;
        case PAUSE: pauseMenu.draw();
                    break;
        case GOVER: gameOver();
                    break;
        }
}

void snake::drawGame(){
        if(frameCounter != GAMESPEED)
                return;

        disp->clear();
        for(int8_t y = tail.y - 1; y < tail.y + 2; y++){
                for(int8_t x = tail.x - 1; x < tail.x + 2; x++){
                        if(grid[y][x] == 0)
                                continue;
                        else if(grid[y][x] == 1)
                                disp->setPixel(y, x, CRGB::Red);
                        else if(grid[y][x] == 2)
                                disp->setPixel(y, x, CRGB::Green);
                }
        }
        disp->update();
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

        grid[ySize/2][xSize/2] = 2;

        head.set(1, 1);
        tail.set(1, 1);

        direction = 0;
        length = 1;

        state = RUN;
        frameCounter = GAMESPEED;
        drawFrame();
}
