#include "LightSettingsPage.h"

#include "com/Jeka8833/PowerWriter/render/Render.h"
#include "com/Jeka8833/PowerWriter/modules/ConfigManager.h"

#define ENTRIES_COUNT 3

#define EDIT_NONE 0
#define EDIT_MIN_LIGHT 1
#define EDIT_MAX_LIGHT 2
#define EDIT_SHIFT_LIGHT 3

const char minEntry[] PROGMEM = "Min light:";
const char maxEntry[] PROGMEM = "Max light:";
const char shiftEntry[] PROGMEM = "Shift lig:";

const char *const LightSettingsPage::entries[ENTRIES_COUNT] PROGMEM = {minEntry, maxEntry, shiftEntry};
uint8_t *LightSettingsPage::values[ENTRIES_COUNT] =
        {&ConfigManager::minLightBrightness, &ConfigManager::maxLightBrightness,
         &ConfigManager::shiftLightBrightness};

uint8_t LightSettingsPage::editPosition = EDIT_NONE;
bool LightSettingsPage::editing = false;

const __FlashStringHelper *LightSettingsPage::getName() {
    return F("Light settings");
}

void LightSettingsPage::render() {
    if (!editing || (millis() >> 10) % 2) {
        Render::lcd.print('>');
    }

    for (int pageIndex = 0; pageIndex < DISPLAY_ROW; pageIndex++) {
        uint8_t row = (editPosition + pageIndex) % ENTRIES_COUNT;

        Render::lcd.setCursor(1, pageIndex);
        Render::lcd.print((const __FlashStringHelper *) pgm_read_ptr(&entries[row]));

        if (row == 2) {
            Render::lcd.setCursor(12, pageIndex);
            Render::lcd.print((int8_t) (*values[(editPosition + pageIndex) % ENTRIES_COUNT]), DEC);
        } else {
            Render::lcd.setCursor(13, pageIndex);
            Render::lcd.print(*values[(editPosition + pageIndex) % ENTRIES_COUNT], DEC);
        }
    }
}

void LightSettingsPage::buttonEvent(VirtButton &leftButton, VirtButton &centerButton, VirtButton &rightButton) {
    if (leftButton.click() || leftButton.step()) {
        if (editing) {
            (*values[editPosition % ENTRIES_COUNT])--;

            ConfigManager::lazyWrite(10);
        } else {
            editPosition--;
        }
    } else if (rightButton.click() || rightButton.step()) {
        if (editing) {
            (*values[editPosition % ENTRIES_COUNT])++;

            ConfigManager::lazyWrite(10);

        } else {
            editPosition++;
        }
    } else if (centerButton.click()) {
        editing = !editing;
    } else if (centerButton.hold(0)) {
        Render::changeScreen(PAGE_MENU);
    }
}

bool LightSettingsPage::isAllowChangeScreen() const {
    return !editing;
}