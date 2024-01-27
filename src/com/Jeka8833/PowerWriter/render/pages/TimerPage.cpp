#include "TimerPage.h"

#include "com/Jeka8833/PowerWriter/render/Render.h"
#include "com/Jeka8833/PowerWriter/modules/ConfigManager.h"

// Hard to calculate, but it's some time
#define TIMER_ALARM_TIME 255

#define EDIT_NONE 0
#define EDIT_DAY 1
#define EDIT_HOUR 2
#define EDIT_MINUTE 3
#define EDIT_SECOND 4

DateTime TimerPage::setTime = nullptr;
TimeSpan TimerPage::editedTime = TimeSpan(0, 0, 1, 0);
uint8_t TimerPage::editPosition = EDIT_NONE;
uint8_t TimerPage::canAlarm = 0;

const __FlashStringHelper *TimerPage::getName() {
    return F("Timer");
}

void TimerPage::render() {
    if (isAlarm() && (millis() >> 10) % 2) {
        if (ConfigManager::alarmSound) {
            Render::lastBuzzerBeep = millis();
        }

        Render::lcd.print(F("Timer Alarm!"));
        Render::lcd.setCursor(0, 1);
        Render::lcd.print(F("Press any button"));

        canAlarm--;
        return;
    }

    TimeSpan span = isTimerEnded() ? editedTime : setTime - ClockManager::rtc.now();

    // 00 days 00:00:00
    Render::lcd.printWithZeroAnimation(span.days(), 2, editPosition == EDIT_DAY);
    Render::lcd.print(F(" days "));
    Render::lcd.printWithZeroAnimation(span.hours(), 2, editPosition == EDIT_HOUR);
    Render::lcd.print(':');
    Render::lcd.printWithZeroAnimation(span.minutes(), 2, editPosition == EDIT_MINUTE);
    Render::lcd.print(':');
    Render::lcd.printWithZeroAnimation(span.seconds(), 2, editPosition == EDIT_SECOND);

    Render::lcd.setCursor(0, 1);
    if (editPosition) {
        Render::lcd.print(F("Editing"));
    } else if (setTime != nullptr) {
        if (isTimerEnded()) {
            Render::lcd.print(F("Timer ended"));
        } else {
            Render::lcd.print(F("Timer started"));
        }
    } else {
        Render::lcd.print(F("Paused"));
    }
}

void TimerPage::buttonEvent(VirtButton &leftButton, VirtButton &centerButton, VirtButton &rightButton) {
    if (isAlarm()) {
        canAlarm = 0;
    } else if (editPosition) {
        if (leftButton.click() || leftButton.step()) {
            addTimeSpan(true);
        } else if (rightButton.click() || rightButton.step()) {
            addTimeSpan(false);
        } else if (centerButton.click()) {
            editPosition++;

            if (editPosition > EDIT_SECOND) {
                editPosition = EDIT_NONE;
            }
        } else if (centerButton.hold(0)) {
            editPosition = EDIT_NONE;
        }
    } else if (centerButton.click()) {
        editPosition = EDIT_DAY;
    } else if (centerButton.hold(0)) {
        Render::changeScreen(PAGE_MENU);
    } else if (leftButton.click()) {
        if (setTime != nullptr) {
            if (isTimerEnded()) {
                editedTime = TimeSpan(0, 0, 1, 0);
            } else {
                editedTime = setTime - ClockManager::rtc.now();
            }

            setTime = nullptr;

            canAlarm = 0;
        } else {
            setTime = ClockManager::rtc.now() + editedTime;

            canAlarm = TIMER_ALARM_TIME;
        }
    } else if (rightButton.hold(0)) {
        setTime = nullptr;
        editedTime = TimeSpan(0, 0, 1, 0);

        canAlarm = 0;
    }
}


void TimerPage::addTimeSpan(bool substract) {
    const int8_t offset = substract ? -1 : 1;

    uint16_t days = editedTime.days();
    uint8_t hours = editedTime.hours();
    uint8_t minutes = editedTime.minutes();
    uint8_t seconds = editedTime.seconds();

    switch (editPosition) {
        case EDIT_DAY:
            days = (days <= 0 && substract) ? 0 : (days + offset);
            break;
        case EDIT_HOUR:
            hours = (hours + 24 + offset) % 24;
            break;
        case EDIT_MINUTE:
            minutes = (minutes + 60 + offset) % 60;
            break;
        case EDIT_SECOND:
            seconds = (seconds + 60 + offset) % 60;
            break;
    }

    editedTime = TimeSpan(days, hours, minutes, seconds);
}

bool TimerPage::isAllowChangeScreen() const {
    return isTimerEnded() || editPosition == EDIT_NONE;
}

bool TimerPage::isTimerEnded() {
    return setTime == nullptr || ClockManager::rtc.now() >= setTime;
}

bool TimerPage::isAlarm() {
    return canAlarm && setTime != nullptr && ClockManager::rtc.now() >= setTime;
}
