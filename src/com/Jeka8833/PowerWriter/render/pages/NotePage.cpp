#include "NotePage.h"

#include "com/Jeka8833/PowerWriter/render/Render.h"
#include "com/Jeka8833/PowerWriter/modules/ClockManager.h"
#include "com/Jeka8833/PowerWriter/modules/SDManager.h"

String NotePage::note = "";

const __FlashStringHelper *NotePage::getName() {
    return F("Note");
}

void NotePage::render() {
    Render::lcd.print(F("Today's note:"));

    if (hasNote()) {
        Render::lcd.longText(0, 1, note.length());
        Render::lcd.print(note);
    } else {
        Render::lcd.setCursor(0, 1);
        Render::lcd.print(F("- No notes"));
    }
}

void NotePage::buttonEvent(VirtButton &leftButton, VirtButton &centerButton, VirtButton &rightButton) {
    carouselButtonProcess();
}

bool NotePage::isAllowChangeScreen() const {
    return true;
}

bool NotePage::hasNote() {
    return note.length() > 0 && ClockManager::rtc.now().unixtime() < SDManager::endMessageTime;
}
