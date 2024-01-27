#ifndef POWERWRITER_CONFIG_H
#define POWERWRITER_CONFIG_H

#include "Arduino.h"
#include "com/Jeka8833/PowerWriter/render/Render.h"

class ConfigManager {
public:
    static uint8_t minLightBrightness;
    static uint8_t shiftLightBrightness;
    static uint8_t maxLightBrightness;
    static uint8_t pageTime[PAGE_COUNT];
    static bool systemSound;
    static bool alarmSound;

    static void tick();

    static void read();

    static void lazyWrite(uint8_t second);

private:
    static void write();

    static uint32_t lazyWriteTime;
};


#endif //POWERWRITER_CONFIG_H
