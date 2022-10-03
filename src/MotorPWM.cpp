#include <MotorPWM.h>

using namespace Driver;

MotorPWM::MotorPWM(int pinEnable, int pin1, int pin2) : pinEnable(pinEnable), Motor_RS(pin1, pin2)
{
    setDutyCycle(0);
}

void MotorPWM::setDutyCycle(unsigned char dutyCycle)
{
    analogWrite(pinEnable, dutyCycle);
}
