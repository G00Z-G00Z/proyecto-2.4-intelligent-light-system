#include <LightSystem.h>
#include <Arduino.h>
#include <RBD_LightSensor.h>

using namespace LightSystem;

IntelligentLightSystem::IntelligentLightSystem(int pinInside, int pinOutside) : inside(pinInside), outside(pinOutside)
{
}

void IntelligentLightSystem::printSerialValues()
{
    Serial.println("Outside: " + String(outside.getRawValue()));
    Serial.println("Inside: " + String(inside.getRawValue()));
}
