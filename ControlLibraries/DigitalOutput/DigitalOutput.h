#ifndef DIGITALOUTPUT_H
#define DIGITALOUTPUT_H

#include <functional>

class DigitalOutput {
private:
    uint8_t _pin;
    std::function<bool()> _setcb;

public:
    void begin(uint8_t pin, std::function<bool()> setcb = NULL){
        _pin = pin;
        _setcb = setcb;
        pinMode(_pin, OUTPUT);
    }
    void set(bool set) { digitalWrite(_pin, set); }
    void on () { set(1); }
    void off() { set(0); }
    void update() {
        if(_setcb) {
            set(_setcb());
        }
    }
};

#endif