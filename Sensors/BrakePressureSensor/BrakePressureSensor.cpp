#include "BrakePressureSensor.h"

void BrakePressureSensor::update_data() {
    float pressure = (this->get_voltage() - 0.5) * 500;
    if (pressure < 0) {
        pressure = 0;
    }
    this->set_data(pressure);
}