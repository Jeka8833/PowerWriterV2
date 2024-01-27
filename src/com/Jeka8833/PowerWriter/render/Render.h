#define DISPLAY_COLUMN 16
#define DISPLAY_ROW 2

#define PAGE_COUNT 12
#define CAROUSEL_COUNT 4

#define PAGE_DATE_TIME 0
#define PAGE_TEMPERATURE_ACTIVE_TIME 1
#define PAGE_OLD_TIME 2
#define PAGE_NOTE 3


#define PAGE_MENU 4
#define PAGE_ABOUT 5
#define PAGE_PAGE_TIME 6
#define PAGE_SD_MESSAGE 7
#define PAGE_LIGHT_SETTINGS 8
#define PAGE_TIMER 9
#define PAGE_SPEAKER_SETTINGS 10
#define PAGE_STOPWATCH 11


#ifndef POWERWRITER_RENDER_H
#define POWERWRITER_RENDER_H

#include "Page.h"
#include "Arduino.h"
#include "com/Jeka8833/PowerWriter/library/hook/LCD.h"

class Render {
public:
    static LCD lcd;
    static Page *pages[PAGE_COUNT];
    static uint32_t lastBuzzerBeep;

    static void init();

    static void render();

    static void changeScreen(uint8_t pageIndex);

    static uint16_t getLightStrength();

    static void nextPage();

    static void prevPage();

    static void checkBuzzer();

private:
    static bool hadButtonEvent;
    static bool pwmLastState;
    static uint8_t currentPage;
    static uint32_t lastPageChange;
    static uint8_t lashHash;
};


#endif //POWERWRITER_RENDER_H
