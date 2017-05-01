# OneClockToRuleThemAll
Our Senior Capstone Project to make a Word Clock on a budget. Weekly updates can be found on the wiki!

The project source code can be found in the sub directory [source/library/clean](source/library/clean)

## Usage Instructions

1. Aquire Necessary Hardware:
  * Arduino Uno (Other ATMEGA328 based boards may work but will probably take tinkering)
  * DS3234 RTC Module
  * Programmible LED strip supported by DOTSTAR library
  * Buttons
  
2. Assemble Hardware:
  * Connect the arrangement of LED strips, the RTC, and at least 3 buttons
  * There are many possible arrangements with the avaliable pins but where you connect things can be set in software.

3. Setup Software:
  * Download and install the latest version of the Arduino IDE (as of this writing: v1.8.2)
  * Some operating systems may require adjusting permissions of the tty interface

4. Setup Code:
  * Download a copy of the subfolder: source/library/clean
  * Download a copy of the libraries folder: libraries
  * Load the source code in Arduino IDE and include the RTC library and the FastLED library.
  * Edit the #define statements at the top of buttons.h, timekeeping.h, and display.h to set the pins where hardware is connected.
  * Plug the board in and flash the software
  
