#pragma once
#include <Motor_RS.h>

/**
 * @brief Driver l293d
 *
 */
namespace Driver
{

    class MotorPWM : public Motor_RS
    {

        int pinEnable;

    public:
        MotorPWM(int pinEnable, int pin1, int pin2);

        void setDutyCycle(unsigned char duty);
    };

};
