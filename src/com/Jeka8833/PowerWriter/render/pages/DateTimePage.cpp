#include "DateTimePage.h"

#include "com/Jeka8833/PowerWriter/render/Render.h"

#define EDIT_NONE 0
#define EDIT_DAY 1
#define EDIT_MONTH 2
#define EDIT_YEAR 3
#define EDIT_HOUR 4
#define EDIT_MINUTE 5
#define EDIT_SECOND 6

const char minEntry[] PROGMEM = "Sunda";
const char maxEntry[] PROGMEM = "Monda";
const char shiftEntry[] PROGMEM = "Tuesd";
const char wednesday[] PROGMEM = "Wedne";
const char thursday[] PROGMEM = "Thurs";
const char friday[] PROGMEM = "Frida";
const char saturday[] PROGMEM = "Satur";

const char *const DateTimePage::daysOfWeekName[] PROGMEM = {
        minEntry, maxEntry, shiftEntry, wednesday, thursday, friday, saturday};
uint8_t DateTimePage::editPosition = EDIT_NONE;
DateTime DateTimePage::editTime = nullptr;

const __FlashStringHelper *DateTimePage::getName() {
    return F("Date and Time");
}

void DateTimePage::render() {
    DateTime now = editPosition ? editTime : ClockManager::rtc.now();

    Render::lcd.printWithZeroAnimation(now.day(), 2, editPosition == EDIT_DAY);
    Render::lcd.print('.');
    Render::lcd.printWithZeroAnimation(now.month(), 2, editPosition == EDIT_MONTH);
    Render::lcd.print('.');
    Render::lcd.printWithZeroAnimation((int16_t) now.year(), 4, editPosition == EDIT_YEAR);
    Render::lcd.print(' ');
    Render::lcd.print((const __FlashStringHelper *) pgm_read_ptr(&daysOfWeekName[now.dayOfTheWeek()]));


    Render::lcd.setCursor(0, 1);
    Render::lcd.print(F("Time: "));
    Render::lcd.printWithZeroAnimation(now.hour(), 2, editPosition == EDIT_HOUR);
    Render::lcd.print(':');
    Render::lcd.printWithZeroAnimation(now.minute(), 2, editPosition == EDIT_MINUTE);
    Render::lcd.print(':');
    Render::lcd.printWithZeroAnimation(now.second(), 2, editPosition == EDIT_SECOND);
}

void DateTimePage::buttonEvent(VirtButton &leftButton, VirtButton &centerButton, VirtButton &rightButton) {
    if (editPosition) {
        if (leftButton.click() || leftButton.step()) {
            addTimeSpan(true);
        } else if (rightButton.click() || rightButton.step()) {
            addTimeSpan(false);
        } else if (centerButton.click()) {
            editPosition++;

            if (editPosition > EDIT_SECOND) {
                ClockManager::rtc.adjust(editTime);

                editPosition = EDIT_NONE;

                editTime = nullptr;
            }
        } else if (centerButton.hold(0)) {
            editPosition = EDIT_NONE;

            editTime = nullptr;
        }
    } else if (centerButton.hold()) {
        editPosition = EDIT_DAY;

        editTime = ClockManager::rtc.now();
    } else {
        carouselButtonProcess();
    }
}

bool DateTimePage::isAllowChangeScreen() const {
    return editPosition == EDIT_NONE;
}

void DateTimePage::addTimeSpan(bool substract) {
    const int8_t offset = substract ? -1 : 1;

    switch (editPosition) {
        case EDIT_DAY: {
            const uint8_t numberOfDays = ClockManager::getNumberOfDays(editTime.month(), editTime.year());

            editTime = DateTime(editTime.year(), editTime.month(),
                                1 + (((editTime.day() - 1) + numberOfDays + offset) % numberOfDays),
                                editTime.hour(), editTime.minute(), editTime.second());
            break;
        }
        case EDIT_MONTH:
            editTime = DateTime(editTime.year(), 1 + (((editTime.month() - 1) + 12 + offset) % 12),
                                editTime.day(), editTime.hour(), editTime.minute(),
                                editTime.second());
            break;
        case EDIT_YEAR:
            editTime = DateTime(2000 + (((editTime.year() - 2000) + 100 + offset) % 100),
                                editTime.month(), editTime.day(), editTime.hour(),
                                editTime.minute(), editTime.second());
            break;
        case EDIT_HOUR:
            editTime = DateTime(editTime.year(), editTime.month(), editTime.day(),
                                (editTime.hour() + 24 + offset) % 24, editTime.minute(),
                                editTime.second());
            break;
        case EDIT_MINUTE:
            editTime = DateTime(editTime.year(), editTime.month(), editTime.day(),
                                editTime.hour(), (editTime.minute() + 60 + offset) % 60,
                                editTime.second());
            break;
        case EDIT_SECOND:
            editTime = DateTime(editTime.year(), editTime.month(), editTime.day(),
                                editTime.hour(), editTime.minute(),
                                (editTime.second() + 60 + offset) % 60);
            break;
    }
}