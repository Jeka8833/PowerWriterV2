#include "ConfigManager.h"

uint8_t EEMEM minLightBrightnessPointer;
uint8_t EEMEM shiftLightBrightnessPointer;
uint8_t EEMEM maxLightBrightnessPointer;
uint8_t EEMEM pageTimePointer[PAGE_COUNT];
uint8_t EEMEM systemSoundPointer;
uint8_t EEMEM alarmSoundPointer;


uint8_t ConfigManager::minLightBrightness = 1;
uint8_t ConfigManager::shiftLightBrightness = 0;
uint8_t ConfigManager::maxLightBrightness = 255;
uint8_t ConfigManager::pageTime[PAGE_COUNT];
bool ConfigManager::systemSound = false;
bool ConfigManager::alarmSound = true;


uint32_t ConfigManager::lazyWriteTime = 0;

void ConfigManager::tick() {
    if (lazyWriteTime && millis() - lazyWriteTime > 0) {
        write();
    }
}

void ConfigManager::read() {
    minLightBrightness = eeprom_read_byte(&minLightBrightnessPointer);
    shiftLightBrightness = eeprom_read_byte(&shiftLightBrightnessPointer);
    maxLightBrightness = eeprom_read_byte(&maxLightBrightnessPointer);

    eeprom_read_block(pageTime, &pageTimePointer, PAGE_COUNT);

    systemSound = eeprom_read_byte(&systemSoundPointer);
    alarmSound = eeprom_read_byte(&alarmSoundPointer);
}

void ConfigManager::write() {
    lazyWriteTime = 0;

    eeprom_update_byte(&minLightBrightnessPointer, minLightBrightness);
    eeprom_update_byte(&shiftLightBrightnessPointer, shiftLightBrightness);
    eeprom_update_byte(&maxLightBrightnessPointer, maxLightBrightness);

    eeprom_update_block(pageTime, &pageTimePointer, PAGE_COUNT);

    eeprom_update_byte(&systemSoundPointer, systemSound);
    eeprom_update_byte(&alarmSoundPointer, alarmSound);
}

void ConfigManager::lazyWrite(uint8_t second) {
    lazyWriteTime = millis() + second * 1000;
}
