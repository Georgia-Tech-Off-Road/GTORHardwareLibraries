#ifndef DIGITALOUTPUT_H
#define DIGITALOUTPUT_H

#include <functional>

#define MAKE_CB(cb) ([](){ return cb; })

class DigitalOutput {
private:
    uint8_t _pin;
    uint8_t _state;
    std::function<bool()> _setcb;
    std::function<bool()> _flipcb;

public:
    DigitalOutput() : _pin(-1), _state(0), _setcb(NULL), _flipcb(NULL) { }

    void begin(uint8_t pin, uint8_t init_state = 0){
        _pin = pin;
        _setcb = NULL;
        _flipcb = NULL;
        _state = init_state;
        pinMode(_pin, OUTPUT);
        digitalWrite(_pin, _state);
    }

    void set(bool set) { digitalWrite(_pin, set); }
    void on () { set(1); }
    void off() { set(0); }
    void flip() { _state = !_state; set(!_state); }

    void set_setcb(std::function<bool()> setcb) {
        _setcb = setcb;
    }
    void set_flipcb(std::function<bool()> flipcb) {
        _flipcb = flipcb;
    }

    void update() {
        if(_setcb) {
            set(_setcb());
        } 
        if (_flipcb) {
            if(_flipcb()) flip();
        }
    }
};

#endif