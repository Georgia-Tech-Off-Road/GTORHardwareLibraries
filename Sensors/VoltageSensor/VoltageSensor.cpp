#include "VoltageSensor.h"

    
template <typename DataType>
void VoltageSensor<DataType>::set_raw(float raw) {
    this->_raw = raw;
    this->set_data(this->get_voltage());
}