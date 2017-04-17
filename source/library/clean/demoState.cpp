#include "demoState.h"

demo::demo(){
        frameCounter = 0;
        curState = 1;
        curTest = 0;
}

void demo::handleInput(){

}

void demo::runLogic(){

}

void demo::drawFrame(){
        switch(curState){
        case 1: testEachPosition();
                break;
        case 2: testRows();
                break;
        case 3: testColumns();
                break;
        default:
                curState = 1;
        }

        frameCounter++;
}

void demo::testEachPosition(){
        const int row = curTest / disp.getHorizSize();

        if(!(frameCounter % 60)){
                disp.clear();
                disp.setPixel(row, (curTest % disp.getHorizSize()));
                curTest++;
        }
        else{
                return;
        }

        if(curTest == disp.getHorizSize() * disp.getVertSize()){
                curState++;
                curTest = 0;
        }
}

void demo::testRows(){
        const int numRows = disp.getVertSize();

        if(!(frameCounter % 60)){
                disp.clear();
                const int numCols = disp.getHorizSize();
                for(int i = 0; i < numCols; i++)
                        disp.setPixel(curTest, i);

                curTest++;
        }
        else{
                return;
        }

        if(curTest == numRows){
                curState++;
                curTest = 0;
        }
}

void demo::testColumns(){
        const int numCols = disp.getHorizSize();

        if(!(frameCounter % 60)){
                disp.clear();
                const int numRows = disp.getVertSize();
                for(int i = 0; i < numRows; i++)
                        disp.setPixel(i, curTest);

                curTest++;
        }
        else{
                return;
        }

        if(curTest == numCols){
                curState++;
                curTest = 0;
        }
}
