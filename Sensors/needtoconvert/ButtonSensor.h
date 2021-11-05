#ifndef BUTTONSENSOR_H
#define BUTTONSENSOR_H

#include <Sensor.h>

class ButtonSensor : public Sensor<bool>{
private:
    uint8_t _pin;
public:
    ButtonSensor(){
        _pack_bytes = sizeof(bool);
    }

    ButtonSensor(uint8_t pin) : _pin(pin){
        _pack_bytes = sizeof(bool);
    }

    void set_pin(uint8_t pin){
        _pin = pin;
    }

    uint8_t get_pin() {
        return _pin;
    }

    void begin(){
        pinMode(_pin, INPUT);
    }

    const bool& get_data (){
        if (_type == ACTIVE) {
            _data = digitalRead(_pin);
        }
        return _data;
    }

    void pack(byte* pack){
        *((bool*)pack) = _data;
    }

    void unpack(const byte* pack){
        _data = *((bool*)pack);
    }
};

#endif
