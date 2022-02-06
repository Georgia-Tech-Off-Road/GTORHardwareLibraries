#include "LMT87Sensor.h"
#define v2 0.538
#define v1 3.121
#define t2 150
#define t1 -37


void LMT87Sensor::update_data() {
    //calculates temperature in celsius (voltage - 3.121)*((150 + 37)/(0.538 - 3.121)) - 37)
    this->set_data((this->get_voltage() - v1)*((t2-t1)/(v2-v1))+t1);
}