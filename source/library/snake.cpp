#include "snake.h"

snake::snake(Adafruit_DotStar *strip, wordClock *wc) : state(strip, wc){
        int i;
        xSize = wc->getLEDSPerRow();
        ySize = wc->getDisplaySize()/xSize;
        
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

bool snake::handleInput(){
        //get left or right button input
        /* TODO*/
        
        if(input == 0){
                //quit button pushed
                return true;
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
        
        return false;
}

void snake::runLogic(){
        if(isPaused){
                paused();
                return;
        }
        
        //update position, check for out of bounds head, check for food
        
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
        isPaused = true;
}