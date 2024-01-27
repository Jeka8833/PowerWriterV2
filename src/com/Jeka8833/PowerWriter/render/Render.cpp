#include "Render.h"

#include "com/Jeka8833/PowerWriter/Settings.h"
#include "com/Jeka8833/PowerWriter/modules/ButtonManager.h"
#include "com/Jeka8833/PowerWriter/modules/ConfigManager.h"
#include "com/Jeka8833/PowerWriter/render/pages/TemperatureActiveTimePage.h"
#include "com/Jeka8833/PowerWriter/render/pages/OldTimePage.h"
#include "com/Jeka8833/PowerWriter/render/pages/MenuPage.h"
#include "com/Jeka8833/PowerWriter/render/pages/DateTimePage.h"
#include "com/Jeka8833/PowerWriter/render/pages/AboutPage.h"
#include "com/Jeka8833/PowerWriter/render/pages/PageTimePage.h"
#include "com/Jeka8833/PowerWriter/render/pages/SDCardMessagePage.h"
#include "com/Jeka8833/PowerWriter/render/pages/NotePage.h"
#include "com/Jeka8833/PowerWriter/render/pages/LightSettingsPage.h"
#include "com/Jeka8833/PowerWriter/render/pages/TimerPage.h"
#include "com/Jeka8833/PowerWriter/render/pages/SpeakerSettingPage.h"
#include "com/Jeka8833/PowerWriter/render/pages/StopwatchPage.h"

Page *Render::pages[PAGE_COUNT] = {new DateTimePage(), new TemperatureActiveTimePage(), new OldTimePage(),
                                   new NotePage(), new MenuPage(), new AboutPage(), new PageTimePage(),
                                   new SDCardMessagePage(), new LightSettingsPage(), new TimerPage(),
                                   new SpeakerSettingPage(), new StopwatchPage()};


LCD Render::lcd(DISPLAY_ADDRESS, DISPLAY_COLUMN, DISPLAY_ROW);
uint8_t Render::currentPage = 0;
uint32_t Render::lastPageChange = 0;
uint8_t Render::lashHash = 0;
uint32_t Render::lastBuzzerBeep = 0;
bool Render::hadButtonEvent = false;
bool Render::pwmLastState = false;

void Render::init() {
    lcd.init();
    lcd.backlight();

    pinMode(PIN_DISPLAY_BRIGHTNESS_PWM, OUTPUT);
    pinMode(PIN_BUZZER_PWM, OUTPUT);

    LIGHT_PWM_SETTINGS
}

void Render::render() {
    Page *page = pages[currentPage];

    lcd.setCursor(0, 0);
    if (LCD::hash != lashHash) {
        lashHash = LCD::hash;

        lcd.clear();
    }

    LCD::hash = 0;
    page->render();

    bool hasButtonEvent = ButtonManager::hasEvent();
    if (hasButtonEvent) {
        lastPageChange = millis();
        hadButtonEvent = true;

        if (ConfigManager::systemSound && (ButtonManager::leftButton.press() || ButtonManager::centerButton.press() ||
                                           ButtonManager::rightButton.press())) {
            lastBuzzerBeep = millis();
        }

        page->buttonEvent(ButtonManager::leftButton, ButtonManager::centerButton, ButtonManager::rightButton);
    }

    uint8_t time = ConfigManager::pageTime[currentPage];
    if (time && page->isAllowChangeScreen() &&
        millis() - lastPageChange > (time * (uint32_t) 1000 + (hadButtonEvent ? (uint32_t) 10000 : 0))) {

        nextPage();

        if (currentPage == PAGE_NOTE && !NotePage::hasNote()) nextPage();
    }


    uint8_t pwm = map(
            max(0, min(0x3FF, (int16_t) getLightStrength() + ((int8_t) ConfigManager::shiftLightBrightness) * 2)),
            0, 0x3FF, ConfigManager::maxLightBrightness, ConfigManager::minLightBrightness);

    analogWrite(PIN_DISPLAY_BRIGHTNESS_PWM, pwm);


    if (TimerPage::isAlarm()) {
        Render::changeScreen(PAGE_TIMER);
    }


    checkBuzzer();

}

uint16_t Render::getLightStrength() {
    return analogRead(PIN_LIGHT_SENSOR);
}

void Render::nextPage() {
    changeScreen((currentPage + 1) % CAROUSEL_COUNT);
}

void Render::prevPage() {
    changeScreen((currentPage + CAROUSEL_COUNT + 1) % CAROUSEL_COUNT);
}

void Render::changeScreen(uint8_t pageIndex) {
    currentPage = pageIndex;
    lastPageChange = millis();
    hadButtonEvent = false;

    lcd.clear();
}

void Render::checkBuzzer() {
    bool state = millis() - lastBuzzerBeep < 300;

    if (pwmLastState != state) {
        pwmLastState = state;
        if (state) {
            BUZZER_PWM_SETTINGS
        } else {
            LIGHT_PWM_SETTINGS
        }
    }

    if (state) {
        analogWrite(PIN_BUZZER_PWM, 127);
    } else {
        analogWrite(PIN_BUZZER_PWM, 0);
    }
}
