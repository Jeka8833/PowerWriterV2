#include <Arduino.h>
#include "com/Jeka8833/PowerWriter/modules/ConfigManager.h"
#include "com/Jeka8833/PowerWriter/render/Render.h"
#include "com/Jeka8833/PowerWriter/modules/SDManager.h"
#include "com/Jeka8833/PowerWriter/modules/ClockManager.h"

void setup() {
    ConfigManager::read();
    ClockManager::init();
    SDManager::init();

    Render::init();
}

void loop() {
    ConfigManager::tick();
    ClockManager::tick();
    SDManager::tick();

    Render::render();
}