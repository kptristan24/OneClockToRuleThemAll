#include "timekeeping.h"

clockLib::clockLib(){
        #ifdef INTERRUPT_PIN // If using the SQW pin as an interrupt
        pinMode(INTERRUPT_PIN, INPUT_PULLUP);
        #endif
        rtc.begin(CS_PIN);
        rtc.autoTime();
        //rtc.setTime(0, 39, 13, 2, 31, 10, 16);
        rtc.update();
        rtc.enableAlarmInterrupt();
}

void clockLib::update(){
        rtc.update();
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

        //To-Do: write state that displays that an alarm has gone off
        //newState = new alarmState(currentTime);
        //signal = 1;

        __setNextAlarm();

        return true;
}

//To-Do: change to insert before correct element, which will remove the need for a full sort
void clockLib::addAlarm(const timeS &newAlarm){
        for(int i = 0; i < alarms.size(); i++){
                if(alarms[i] == newAlarm){
                        Serial.print("tried to set alarm at time of existing alarm");
                        return;
                }
        }

        alarms.insert_ordered(newAlarm);
        __setNextAlarm();
}

bool clockLib::removeAlarm(const int &position){
        if(position < alarms.size()){
                alarms.erase(position);
                __setNextAlarm();
                return true;
        }

        return false;
}

bool clockLib::removeAlarm(const timeS &alarmTime){
        for(int i = 0; i < alarms.size(); i++){
                if(alarmTime == alarms[i]){
                        alarms.erase(i);
                        __setNextAlarm();
                        return true;
                }
        }

        return false;
}

//Double check the implementaiton of trigger alarm next day

void clockLib::__setNextAlarm(){
        if(alarms.size() == 0){ //nothing to set
                return;
        }
        else if(alarms.size() == 1){ //the only alarm, might be tomorrow
                uint8_t day = rtc.getDay() + 1;
                if(day > 7)
                        day = 1;
                rtc.setAlarm1((uint8_t)255, alarms[0].minute, alarms[0].hour, day, true);
                return;
        }

        timeS currentTime(curMinute(), curHour());

        //found an alarm later in the day to set
        for(int i = 0; i < alarms.size(); i++){
                if(alarms[i] > currentTime){
                        rtc.setAlarm1((uint8_t)255, alarms[i].minute, alarms[i].hour);
                        return;
                }
        }

        //otherwise set first alarm for tomorrow
        rtc.setAlarm1((uint8_t)255, alarms[0].minute, alarms[0].hour, (uint8_t)(rtc.getDay() + 1), true);
}
