#include "OldTimePage.h"

#include "com/Jeka8833/PowerWriter/render/Render.h"
#include "com/Jeka8833/PowerWriter/modules/ClockManager.h"

const __FlashStringHelper *OldTimePage::getName() {
    return F("Last Off Time and Last Active Time");
}

void OldTimePage::render() {
    TimeSpan disabledTime = ClockManager::deviceRunAt - ClockManager::mainAlarm;

    // Disable Time: 00d 00h 00m 00s
    Render::lcd.longText(0, 0, 29);
    Render::lcd.print(F("Disable Time: "));
    Render::lcd.printWithZero(disabledTime.days(), 2);
    Render::lcd.print(F("d "));
    Render::lcd.printWithZero(disabledTime.hours(), 2);
    Render::lcd.print(F("h "));
    Render::lcd.printWithZero(disabledTime.minutes(), 2);
    Render::lcd.print(F("m "));
    Render::lcd.printWithZero(disabledTime.seconds(), 2);
    Render::lcd.print('s');

    TimeSpan lastEnabledTime = ClockManager::mainAlarm - ClockManager::supportAlarm;

    // Last Active Time: 00d 00h 00m 00s
    Render::lcd.longText(0, 1, 33);
    Render::lcd.print(F("Last Active Time: "));
    Render::lcd.printWithZero(lastEnabledTime.days(), 2);
    Render::lcd.print(F("d "));
    Render::lcd.printWithZero(lastEnabledTime.hours(), 2);
    Render::lcd.print(F("h "));
    Render::lcd.printWithZero(lastEnabledTime.minutes(), 2);
    Render::lcd.print(F("m "));
    Render::lcd.printWithZero(lastEnabledTime.seconds(), 2);
    Render::lcd.print('s');
}

void OldTimePage::buttonEvent(VirtButton &leftButton, VirtButton &centerButton, VirtButton &rightButton) {
    carouselButtonProcess();
}

bool OldTimePage::isAllowChangeScreen() const {
    return true;
}
