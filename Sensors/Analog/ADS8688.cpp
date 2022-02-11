#include <Arduino.h>
#include <SPI.h>
#include "ADS8688.h"

ADS8688::ADS8688(uint8_t CSPin){
    _CSPin = CSPin;
    for(uint8_t i = 0; i<8 ; i++){
        set_port_vrange(i, 1);
    }

}
void ADS8688::attach_sensor(BaseAnalogSensor& sensor, uint8_t port){
    // Check to see if something is already attached on the port.
    for (auto it = _sensors.begin(); it != _sensors.end(); it++){
        if((*it)->get_port() == port)
            return;
    }
    sensor.set_port(port);
    sensor.set_vrange(0, 5.12);
    sensor.set_adc(this);
    _sensors.push_back(&sensor);
}

uint32_t ADS8688::get_max() {
    return 65535;
}

void ADS8688::set_port_vrange(uint8_t port, uint8_t vrange) {
    // 5 = +-10.24V
    // 4 = +-5.12V
    // 3 = +-2.56V
    // 2 = 0-10.24V
    // 1 = 0-5.12V
    voltage_reg_t voltage_range = UNSIGNED_5V12;
    program_reg_t reg_port;
    switch (vrange) {
        case 1:
            voltage_range = UNSIGNED_5V12;
            _vmin[port] = 0;
            _vmax[port] = 5.12;
            break;
        case 2:
            voltage_range = UNSIGNED_10V24;
            _vmin[port] = 0;
            _vmax[port] = 10.24;
            break;
        case 3:
            voltage_range = SIGNED_2V56;
            _vmin[port] = -2.56;
            _vmax[port] = 2.56;
            break;
        case 4:
            voltage_range = SIGNED_5V12;
            _vmin[port] = -5.12;
            _vmax[port] = 5.12;
            break;
        case 5:
            voltage_range = SIGNED_10V24;
            _vmin[port] = -10.24;
            _vmax[port] = 10.24;
            break;
        default:
            break;
    }

    switch (port) {
        case 0:
            reg_port = CH0;
            break;
        case 1:
            reg_port = CH1;
            break;
        case 2:
            reg_port = CH2;
            break;
        case 3:
            reg_port = CH3;
            break;
        case 4:
            reg_port = CH4;
            break;
        case 5:
            reg_port = CH5;
            break;
        case 6:
            reg_port = CH6;
            break;
        case 7:
            reg_port = CH7;
            break;
        default:
            break;
    }

    uint16_t write_message = (reg_port << 9) | (1 << 8) | voltage_range;

    SPI.beginTransaction(SPISettings(17000000, MSBFIRST, SPI_MODE0)); // Might be mode 1
    digitalWrite(_CSPin, LOW);
    SPI.transfer16(write_message);
    SPI.transfer(0);// if writing, contains data written, if reading contains data in addressed register
    digitalWrite(_CSPin, HIGH);
    SPI.endTransaction();

    update_sensor_vrange(); // updates vrange for each sensor
}

void ADS8688::update_sensor_vrange(){
    // goes through each sensor and updates their vrange.
    for (auto it = _sensors.begin(); it != _sensors.end(); it++){
        (*it)->set_vrange(_vmin[(*it)->get_port()], _vmax[(*it)->get_port()]);
    }
}

uint16_t ADS8688::get_sample(command_reg_t port){
    uint16_t port_voltage = 0;
    SPI.beginTransaction(SPISettings(17000000, MSBFIRST, SPI_MODE0)); // Might be mode 1
    digitalWrite(_CSPin, LOW);
    SPI.transfer16(port);
    SPI.transfer16(NO_OP);
    digitalWrite(_CSPin, HIGH);
    SPI.endTransaction();

    SPI.beginTransaction(SPISettings(17000000, MSBFIRST, SPI_MODE0)); // Might be mode 1
    digitalWrite(_CSPin, LOW);
    SPI.transfer16(NO_OP);
    port_voltage = SPI.transfer16(NO_OP);
    digitalWrite(_CSPin, HIGH);
    SPI.endTransaction();
    return port_voltage;
}

void ADS8688::update_sensor(BaseAnalogSensor& sensor) {
    uint8_t port = sensor.get_port();
    int16_t sensor_voltage = 0;
    switch (port)
    {
    case 0:
        sensor_voltage = get_sample(MAN_Ch_0);
        break;
    case 1:
        sensor_voltage = get_sample(MAN_Ch_1);
        break;
    case 2:
        sensor_voltage = get_sample(MAN_Ch_2);
        break;
    case 3:
        sensor_voltage = get_sample(MAN_Ch_3);
        break;
    case 4:
        sensor_voltage = get_sample(MAN_Ch_4);
        break;
    case 5:
        sensor_voltage = get_sample(MAN_Ch_5);
        break;
    case 6:
        sensor_voltage = get_sample(MAN_Ch_6);
        break;
    case 7:
        sensor_voltage = get_sample(MAN_Ch_7);
        break;
    default:
        break;
    }
    if (sensor.get_vmin() < 0) {
        sensor.set_raw( ( ((float)sensor_voltage/(1 << 15)) + 1 ) / 2 );
    } else {
        sensor.set_raw( (float)((uint16_t)sensor_voltage) / get_max() );
    }
    
    sensor.update_data();
}

void ADS8688::update_sensors() {
	for(auto it = _sensors.begin(); it != _sensors.end(); ++it){
		this->update_sensor(*(*it));
	}
}

void ADS8688::update_sensor(uint8_t port) {
    for (auto it = _sensors.begin(); it != _sensors.end(); it++){
        if((*it)->get_port() == port) {
            update_sensor(*(*it));
            return;
        }
    }
}