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
Adafruit_DotStar strip = Adafruit_DotStar(
  NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);
// The last parameter is optional -- this is the color data order of the
// DotStar strip, which has changed over time in different production runs.
// Your code just uses R,G,B colors, the library then reassigns as needed.
// Default is DOTSTAR_BRG, so change this if you have an earlier strip.

// Hardware SPI is a little faster, but must be wired to specific pins
// (Arduino Uno = pin 11 for data, 13 for clock, other boards are different).
//Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DOTSTAR_BRG);

void setup() {

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif

  strip.begin(); // Initialize pins for output
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

void loop() {

  //color = Color(r, g, b); //Convert separate uint8_t r, g, and b into single uint32_t
  color = ((uint32_t)r << 16) | ((uint32_t)g << 8) | b; //Taken from Adafruit_DotStay.h
  
  for(int i = NUMPIXELS - 1; i > 0 ; i--){ 
    strip.setPixelColor(i, list[i-1]); //Changes LED color to color of previous LED
    list[i] = list[i - 1]; //Changes LED color in list to color of previous LED
  }
  strip.setPixelColor(0, color); //Changes first LED to new color
  list[0] = color; //Stores new color to first position of LED list
  strip.show();
  delay(10);

  //Logic to loop through colors
  if(r == 255 && b == 0 && g < 255){
    g++;
  }else if(g == 255 && b == 0 && r > 0){
    r--;
  }else if(r == 0 && g == 255 && b < 255){
    b++;
  }else if(b == 255 && r == 0 && g > 0){
    g--;
  }else if(g == 0 && b == 255 && r < 255){
    r++;
  }else if(r == 255 && g == 0 && b > 0){
    b--;
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
