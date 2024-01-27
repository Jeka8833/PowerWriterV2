#ifndef POWERWRITERV2_STOPWATCHPAGE_H
#define POWERWRITERV2_STOPWATCHPAGE_H

#include "com/Jeka8833/PowerWriter/render/Page.h"
#include "com/Jeka8833/PowerWriter/modules/ClockManager.h"

class StopwatchPage : public Page {
public:
    const __FlashStringHelper *getName() override;

    void render() override;

    void buttonEvent(VirtButton &leftButton, VirtButton &centerButton, VirtButton &rightButton) override;

    bool isAllowChangeScreen() const override;

private:
    static DateTime startTime;

    static TimeSpan endTime;
    static TimeSpan savedTime;
};


#endif //POWERWRITERV2_STOPWATCHPAGE_H
