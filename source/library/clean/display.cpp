#include "display.h"

display::display(){
        FastLED.addLeds<CHIPSET, DATA_PIN, CLOCK_PIN, BGR>(LEDstrip, NUM_LEDS);

        clearScrollingText(ALL);
        FastLED.setBrightness(5);
        FastLED.clear();
        FastLED.show();
}


int display::getVertSize(){
        return NUM_LEDS / ROW_LENGTH;
}

int display::getHorizSize(){
        return ROW_LENGTH;
}

void display::update(){
        //debugUpdateDisplay();
        FastLED.show();
}

void display::clear(){
        FastLED.clear();
}

void display::debugUpdateDisplay(){
        uint8_t rows;
        uint16_t rowContents;
        rows = NUM_LEDS / ROW_LENGTH;

        Serial.print(F("Display state:\n"));
        for(int i = 0; i < rows; i++){
                rowContents = 0;
                for(int j = 0; j < ROW_LENGTH; j++){
                        if(LEDstrip[j + (i*ROW_LENGTH)])
                                Serial.print("1 ");
                                //rowContents |= 1 << j;
                        else
                                Serial.print("0 ");

                                //rowContents |= 0 << j;
                }
                //Serial.print(rowContents, BIN);
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

void display::setPixel(int y, int x, const CRGB &color){
        if((x < ROW_LENGTH) && (y < NUM_LEDS/ROW_LENGTH))
                __arrayAccessFunction(y, x, color);
}

void display::setPixel(int x, const CRGB &color){
        if(x < NUM_LEDS){
                const int y = x / ROW_LENGTH;
                __arrayAccessFunction(y, (x - y*ROW_LENGTH), color);
        }
}

void display::clearScrollingText(int strip){
        if(strip == TOP || strip == ALL){ //clear top strip
                text[0] = 0;
                offset[0] = 0;
                length[0] = 0;
                currentChar[0] = 0;
                frameCounter[0] = 0;
        }

        if(strip == BOT || strip == ALL){ //clear bot strip
                text[1] = 0;
                offset[1] = 0;
                length[1] = 0;
                currentChar[1] = 0;
                frameCounter[1] = 0;
        }
}

void display::drawChar(char c, int horizOffset, int row, const CRGB &color){
        int vertOffset = ((NUM_LEDS/ROW_LENGTH) * row)/2;
        uint8_t charData[3];
        __bufferChar(charData,(((int)c - 32) * 3) + 6);
        int charPosition = (((int)c - 32) * 3) + 6;

        for(int j = horizOffset; j < horizOffset + 3; j++){
                if(j < 0 || j >= ROW_LENGTH)
                        continue;
                for(int k = 0; k < 5; k++){
                        if(CHECKBIT(charData[j - horizOffset], k))
                                setPixel(vertOffset + k, j, color);
                }
        }
}

//To-Do: figure out better color control, maybe per character
void display::staticText(const char *m, uint8_t row, int length, const CRGB &col1, const CRGB &col2){
        int numChars = length;
        if(numChars > (ROW_LENGTH / 3))
                numChars = ROW_LENGTH / 3;

        for(int i = 0; i < numChars; i++){
                if(i & 1)
                        drawChar(m[i], i*3, row, col1);
                else
                        drawChar(m[i], i*3, row, col2);
        }
}

void display::staticText(const char *m, uint8_t row, int length, const CRGB *colors){
        int numChars = length;
        if(numChars > (ROW_LENGTH / 3))
                numChars = ROW_LENGTH / 3;

        for(int i = 0; i < numChars; i++){
                drawChar(m[i], i*3, row, colors[i]);
        }
}

void display::staticText(const char *m, uint8_t row, int length, const CRGB &col1,
                const CRGB &col2, const CRGB &col3, const CRGB &col4){
        int numChars = length;
        if(numChars > (ROW_LENGTH / 3))
                numChars = ROW_LENGTH / 3;

        for(int i = 0; i < numChars; i++){
                switch(i){
                case 0: drawChar(m[i], 0, row, col1);
                        break;
                case 1: drawChar(m[i], 3, row, col2);
                        break;
                case 2: drawChar(m[i], 6, row, col3);
                        break;
                case 3: drawChar(m[i], 9, row, col4);
                        break;
                }
        }
}

void display::scrollingText(const char *m, int row, const CRGB &col1, const CRGB &col2){
        if(!text[row]){
                text[row] = 1;
                currentChar[row] = 0;
                frameCounter[row]= 0;
                length[row] = strlen(m);
        }

        int tempCurrentChar = currentChar[row];

        for(int i = 0; i < 5; i++){
                if(tempCurrentChar >= length[row])
                        tempCurrentChar = 0;

                if(tempCurrentChar % 2){ //odd numbered character in m
                        drawChar(m[tempCurrentChar], -offset[row] + (3 * i), row, col1);
                        //Serial.println(m[tempCurrentChar]);
                }
                else //even numbered character in m
                        drawChar(m[tempCurrentChar], -offset[row] + (3 * i), row, col2);
                tempCurrentChar++;
        }

        __updateTextVariables(row);
}

void display::__updateTextVariables(uint8_t row){
        if(frameCounter[row] >= TEXT_SPEED){
                frameCounter[row] = 0;
                offset[row]++;
                if(offset[row] == 3){
                        offset[row] = 0;
                        currentChar[row]++;
                        if(currentChar[row] == length[row])
                                currentChar[row] = 0;
                }
        }

        frameCounter[row]++;
}

void display::__bufferChar(uint8_t *buffer, int whichChar){
        buffer[0] = pgm_read_byte_near(&Wendy3x5[whichChar]);
        buffer[1] = pgm_read_byte_near(&Wendy3x5[whichChar + 1]);
        buffer[2] = pgm_read_byte_near(&Wendy3x5[whichChar + 2]);
}

void display::__arrayAccessFunction(int y, int x, const CRGB &color){
        //currently no idiot checking for if x or y are in range
        if(ALT_DIR){
                int basePos = y * ROW_LENGTH;
                if(y & 1){
                        LEDstrip[basePos + (ROW_LENGTH - x - 1)] = color;
                        //Serial.print(basePos + (ROW_LENGTH - x - 1));
                }
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

        uint8_t buffer[5];
        __bufferWordPos(buffer, w*5);

        if(buffer[4])
                for(uint8_t y = buffer[1]; y <= buffer[3]; y++)
                        __arrayAccessFunction(y, buffer[0], color);
        else
                for(uint8_t x = buffer[0]; x <= buffer[2]; x++)
                        __arrayAccessFunction(buffer[1], x, color);
}

void display::__bufferWordPos(uint8_t *buffer, uint8_t pos){
        buffer[0] = pgm_read_byte_near(&WordLayout[pos]);
        buffer[1] = pgm_read_byte_near(&WordLayout[pos + 1]);
        buffer[2] = pgm_read_byte_near(&WordLayout[pos + 2]);
        buffer[3] = pgm_read_byte_near(&WordLayout[pos + 3]);
        buffer[4] = pgm_read_byte_near(&WordLayout[pos + 4]);
}

void display::setFromTime(uint8_t h, uint8_t m, const CRGB &color){
        uint8_t afternoonT = h; //1
        uint8_t timeRange = m / 5; //3
        //it is
        setWordBuiltin(20, color);
        setWordBuiltin(21, color);
        //set am or pm
        if(h > 11){
                setWordBuiltin(23, color);
                afternoonT = afternoonT - 12;
        }
        else
                setWordBuiltin(22, color);

        //set hour word
        if(timeRange > 6){
                afternoonT++;
                if(afternoonT > 12)
                        afternoonT = afternoonT - 12;
                setWordBuiltin(afternoonT, color);

        }
        else
                setWordBuiltin(afternoonT, color);

        //set minute word
        if(timeRange)
                setMinutePhrase(timeRange, color);

        //set minute increments
        /*
        switch(m - (timeRange * 5)){
        case 4: __arrayAccessFunction(11,11,CRGB::White);
        case 3: __arrayAccessFunction(11,0,CRGB::White);
        case 2: __arrayAccessFunction(11,0,CRGB::White);
        case 1: __arrayAccessFunction(0,0,CRGB::White);
        }
        */
}

void display::setMinutePhrase(uint8_t m, const CRGB &color){
        if(m > 0 && m < 7)
                setWordBuiltin(17, color); //past the hour
        else
                setWordBuiltin(18, color); //till

        switch(m){
        case 1: setWordBuiltin(12, color);
                setWordBuiltin(19, color);
                break;
        case 2: setWordBuiltin(13, color);
                setWordBuiltin(19, color);
                break;
        case 3: setWordBuiltin(14, color);
                break;
        case 4: setWordBuiltin(15, color);
                setWordBuiltin(19, color);
                break;
        case 5: setWordBuiltin(15, color);
                setWordBuiltin(12, color);
                setWordBuiltin(19, color);
                break;
        case 6: setWordBuiltin(16, color);
                break;
        case 7: setWordBuiltin(15, color);
                setWordBuiltin(12, color);
                setWordBuiltin(19, color);
                break;
        case 8: setWordBuiltin(15, color);
                setWordBuiltin(19, color);
                break;
        case 9: setWordBuiltin(14, color);
                break;
        case 10: setWordBuiltin(13, color);
                 setWordBuiltin(19, color);
                 break;
        case 11: setWordBuiltin(12, color);
                 setWordBuiltin(19, color);
                 break;
        }
}

CRGB display::getColorFromTime(const timeS &inputTime){
        //still looking into algorithms
        return CRGB::Red;
}

void display::setFromTime(const timeS &t, const CRGB &color){
        int afternoonT = t.hour;
        int timeRange = t.minute / 5;
        //set am or pm
        if(afternoonT > 11){
                setWordBuiltin(23, color);
                afternoonT = afternoonT - 12;
        }
        else
                setWordBuiltin(24, color);
        //set hour word
        setWordBuiltin(afternoonT, color);
        //set minute word
        if(timeRange)
                setWordBuiltin(timeRange + 12, color);

        //To-Do: set minute increments
        //To-Do: set filler words
}
