#ifndef POWERWRITERV2_PAGETIMEPAGE_H
#define POWERWRITERV2_PAGETIMEPAGE_H

#include "com/Jeka8833/PowerWriter/render/Page.h"

class PageTimePage : public Page {
public:
    const __FlashStringHelper *getName() override;

    void render() override;

    void buttonEvent(VirtButton &leftButton, VirtButton &centerButton, VirtButton &rightButton) override;

    bool isAllowChangeScreen() const override;

private:
    static uint8_t select;
    static bool isEditing;
};


#endif //POWERWRITERV2_PAGETIMEPAGE_H
