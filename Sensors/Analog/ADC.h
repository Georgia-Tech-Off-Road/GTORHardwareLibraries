#ifndef ADC_H 
#define ADC_H

#include "Arduino.h"
#include <vector>
#include "AnalogSensor.h"

class BaseAnalogSensor;

class ADC {
protected:
	std::vector<BaseAnalogSensor*> _sensors;

public:
	virtual void attach_sensor(BaseAnalogSensor& sensor, uint8_t port) = 0;
	virtual void update_sensors() = 0;
	virtual void update_sensor(BaseAnalogSensor& sensor) = 0;
	virtual void update_sensor(uint8_t port) = 0;
	virtual uint32_t get_max() = 0;
};

#endif