#include "SpeakerSettingPage.h"

#include "com/Jeka8833/PowerWriter/render/Render.h"
#include "com/Jeka8833/PowerWriter/modules/ConfigManager.h"

#define ENTRIES_COUNT 2

#define EDIT_NONE 0
#define EDIT_SYSTEM_SOUND 1
#define EDIT_ALARM_SOUND 2

const char systemSoundEntry[] PROGMEM = "System:";
const char alarmSoundEntry[] PROGMEM = "Alarm:";

const char *const SpeakerSettingPage::entries[ENTRIES_COUNT] PROGMEM = {systemSoundEntry, alarmSoundEntry};
bool *SpeakerSettingPage::values[ENTRIES_COUNT] = {&ConfigManager::systemSound, &ConfigManager::alarmSound};

uint8_t SpeakerSettingPage::editPosition = EDIT_NONE;

const __FlashStringHelper *SpeakerSettingPage::getName() {
    return F("Speaker Settings");
}

void SpeakerSettingPage::render() {
    Render::lcd.print('>');

    for (int pageIndex = 0; pageIndex < DISPLAY_ROW; pageIndex++) {
        uint8_t row = (editPosition + pageIndex) % ENTRIES_COUNT;

        Render::lcd.setCursor(1, pageIndex);
        Render::lcd.print((const __FlashStringHelper *) pgm_read_ptr(&entries[row]));

        Render::lcd.setCursor(11, pageIndex);
        Render::lcd.print((*values[(editPosition + pageIndex) % ENTRIES_COUNT]) ? F("True") : F("False"));
    }
}

void SpeakerSettingPage::buttonEvent(VirtButton &leftButton, VirtButton &centerButton, VirtButton &rightButton) {
    if (leftButton.click() || leftButton.step()) {
        editPosition--;
    } else if (rightButton.click() || rightButton.step()) {
        editPosition++;
    } else if (centerButton.click()) {
        (*values[editPosition % ENTRIES_COUNT]) = !(*values[editPosition % ENTRIES_COUNT]);

        ConfigManager::lazyWrite(10);
    } else if (centerButton.hold(0)) {
        Render::changeScreen(PAGE_MENU);
    }
}

bool SpeakerSettingPage::isAllowChangeScreen() const {
    return true;
}