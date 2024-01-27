#include "Page.h"

#include "com/Jeka8833/PowerWriter/render/Render.h"
#include "com/Jeka8833/PowerWriter/modules/ConfigManager.h"

void Page::carouselButtonProcess() {
    if (ButtonManager::leftButton.click() || ButtonManager::leftButton.step(0)) {
        Render::prevPage();
    } else if (ButtonManager::rightButton.click() || ButtonManager::rightButton.step(0)) {
        Render::nextPage();
    } else if (ButtonManager::leftButton.hasClicks(1) || ButtonManager::leftButton.step(1)) {
        ConfigManager::shiftLightBrightness--;

        ConfigManager::lazyWrite(10);
    } else if (ButtonManager::rightButton.hasClicks(1) || ButtonManager::rightButton.step(1)) {
        ConfigManager::shiftLightBrightness++;

        ConfigManager::lazyWrite(10);
    } else if (ButtonManager::centerButton.click()) {
        Render::changeScreen(PAGE_MENU);
    }
}
