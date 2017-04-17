#ifndef TIMEKEEPING_H
#define TIMEKEEPING_H

#include <SparkFunDS3234RTC.h>
#include <TimeLib.h>
#include "stateStack.h"
#include "alarmState.h"

//hardware setup
#define CS_PIN         10       // DeadOn RTC Chip-select pin
#define INTERRUPT_PIN  2

extern state *newState;
extern uint8_t signal;

struct timeS{
        timeS(const int &m, const int &h){
                minute = m;
                hour = h;
        }
        bool equals(const timeS &lH, const timeS &rH) const {
                return (rH.minute == lH.minute)
                    && (rH.hour == lH.hour);
        }
        bool operator>(const timeS &rH) const {
                return (hour > rH.hour)
                    || ((hour == rH.hour) && (minute > rH.minute));
        }
        bool operator<(const timeS &rH) const {
                return (hour < rH.hour)
                    || ((hour == rH.hour) && (minute < rH.minute));
        }

        uint8_t minute;
        uint8_t hour;
};

class clockLib{
public:
        clockLib();

        //get time functions DEPRICATED!!! DO NOT USE. USE DIRECT RTC FUNCTIONS
        uint32_t curMinute();
        uint32_t curHour();
        uint32_t curSecond();

        /*
        //Alarm functions
        bool checkAlarms();
        void addAlarm(const timeS &); //attempts to add alarm, won't add at duplicate time

        //remove an alarm at a position or a specific time, returns true on success
        bool removeAlarm(const int &);
        bool removeAlarm(const timeS &);
        */
        //To-Do functions

private:
        //Update the rtc hardware alarm to match the next upcoming alarm
        /*
        void __setNextAlarm(const int &);
        void __sortAlarms();
        void __compareTimes(const timeS &first, const timeS &second);

        vector<timeS> alarms;
        */
};

#endif
