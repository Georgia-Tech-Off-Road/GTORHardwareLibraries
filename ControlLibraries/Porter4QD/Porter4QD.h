#ifndef PORTER4QD_H
#define PORTER4QD_H

#include <Arduino.h>
//#include <Sensor.h>

/**
 * Porter4QD.h
 * A library to work with Porter Series motor controllers
 * 
 * ------ Constructor ------
 * Porter p(throttle_pin, enable_pin, scale, offset);
 * 
 * where:
 * - throttle_pin is an analog output pin that controls the speed of the motor
 * - enable_pin is a digital output pin that enables the controller
 * - offset and scale are values such that (speed*scale + offset) yields a value
 *   between 0 and 255 that maps (through external circuitry) to a voltage of
 *   between 1V and 4V, given that the range of analogWrite is from 0V to 3.3V.
 */

class Porter4QD {
private:
    uint8_t _throttle_pin;
    uint8_t _enable_pin;
    uint8_t _offset;
    float _scale;
    bool _enabled;

public:
    Porter4QD(uint8_t throttle_pin, uint8_t enable_pin, float scale, float offset);
    void begin();
    void setSpeed(uint8_t speed);
    void kill();
};

#endif
