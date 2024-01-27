#include "LCD.h"

#include "Arduino.h"
#include "com/Jeka8833/PowerWriter/render/Render.h"

#define MAX_CHAR_BUFFER 40
#define ANIMATION_SPEED 400

uint8_t LCD::skipCount = 0;
uint8_t LCD::hash = 0;

inline size_t LCD::write(uint8_t value) {
    if (skipCount) {
        skipCount--;
    } else {
        hash = 3 * hash + value;

        LiquidCrystal_I2C::write(value);
    }

    return 1;
}

void LCD::clear() {
    skipCount = 0;

    LiquidCrystal_I2C::clear();
}

void LCD::setCursor(uint8_t col, uint8_t row) {
    longText(col, row, 0);
}

void LCD::longText(uint8_t col, uint8_t row, uint8_t length) {
    if (col >= DISPLAY_COLUMN || (length + col) < DISPLAY_COLUMN) {
        skipCount = 0;
    } else {
        uint8_t alwaysSkipCount = col + length > MAX_CHAR_BUFFER ? (col + length) - MAX_CHAR_BUFFER : 0;

        if (alwaysSkipCount) length = MAX_CHAR_BUFFER - col;

        uint8_t needSkip = length - (DISPLAY_COLUMN - col);

        skipCount = alwaysSkipCount +
                    abs((int8_t) needSkip - (int8_t) ((millis() / ANIMATION_SPEED) % ((needSkip << 1) + 1)));
    }

    LiquidCrystal_I2C::setCursor(col, row);
}

void LCD::printWithZero(int16_t value, uint8_t length) {
    printWithZeroAnimation(value, length, false);
}

void LCD::printWithZeroAnimation(int16_t value, uint8_t length, bool animation) {
    if (animation && (millis() >> 10) % 2) {
        while (length--) {
            print('_');
        }

        return;
    }

    //-32768
    if (value < 0) {
        print('-');

        length--;
    }

    int16_t tempValue = value;
    while (tempValue) {
        tempValue /= 10;

        length--;
    }

    // 6 is number of digits in -32768, if length is bigger than 6, then it's overflow
    while (--length < 6) {
        print('0');
    }

    if (value) {
        uint16_t tempValue1 = abs((int32_t) value);

        print(tempValue1, DEC);
    }
}
