#ifndef POWERWRITERV2_NOTEPAGE_H
#define POWERWRITERV2_NOTEPAGE_H

#include "com/Jeka8833/PowerWriter/render/Page.h"

class NotePage : public Page {
public:
    const __FlashStringHelper *getName() override;

    void render() override;

    void buttonEvent(VirtButton &leftButton, VirtButton &centerButton, VirtButton &rightButton) override;

    bool isAllowChangeScreen() const override;

    static bool hasNote();

    static String note;
};


#endif //POWERWRITERV2_NOTEPAGE_H
