#ifndef POWERWRITERV2_TEMPERATUREACTIVETIMEPAGE_H
#define POWERWRITERV2_TEMPERATUREACTIVETIMEPAGE_H

#include "com/Jeka8833/PowerWriter/render/Page.h"

class TemperatureActiveTimePage : public Page {
public:
    const __FlashStringHelper *getName() override;

    void render() override;

    void buttonEvent(VirtButton &leftButton, VirtButton &centerButton, VirtButton &rightButton) override;

    bool isAllowChangeScreen() const override;
};


#endif //POWERWRITERV2_TEMPERATUREACTIVETIMEPAGE_H
