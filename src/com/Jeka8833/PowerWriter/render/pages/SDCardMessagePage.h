#ifndef POWERWRITERV2_SDCARDMESSAGEPAGE_H
#define POWERWRITERV2_SDCARDMESSAGEPAGE_H

#include "com/Jeka8833/PowerWriter/render/Page.h"

class SDCardMessagePage : public Page {
public:
    const __FlashStringHelper *getName() override;

    void render() override;

    void buttonEvent(VirtButton &leftButton, VirtButton &centerButton, VirtButton &rightButton) override;

    bool isAllowChangeScreen() const override;

    static const __FlashStringHelper *message;
};


#endif //POWERWRITERV2_SDCARDMESSAGEPAGE_H
