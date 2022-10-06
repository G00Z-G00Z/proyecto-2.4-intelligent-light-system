#pragma once
#include <RBD_LightSensor.h>

namespace VoltageAnalog
{

    /**
     * @brief Reads an analoge input and returns the voltage
     *
     */
    class Reader : private RBD::LightSensor
    {

    public:
        Reader(int pin) : RBD::LightSensor(pin) {}
        float getVoltage();
    };

};
