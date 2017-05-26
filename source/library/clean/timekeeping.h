#ifndef TIMEKEEPING_H
#define TIMEKEEPING_H

#include <SparkFunDS3234RTC.h>
//#include <TimeLib.h>
#include "stateStack.h"
#include "alarmState.h"
#include "timeS.h"
#include "avec.h"

//hardware setup
#define CS_PIN         10       // DeadOn RTC Chip-select pin
#define INTERRUPT_PIN  2

extern state *newState;
extern uint8_t signal;

class clockLib{
public:
        clockLib();

        void update();
        const timeS getCurrentTime() const;

        //get time functions DEPRICATED!!! DO NOT USE. USE DIRECT RTC FUNCTIONS
        uint8_t curMinute() const;
        uint8_t curHour() const;
        uint8_t curSecond() const;


        //Alarm functions
        bool checkAlarms();
        void addAlarm(const timeS &); //attempts to add alarm, won't add at duplicate time

        //remove an alarm at a position or a specific time, returns true on success
        bool removeAlarm(const uint8_t &);
        bool removeAlarm(const timeS &);

        uint8_t getAlarmTime(uint8_t, timeS &) const;
        //To-Do functions

private:
        //Update the rtc hardware alarm to match the next upcoming alarm
        aVec alarms;
};

#endif
