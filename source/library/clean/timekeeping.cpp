#include "timekeeping.h"

clockLib::clockLib(){
#if REAL_RTC
        #ifdef INTERRUPT_PIN // If using the SQW pin as an interrupt
        pinMode(INTERRUPT_PIN, INPUT_PULLUP);
        #endif
        rtc.begin(DS13074_CS_PIN);
        //rtc.autoTime();
        rtc.setTime(0, 39, 13, 2, 31, 10, 16);
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
