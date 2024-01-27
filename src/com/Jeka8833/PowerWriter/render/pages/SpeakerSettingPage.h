#ifndef POWERWRITERV2_SPEAKERSETTINGPAGE_H
#define POWERWRITERV2_SPEAKERSETTINGPAGE_H

#include "com/Jeka8833/PowerWriter/render/Page.h"

class SpeakerSettingPage : public Page {
public:
    const __FlashStringHelper *getName() override;

    void render() override;

    void buttonEvent(VirtButton &leftButton, VirtButton &centerButton, VirtButton &rightButton) override;

    bool isAllowChangeScreen() const override;

private:
    static const char *const entries[] PROGMEM;
    static bool *values[];
    static uint8_t editPosition;
};


#endif //POWERWRITERV2_SPEAKERSETTINGPAGE_H
