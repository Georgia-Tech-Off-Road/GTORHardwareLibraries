#ifndef ANALOGSENSOR_H
#define ANALOGSENSOR_H

#include "Arduino.h"
#include <type_traits>
#include "ADC.h"
#include "Block.h"

class ADC;

class BaseAnalogSensor : public BaseBlock {
protected:
	float _raw;
	uint8_t _port;
	float _vmin;
	float _vmax;
	ADC* _adc;

public:
	void set_port(uint8_t port);
	void set_vrange(float vmin, float vmax);
	void set_adc(ADC* adc);
	
	// Need to implement for individual sensors.
	// raw is normalized from 0.0-1.0, need to set_data here.
	virtual void set_raw(uint32_t raw) = 0;


	uint8_t get_port();
	ADC* get_adc();
	uint32_t get_raw();
	float get_voltage();

};

template <typename DataType>
class AnalogSensor : public Block<DataType>,
					 public BaseAnalogSensor {
public:
	void update();
};

#include "AnalogSensorTypes.h"

#endif