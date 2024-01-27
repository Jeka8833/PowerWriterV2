#ifndef POWERWRITER_ABOUTPAGE_H
#define POWERWRITER_ABOUTPAGE_H

#include "com/Jeka8833/PowerWriter/render/Page.h"

class AboutPage : public Page {
public:
    const __FlashStringHelper *getName() override;

    void render() override;

    void buttonEvent(VirtButton &leftButton, VirtButton &centerButton, VirtButton &rightButton) override;

    bool isAllowChangeScreen() const override;
};


#endif //POWERWRITER_ABOUTPAGE_H
