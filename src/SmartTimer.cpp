#include <SmartTimer.h>
#include <Arduino.h>

using namespace SmartTimer;

Timer::Timer(){};

Timer::Timer(time interval_ms) : interval_ms(interval_ms)
{
    startTime = millis();
}

void Timer::reset()
{
    startTime = millis();
}

bool Timer::hasIntervalPassed()
{
    return millis() - startTime >= interval_ms;
}