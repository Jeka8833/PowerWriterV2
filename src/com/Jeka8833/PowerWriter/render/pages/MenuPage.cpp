#include "MenuPage.h"

#include "com/Jeka8833/PowerWriter/render/Render.h"
#include "com/Jeka8833/PowerWriter/modules/SDManager.h"

#define MENU_ENTRY_COUNT 7
constexpr const uint8_t MenuPage::showedEntries[MENU_ENTRY_COUNT] =
        {PAGE_ABOUT, PAGE_PAGE_TIME, PAGE_SD_MESSAGE, PAGE_LIGHT_SETTINGS, PAGE_TIMER,
         PAGE_SPEAKER_SETTINGS, PAGE_STOPWATCH};

uint8_t MenuPage::select = 0;

const __FlashStringHelper *MenuPage::getName() {
    return F("Settings");
}

void MenuPage::render() {
    if ((millis() >> 10) % 2) {
        Render::lcd.print('>');
    }

    for (int pageIndex = 0; pageIndex < DISPLAY_ROW; pageIndex++) {
        Page *page = Render::pages[showedEntries[(select + pageIndex) % MENU_ENTRY_COUNT]];

        const __FlashStringHelper *name = page->getName();

        Render::lcd.longText(1, pageIndex, ((String) name).length());
        Render::lcd.print(name);
    }
}

void MenuPage::buttonEvent(VirtButton &leftButton, VirtButton &centerButton, VirtButton &rightButton) {
    if (leftButton.click() || leftButton.step(0)) {
        select--;
    } else if (rightButton.click() || rightButton.step(0)) {
        select++;
    } else if (centerButton.click()) {
        uint8_t page = showedEntries[select % MENU_ENTRY_COUNT];

        if (page == PAGE_SD_MESSAGE) {
            SDManager::readNotes();
        }

        Render::changeScreen(page);
    } else if (centerButton.hold()) {
        Render::nextPage();
    }
}

bool MenuPage::isAllowChangeScreen() const {
    return true;
}
