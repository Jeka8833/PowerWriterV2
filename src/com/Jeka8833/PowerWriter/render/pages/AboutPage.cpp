#include "AboutPage.h"

#include "com/Jeka8833/PowerWriter/render/Render.h"

const __FlashStringHelper *AboutPage::getName() {
    return F("About");
}

void AboutPage::render() {
    Render::lcd.print(F("Power Writer"));

    Render::lcd.longText(0, 1, 25);
    Render::lcd.print(F("by Jeka8833 - KPI student"));
}

void AboutPage::buttonEvent(VirtButton &leftButton, VirtButton &centerButton, VirtButton &rightButton) {
    if (leftButton.click() || centerButton.click() || rightButton.click() ||
        leftButton.hold() || centerButton.hold() || rightButton.hold()) {
        Render::changeScreen(PAGE_MENU);
    }
}

bool AboutPage::isAllowChangeScreen() const {
    return true;
}
