#include "TeensyADC.h"

void TeensyADC::attach_sensor(BaseAnalogSensor& sensor, uint8_t port){
    // Check to see if something is already attached on the port.
    for (auto it = _sensors.begin(); it != _sensors.end(); it++){
        if((*it)->get_port() == port)
            return;
    }
    sensor.set_port(port);
    sensor.set_vrange(0, 3.3);
    sensor.set_adc(this);
    _sensors.push_back(&sensor);
}

void TeensyADC::update_sensors() {
	for(auto it = _sensors.begin(); it != _sensors.end(); ++it){
		this->update_sensor(*(*it));
	}
}

void TeensyADC::update_sensor(BaseAnalogSensor& sensor) {
    float a = analogRead(sensor.get_port());
    sensor.set_raw(a / get_max());
}

void TeensyADC::update_sensor(uint8_t port) {
    for (auto it = _sensors.begin(); it != _sensors.end(); it++){
        if((*it)->get_port() == port) {
            update_sensor(*(*it));
            return;
        }
    }
}

uint32_t TeensyADC::get_max() {
    return 1023;
}
