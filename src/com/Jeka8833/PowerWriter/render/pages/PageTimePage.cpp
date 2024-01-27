#include "PageTimePage.h"

#include "com/Jeka8833/PowerWriter/render/Render.h"
#include "com/Jeka8833/PowerWriter/modules/ConfigManager.h"

uint8_t PageTimePage::select = 0;
bool PageTimePage::isEditing = false;

const __FlashStringHelper *PageTimePage::getName() {
    return F("Page Time");
}

void PageTimePage::render() {
    if (!isEditing || (millis() >> 10) % 2) {
        Render::lcd.print('>');
    }

    for (int pageIndex = 0; pageIndex < DISPLAY_ROW; pageIndex++) {
        if (isEditing && pageIndex > 0) continue;

        Page *page = Render::pages[(select + pageIndex) % PAGE_COUNT];

        const __FlashStringHelper *name = page->getName();

        Render::lcd.longText(1, pageIndex, ((String) name).length());
        Render::lcd.print(name);
    }

    if (isEditing) {
        Render::lcd.setCursor(0, 1);
        Render::lcd.print(F("Page time: "));

        uint8_t pageTime = ConfigManager::pageTime[select % PAGE_COUNT];
        if (!pageTime) {
            Render::lcd.print(F("Off"));
        } else {
            Render::lcd.print(pageTime, DEC);
            Render::lcd.print(F(" s"));
        }
    }
}

void PageTimePage::buttonEvent(VirtButton &leftButton, VirtButton &centerButton, VirtButton &rightButton) {
    if (ButtonManager::leftButton.click() || ButtonManager::leftButton.step(0)) {
        if (isEditing) {
            ConfigManager::pageTime[select % PAGE_COUNT]--;
        } else {
            select--;
        }
    } else if (rightButton.click() || rightButton.step(0)) {
        if (isEditing) {
            ConfigManager::pageTime[select % PAGE_COUNT]++;
        } else {
            select++;
        }
    } else if (centerButton.click()) {
        isEditing = !isEditing;

        if (!isEditing) ConfigManager::lazyWrite(60);
    } else if (centerButton.hold()) {
        isEditing = false;

        Render::changeScreen(PAGE_MENU);
    }
}

bool PageTimePage::isAllowChangeScreen() const {
    return !isEditing;
}
