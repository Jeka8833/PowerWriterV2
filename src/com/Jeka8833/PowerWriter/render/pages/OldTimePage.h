#ifndef POWERWRITERV2_OLDTIMEPAGE_H
#define POWERWRITERV2_OLDTIMEPAGE_H

#include "com/Jeka8833/PowerWriter/render/Page.h"

class OldTimePage : public Page {
public:
    const __FlashStringHelper *getName() override;

    void render() override;

    void buttonEvent(VirtButton &leftButton, VirtButton &centerButton, VirtButton &rightButton) override;

    bool isAllowChangeScreen() const override;
};


#endif //POWERWRITERV2_OLDTIMEPAGE_H
