#include <Display.h>
#include <Arduino.h>

namespace Display
{
    void clearAndResetCursor(Display::LCD &lcd)
    {
        lcd.clear();
        lcd.home();
    }

    void printPowerLeds(Display::LCD &lcd, float pow1, float pow2)
    {
        clearAndResetCursor(lcd);
        printPowerInfo(lcd, 1, pow1);
        lcd.setCursor(0, 1);
        printPowerInfo(lcd, 2, pow2);
    }

    static void printPowerInfo(Display::LCD &lcd, float ledNum, float power)
    {
        lcd.print("Led" + String(ledNum) + ": " + String(power) + "W");
    }
};
