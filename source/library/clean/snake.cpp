#include "snake.h"

snake::snake(){
        int i;
        xSize = disp->getHorizSize();
        ySize = disp->getVertSize();

        grid = new int*[ySize];
        for(i = 0; i < ySize; i++){
                grid[i] = new int[xSize];
        }

        newGame();
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
        const uint8_t input = buttons.getInput();

        if(input == 0){
                signal = 2;
        }
        else if(input == 3){
                if(isPaused){
                        isPaused = false;
                }
                else{
                        isPaused = true;
                }
        }
        else if(input == 1 && !isPaused){
                direction++;
                if(direction == 4)
                        direction = 0;
        }
        else if(input == 2 && !isPaused){
                direction--;
                if(direction == -1)
                        direction = 4;
        }
}

void snake::runLogic(){
        if(isPaused){
                paused();
                return;
        }

        //update position, check for out of bounds head, check for food
        moveSnake();

        //check if food found
        if(head == food){
                moveFood();
                length++;
        }
        else{ //shrink tail
                updateTail();
        }

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
        x = random(xSize);
        y = random(ySize);

        while(grid[y][x]){
                x = random(xSize);
                y = random(ySize);
        }

        food.set(x,y);
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

}

void snake::paused(){
        //print a paused message
        /* TODO*/
        /*
        Depends on display library for text
        */
}

void snake::gameOver(){
        //print a victory/loss message
        /* TODO*/
        /*
        Depends on display library for text
        */
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

        food.set(10, 10);

        direction = 0;
        length = 1;
        isPaused = false;
        state = 1;
        grow = 0;
}
