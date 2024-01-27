#include "ClockManager.h"

#define UPDATE_ALARM_TIME 1000

RTC_DS3231 ClockManager::rtc;

uint32_t ClockManager::nextUpdateAlarm = 0;

DateTime ClockManager::deviceRunAt;
DateTime ClockManager::mainAlarm;
DateTime ClockManager::supportAlarm;

void ClockManager::init() {
    if (!rtc.begin()) return;

    deviceRunAt = rtc.now();

    mainAlarm = getAlarm1(deviceRunAt);
    supportAlarm = getAlarm2(mainAlarm);

    rtc.setAlarm2(mainAlarm, Ds3231Alarm2Mode::DS3231_A2_Date);
}

void ClockManager::tick() {
    if (millis() - nextUpdateAlarm > UPDATE_ALARM_TIME) {
        nextUpdateAlarm = millis();

        rtc.setAlarm1(rtc.now(), Ds3231Alarm1Mode::DS3231_A1_Date);
    }
}

DateTime ClockManager::getAlarm1(const DateTime &now) {
    DateTime timeAlarm1 = rtc.getAlarm1();

    DateTime modTime =
            timeAlarm1.day() > now.day() ?
            now -
            TimeSpan(getNumberOfDays(now.month(), now.year()), 0, 0, 0) :
            now;
    return {modTime.year(), modTime.month(), timeAlarm1.day(),
            timeAlarm1.hour(), timeAlarm1.minute(), timeAlarm1.second()};
}

DateTime ClockManager::getAlarm2(const DateTime &alarm1) {
    DateTime timeAlarm2 = rtc.getAlarm2();

    DateTime modTime =
            timeAlarm2.day() > alarm1.day() ?
            alarm1 -
            TimeSpan(getNumberOfDays(alarm1.month(), alarm1.year()), 0, 0, 0) :
            alarm1;
    return {modTime.year(), modTime.month(), timeAlarm2.day(),
            timeAlarm2.hour(), timeAlarm2.minute(), alarm1.second()};
}

uint8_t ClockManager::getNumberOfDays(uint8_t month, uint16_t year) {
    // Array to store number of days in each month
    static const uint8_t daysInMonth[12] PROGMEM =
            {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Check for leap year
    if (month == 2 && ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))) {
        return 29;
    }

    // Return number of days in the given month
    return pgm_read_byte(&daysInMonth[month - 1]);
}
