#ifndef POWERWRITER_DATETIMEPAGE_H
#define POWERWRITER_DATETIMEPAGE_H

#include "com/Jeka8833/PowerWriter/render/Page.h"
#include "com/Jeka8833/PowerWriter/modules/ClockManager.h"

class DateTimePage : public Page {

public:
    const __FlashStringHelper *getName() override;

    void render() override;

    void buttonEvent(VirtButton &leftButton, VirtButton &centerButton, VirtButton &rightButton) override;

    bool isAllowChangeScreen() const override;

private:
    static const char * const daysOfWeekName[] PROGMEM;
    static uint8_t editPosition;
    static DateTime editTime;

    static void addTimeSpan(bool isSubtract);
};


#endif //POWERWRITER_DATETIMEPAGE_H
