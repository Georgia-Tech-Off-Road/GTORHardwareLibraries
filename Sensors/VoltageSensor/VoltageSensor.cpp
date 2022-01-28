#include "VoltageSensor.h"

    
template <typename DataType>
void VoltageSensor<DataType>::update_data() {
    this->set_data(this->get_voltage());
}