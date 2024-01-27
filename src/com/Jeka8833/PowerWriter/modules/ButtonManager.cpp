#include "ButtonManager.h"

#include "com/Jeka8833/PowerWriter/Settings.h"

#define BUTTON_PRESS_NONE 0
#define BUTTON_PRESS_RIGHT 1
#define BUTTON_PRESS_CENTER 2
#define BUTTON_PRESS_LEFT 3

VirtButton ButtonManager::leftButton = VirtButton();
VirtButton ButtonManager::centerButton = VirtButton();
VirtButton ButtonManager::rightButton = VirtButton();

bool ButtonManager::hasEvent() {
    uint8_t button = readButton();

    bool hasEvent = false;
    hasEvent |= leftButton.tick(button == BUTTON_PRESS_LEFT);
    hasEvent |= centerButton.tick(button == BUTTON_PRESS_CENTER);
    hasEvent |= rightButton.tick(button == BUTTON_PRESS_RIGHT);

    return hasEvent;
}

uint8_t ButtonManager::readButton() {
    uint16_t button = analogRead(PIN_BUTTONS);

    if (button < BUTTON_RIGHT / 2) {
        return BUTTON_PRESS_NONE;
    } else if (button < BUTTON_CENTER - (BUTTON_CENTER - BUTTON_RIGHT) / 2) {
        return BUTTON_PRESS_RIGHT;
    } else if (button < BUTTON_LEFT - (BUTTON_LEFT - BUTTON_CENTER) / 2) {
        return BUTTON_PRESS_CENTER;
    } else {
        return BUTTON_PRESS_LEFT;
    }
}
