#include "SDCardMessagePage.h"

#include "com/Jeka8833/PowerWriter/render/Render.h"

const __FlashStringHelper *SDCardMessagePage::message;

const __FlashStringHelper *SDCardMessagePage::getName() {
    return F("SD Reload");
}

void SDCardMessagePage::render() {
    Render::lcd.print(F("SD card status"));

    Render::lcd.setCursor(0, 1);
    Render::lcd.print(message);
}

void SDCardMessagePage::buttonEvent(VirtButton &leftButton, VirtButton &centerButton, VirtButton &rightButton) {
    if (leftButton.click() || centerButton.click() || rightButton.click() ||
        leftButton.hold() || centerButton.hold() || rightButton.hold()) {
        Render::nextPage();
    }
}

bool SDCardMessagePage::isAllowChangeScreen() const {
    return true;
}
