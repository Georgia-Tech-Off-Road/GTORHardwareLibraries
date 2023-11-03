#include "StrainGauge.h"

void StrainGauge::update_data(){
    //set_data(-4*(get_voltage())/(2.1*(1+2*get_voltage())));
    float offset = 2.5;
    float gain = 32.333;
    float GF = 2.0;
    float voltage = (get_voltage()-offset)/gain; // actual voltage difference across wheatstone bridge
    float v_unstrained = 0;  //initial unstrained voltage
    float v_ex = 3.3;
    float v_r = (voltage - v_unstrained)/(v_ex);
    float strain = (-4*v_r)/(GF+(1+2*v_r));

    uint64_t youngs_modulus = 70000000000; //youngs modulus of aluminum;
    float length = 0.0125;
    float width = 0.00145;
    float area = width * length //cross sectional area of material that gauge is on;
    float force = strain * area * youngs_modulus;
    set_data(this->get_voltage());
}

void StrainGauge::tare(){
    ADC& adc = *(this->get_adc());
    adc.update_sensor(*this);
    _offset = this->get_data();
}

void StrainGauge::set_scale(float scale) {
    _scale = scale;
}

float StrainGauge::get_scale() {
    return _scale;
}