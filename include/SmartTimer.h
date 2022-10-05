#pragma once

/**
 * @brief Smart timer has functions that use millis() function to create custom
 * timers that do not require delay()
 *
 */
namespace SmartTimer
{
    using time = unsigned long;

    /**
     * @brief Timer that saves an interval and tells you when has the interval
     * passed
     *
     */
    class Timer
    {
        time interval_ms;
        time startTime;

    public:
        Timer();
        Timer(time interval);

        void reset();

        bool hasIntervalPassed();
    };

};
