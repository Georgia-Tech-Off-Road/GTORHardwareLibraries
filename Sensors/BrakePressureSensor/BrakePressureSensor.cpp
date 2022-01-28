#include "BrakePressureSensor.h"

void BrakePressureSensor::set_raw(float raw) {
    this->_raw = raw;
    float volt = this->get_voltage();
    float pressure = (volt - 0.5) * 500;
    if (pressure < 0) {
        pressure = 0;
    }
    this->set_data(pressure);
}