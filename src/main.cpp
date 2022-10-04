#include <Arduino.h>
#include <Display.h>

const int rs = 40,
          en = 41,
          d4 = 42,
          d5 = 43,
          d6 = 44,
          d7 = 45;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Hello world");
  Serial.println("Hello world!");
}

void loop()
{
  Display::printPowerLeds(lcd, 1.0f, 55.5f);
  delay(300);
}