#include "LEDControl.h"

LEDControl::LEDControl(uint8_t pin, float freq) : _state(0), _pin(pin), _freq(freq) {
    _period = (1/freq) / 2;
    _last_updated = micros();
}

void LEDControl::begin(){
    pinMode(_pin, OUTPUT);
}

void LEDControl::update(){
    if (abs(micros() - _last_updated) > _period){
        _state = !_state;
        digitalWrite(_pin, _state);
    }
}