#ifndef POWERWRITERV2_LCD_H
#define POWERWRITERV2_LCD_H

#include "LiquidCrystal_I2C.h"

class LCD : public LiquidCrystal_I2C {
    using LiquidCrystal_I2C::LiquidCrystal_I2C;

public:
    virtual size_t write(uint8_t);

    void clear();

    void setCursor(uint8_t col, uint8_t row);

    void longText(uint8_t col, uint8_t row, uint8_t length);

    void printWithZero(int16_t value, uint8_t length);

    void printWithZeroAnimation(int16_t value, uint8_t length, bool animation);

    static uint8_t hash;

private:
    static uint8_t skipCount;
};


#endif //POWERWRITERV2_LCD_H
