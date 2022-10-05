#include <Arduino.h>
#include <Display.h>
#include <MotorPWM.h>
#include <LightSystem.h>
#include <VoltageAnalogInput.h>

#define DRIVER_EN 9
#define DRIVER_IN1 30
#define DRIVER_IN2 31

// Analog pins
#define PIN_OUTSIDE A0
#define PIN_INSIDE A1

// constants
#define MAX_LIGTH_OUTSIDE 820
#define MIN_LIGTH_OUTSIDE 770
#define IDEAL_LIGTH 1010

// Motor
Driver::MotorPWM leds(DRIVER_EN, DRIVER_IN1, DRIVER_IN2);

LightSystem::IntelligentLightSystem lightSystem(PIN_INSIDE, PIN_OUTSIDE, leds, 955);

VoltageAnalog::Reader readear(A2);

// Lcd
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
  leds.setDutyCycle(map(100, 0, 100, 0, 255));
}

static float referenceVoltage = 5.0f;

void printValuesEvery1000ms()
{
  static double passedTime = millis();
  double currentTime = millis();

  if (currentTime - passedTime < 1000)
  {
    return;
  }

  // lightSystem.printSerialValues();

  // Power
  float outputVoltage = readear.getVoltage();
  float inputVoltage = (float)lightSystem.getCurrentDuty() / 255.0f * referenceVoltage;

  float differeceVoltage = inputVoltage - outputVoltage;

  float currentmA = LightSystem::voltageToCurrent(inputVoltage) * 1000;

  float powerMW = currentmA * differeceVoltage;

  Serial.println(
      "|Vin" + String(inputVoltage) + "|Vout" + String(outputVoltage) + "|dV:" + String(differeceVoltage) + "|mA" + String(currentmA) + "|mW" + String(powerMW));

  Display::printPowerLeds(lcd, powerMW, powerMW);
  passedTime = currentTime;
}

void loop()
{
  printValuesEvery1000ms();
  lightSystem.update();
}
