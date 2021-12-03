#include <Arduino.h>
#include <SPI.h>

#include "ADS8332.h"

ADS8332::ADS8332(uint8_t _SelectPin, uint8_t _ConvertPin, uint8_t _EOCPin = -1) {
	SelectPin = _SelectPin;
	pinMode(ConvertPin, OUTPUT);
	digitalWrite(ConvertPin, HIGH);
	pinMode(SelectPin, OUTPUT);
	digitalWrite(SelectPin, HIGH);
	if(_EOCPin != -1) {
		pinMode(EOCPin, INPUT);
		manual_trigger = true;
	}
	Vref = 2.5;
	EOCTimeout = 100000;
	ConnectionSettings = SPISettings(12000000, MSBFIRST, SPI_MODE1);
	manual_trigger = false;
}

void ADS8332::attach_sensor(BaseAnalogSensor& sensor, uint8_t port) {
	// Check to see if something is already attached on the port.
    for (auto it = _sensors.begin(); it != _sensors.end(); it++) {
        if((*it)->get_port() == port)
            return;
    }
    sensor.set_port(port);
    sensor.set_vrange(0, 3.3);
    sensor.set_adc(this);
    _sensors.push_back(&sensor);
}

void ADS8332::update_sensors() {
	for(auto it = _sensors.begin(); it != _sensors.end(); ++it) {
		update_sensor(*(*it));
	}
}

void ADS8332::update_sensor(BaseAnalogSensor& sensor) {
	uint16_t a = 0;
	getSample(&a, sensor.get_port());
    sensor.set_raw(a / (float)get_max());
}

void ADS8332::update_sensor(uint8_t port) {
	for (auto it = _sensors.begin(); it != _sensors.end(); it++) {
        if((*it)->get_port() == port) {
            update_sensor(*(*it));
            return;
        }
    }
}

uint32_t ADS8332::get_max() {
	return 65535;
}

void ADS8332::setCommandBuffer(CommandRegister Command) {
	CommandBuffer = 0;
	CommandBuffer = ((uint16_t)static_cast<uint8_t>( Command )) << 12;
}

void ADS8332::begin() {
	setCommandBuffer(CommandRegister::WriteConfig);
	setConfiguration(ConfigRegisterMap::ChannelSelectMode, false);
	setConfiguration(ConfigRegisterMap::ClockSource, true);
	setConfiguration(ConfigRegisterMap::TriggerMode, manual_trigger);
	setConfiguration(ConfigRegisterMap::SampleRate, true);
	setConfiguration(ConfigRegisterMap::EOCINTPolarity, true);
	setConfiguration(ConfigRegisterMap::EOCINTMode, true);
	setConfiguration(ConfigRegisterMap::ChainMode, true);
	setConfiguration(ConfigRegisterMap::AutoNap, true);
	setConfiguration(ConfigRegisterMap::Nap, true);
	setConfiguration(ConfigRegisterMap::Sleep, true);
	setConfiguration(ConfigRegisterMap::TAG, true);
	setConfiguration(ConfigRegisterMap::Reset, true);
	sendCommandBuffer(true);
}

void ADS8332::reset() {
	begin();
}

void ADS8332::setConfiguration(ConfigRegisterMap Option, bool Setting) {
	bitWrite(CommandBuffer, static_cast<uint8_t>(Option), Setting);
}

void ADS8332::setVref(float NewVref) {
	Vref = NewVref;
}

float ADS8332::getVref() {
	return Vref;
}

uint16_t ADS8332::getConfig() {
	setCommandBuffer(CommandRegister::ReadConfig);
	return sendCommandBuffer(true);
	//return sendReadCommandBuffer();
}

void ADS8332::print_binary(uint32_t v) {
	int mask = 0;
	int n = 0;
	int num_places = 32;
	for (n=1; n<=num_places; n++) {
		mask = (mask << 1) | 0x0001;
	}
	v = v & mask;  // truncate v to specified number of places
	while(num_places) {
		if (v & (0x0001 << (num_places-1) )) {
			Serial.print("1");
		}
		else {
			Serial.print("0");
		}
		--num_places;
	}
}

uint16_t ADS8332::sendCommandBuffer(bool SendLong) {
	union DataConverter {
		uint16_t UIntLargeData;
		uint8_t UIntSmallData[2];
	};
	DataConverter TempInput;
	DataConverter TempOutput;
	TempOutput.UIntLargeData = CommandBuffer;

	SPI.beginTransaction(ConnectionSettings);
	SPI.transfer(0);

	digitalWrite(SelectPin,LOW);

	if (SendLong) {
		TempInput.UIntSmallData[1] = SPI.transfer( TempOutput.UIntSmallData[1] );
		TempInput.UIntSmallData[0] = SPI.transfer( TempOutput.UIntSmallData[0] );
	}
	else {
		TempInput.UIntSmallData[1] = SPI.transfer( TempOutput.UIntSmallData[1] );
	}
	digitalWrite(SelectPin, HIGH);
	SPI.endTransaction();
	return TempInput.UIntLargeData;
}

// uint8_t ADS8332::getSample(float* WriteVariable, uint8_t UseChannel)
// {
// 	uint16_t IntegerValue = 0;
// 	uint8_t status = getSample(&IntegerValue, UseChannel);
// 	*WriteVariable = Vref * ( (float)(IntegerValue) / 65535.0);
// 	return status;
// }

uint8_t ADS8332::getSample(uint16_t* WriteVariable, uint8_t UseChannel) {
	Channel = (uint8_t)( constrain(UseChannel,0,7) );

	//because of the limitations of the ADS8332, we must
	//disable auto trigger before changing the channel

	if (!manual_trigger) {
		setCommandBuffer(CommandRegister::WriteConfig);
		setConfiguration(ConfigRegisterMap::ChannelSelectMode, false);
		setConfiguration(ConfigRegisterMap::ClockSource, true);
		setConfiguration(ConfigRegisterMap::TriggerMode, true);
		setConfiguration(ConfigRegisterMap::SampleRate, true);
		setConfiguration(ConfigRegisterMap::EOCINTPolarity, true);
		setConfiguration(ConfigRegisterMap::EOCINTMode, true);
		setConfiguration(ConfigRegisterMap::ChainMode, true);
		setConfiguration(ConfigRegisterMap::AutoNap, true);
		setConfiguration(ConfigRegisterMap::Nap, true);
		setConfiguration(ConfigRegisterMap::Sleep, true);
		setConfiguration(ConfigRegisterMap::TAG, true);
		setConfiguration(ConfigRegisterMap::Reset, true);
		sendCommandBuffer(true);
	}
	
	setSampleChannel();

	if (!manual_trigger) {
		setCommandBuffer(CommandRegister::WriteConfig);
		setConfiguration(ConfigRegisterMap::ChannelSelectMode, false);
		setConfiguration(ConfigRegisterMap::ClockSource, true);
		setConfiguration(ConfigRegisterMap::TriggerMode, false);
		setConfiguration(ConfigRegisterMap::SampleRate, true);
		setConfiguration(ConfigRegisterMap::EOCINTPolarity, true);
		setConfiguration(ConfigRegisterMap::EOCINTMode, true);
		setConfiguration(ConfigRegisterMap::ChainMode, true);
		setConfiguration(ConfigRegisterMap::AutoNap, true);
		setConfiguration(ConfigRegisterMap::Nap, true);
		setConfiguration(ConfigRegisterMap::Sleep, true);
		setConfiguration(ConfigRegisterMap::TAG, true);
		setConfiguration(ConfigRegisterMap::Reset, true);
		sendCommandBuffer(true);
	}

	delayMicroseconds(3);
	return getSampleInteger(WriteVariable);
}

void ADS8332::setSampleChannel() {
	switch (Channel) {
		case(0):
			setCommandBuffer(CommandRegister::SelectCh0);
			break;
		case(1):
			setCommandBuffer(CommandRegister::SelectCh1);
			break;
		case(2):
			setCommandBuffer(CommandRegister::SelectCh2);
			break;
		case(3):
			setCommandBuffer(CommandRegister::SelectCh3);
			break;
		case(4):
			setCommandBuffer(CommandRegister::SelectCh4);
			break;
		case(5):
			setCommandBuffer(CommandRegister::SelectCh5);
			break;
		case(6):
			setCommandBuffer(CommandRegister::SelectCh6);
			break;
		case(7):
			setCommandBuffer(CommandRegister::SelectCh7);
			break;
		default:
			setCommandBuffer(CommandRegister::SelectCh0);
			break;
	}
	sendCommandBuffer(false);
}

uint8_t ADS8332::getSampleInteger(uint16_t* WriteVariable) {
	if (!beginsent) {
		begin();
		beginsent = true;
	}
	union DataConverter {
		uint16_t UIntLargeData;
		uint8_t UIntSmallData[2];
	};
	DataConverter TempInput;
	DataConverter TempOutput;
	setCommandBuffer(CommandRegister::ReadData);
	TempOutput.UIntLargeData = CommandBuffer;
	uint32_t starttime = micros();
	bool keepwaiting = true;
	digitalWrite(ConvertPin, LOW);
	while(manual_trigger && keepwaiting) {
		if (digitalRead(EOCPin) == 0) {
			keepwaiting = false;
		}
		else {
			if ( (micros() - starttime) > EOCTimeout) {
				digitalWrite(ConvertPin, HIGH);
				return 1;
			}
		}
	}
	digitalWrite(ConvertPin, HIGH);
	keepwaiting = true;
	starttime = micros();
	SPI.beginTransaction(ConnectionSettings);
	while(manual_trigger && keepwaiting) {
		if (digitalRead(EOCPin) == 1) {
			keepwaiting = false;
		}
		else {
			if ( (micros() - starttime) > EOCTimeout) {
				return 2;
			}
		}
	}
	starttime = micros();
	keepwaiting = true;
	uint8_t TAGData = 255;
	bool ChannelCorrect = false;
	bool TagBlank = false;
	uint8_t ChannelTag = 255;
	while(keepwaiting) {
		digitalWrite(SelectPin,LOW);
		TempInput.UIntSmallData[1] = SPI.transfer( TempOutput.UIntSmallData[1] );
		TempInput.UIntSmallData[0] = SPI.transfer( TempOutput.UIntSmallData[0] );
		TAGData = SPI.transfer( 0 );
		digitalWrite(SelectPin, HIGH);
		SPI.endTransaction();
		ChannelTag = (uint8_t)(TAGData>>5);
		ChannelCorrect = ( ChannelTag == Channel );
		TagBlank = (uint8_t)(TAGData << 3) == (uint8_t)(0);
		if (ChannelCorrect && TagBlank) {
			*WriteVariable = TempInput.UIntLargeData;
			return 0;
		}
		else {
			Serial.printf("Expected channel %d but received channel %d\n", Channel, ChannelTag);
			if ( (micros() - starttime) > EOCTimeout) {
				return 3;
			}
		}
	}
	return 4;
}

SPISettings* ADS8332::GetSPISettings() {
	return &ConnectionSettings;
}