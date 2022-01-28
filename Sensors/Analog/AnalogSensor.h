#ifndef ANALOGSENSOR_H
#define ANALOGSENSOR_H

#include "Arduino.h"
#include "ADC.h"
#include "Block.h"

class ADC;

class BaseAnalogSensor {
protected:
	float _raw;
	uint8_t _port;
	float _vmin;
	float _vmax;
	ADC* _adc;
	// Need to implement for individual sensors, it will use either this->get_voltage() or
	// this->get_raw() to get the current voltage or normalized "voltage" (a number from 
	// 0 to 1) to do this->set_data() with the current data in whatever units makes sense
	// for that given sensor.
	virtual void update_data() = 0;

public:
	void set_port(uint8_t port);
	void set_vrange(float vmin, float vmax);
	void set_adc(ADC* adc);
	void set_raw(float raw);	
	
	uint8_t get_port();
	ADC* get_adc();
	float get_raw();	
	float get_voltage();

	friend class ADC;
};

template <typename DataType>
class AnalogSensor : public BaseAnalogSensor, public Block<DataType> {
protected:
	virtual void update_data() = 0;

public:
	void update();
};

#include "AnalogSensorTypes.h"

#endif