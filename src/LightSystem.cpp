#include <LightSystem.h>
#include <math.h>
#include <Arduino.h>
#include <RBD_LightSensor.h>
#include <SmartTimer.h>
#include <MotorPWM.h>

using namespace LightSystem;

static const int threshold = 10;
static const int changeFactor = 5;

IntelligentLightSystem::IntelligentLightSystem(int pinInside, int pinOutside, Driver::MotorPWM &motor, int idealLightValue)
    : inside(RBD::LightSensor(pinInside)),
      outside(RBD::LightSensor(pinOutside)),
      motor(&motor),
      currentDuty(0)
{
    values.ideal = idealLightValue;
    motor.setDutyCycle(currentDuty);
    motor.forward();
    t = SmartTimer::Timer(100);
    t.reset();
}

void IntelligentLightSystem::printSerialValues()
{
    Serial.println("Outside: " + String(values.outside));
    Serial.println("Inside: " + String(values.inside));
}

void IntelligentLightSystem::updateValues()
{
    values.inside = inside.getRawValue();
    values.outside = outside.getRawValue();
}

int IntelligentLightSystem::getModifyGradient()
{
    int difference = (values.ideal - (values.inside + values.outside));
    bool isPositive = difference > 0;

    if (abs(difference) <= threshold)
    {
        return 0;
    }

    return isPositive ? 1 : -1;
}

void IntelligentLightSystem::update(bool verbose = false)
{

    if (!t.hasIntervalPassed())
    {
        return;
    }

    updateValues();

    if (mode == Mode::NORMAL)
    {

        currentDuty = 255;
        motor->setDutyCycle(255);
        return;
    }

    int gradient = getModifyGradient();
    int change = changeFactor * gradient;
    int nextDuty = change + currentDuty;

    // Check bounds
    if (nextDuty < 0 or 255 < nextDuty)
    {
        return;
    }

    if (verbose)
    {
        Serial.println(
            "G:" + String(change) +
            "|N:" + String(nextDuty));
    }

    currentDuty = nextDuty;

    motor->setDutyCycle(currentDuty);

    t.reset();
}

static float coefficients[] = {
    0.00437876,
    -0.01385081, 0.00541345};

float LightSystem::voltageToCurrent(float voltage)
{

    if (voltage < 2.5)
    {
        return 0;
    }

    float modelCurrent = coefficients[0] + coefficients[1] * voltage + coefficients[2] * voltage * voltage;

    return modelCurrent < 0 ? 0 : modelCurrent;
}

void IntelligentLightSystem::changeMode(IntelligentLightSystem::Mode mode)
{
    this->mode = mode;
}

void IntelligentLightSystem::toggleMode()
{
    if (mode == Mode::SMART)
    {
        changeMode(Mode::NORMAL);
    }
    else
    {
        changeMode(Mode::SMART);
    }
}
