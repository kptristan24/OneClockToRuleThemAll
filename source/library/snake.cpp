#include "snake.h"

snake::snake(Adafruit_DotStar *strip) : game(strip){
        xSize = display->getLEDSPerRow();
        ySize = display->getDisplaySize()/x;
        
        grid = new int*[ySize];
        for(int i = 0; i < ySize; i++){
                grid[i] = new int[xSize];
        }
        
        head.set(1, 1);
        tail.set(1, 1);
        
        food.set(10, 10);
        
        direction = 0;
        length = 1;
        quit = false;
}
      
snake::~snake(){
        if(!grid)
                return;
                
        for(int i = 0; i < y; i++){
                delete [] grid[i];
        }
        delete [] grid;

}

bool handleInput(){
        //get left or right button input
        /* TODO*/
        
        if(input == 1){
                direction++;
                if(direction == 4)
                        direction = 0;
        }
        else if(input == 2){
                direction--;
                if(direction == -1)
                        direction = 4;
        }
        else if(input == 0){
                return true;
        }
        
        return false;
}

void runLogic(){

        
}

void drawFrame(){
        
}