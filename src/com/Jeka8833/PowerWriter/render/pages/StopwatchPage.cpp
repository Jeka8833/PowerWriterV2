#include "StopwatchPage.h"

#include "com/Jeka8833/PowerWriter/render/Render.h"

DateTime StopwatchPage::startTime = nullptr;

TimeSpan StopwatchPage::endTime = TimeSpan(0);
TimeSpan StopwatchPage::savedTime = TimeSpan(0);

const __FlashStringHelper *StopwatchPage::getName() {
    return F("Stopwatch");
}

void StopwatchPage::render() {
    TimeSpan time = startTime == nullptr ? endTime : ClockManager::rtc.now() - startTime;

    // 00 days 00:00:00
    Render::lcd.printWithZero(time.days(), 2);
    Render::lcd.print(F(" days "));
    Render::lcd.printWithZero(time.hours(), 2);
    Render::lcd.print(':');
    Render::lcd.printWithZero(time.minutes(), 2);
    Render::lcd.print(':');
    Render::lcd.printWithZero(time.seconds(), 2);

    if (savedTime.totalseconds() > 0) {
        // Saved: 00 days 00:00:00
        Render::lcd.longText(0, 1, 23);
        Render::lcd.print(F("Saved: "));
        Render::lcd.printWithZero(savedTime.days(), 2);
        Render::lcd.print(F(" days "));
        Render::lcd.printWithZero(savedTime.hours(), 2);
        Render::lcd.print(':');
        Render::lcd.printWithZero(savedTime.minutes(), 2);
        Render::lcd.print(':');
        Render::lcd.printWithZero(savedTime.seconds(), 2);
    }
}

void StopwatchPage::buttonEvent(VirtButton &leftButton, VirtButton &centerButton, VirtButton &rightButton) {
    if (centerButton.click()) {
        if (startTime != nullptr) {
            savedTime = ClockManager::rtc.now() - startTime;
        }
    } else if (centerButton.hold()) {
        Render::changeScreen(PAGE_MENU);
    } else if (leftButton.click()) {
        if (startTime == nullptr) {
            startTime = ClockManager::rtc.now();
        } else {
            endTime = ClockManager::rtc.now() - startTime;
            startTime = nullptr;
        }
    } else if (rightButton.click()) {
        startTime = nullptr;
        endTime = TimeSpan(0);
        savedTime = TimeSpan(0);
    }
}

bool StopwatchPage::isAllowChangeScreen() const {
    return startTime == nullptr;
}