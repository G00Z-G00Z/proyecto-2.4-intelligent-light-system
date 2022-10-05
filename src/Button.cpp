#include <Button.h>
#include <Arduino.h>

using namespace Buttons;

Button::Button()
{
}

Button::Button(int pin) : pin(pin)
{
    pinMode(this->pin, INPUT);
}

int Button::read()
{
    return digitalRead(pin);
}

bool Button::isBeignClicked()
{
    return this->read() == HIGH;
}

bool Button::wasPressed()
{

    bool wasPressed = false;

    // Debouncing
    while (this->isBeignClicked())
    {
        wasPressed = true;
    }

    return wasPressed;
}
