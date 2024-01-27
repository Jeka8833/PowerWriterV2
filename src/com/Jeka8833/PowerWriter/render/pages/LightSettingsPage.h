#ifndef POWERWRITERV2_LIGHTSETTINGSPAGE_H
#define POWERWRITERV2_LIGHTSETTINGSPAGE_H

#include "com/Jeka8833/PowerWriter/render/Page.h"

class LightSettingsPage : public Page {
public:
    const __FlashStringHelper *getName() override;

    void render() override;

    void buttonEvent(VirtButton &leftButton, VirtButton &centerButton, VirtButton &rightButton) override;

    bool isAllowChangeScreen() const override;

private:
    static const char *const entries[] PROGMEM;
    static uint8_t *values[];
    static uint8_t editPosition;
    static bool editing;
};


#endif //POWERWRITERV2_LIGHTSETTINGSPAGE_H
