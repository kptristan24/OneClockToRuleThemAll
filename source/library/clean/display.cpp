#include "display.h"

display::display(){
        FastLED.addLeds<CHIPSET, DATA_PIN, CLOCK_PIN>(LEDstrip, NUM_LEDS);
        
        array = new CRGB*[NUM_LEDS/ROW_LENGTH];
        for(int i = 0; i < NUM_LEDS/ROW_LENGTH; i++){
                array[i] = LEDstrip[ROW_LENGTH * i];
        }
        
        botText = 0;
        topText = 0;
        
        words = new uint8_t*[NUM_WORDS + NUM_EXTRA];
        setupWords();
        setupExtraWords();
}

void display::setupWords(){
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
}

void display::setupExtraWords(){
        if(extra[0])
                letters[23] = amE;
        if(extra[1])
                letters[24] = pmE;
        if(extra[2])
                letters[25] = minOne;
        if(extra[3])
                letters[26] = minTwo;
        if(extra[4])
                letters[27] = minThree;
        if(extra[5])
                letters[28] = minFour;
}

void display::updateDisplay(){
#if !HEADLESS

        FastLED.show();
#else
        debugUpdateDisplay();
#endif
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
        return array;
}

void display::updateFromArray(int **numArray, CRGB &color, bool refresh){
        FastLED.clear();
        for(int i = 0; i < NUM_LEDS/ROW_LENGTH; i++){
                for(int j = 0; j < ROW_LENGTH; j++){
                        if(numArray[i][j])
                                array[i][j] = color;
                }
        }
        
        if(refresh)
                updateDisplay();
}

void display::setPixel(const int &x, const int &y, CRGB &color){
        if((x < ROW_LENGTH) && (y < NUM_LEDS/ROW_LENGTH))
                array[y][x] = color;
}

void display::setPixel(const int &position, CRGB &color){
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

/*
 * Outer loop is number of letters to copy
 * Inner loop is each row of the letter
 * Second inner loop is each column of each letter
 *
 */
void display::updateMessage(const char *message, const int &strip){
        const uint8_t vertOffset = strip * ((NUM_LEDS/ROW_LENGTH)/2);
        
        
}