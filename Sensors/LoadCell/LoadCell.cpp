#include "LoadCell.h"

void LoadCell::update_data(){
    set_data(this->get_voltage()*_scale + _offset);
}

void LoadCell::tare(){
    ADC& adc = *(this->get_adc());
    adc.update_sensor(*this);
    _offset -= this->get_data();
}

void LoadCell::set_scale(float scale) {
    _scale = scale;
}

float LoadCell::get_scale() {
    return _scale;
}
