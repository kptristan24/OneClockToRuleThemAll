#include "timekeeping.h"

clockLib::clockLib(){
        #ifdef INTERRUPT_PIN // If using the SQW pin as an interrupt
        pinMode(INTERRUPT_PIN, INPUT_PULLUP);
        #endif
        rtc.begin(DS13074_CS_PIN);
        rtc.autoTime();
        //rtc.setTime(0, 39, 13, 2, 31, 10, 16);
        rtc.update();
        rtc.enableAlarmInterrupt();
}

//DEPRICATED: use rtc directly
uint32_t clockLib::curHour(){
#if REAL_RTC
        return (uint32_t)rtc.hour();
#else
        return (uint32_t)hour();
#endif
}

//DEPRICATED: use rtc directly
uint32_t clockLib::curMinute(){
#if REAL_RTC
        return (uint32_t)rtc.minute();
#else
        return (uint32_t)minute();
#endif
}

//DEPRICATED: use rtc directly
uint32_t clockLib::curSecond(){
#if REAL_RTC
        return (uint32_t)rtc.second();
#else
        return (uint32_t)second();
#endif
}

bool clockLib::checkAlarms(){
        if(!rtc.alarm1()){
                return false;
        }
        
        timeS currentTime(curMinute(), curHour());
        
        //To-Do: write state that displays that an alarm has gone off
        //newState = new alarmState(currentTime);
        //signal = 1;
        
        __setNextAlarm(currentTime);

        return true;
}

//To-Do: change to insert before correct element, which will remove the need for a full sort
void clockLib::addAlarm(const timeS &newAlarm){
        for(auto t : alarms){
                if(equals(*t, newAlarm)){
                        Serial.print("tried to set alarm at time of existing alarm");
                        return;
                }
        }
        
        alarms.pushback(newAlarm);
        __sortAlarms();
        __setNextAlarm();
}

bool clockLib::removeAlarm(const int &position){
        if(position < alarms.size()){
                alarms.erase(alarms.at(position))
                __setNextAlarm();
                return true;
        }

        return false;
}

bool clockLib::removeAlarm(const timeS &alarmTime){
        for(auto t : alarms){
                if(equal(*t, alarmTime)){
                        alarms.erase(t);
                        __setNextAlarm();
                        return true;
                }
        }
        
        return false;
}

//Double check the implementaiton of trigger alarm next day

void clockLib::__setNextAlarm(const int &position){
        if(alarms.size() == 1){
                uint8_t day = rtc.getDay() + 1;
                if(day > 7)
                        day = 1;
                rtc.setAlarm1(255, alarms[0].m, alarms[0].h, day, true);
                return;
        }
        
        timeS currentTime(curMinute(), curHour());
        
        //found an alarm later in the day to set
        for(auto t : alarms){
                if(*t > currentTime){
                        rtc.setAlarm(255, (*it).m, (*it).h);
                        return;
                }
        }
        
        //otherwise set first alarm for tomorrow
        std::vector<timeS>::iterator it = alarms.begin();
        rtc.setAlarm1(255, (*it).m, (*it).h, day, true);
}

void clockLib::__sortAlarms(){
        if(alarms.size() < 2){
                return;
        }
        
        std::sort(alarms.begin(), alarms.end(), compareTimes);
}

bool compareTimes(const timeS &first, const timeS &second){
        return (first.hour < second.hour)
            || ((first.hour == second.hour) && (first.minute < second.minute));
}