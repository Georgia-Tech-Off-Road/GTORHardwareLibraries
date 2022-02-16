/**
 * ADS8688.h
 * A library to work with ADS8688.
 * 
 * ------ Constructor ------
 * ADS8688 adc(uint8_t CSPin);
 * 
 * CSPin -> The chip select pin, maybe set to 10?
 * 
 * ------ Usage ------
 * adc.attach_sensor(sensor, port);
 *      - This will attach a sensor to a port on the adc
 * 
 * adc.set_port_vrange(port, vrange);
 * 		- This will set the voltage range of a specific port on the adc
<<<<<<< HEAD
 * 		- vrange input must be of the form ADS8688::VOLTAGE_RANGE::SIGNED_5V12
 * 		- port is an integer from 0 - 7
=======
 * 		- vrange must be
>>>>>>> main
 * 
 * int temp_data = temp.get_data();
 *      - This will read the data from the ADC that the LMT87Sensor is attached to and return it
 * 
 * temp.update();
 *      - This will update the sensor to be used by the communication utility
 */
#ifndef ADS8688_H
#define ADS8688_H

#include "Arduino.h"
#include "ADC.h"

#include <SPI.h>

class ADS8688 : public ADC {
private:
// Command Register
// RESISTER_SELECT B[15:8] | 0 B[7:0]
    typedef enum {
        NO_OP =    0x0000,
		STDBY =    0x8200,
		PWR_DN =   0x8300,
		RST =      0x8500,
		AUTO_RST = 0xA000,
		MAN_Ch_0 = 0xC000,
		MAN_Ch_1 = 0xC400,
		MAN_Ch_2 = 0xC800,
		MAN_Ch_3 = 0xCC00,
		MAN_Ch_4 = 0xD000,
		MAN_Ch_5 = 0xD400,
		MAN_Ch_6 = 0xD800,
		MAN_Ch_7 = 0xDC00,
		MAN_AUX =  0xE000
    } command_reg_t;

// Program Register
// RESISTER_SELECT B[15:9] | R/W | REGISTER_DATA B[7:0]
	typedef enum {
		AUTO_SEQ_EN_R = 0x02, //Used to enable channels to be read from automatically
		AUTO_SEQ_EN_W = 0x03,
		CHANNEL_POWER_DOWN_R = 0x04, //Used to power down chosen channels
		CHANNEL_POWER_DOWN_W = 0x05,
		FEATURE_SELECT_R = 0x06, //Used for Daisy Chain
		FEATURE_SELECT_W = 0x07,
		//The below things can change the input voltage range
		//REGISTER_DATA B[7:4] = 0
		//REGISTER_DATA B[3:0] = 
		// 0000 for input range = +-2.5*VREF
		// 0001 for input range = +-2.5*VREF
		// 0010 for input range = +-2.5*VREF
		// 0101 for input range = +-2.5*VREF
		// 0110 for input range = +-2.5*VREF
		CH0 = 0x0B, 
		CH1 = 0x0D,
		CH2 = 0x0F,
		CH3 = 0x11,
		CH4 = 0x13,
		CH5 = 0x15,
		CH6 = 0x17,
		CH7 = 0x19,
		COMMAND_READ_BACK = 0x7E //Reads back the command word (MSB) executed in previous data frame
	} program_reg_t;

	uint8_t _CSPin;
	//Contains the min and max voltage, index of array = channel number
	//Ex: Channel # minimum voltage = _vmin[#]
	float _vmin[8] = {0,0,0,0,0,0,0,0};
	float _vmax[8] = {5.12,5.12,5.12,5.12,5.12,5.12,5.12,5.12};


public:
	// Range Select Channel
	// 0000 - +-10.24V
	// 0001 - +-5.12V
	// 0010 - +-2.56V
	// 0101 - 0-10.24V
	// 0110 - 0-5.12V
	typedef enum {
		SIGNED_10V24 =   0b00000000,
		SIGNED_5V12 =    0b00000001,
		SIGNED_2V56 =    0b00000010,
		UNSIGNED_10V24 = 0b00000101,
		UNSIGNED_5V12 =  0b00000110
	} VOLTAGE_RANGE;


	ADS8688(uint8_t CSPin);
	void begin();
	void attach_sensor(BaseAnalogSensor& sensor, uint8_t port);
	void update_sensors();
	void update_sensor(BaseAnalogSensor& sensor);
	void update_sensor(uint8_t port);
	void set_port_vrange(uint8_t port, VOLTAGE_RANGE vrange);
	void update_sensor_vrange();
	uint16_t get_sample(command_reg_t port);
	uint32_t get_max();
};

#endif