#ifndef BUTTONS_H
#define BUTTONS_H

//how quickly to accept a new input from a button
#define WAIT_TIME       30 //30 cycles of the main loop
#define NUM_BUTTONS     3
const int BUTTON_PINS[NUM_BUTTONS] = {4, 7, 9};

class Buttons{
public:
        Buttons(){
                for(int i = 0; i < NUM_BUTTONS; i++){
                        buttonStatus[i] = 0;
                        buttonChecked[i] = 0;
                        pinMode(BUTTON_PINS[i], INPUT);
                }
        }
        void update(){
                //check if a button has been pressed
                for(int i = 0; i < NUM_BUTTONS; i++){
                        if(!buttonStatus[i]){
                                if(digitalRead(BUTTON_PINS[i]) == HIGH)
                                        buttonStatus[i] = WAIT_TIME;
                        }
                }

                //update counters
                for(int i = 0; i < NUM_BUTTONS; i++)
                        if(buttonStatus[i]){
                                buttonStatus[i]--;
                                if(!buttonStatus[i])
                                        buttonChecked[i] = 0;
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
        uint8_t buttonStatus[NUM_BUTTONS];
        uint8_t buttonChecked[NUM_BUTTONS];
};

#endif
