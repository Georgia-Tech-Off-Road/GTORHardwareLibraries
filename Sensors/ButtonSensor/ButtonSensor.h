/**
 * ButtonSensor.h
 * A library to work with buttons to measure if they've been pressed
 * 
 * ------ Constructor ------
 * ButtonSensor button;
 * 
 * ------ Usage ------
 * button.begin();
 *      - This will initialize the Teensy hardware so that the button sensor can work
 * 
 * bool button_state = button.get_data();
 *      - This will read the state of the button
 * 
 * button.update();
 *      - This will update the sensor to be used by the communication utility
 */

#ifndef BUTTONSENSOR_H
#define BUTTONSENSOR_H

#include <Block.h>

class ButtonSensor : public Block<bool>{
private:
    uint8_t _pin;
public:
    ButtonSensor(uint8_t pin) : _pin(pin){}

    void begin() pinMode(_pin, INPUT);    
    void update() this->set_data(digitalRead(_pin));
};

#endif
