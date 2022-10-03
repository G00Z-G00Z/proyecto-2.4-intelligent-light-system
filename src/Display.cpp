#include <Display.h>
#include <Arduino.h>

using namespace Display;

void LightLevelsDisplay::clearAndResetCursor()
{
    this->clear();
    this->home();
}

void LightLevelsDisplay::printPowerLeds(float pow1, float pow2)
{
    this->clearAndResetCursor();
    this->printPowerInfo(1, pow1);
    this->setCursor(0, 1);
    this->printPowerInfo(2, pow2);
}

void LightLevelsDisplay::printPowerInfo(int ledNum, float power)
{
    this->print("Led" + String(ledNum) + ": " + String(power) + "W");
}
