#ifndef PORTER4QD_H
#define PORTER4QD_H

#include <Arduino.h>
#include <Sensor.h>

class Porter4QD {
private:
    uint8_t _pin;
    uint8_t _offset;
    float _scale;

public:
    Porter4QD(uint8_t pin, uint8_t offset = 0, float scale = 1);
    void begin();
    void setSpeed(uint8_t speed);
    void kill();
};

#endif
