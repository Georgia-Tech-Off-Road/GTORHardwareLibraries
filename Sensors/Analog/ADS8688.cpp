#include "TeensyADC.h"
#include <Arduino.h>

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
		float a = analogRead((*it)->get_port());
		(*it)->set_raw(a / get_max());
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

uint16_t ADS8688::get_channel_voltage(command_reg_t channel){
    uint16_t channel_voltage = 0;
    SPI.beginTransaction(SPISettings(17000000, MSBFIRST, SPI_MODE0)); // Might be mode 1
    digitalWrite(_CSPin, LOW);
    SPI.transfer16(channel);
    SPI.transfer16(0);
    digitalWrite(_CSPin, HIGH);
    SPI.endTransaction();

    SPI.beginTransaction(SPISettings(17000000, MSBFIRST, SPI_MODE0)); // Might be mode 1
    digitalWrite(_CSPin, LOW);
    SPI.transfer16(NO_OP);
    channel_voltage = SPI.transfer16(0);
    digitalWrite(_CSPin, HIGH);
    SPI.endTransaction();
    return channel_voltage;
}
