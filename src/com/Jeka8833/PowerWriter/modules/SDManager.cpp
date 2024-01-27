#include "SDManager.h"

// 5 * 60 * 1000
#define TIME_STATUS_WRITE 300000

#include "com/Jeka8833/PowerWriter/Settings.h"
#include "com/Jeka8833/PowerWriter/render/Render.h"
#include "com/Jeka8833/PowerWriter/render/pages/SDCardMessagePage.h"
#include "com/Jeka8833/PowerWriter/render/pages/NotePage.h"
#include "ClockManager.h"

uint32_t SDManager::lastStatusWrite = 0;
uint8_t SDManager::lastNoteRead = 0;
uint32_t SDManager::endMessageTime = 0;

void SDManager::init() {
    writeShutDown();
    readNotes();
}

// =ТЕКСТ((((A35/60)/60)/24)+25569,"MM/DD/YYYY HH:MM:SS")

void SDManager::tick() {
    if (millis() - lastStatusWrite > TIME_STATUS_WRITE) {
        writeCurrentStatus();

        lastStatusWrite = millis();
    }

    DateTime now = ClockManager::rtc.now();

    uint8_t day = now.day();

    if (lastNoteRead != day || (endMessageTime && (now.unixtime() > endMessageTime))) {
        lastNoteRead = day;

        readNotes();
    }
}


void SDManager::writeShutDown() {
    File file = openFile(F("SHUTDOWN.CSV"));
    if (!file) return;

    file.print(ClockManager::rtc.now().unixtime());
    file.print(',');
    file.print(ClockManager::mainAlarm.unixtime());
    file.print(',');
    file.print(ClockManager::supportAlarm.unixtime());
    file.println();

    file.close();
}

void SDManager::writeCurrentStatus() {
    File file = openFile(F("STATUS.CSV"));
    if (!file) return;

    file.print(ClockManager::rtc.now().unixtime());
    file.print(',');
    file.print(ClockManager::rtc.getTemperature());
    file.print(',');
    file.print(Render::getLightStrength());
    file.println();

    file.close();
}

void SDManager::readNotes() {
    endMessageTime = 0;

    File file = openFile(F("NOTES.CSV"), true);
    if (!file) return;

    uint32_t unixtime = ClockManager::rtc.now().unixtime();
    while (true) {
        uint32_t startTime = file.parseInt(SKIP_ALL);
        if (!startTime) break;
        if (startTime > unixtime) {
            file.find('\n');
            continue;
        }

        uint32_t endTime = file.parseInt(SKIP_ALL);
        if (!endTime) break;
        if (endTime < unixtime) {
            file.find('\n');
            continue;
        }

        file.find(',');
        String note = file.readStringUntil('\n');
        note.trim();

        endMessageTime = endTime;
        NotePage::note = note;
        break;
    }

    file.close();

    SDCardMessagePage::message = F("Notes readed!");
}

File SDManager::openFile(const __FlashStringHelper *filepath, bool read) {
    if (!SD.begin(CS_PIN_SD)) {
        Render::changeScreen(PAGE_SD_MESSAGE);
        SDCardMessagePage::message = F("Card not found!");

        return {};
    }

    File file = SD.open(filepath, FILE_WRITE);

    if (!file) {
        Render::changeScreen(PAGE_SD_MESSAGE);
        SDCardMessagePage::message = F("Fail Create File");
    }

    if (!read) return file;

    file.close();

    file = SD.open(filepath);
    if (!file) {
        Render::changeScreen(PAGE_SD_MESSAGE);
        SDCardMessagePage::message = F("Fail Open File");
    }

    return file;
}
