#include <Arduino.h>
#include <Button.h>
#include <Display.h>
#include <LightSystem.h>
#include <MotorPWM.h>
#include <VoltageAnalogInput.h>

// Pins in driver
#define DRIVER_EN 9
#define DRIVER_IN1 30
#define DRIVER_IN2 31

// Other pins
#define PIN_OUTSIDE A0
#define PIN_INSIDE A1
#define PIN_BUTTON 38
#define PIN_ANALOG_READER A2

// Constants
#define IDEAL_LIGTH 955

// Leds in Driver
Driver::MotorPWM leds(DRIVER_EN, DRIVER_IN1, DRIVER_IN2);

/**
 * @brief Intelligent light system that controlls the leds brigthness
 *
 */
LightSystem::IntelligentLightSystem lightSystem(PIN_INSIDE, PIN_OUTSIDE, leds, IDEAL_LIGTH);

/**
 * @brief Analog reader to read the output voltage
 *
 */
VoltageAnalog::Reader readear(PIN_ANALOG_READER);

/**
 * @brief Button to change the mode of the intelligent Light system
 *
 */
Buttons::Button btn(PIN_BUTTON);

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
  lcd.print("Intelligent Systems");
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

  if (btn.wasPressed())
  {
    lightSystem.toggleMode();
  }
}
