#include "display.h"

display::display(){
        for(int i = 0; i < 6; i++){
                pinMode(select_pins[i], OUTPUT);
        }

        for(int i = 0; i < 4; i++){
                pinMode(data_pins[i], OUTPUT);
        }

}

/*
void display::setupWords(){
        words[0] = fiveM;
        words[1] = tenM;
        words[2] = fifteenM;
        words[3] = twentyM;
        words[4] = twentyfiveM;
        words[5] = thirtyM;
        words[6] = thirtyfiveM;
        words[7] = fourtyM;
        words[8] = fourtyfiveM;
        words[9] = fiftyM;
        words[10] = fiftyfiveM;
        words[11] = one;
        words[12] = two;
        words[13] = three;
        words[14] = four;
        words[15] = five;
        words[16] = six;
        words[17] = seven;
        words[18] = eight;
        words[19] = nine;
        words[20] = ten;
        words[21] = eleven;
        words[22] = twelve;
}

void display::setupExtraWords(){
        if(extra[0])
                words[23] = amE;
        if(extra[1])
                words[24] = pmE;
        if(extra[2])
                words[25] = minOne;
        if(extra[3])
                words[26] = minTwo;
        if(extra[4])
                words[27] = minThree;
        if(extra[5])
                words[28] = minFour;
}

int display::getVertSize(){
        return NUM_LEDS / ROW_LENGTH;
}

int display::getHorizSize(){
        return ROW_LENGTH;
}

void display::update(){
#if !HEADLESS

        FastLED.show();
#else
        debugUpdateDisplay();
#endif
}

void display::clear(){
        FastLED.clear();
}

void display::debugUpdateDisplay(){
        int rows;
        unsigned char rowContents;
        rows = NUM_LEDS / ROW_LENGTH;

        Serial.print("Display state:");
        for(int i = 0; i < rows; i++){
                rowContents = 0;
                for(int j = 0; j < ROW_LENGTH; j++){
                        if(LEDstrip[j + (i*ROW_LENGTH)])
                                rowContents |= 1 << j;
                }
                Serial.print(rowContents, BIN);
        }
}

CRGB **display::rawStrip(){
        return dispArray;
}

void display::updateFromArray(int **numArray, CRGB &color, bool refresh){
        FastLED.clear();
        for(int i = 0; i < NUM_LEDS/ROW_LENGTH; i++){
                for(int j = 0; j < ROW_LENGTH; j++){
                        if(numArray[i][j])
                                dispArray[i][j] = color;
                }
        }

        if(refresh)
                update();
}

void display::setPixel(const int &x, const int &y, const CRGB &color){
        if((x < ROW_LENGTH) && (y < NUM_LEDS/ROW_LENGTH))
                dispArray[y][x] = color;
}

void display::setPixel(const int &position, const CRGB &color){
        if(position < NUM_LEDS)
                LEDstrip[position] = color;
}

void display::clearScrollingText(const int &strip){
        if(!strip)
                topText = 0;
        else if(strip == 1)
                botText = 0;
        else if(strip == 2){
                topText = 0;
                botText = 0;
        }
}

void display::setScrollingText(const char *message, const int &strip){
        if(!strip){ //set top strip
                topPosition = 0;
                topText = 1;
                topLength = strlen(message);
                updateMessage(message, strip);
        }
        else{ //set bot strip
                botPosition = 0;
                botText = 1;
                botLength = strlen(message);
                updateMessage(message, strip);
        }
}

// Outer loop is number of letters to copy
// Inner loop is each row of the letter
// Second inner loop is each column of each letter

void display::updateMessage(const char *message, const int &strip){
        const uint8_t vertOffset = strip * ((NUM_LEDS/ROW_LENGTH)/2);


}

void display::setWordBuiltin(const int &w, const CRGB &color){
        if(w >= (NUM_WORDS + NUM_EXTRA)){
                return;
        }

        int constCoord;

        if(words[w][4]){
                constCoord = words[w][0];
                for(int y = words[w][1]; y < words[w][3]; y++){
                        dispArray[y][constCoord] = color;
                }
        }
        else{
                constCoord = words[w][1];
                for(int x = words[w][0]; x < words[w][2]; x++){
                        dispArray[constCoord][x] = color;
                }
        }
}

void display::setFromTime(const int &h, const int &m, const CRGB &color){
        int afternoonT = h;
        int timeRange = m / 5;

        //set am or pm if they exist
        if(h > 11 && extra[1])
                setWordBuiltin(24, color);
        else if(extra[0]){
                setWordBuiltin(23, color);
                afternoonT = h - 12;
        }

        //set hour word
        setWordBuiltin(11+afternoonT, color);

        //set minute word
        if(timeRange)
                setWordBuiltin(timeRange, color);

        //To-Do: set minute increments

        //To-Do: set filler words
}
*/
