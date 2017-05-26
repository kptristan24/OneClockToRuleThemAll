#include "snake.h"

snake::snake(){
        Serial.print(F("Snake start\n"));
        disp.clearScrollingText(display::ALL);
        xSize = disp.getHorizSize();
        ySize = disp.getVertSize();
        state = MENU;

        gameMenu.setupMenu(F("Snake "), this);
        gameMenu.addOption(F("Exit"), &signal, SET, stateStack::EXIT);
        gameMenu.addOption(F("New Game "), &state, SET, START);

        pauseMenu.setupMenu(F("Paused "), this);
        pauseMenu.addOption(F("Cont"), &state, SET, RUN);
        pauseMenu.addOption(F("Quit"), &state, SET, GOVER);

        Serial.print(F("fin\n"));
}

snake::~snake(){} //just here so that menu destructors get called

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
        case START: changeToStart();
                    break;
        }
}

void snake::gameOverInput(){
        const int input = buttons.getInput();
        if(input > -1){
                state = MENU;
                disp.clearScrollingText(display::ALL);
        }
}

void snake::gameInput(){
        const int input = buttons.getInput();

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
                disp.clearScrollingText(display::ALL);
                break;
        }
}

void snake::changeToStart(){
        newGame();
}

void snake::runLogic(){
        if(state != RUN)
                return;
        else if(frameCounter){
                Serial.print(F(" Frame : "));
                Serial.print(frameCounter);
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

        if(tempX < 0 || tempX >= xSize){
                state = GOVER;
                disp.clear();
        }
        else if(tempY < 0 || tempY >= ySize){
                state = GOVER;
                disp.clear();
        }
        else if(grid[tempY][tempX] == 1){
                state = GOVER;
                disp.clear();
        }

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
        Serial.print(F(" frame: "));
        Serial.print(state);
        Serial.print(F("Pos (x,y): "));
        Serial.print(head.x);
        Serial.print(F(", "));
        Serial.println(head.y);
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
        disp.update();
}

void snake::drawGame(){
        if(frameCounter != GAMESPEED)
                return;
        disp.clear();
        for(int8_t y = 0; y < ySize; y++){
                for(int8_t x = 0; xSize; x++){
                        if(grid[y][x] == 0)
                                continue;
                        else if(grid[y][x] == 1)
                                disp.setPixel(y, x, CRGB::Red);
                        else if(grid[y][x] == 2)
                                disp.setPixel(y, x, CRGB::Green);
                }
        }
        Serial.print(F("Fin Draw\n"));
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
        disp.clear();
        CRGB temp[4] = {CRGB::Blue, CRGB::Green, CRGB::Blue};

        disp.scrollingText(F("Game Over "), display::TOP, CRGB::Red, CRGB::Blue);
        disp.staticText(lengStr, display::BOT, 3, temp);
}

void snake::newGame(){
        Serial.print(F("New Game\n"));
        disp.clear();

        //create clean game state
        for(uint8_t i = 0; i < ySize; i++){
                for(uint8_t j = 0; j < xSize; j++){
                        grid[i][j] = 0;
                }
        }

        grid[ySize/2][xSize/2] = 2;

        head.set(1, 1);
        grid[1][1] = 1;
        tail.set(1, 1);

        direction = 0;
        length = 1;

        state = RUN;
        frameCounter = GAMESPEED;
        Serial.print(F("fin\n"));
}
