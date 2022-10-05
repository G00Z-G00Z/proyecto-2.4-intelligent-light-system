#pragma once
#include <SmartTimer.h>
#include <RBD_LightSensor.h>
#include <MotorPWM.h>

namespace LightSystem
{

    /**
     * @brief Intelligente light systema that regulates a room light
     * For the light sensors, 0 -> darkess, 1023 -> Light
     */
    class IntelligentLightSystem
    {

        SmartTimer::Timer t;

        struct LightValues
        {
            int inside;
            int outside;
            int ideal;
        };

        RBD::LightSensor inside;
        RBD::LightSensor outside;

        LightValues values;

        Driver::MotorPWM *motor;

        int currentDuty;

        /**
         * @brief Gets the sum of the inside and the outside values, and
         * returns a 1 the light source must increase, 0 if its good, and -1 if
         * it should decrease
         *
         * @return int
         */
        int getModifyGradient();

        void updateValues();

    public:
        IntelligentLightSystem(int pinInside, int pinOutside, Driver::MotorPWM &motor, int idealLightValue);

        void printSerialValues();

        /**
         * @brief Updates the values and the pwm every 100ms. You must call it
         * without delays
         *
         */
        void update();
    };

};
