#ifndef ADS8688_H
#define ADS8688_H

#include "ADC.h"

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
		CH0 = 0x0B,
		CH1 = 0x0D,
		CH2 = 0x0F,
		CH3 = 0x11,
		CH4 = 0x13,
		CH5 = 0x15,
		CH6 = 0x17,
		CH8 = 0x19
	} program_reg_t;

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
	}

	uint8_t _CSPin;

public:
	ADS8688(uint8_t CSPin);
	void attach_sensor(BaseAnalogSensor& sensor, uint8_t port);
	void update_sensors();
	void update_sensor(BaseAnalogSensor& sensor);
	void update_sensor(uint8_t port);
	uint32_t get_max();
	uint16_t get_channel_voltage(uint8_t channel);
};

#endif