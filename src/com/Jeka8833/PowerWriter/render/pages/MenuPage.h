#ifndef POWERWRITER_MENUPAGE_H
#define POWERWRITER_MENUPAGE_H

#include "com/Jeka8833/PowerWriter/render/Page.h"

class MenuPage : public Page {
public:
    const __FlashStringHelper *getName() override;

    void render() override;

    void buttonEvent(VirtButton &leftButton, VirtButton &centerButton, VirtButton &rightButton) override;

    bool isAllowChangeScreen() const override;

private:
    static const uint8_t showedEntries[];
    static uint8_t select;
};


#endif //POWERWRITER_MENUPAGE_H
