#ifndef POWERWRITER_CLOCKMANAGER_H
#define POWERWRITER_CLOCKMANAGER_H

#include "RTClib.h"

class ClockManager {
public:
    static RTC_DS3231 rtc;

    static DateTime deviceRunAt;
    static DateTime mainAlarm;
    static DateTime supportAlarm;


    static void init();

    static void tick();

    static uint8_t getNumberOfDays(uint8_t month, uint16_t year);

private:
    static uint32_t nextUpdateAlarm;

    static DateTime getAlarm1(const DateTime &now);

    static DateTime getAlarm2(const DateTime &alarm1);
};


#endif //POWERWRITER_CLOCKMANAGER_H
