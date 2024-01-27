#ifndef POWERWRITER_PAGE_H
#define POWERWRITER_PAGE_H

#include "Arduino.h"
#include "com/Jeka8833/PowerWriter/modules/ButtonManager.h"

class Page {
public:
    virtual const __FlashStringHelper *getName();

    virtual void render();

    virtual void buttonEvent(VirtButton &leftButton, VirtButton &centerButton, VirtButton &rightButton);

    virtual bool isAllowChangeScreen() const;

    static void carouselButtonProcess();
};


#endif //POWERWRITER_PAGE_H
