#include "AnalogSensor.h"

void BaseAnalogSensor::set_port(uint8_t port){
	_port = port;
}

void BaseAnalogSensor::set_vrange(float vmin, float vmax){
	_vmin = vmin;
	_vmax = vmax;
}

uint8_t BaseAnalogSensor::get_port() {
	return _port;
}

ADC* BaseAnalogSensor::get_adc() {
	return _adc;
}

uint32_t BaseAnalogSensor::get_raw() {
	return _raw;
}

float BaseAnalogSensor::get_voltage() {
	return _vmin + _raw * (_vmax - _vmin);
}

template <typename DataType>
void AnalogSensor<DataType>::update() {
	_adc->update_sensor(*this);
}
