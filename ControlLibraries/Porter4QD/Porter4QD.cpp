#ifndef PORTER4QD_CPP
#define PORTER4QD_CPP

#include "Porter4QD.h"

Porter4QD::Porter4QD(uint8_t throttle_pin, uint8_t enable_pin, float scale, float offset){
    _throttle_pin = throttle_pin;
    _enable_pin = enable_pin;
    _scale = scale;
    _offset = offset;
}

void Porter4QD::begin(){
    pinMode(_throttle_pin, OUTPUT);
    pinMode(_enable_pin, OUTPUT);
    _enabled = false;
    digitalWrite(_enable_pin, LOW);
}

void Porter4QD::setSpeed(uint8_t speed){
    if (!_enabled) {
        _enabled = true;
        digitalWrite(_enable_pin, HIGH);
    }
    uint8_t scaled_speed = max(min((speed * _scale + _offset), 255), 0);
    analogWrite(_throttle_pin, scaled_speed);
}

void Porter4QD::kill(){
    _enabled = false;
    digitalWrite(_enable_pin, LOW);
    analogWrite(_throttle_pin, 0);
}

#endif
