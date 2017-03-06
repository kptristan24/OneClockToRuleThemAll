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

void wordClock::wordClockSetup(Adafruit_DotStar *strip, int hours, int minutes){
        color = genTimeColor(hours, minutes);
        updateGridFromTime(hours, minutes);
        updateDisplayFromGrid(strip);
}

void wordClock::testMe(){
        Serial.print(test);
}

uint32_t wordClock::genTimeColor(int hours, int minutes){
        //using colorspecturm, generate a color for the time of day
}

void wordClock::updateGridFromTime(int hours, int minutes){
        int i, hourPos = 0, minutePos = 0;
        
        //figure out the correct color
        color = genTimeColor(hours,minutes);
        
        //clear grid
        for(i = 0; i < NUM_LEDS; i++){
                gridLEDs[i] = 0;
        }
        
        //figure out hour and time phrase positions
        /* TODO */
        
        //turn on grid for hour
        for(i = 1; i < letters[hourPos][0]; i++){
                gridLEDs[letters[hourPos][i]] = 1;
        }
        
        //turn on grid for minutes phrase
        for(i = 1; i < letters[minutePos][0]; i++){
                gridLEDs[letters[minutePos][i]] = 1;
        }
        
        //Set additional words...

}

void wordClock::updateDisplayFromGrid(Adafruit_DotStar *strip){
        int i;
  
        strip->clear();
        for(i = 0; i < NUM_LEDS; i++){
                if(gridLEDs[i]){
                        strip->setPixelColor(i, color);
                }
        }
        
        strip->show();
}


