#include "timekeeping.h"

clockLib::clockLib(){
#if REAL_RTC
        #ifdef INTERRUPT_PIN // If using the SQW pin as an interrupt
        pinMode(INTERRUPT_PIN, INPUT_PULLUP);
        #endif
        rtc.begin(DS13074_CS_PIN);
        rtc.autoTime();
        //rtc.setTime(0, 39, 13, 2, 31, 10, 16);
        rtc.update();
        rtc.enableAlarmInterrupt();
#else
        setTime(0, 0, 0, 12, 2, 2017);
#endif
}

uint32_t clockLib::curHour(){
#if REAL_RTC
        return (uint32_t)rtc.hour();
#else
        return (uint32_t)hour();
#endif
}

uint32_t clockLib::curMinute(){
#if REAL_RTC
        return (uint32_t)rtc.minute();
#else
        return (uint32_t)minute();
#endif
}
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

void clockLib::addAlarm(const timeS &newAlarm){
        for(auto t : alarms){
                if(equals(*t, newAlarm)){
                        Serial.print("tried to set alarm at time of existing alarm");
                        return;
                }
        }
        
        alarms.pushback(newAlarm);
        if(alarms.size() == 1){
                rtc.setAlarm1(255, newAlarm.m, newAlarm.h);
        }
}

void clockLib::removeAlarm(const int &position){
        alarms.erase(alarms.at(position));
}

//Double check the implementaiton of trigger alarm next day
/*
void clockLib::__setNextAlarm(const int &position){
        if(alarms.size() == 1){
                uint8_t day = rtc.getDay() + 1;
                if(day > 7)
                        day = 1;
                rtc.setAlarm1(255, alarms[0].m, alarms[0].h, day, true);
                return;
        }
        
        std::vector<timeS>::iterator it = alarms.at(position);
        
        for(auto t : alarms){
                if(*t > *it){
                        it = t;
                }
        }
        
        if(*it > alarms.at(position)){
                rtc.setAlarm(255, (*it).m, (*it).h);
        }
        else{
                it = alarms.at(0);
                for(auto t : alarms){
                        if(*t < *it){
                                it = t;
                        }
                }
                
                uint8_t day = rtc.getDay() + 1;
                if(day > 7)
                        day = 1;
                rtc.setAlarm1(255, (*it).m, (*it).h, day, true);
        }
}
*/