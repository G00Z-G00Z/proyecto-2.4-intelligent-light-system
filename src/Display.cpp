#include <Display.h>
#include <Arduino.h>

static void printPowerInfo(Display::LCD &lcd, int ledNum, float power)
{
    lcd.print("Led" + String(ledNum) + ": " + String(power) + "mW");
}

void Display::clearAndResetCursor(Display::LCD &lcd)
{
    lcd.clear();
    lcd.home();
}

void Display::printPowerLeds(Display::LCD &lcd, float pow1, float pow2)
{
    using namespace Display;
    clearAndResetCursor(lcd);
    printPowerInfo(lcd, 1, pow1);
    lcd.setCursor(0, 1);
    printPowerInfo(lcd, 2, pow2);
}
