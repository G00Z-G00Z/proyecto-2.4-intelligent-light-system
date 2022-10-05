#include <VoltageAnalogInput.h>

using namespace VoltageAnalog;

static float referenceVoltage = 5.0f;

float Reader::getVoltage()
{

    return (float)(this->getPercentValue()) / 100.0f * referenceVoltage;
}