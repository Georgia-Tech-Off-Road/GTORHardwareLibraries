#include "Potentiometer.h"

template <typename DataType>
Potentiometer<DataType>::Potentiometer(uint16_t full_scale_range, bool is_reversed) {
        _full_scale_range = full_scale_range;
        _is_reversed = is_reversed;
}
    
template <typename DataType>
void Potentiometer<DataType>::set_raw(float raw) {
    this->_raw = raw;
    if (std::is_same<DataType, uint32_t>::value || std::is_same<DataType, uint16_t>::value || std::is_same<DataType, uint8_t>::value){
        // If DataType is uint32_t, uint16_t, or uint8_t, then return the number of degrees of the potentiometer from 0-255, 0-65535,
        // or 0-4294967295 respectively
        if(_is_reversed){
            this->set_data(round(this->_raw * _full_scale_range) * -1 + _full_scale_range);
        } else {
            this->set_data(round(this->_raw * _full_scale_range));
        }
    } 
    else if (std::is_same<DataType, float>::value || std::is_same<DataType, double>::value){
        // If DataType is float, then return the number of degrees of the potentiometer from 0-_full_scale_range
        if(_is_reversed){
            this->set_data(this->_raw * _full_scale_range * -1 + _full_scale_range);
        } else {
            this->set_data(this->_raw * _full_scale_range);
        }
    }
}