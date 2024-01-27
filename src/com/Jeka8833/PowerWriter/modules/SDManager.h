#ifndef POWERWRITERV2_SDMANAGER_H
#define POWERWRITERV2_SDMANAGER_H

#include "SD.h"

class SDManager {
public:
    static void init();

    static void tick();

    static void readNotes();

    static uint32_t endMessageTime;

private:
    static void writeCurrentStatus();

    static void writeShutDown();

    static File openFile(const __FlashStringHelper *filepath, bool read = false);

    static uint32_t lastStatusWrite;
    static uint8_t lastNoteRead;
};


#endif //POWERWRITERV2_SDMANAGER_H
