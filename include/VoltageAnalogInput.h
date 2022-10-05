#pragma once
#include <RBD_LightSensor.h>

namespace VoltageAnalog
{

    class Reader : private RBD::LightSensor
    {

    public:
        Reader(int pin) : RBD::LightSensor(pin) {}
        float getVoltage();
    };

};
