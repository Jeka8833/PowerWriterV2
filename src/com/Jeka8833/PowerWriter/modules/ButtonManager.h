#ifndef POWERWRITER_BUTTONMANAGER_H
#define POWERWRITER_BUTTONMANAGER_H

#define EB_NO_CALLBACK
#define EB_DEB_TIME 50     // debounce timeout
#define EB_CLICK_TIME 500  // click waiting timeout
#define EB_HOLD_TIME 600   // hold timeout
#define EB_STEP_TIME 200   // impulse hold timeout

#include "Arduino.h"
#include "com/Jeka8833/PowerWriter/library/VirtButton.h"

class ButtonManager {
public:
    static VirtButton leftButton;
    static VirtButton centerButton;
    static VirtButton rightButton;

    static bool hasEvent();

private:
    static inline uint8_t readButton();
};


#endif //POWERWRITER_BUTTONMANAGER_H
