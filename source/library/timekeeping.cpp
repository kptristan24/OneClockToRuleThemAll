#include "timekeeping.h"

clockLib::clockLib(){
#ifdef INTERRUPT_PIN // If using the SQW pin as an interrupt
        pinMode(INTERRUPT_PIN, INPUT_PULLUP);
#endif
        rtc.begin(CS_PIN);
        rtc.update();
        rtc.enableAlarmInterrupt();
}

void clockLib::update(){
        rtc.update();
}

const timeS clockLib::getCurrentTime() const{
        return timeS(rtc.second(), rtc.minute(), rtc.hour());
}

//DEPRICATED: use rtc directly
uint8_t clockLib::curHour() const{
        return rtc.hour();
}

//DEPRICATED: use rtc directly
uint8_t clockLib::curMinute() const{
        return rtc.minute();
}

//DEPRICATED: use rtc directly
uint8_t clockLib::curSecond() const{
        return rtc.second();
}

bool clockLib::checkAlarms(){
        const timeS currentTime = getCurrentTime();
        for(uint8_t i = 0; i < alarms.size(); i++)
                if(alarms[i] == currentTime)
                        return true;

        return false;
}

//To-Do: change to insert before correct element, which will remove the need for a full sort
void clockLib::addAlarm(const timeS &newAlarm){
        for(uint8_t i = 0; i < alarms.size(); i++)
                if(alarms[i] == newAlarm){
                        Serial.print(F("duplicate alarm\n"));
                        return;
                }

        alarms.insert_ordered(newAlarm);
}

bool clockLib::removeAlarm(const uint8_t &position){
        if(position < alarms.size()){
                alarms.erase(position);
                return true;
        }

        return false;
}

bool clockLib::removeAlarm(const timeS &alarmTime){
        for(int i = 0; i < alarms.size(); i++){
                if(alarmTime == alarms[i]){
                        alarms.erase(i);
                        return true;
                }
        }

        return false;
}

//Double check the implementaiton of trigger alarm next day

uint8_t clockLib::getAlarmTime(uint8_t pos, timeS &extTime) const{
        if(pos >= alarms.size() || alarms.size() == 0)
                return 0;

        extTime = alarms[pos];
        return 1;
}
