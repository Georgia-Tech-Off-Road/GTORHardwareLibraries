#ifndef DIGITALOUTPUT_H
#define DIGITALOUTPUT_H

#include <functional>
#include "Block.h"

#define MAKE_CB(cb) ([](){ return cb; })

class DigitalOutput : public Block<bool> {
private:
    uint8_t _pin;
    std::function<bool()> _setcb;
    std::function<bool()> _flipcb;

public:
    DigitalOutput() : _pin(-1), _setcb(NULL), _flipcb(NULL) { }

    void begin(uint8_t pin, uint8_t init_state = 0){
        _pin = pin;
        _setcb = NULL;
        _flipcb = NULL;
        this->set_data(init_state);
        pinMode(_pin, OUTPUT);
        digitalWrite(_pin, this->get_data());
    }

    void set(bool state) { 
        set_data(state);
        if(_pin != -1) digitalWrite(_pin, this->get_data()); 
    }
    void on () { set(1); }
    void off() { set(0); }
    void flip() { set(!this->get_data()); }

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