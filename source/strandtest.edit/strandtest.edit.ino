// Simple strand test for Adafruit Dot Star RGB LED strip.
// This is a basic diagnostic tool, NOT a graphics demo...helps confirm
// correct wiring and tests each pixel's ability to display red, green
// and blue and to forward data down the line.  By limiting the number
// and color of LEDs, it's reasonably safe to power a couple meters off
// the Arduino's 5V pin.  DON'T try that with other code!

#include <Adafruit_DotStar.h>
// Because conditional #includes don't work w/Arduino sketches...
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
//#include <avr/power.h> // ENABLE THIS LINE FOR GEMMA OR TRINKET

#define NUMPIXELS 12 // Number of LEDs in strip

// Here's how to control the LEDs from any two pins:
#define DATAPIN    12
#define CLOCKPIN   13
#define RTC        0
Adafruit_DotStar strip = Adafruit_DotStar(
  NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);
// The last parameter is optional -- this is the color data order of the
// DotStar strip, which has changed over time in different production runs.
// Your code just uses R,G,B colors, the library then reassigns as needed.
// Default is DOTSTAR_BRG, so change this if you have an earlier strip.

// Hardware SPI is a little faster, but must be wired to specific pins
// (Arduino Uno = pin 11 for data, 13 for clock, other boards are different).
//Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DOTSTAR_BRG);
uint8_t mode;
uint8_t curr_pixel;
uint32_t brightness;
uint8_t binaryMonth;
uint8_t binaryDay;
uint8_t day;
uint8_t month;
uint32_t year;

void messWithLEDS();

void setup() {

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif
  curr_pixel = 0;
  mode = 5;
  brightness = 0;
  if(RTC){
    //read date + time
    //set date + time
  }
  else{
    day = 17;
    month = 6;
    year = 2017;
  }
  Serial.begin(9600);
  strip.begin(); // Initialize pins for output
  strip.setBrightness(255);
  strip.show();  // Turn all LEDs off ASAP
}

// Runs 10 LEDs at a time along strip, cycling through red, green and blue.
// This requires about 200 mA for all the 'on' pixels + 1 mA per 'off' pixel.

int      head  = 0, tail = NUMPIXELS; // Index of first 'on' and 'off' pixels
uint32_t color = 0x000000;
uint8_t r = 0xFF; 
uint8_t g = 0x00; 
uint8_t b = 0x00;
uint32_t list[NUMPIXELS];

void loop(){  
  //handleInput();
  switch(mode){
  case 0: //timeDisplayWords();
          break;
  case 1: //timeDisplayTicker();
          break;
  case 2: //dateTicker();
          break;
  case 3: //alarmTrigger();
          break;
  case 4: messWithLEDS();
          break;
  case 5: hackyDate();
          break;
  }
}


void dateToBinary(){
  int c;
  binaryDay = 0;
  binaryMonth = 0;
  for (c = 4; c >= 0; c--)
     binaryMonth += (month >> c) * pow(10, c);

  for (c = 5; c >= 0; c--)
     binaryDay += (day >> c) * pow(10, c);
  
  Serial.print("Day:");
  Serial.print(binaryDay, BIN);
  Serial.print(" Month:");
  Serial.print(binaryMonth, BIN);
  Serial.println();
  
}

void hackyDate(){
  strip.clear();
  dateToBinary();
  switch(curr_pixel){
  case 0: if(binaryMonth & 00001000)
            strip.setPixelColor(0, 0xFF);
          break;
  case 1: if(binaryMonth & 00000100)
            strip.setPixelColor(1, 0xFF);
          break;
  case 2: if(binaryMonth & 00000010)
            strip.setPixelColor(2, 0xFF);
          break;
  case 3: if(binaryMonth & 00000001)
            strip.setPixelColor(3, 0xFF);
          break;
  case 4:
          break;
  case 5:
          break;
  case 6:
          break;
  case 7: if(binaryDay & 00010000)
            strip.setPixelColor(7, 0xFF);
          break;
  case 8: if(binaryDay & 00001000)
            strip.setPixelColor(8, 0xFF);
          break;
  case 9: if(binaryDay & 00000100)
            strip.setPixelColor(9, 0xFF);
          break;
  case 10:if(binaryDay & 00001000)
            strip.setPixelColor(10, 0xFF);
          break;
  case 11: if(binaryDay & 00000001)
            strip.setPixelColor(11, 0xFF);
          break;
  }
  strip.show();
  //delay(5);

  curr_pixel++;
  curr_pixel % 12;
}

void messWithLEDS(){
  strip.clear();
  //color = Color(r, g, b); //Convert separate uint8_t r, g, and b into single uint32_t
  color = ((uint32_t)r << 16) | ((uint32_t)g << 8) | b; //Taken from Adafruit_DotStay.h
  /*
  for(int i = NUMPIXELS - 1; i > 0 ; i--){ 
    strip.setPixelColor(i, list[i-1]); //Changes LED color to color of previous LED
    list[i] = list[i - 1]; //Changes LED color in list to color of previous LED
  }
  strip.setPixelColor(0, color); //Changes first LED to new color
  list[0] = color; //Stores new color to first position of LED list
  */
  strip.setPixelColor(curr_pixel, color);
  strip.setBrightness(brightness / 16);
  strip.show();
  //delay(1);

  //Logic to loop through colors
  if(r == 255 && b == 0 && g < 255){
    g += 1;
  }else if(g == 255 && b == 0 && r > 0){
    r -= 1;
  }else if(r == 0 && g == 255 && b < 255){
    b += 1;
  }else if(b == 255 && r == 0 && g > 0){
    g -= 1;
  }else if(g == 0 && b == 255 && r < 255){
    r += 1;
  }else if(r == 255 && g == 0 && b > 0){
    b -= 1;
  }

  brightness++;
  brightness = brightness % 4095;

  curr_pixel++;
  if(curr_pixel >= NUMPIXELS){
    curr_pixel = 0;
  }
}
/*
void loop() {
  strip.clear();
  //color = Color(r, g, b); //Convert separate uint8_t r, g, and b into single uint32_t
  color = ((uint32_t)r << 16) | ((uint32_t)g << 8) | b; //Taken from Adafruit_DotStay.h
  
  for(int i = NUMPIXELS - 1; i > 0 ; i--){ 
    strip.setPixelColor(i, list[i-1]); //Changes LED color to color of previous LED
    list[i] = list[i - 1]; //Changes LED color in list to color of previous LED
  }
  strip.setPixelColor(0, color); //Changes first LED to new color
  list[0] = color; //Stores new color to first position of LED list
  
  strip.setPixelColor(curr_pixel, color);
  strip.setBrightness(brightness / 16);
  strip.show();
  //delay(1);

  //Logic to loop through colors
  if(r == 255 && b == 0 && g < 255){
    g += 1;
  }else if(g == 255 && b == 0 && r > 0){
    r -= 1;
  }else if(r == 0 && g == 255 && b < 255){
    b += 1;
  }else if(b == 255 && r == 0 && g > 0){
    g -= 1;
  }else if(g == 0 && b == 255 && r < 255){
    r += 1;
  }else if(r == 255 && g == 0 && b > 0){
    b -= 1;
  }

  brightness++;
  brightness = brightness % 4095;

  curr_pixel++;
  if(curr_pixel >= NUMPIXELS){
    curr_pixel = 0;
  }
  //Messing around with print statements. I need some tips on this section
  
  Serial.print("r = ");
  Serial.print(r, DEC);
  Serial.print(", g = ");
  Serial.print(g, DEC);
  Serial.print(", b = ");
  Serial.print(b, DEC);
  Serial.println();
  
}
*/
