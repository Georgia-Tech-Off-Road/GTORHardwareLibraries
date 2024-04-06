#include "StrainGauge.h"

void StrainGauge::update_data(){
    //set_data(-4*(get_voltage())/(2.1*(1+2*get_voltage())));
    double offset = 2.5; // voltage offset 
    double gain = 32.333333; // amplifies the voltage 
    double GF = 2.0; // gauge factor 
    double voltage = (get_voltage()-offset)/gain; // actual voltage difference across wheatstone bridge
    float R1 = ((5 * 350) / (voltage + 2.5)) - 350;
    float deltaR = (R1 - 350); // delta R
    float strain = ((deltaR / 350)) / GF;
    // float v_unstrained = 0;  //initial unstrained voltage
    // float v_ex = 3.3;
    // float v_r = (voltage - v_unstrained)/(v_ex);
    // float strain = (-4*v_r)/(GF+(1+2*v_r));
    uint64_t youngs_modulus = 70000000000; //youngs modulus of aluminum;
    float length = 0.0127;
    float width = 0.002;
    float area = width * length; //cross sectional area of material that gauge is on;
    float force = strain * area * youngs_modulus;

    set_data(strain);
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