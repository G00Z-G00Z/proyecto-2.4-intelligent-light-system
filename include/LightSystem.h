#pragma once
#include <RBD_LightSensor.h>

namespace LightSystem
{
    class IntelligentLightSystem
    {

        RBD::LightSensor inside;
        RBD::LightSensor outside;

    public:
        IntelligentLightSystem(int pinInside, int pinOutside);

        void printSerialValues();
    };
};
