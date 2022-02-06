#ifndef ADCSENSOR_H
#define ADCSENSOR_H

#include "../Sensor.h"
#include <Adafruit_ADS1X15.h>

class adc_data_t {
public:
	const float& operator[](uint8_t i) const { 
		return _data[i];
	}
	float& operator[](uint8_t i) {
		return _data[i];
	}
private:
	float _data[4];
};

class ADCSensor : public Sensor<adc_data_t> {
public:
	ADCSensor(){ 
		_pack_bytes = sizeof(_data);
	}

	bool begin(uint8_t i2c_addr){
		return _ads.begin(i2c_addr);
	}

	const adc_data_t& get_data(){
		if(_type == ACTIVE){
			_data[0] = _ads.computeVolts(_ads.readADC_SingleEnded(0));
			_data[1] = _ads.computeVolts(_ads.readADC_SingleEnded(1));
			_data[2] = _ads.computeVolts(_ads.readADC_SingleEnded(2));
			_data[3] = _ads.computeVolts(_ads.readADC_SingleEnded(3));
		}
		return _data;
	} 
	void pack(uint8_t* pack){
        this->get_data();
		float* p = (float*) pack;
		const float* data = &(_data[0]);
		memcpy(p, data, sizeof(_data));
	}
	void unpack(uint8_t* pack){
		const float* p = (float*) pack;
		float* data = &(_data[0]);
		memcpy(data, p, sizeof(_data));
	}

	void setGain(adsGain_t gain) { _ads.setGain(gain); }
	adsGain_t getGain() { return _ads.getGain(); }
	void setDataRate(uint16_t rate) { _ads.setDataRate(rate); }
	uint16_t getDataRate() { return _ads.getDataRate(); }

private:
	Adafruit_ADS1115 _ads;
};


#endif // ADCSENSOR_H