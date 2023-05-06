#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

#include "AnalogSensor.h"

class TempSensor : public AnalogSensor<float> {
public:
  void update_data() {
    this->set_data(144-19.7*(this->_raw)-111*((this->_raw)*(this->_raw)));
  }
};

#endif