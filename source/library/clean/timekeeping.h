#ifndef TIMEKEEPING_H
#define TIMEKEEPING_H

#include <SparkFunDS3234RTC.h>
#include <TimeLib.h>

//hardware setup
#define REAL_RTC       0        //set to 1 if using a connected RTC
#define CS_PIN         10       // DeadOn RTC Chip-select pin
#define INTERRUPT_PIN  2

class clockLib{
public:
        clockLib();
        uint32_t curMinute();
        uint32_t curHour();
        uint32_t curSecond();

        //To-do Alarm functions
private:

};

#endif
