#ifndef TIMESENSOR_H
#define TIMESENSOR_H

#include <Block.h>

enum time_type_e {
    MILLIS, MICROS
};

class TimeSensor : public Block<uint32_t> {
private:
    time_type_e _time_type;
public:
    TimeSensor(time_type_e time_type = MICROS) : 
        _time_type(time_type) { }
    
    void begin() { update(); }

    void update() {
        if(_time_type == MICROS) _data = micros();
        else if (_time_type == MILLIS) _data = millis();
    }
};

#endif