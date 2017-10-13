#ifndef BUTTONS_H
#define BUTTONS_H

//how quickly to accept a new input from a button
#define WAIT_TIME       250 //number of milliseconds
#define NUM_BUTTONS     3
const uint8_t BUTTON_PINS[NUM_BUTTONS] = {6, 7, 9};

class Buttons{
public:
        Buttons(){
                for(int i = 0; i < NUM_BUTTONS; i++){
                        buttonStatus[i] = 0;
                        buttonChecked[i] = 0;
                        pinMode(BUTTON_PINS[i], INPUT_PULLUP);
                }
        }
        void update(){
                //check if a button has been pressed
                for(int i = 0; i < NUM_BUTTONS; i++){
                        if(!buttonStatus[i] && digitalRead(BUTTON_PINS[i]) == HIGH){
                                buttonStatus[i] = millis();
                        }
                }

                //update counters
                for(int i = 0; i < NUM_BUTTONS; i++)
                        if(buttonStatus[i] && buttonChecked[i]){
                                unsigned long temp = millis() - buttonStatus[i];
                                if(temp > WAIT_TIME){
                                        buttonChecked[i] = 0;
                                        buttonStatus[i] = 0;
                                }
                        }
        }
        const int getInput(){
                for(int i = 0; i < NUM_BUTTONS; i++){
                        if(buttonStatus[i] && !buttonChecked[i]){
                                buttonChecked[i] = 1;
                                return i;
                        }
                }

                return -1;
        }
private:
        unsigned long buttonStatus[NUM_BUTTONS];
        uint8_t buttonChecked[NUM_BUTTONS];
};

#endif
