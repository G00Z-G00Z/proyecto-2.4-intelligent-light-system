#pragma once
#include <LiquidCrystal.h>

namespace Display
{

    using LCD = LiquidCrystal;

    void clearAndResetCursor(LCD *lcd);

    void printPowerLeds(LCD *lcd, float pow1, float pow2);

};
