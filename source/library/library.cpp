#include "library.h"

wordClock::wordClock(){
        test = 4;
        letters = new int*[23 + 6];
        
        letters[0] = fiveM;
        letters[1] = tenM;
        letters[2] = fifteenM;
        letters[3] = twentyM;
        letters[4] = twentyfiveM;
        letters[5] = thirtyM;
        letters[6] = thirtyfiveM;
        letters[7] = fourtyM;
        letters[8] = fourtyfiveM;
        letters[9] = fiftyM;
        letters[10] = fiftyfiveM;
        letters[11] = one;
        letters[12] = two;
        letters[13] = three;
        letters[14] = four;
        letters[15] = five;
        letters[16] = six;
        letters[17] = seven;
        letters[18] = eight;
        letters[19] = nine;
        letters[20] = ten;
        letters[21] = eleven;
        letters[22] = twelve;
        letters[23] = amE;
        letters[24] = pmE;
        
                
}

wordClock::~wordClock(){ 
        delete [] letters;
}

void wordClock::testMe(){
        Serial.print(test);
}

void wordClock::updateGrid(int hours, int minutes){
        
}


