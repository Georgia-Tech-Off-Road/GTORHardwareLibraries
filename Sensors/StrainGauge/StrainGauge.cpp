#include "StrainGauge.h"

void StrainGauge::update_data(){


    set_data(-4*(get_voltage())/(2.1*(1+2*get_voltage())));
}

void StrainGauge::tare(){
    ADC& adc = *(this->get_adc());
    adc.update_sensor(*this);
    _offset -= this->get_data();
}

void StrainGauge::set_scale(float scale) {
    _scale = scale;
}

float StrainGauge::get_scale() {
    return _scale;
}