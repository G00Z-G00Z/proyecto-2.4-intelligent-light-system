#include <LightSystem.h>
#include <math.h>
#include <Arduino.h>
#include <RBD_LightSensor.h>
#include <MotorPWM.h>

using namespace LightSystem;

static const int threshold = 5;
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
    int difference = (values.ideal - values.inside + values.outside);
    bool isPositive = difference > 0;

    if (abs(difference) <= threshold)
    {
        return 0;
    }

    return isPositive ? 1 : -1;
}

void IntelligentLightSystem::update()
{
    updateValues();
    int gradient = getModifyGradient();
    int change = changeFactor * gradient;
    int nextDuty = change + currentDuty;

    Serial.println("Calculating gradient:" + String(gradient) + "/" + String(currentDuty) + "/" + String(nextDuty));

    // Check bounds
    if (nextDuty < 0 or 255 < nextDuty)
    {
        return;
    }

    currentDuty = nextDuty;

    motor->setDutyCycle(currentDuty);
}
