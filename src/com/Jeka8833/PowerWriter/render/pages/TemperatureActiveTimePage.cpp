#include "TemperatureActiveTimePage.h"

#include "com/Jeka8833/PowerWriter/render/Render.h"
#include "com/Jeka8833/PowerWriter/modules/ClockManager.h"

const __FlashStringHelper *TemperatureActiveTimePage::getName() {
    return F("Ambient Temperature and Operating Time");
}

void TemperatureActiveTimePage::render() {
    // Temp: 000.00°C
    Render::lcd.print(F("Temp: "));
    Render::lcd.print(ClockManager::rtc.getTemperature());
    Render::lcd.print((char) 0xDF);
    Render::lcd.print('C');


    TimeSpan time = ClockManager::rtc.now() - ClockManager::deviceRunAt;

    // Active Time: 00d 00h 00m 00s
    Render::lcd.longText(0, 1, 28);
    Render::lcd.print(F("Active Time: "));
    Render::lcd.printWithZero(time.days(), 2);
    Render::lcd.print(F("d "));
    Render::lcd.printWithZero(time.hours(), 2);
    Render::lcd.print(F("h "));
    Render::lcd.printWithZero(time.minutes(), 2);
    Render::lcd.print(F("m "));
    Render::lcd.printWithZero(time.seconds(), 2);
    Render::lcd.print('s');
}

void TemperatureActiveTimePage::buttonEvent(VirtButton &leftButton, VirtButton &centerButton, VirtButton &rightButton) {
    carouselButtonProcess();
}

bool TemperatureActiveTimePage::isAllowChangeScreen() const {
    return true;
}
