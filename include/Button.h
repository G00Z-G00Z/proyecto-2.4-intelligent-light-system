#pragma once

namespace Buttons
{

    /**
     * @brief Class that handles a button pin.
     *
     * @tparam pin The pin of the class
     */
    class Button
    {

    private:
        int pin = -1;

    public:
        Button();

        Button(int pin);

        /**
         * @brief Reads the current value of the class
         *
         * @return int
         */
        int read();
        /**
         * @brief Returs true if the button is HIGH
         *
         * @return true
         * @return false
         */
        bool isBeignClicked();
        /**
         * @brief Debounces, and checks if the button has been released or hastn been pressed
         *
         * @return true
         * @return false
         */
        bool wasPressed();
    };

};
