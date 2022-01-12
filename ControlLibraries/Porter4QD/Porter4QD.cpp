#ifndef PORTER4QD_CPP
#define PORTER4QD_CPP

#include "Porter4QD.h"

Porter4QD::Porter4QD(uint8_t pin, uint8_t offset = 0, float scale = 1){
    _pin = pin;
    _offset = offset;
    _scale = scale;
}

void Porter4QD::begin(){
    pinMode(_pin, OUTPUT);
}

void Porter4QD::setSpeed(uint8_t speed){
    uint8_t scaled_speed = max( min( (speed * _scale + _offset), 255), 0);
    analogWrite(_pin, scaled_speed);
}

void Porter4QD::kill(){
    analogWrite(_pin, 0);     
}

#endif
