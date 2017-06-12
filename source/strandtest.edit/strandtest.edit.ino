
// Because conditional #includes don't work w/Arduino sketches...
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
#include <SparkFunDS3234RTC.h>
//#include <avr/power.h> // ENABLE THIS LINE FOR GEMMA OR TRINKET
#include <Adafruit_DotStar.h>
#include <TimeLib.h>
#define NUMPIXELS 14 // Number of LEDs in strip
#define DS13074_CS_PIN 10 // DeadOn RTC Chip-select pin
#define INTERRUPT_PIN 2 // DeadOn RTC SQW/interrupt pin (optional)

// Here's how to control the LEDs from any two pins:
#define DATAPIN    4 //RED WIRE
#define CLOCKPIN   5 //GREEN WIRE
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
//uint8_t day;
//uint8_t month;
//uint32_t year;

void messWithLEDS();

void setup() {
   Serial.begin(9600);

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif
  curr_pixel = 0;
  mode = 4;
  //brightness = 0;
  if(RTC){
    #ifdef INTERRUPT_PIN // If using the SQW pin as an interrupt
      pinMode(INTERRUPT_PIN, INPUT_PULLUP);
    #endif
    rtc.begin(DS13074_CS_PIN);
    //rtc.autoTime();
    rtc.setTime(0, 39, 13, 2, 31, 10, 16);
    rtc.update();
    rtc.enableAlarmInterrupt();
  }
  else{
    //day = 17;
    //month = 6;
    //year = 2017;
    setTime(0, 0, 0, 12, 2, 2017);
  }
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
  rtc.update();
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
  case 4: rainbowPuke();
          break;
  case 5: hackyMinSec();
          break;
  }
}

void hackyMinSec(){
  strip.clear();
  strip.setBrightness(255);
  uint32_t colorMin = 0xFF0000; //Green
  uint32_t colorSec = 0x00FF00; //Red
  int mins;
  int secs;
  if(RTC){
    mins = rtc.hour();
    secs = rtc.minute(); 
  }
  else{
    mins = minute();
    secs = second(); 
  }
  int counter = 5;
  int i = 32;

  Serial.print("Min: ");
  Serial.print(mins);
  Serial.print(" Sec: ");
  Serial.print(secs);
  Serial.println();
  
  
  while(counter >= 0){
    if(mins - i >= 0){
      strip.setPixelColor(counter+6, colorMin);
      strip.show();
      mins = mins - i;   
    } else {
      strip.setPixelColor(counter+6, 0x000000);
      strip.show();
    } if(secs - i >= 0){
      strip.setPixelColor(counter, colorSec);
      strip.show();
      secs = secs - i;
    } else {
      strip.setPixelColor(counter, 0x000000);
      strip.show();
    }
    i = i / 2;
    counter--;
  } 
}

void rainbowPuke() {
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
  
}
