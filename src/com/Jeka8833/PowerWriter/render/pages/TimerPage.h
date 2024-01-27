#ifndef POWERWRITERV2_TIMERPAGE_H
#define POWERWRITERV2_TIMERPAGE_H

#include "com/Jeka8833/PowerWriter/render/Page.h"
#include "com/Jeka8833/PowerWriter/modules/ClockManager.h"

class TimerPage : public Page {
public:
    const __FlashStringHelper *getName() override;

    void render() override;

    void buttonEvent(VirtButton &leftButton, VirtButton &centerButton, VirtButton &rightButton) override;

    bool isAllowChangeScreen() const override;

    static bool isAlarm();

private:
    static bool isTimerEnded();

    static void addTimeSpan(bool isSubtract);

    static DateTime setTime;
    static TimeSpan editedTime;
    static uint8_t editPosition;
    static uint8_t canAlarm;
};


#endif //POWERWRITERV2_TIMERPAGE_H
