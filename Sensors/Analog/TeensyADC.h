#ifndef TEENSYADC_H
#define TEENSYADC_H

#include "ADC.h"

class TeensyADC : public ADC {
public:
	void attach_sensor(BaseAnalogSensor& sensor, uint8_t port);
	void update_sensors();
	void update_sensor(BaseAnalogSensor& sensor);
	void update_sensor(uint8_t port);
	uint32_t get_max();
};

#endif