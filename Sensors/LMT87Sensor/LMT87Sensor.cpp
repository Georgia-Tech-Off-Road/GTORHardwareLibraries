#include "LMT87Sensor.h"
#define v2 0.538
#define v1 3.121
#define t2 150
#define t1 -37


void LMT87Sensor::set_raw(float raw) {
    this->_raw = raw;
    //returns voltage outputed by LMT87Sensor in volts?
    float volt = this->get_voltage();
    float temp;
    //calculates temperature in celsius
    temp =  (volt - v1)*((t2-t1)/(v2-v1))+t1;
    // temp = (int)temp;

    this->set_data(temp);


    

    
}