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

#ifndef DIGITALSENSOR_H
#define DIGITALSENSOR_H

#include <Block.h>

class DigitalSensor : public Block<bool>{
private:
    uint8_t _pin;
    uint8_t _mode;
public:
    DigitalSensor() : _pin(-1), _mode(INPUT) {}

    void begin(uint8_t pin, uint8_t mode = INPUT) {
        _pin = pin;
        _mode = mode;
        pinMode(_pin, _mode);
    }
    void update() { 
        this->set_data(digitalRead(_pin));
    }
};

#endif
