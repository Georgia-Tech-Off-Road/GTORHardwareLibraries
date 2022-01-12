#include "VoltageSensor.h"

    
template <typename DataType>
void VoltageSensor<DataType>::set_raw(float raw) {
    this->_raw = raw;
    if (std::is_same<DataType, int8_t>::value || std::is_same<DataType, uint8_t>::value){
        // If DataType is uint32_t, uint16_t, or uint8_t, then return the number of degrees of the potentiometer from 0-255, 0-65535,
        // or 0-4294967295 respectively
        this->set_data(round(this->_raw * _full_scale_range));
    } 
    else if (std::is_same<DataType, float>::value>::value){
        // If DataType is float, then return the number of degrees of the potentiometer from 0-_full_scale_range
        this->set_data(this->_raw * _full_scale_range);
    }
}