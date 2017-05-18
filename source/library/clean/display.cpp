#include "display.h"

display::display(){
        FastLED.addLeds<CHIPSET, DATA_PIN, CLOCK_PIN, BGR>(LEDstrip, NUM_LEDS);

        clearScrollingText(2);

        words = new uint8_t const *[NUM_WORDS + NUM_EXTRA];
        setupWords();
        setupExtraWords();

        FastLED.setBrightness(255);
        FastLED.clear();
        FastLED.show();
}

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
        FastLED.show();
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
                Serial.print("\n");
        }
}

void display::updateFromArray(int **numArray, CRGB &color, bool refresh){
        FastLED.clear();
        for(int i = 0; i < NUM_LEDS/ROW_LENGTH; i++){
                for(int j = 0; j < ROW_LENGTH; j++){
                        if(numArray[i][j])
                                __arrayAccessFunction(i, j, color);
                }
        }

        if(refresh)
                update();
}

void display::setPixel(int x, int y, const CRGB &color){
        if((x < ROW_LENGTH) && (y < NUM_LEDS/ROW_LENGTH))
                __arrayAccessFunction(y, x, color);
}

void display::setPixel(int x, const CRGB &color){
        if(x < NUM_LEDS)
                LEDstrip[x] = CRGB::Red;

}

void display::clearScrollingText(int strip){
        if(strip == 0 || strip == 2){ //clear top strip
                text[0] = 0;
                offset[0] = 0;
                length[0] = 0;
                currentChar[0] = 0;
        }

        if(strip == 1 || strip == 2){ //clear bot strip
                text[1] = 0;
                offset[1] = 0;
                length[1] = 0;
                currentChar[1] = 0;
        }

        if(strip == 2)
                frameCounter = 0;
}

void display::drawChar(char c, int horizOffset, int row, const CRGB &color){
        int vertOffset = (NUM_LEDS/ROW_LENGTH)/2 * row;
        uint8_t charData[3];
        __bufferChar(charData,(((int)c - 32) * 3) + 6);
        int charPosition = (((int)c - 32) * 3) + 6;

        for(int j = horizOffset; j < horizOffset + 3; j++){
                if(j < 0 || j >= ROW_LENGTH)
                        continue;
                for(int k = 0; k < 5; k++)
                        //if(CHECKBIT(Wendy3x5[charPosition + (j - horizOffset)], k))
                        if(CHECKBIT(charData[j], k))
                                __arrayAccessFunction(vertOffset + k, j, color);
        }
}

//To-Do: figure out better color control, maybe per character
void display::staticText(const char *m, int row, int length, const CRGB &col1, const CRGB &col2){
        int numChars = length;
        if(numChars > (ROW_LENGTH / 3))
                numChars = ROW_LENGTH / 3;

        for(int i = 0; i < numChars; i++){
                drawChar(m[i], i*3, row, col1);
        }
}

void display::staticText(const char *m, int row, int length, const CRGB *colors){
        int numChars = length;
        if(numChars > (ROW_LENGTH / 3))
                numChars = ROW_LENGTH / 3;

        for(int i = 0; i < numChars; i++){
                drawChar(m[i], i*3, row, colors[i]);
        }
}

void display::scrollingText(const char *m, int row, const CRGB &col1, const CRGB &col2){
        Serial.print("Scrolling text called: \n");
        if(!text[row])
                length[row] = strlen(m);

        int tempCurrentChar = currentChar[row];
        __updateTextVariables(row);

        for(int i = 0; i < 5; i++){
                if(tempCurrentChar >= length[row])
                        tempCurrentChar = 0;

                if(CHECKBIT(tempCurrentChar, 1)) //odd numbered character in m
                        drawChar(m[tempCurrentChar], -offset[row] + (3 * i), row, col1);
                else //even numbered character in m
                        drawChar(m[tempCurrentChar], -offset[row] + (3 * i), row, col2);

                tempCurrentChar++;
        }
}

void display::__updateTextVariables(uint8_t row){
        if(frameCounter >= TEXT_SPEED){
                frameCounter = 0;
                offset[row]++;
                if(offset[row] == 3){
                        offset[row] = 0;
                        currentChar[row]++;
                        if(currentChar[row] == length[row])
                                currentChar[row] = 0;
                }
        }

        frameCounter++;
}

void display::__bufferChar(uint8_t *buffer, int whichChar){
        buffer[0] = pgm_read_byte_near(Wendy3x5[whichChar]);
        buffer[1] = pgm_read_byte_near(Wendy3x5[whichChar + 1]);
        buffer[2] = pgm_read_byte_near(Wendy3x5[whichChar + 2]);
}

void display::__arrayAccessFunction(int y, int x, const CRGB &color){
        //currently no idiot checking for if x or y are in range
        if(ALT_DIR){
                int basePos;
                basePos = y * ROW_LENGTH;
                if(y & 1)
                        LEDstrip[basePos + (ROW_LENGTH - x - 1)] = color;
                else
                        LEDstrip[basePos + x] = color;
        }
        else{
                LEDstrip[(y * ROW_LENGTH) + x] = color;
        }
}

void display::setWordBuiltin(int w, const CRGB &color){
        if(w >= (NUM_WORDS + NUM_EXTRA)){
                return;
        }

        int constCoord;

        if(words[w][4]){
                constCoord = words[w][0];
                for(int y = words[w][1]; y < words[w][3]; y++){
                        __arrayAccessFunction(y, constCoord, color);
                }
        }
        else{
                constCoord = words[w][1];
                for(int x = words[w][0]; x < words[w][2]; x++){
                        __arrayAccessFunction(constCoord, x, color);
                }
        }
}

void display::setFromTime(int h, int m, const CRGB &color){
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

CRGB display::getColorFromTime(const timeS &){

}

void display::setFromTime(const timeS &t, const CRGB &color){
        int afternoonT = t.hour;
        int timeRange = t.minute / 5;

        //set am or pm if they exist
        if(t.hour > 11 && extra[1])
                setWordBuiltin(24, color);
        else if(extra[0]){
                setWordBuiltin(23, color);
                afternoonT = t.hour - 12;
        }

        //set hour word
        setWordBuiltin(11+afternoonT, color);

        //set minute word
        if(timeRange)
                setWordBuiltin(timeRange, color);

        //To-Do: set minute increments

        //To-Do: set filler words
}
