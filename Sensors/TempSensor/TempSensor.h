#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

#include "AnalogSensor.h"

class TempSensor : public AnalogSensor<float> {
public:
  void update_data() {
    this->set_data(exp(.003 * ((this->_raw - 1) * -1024)) * 7 - 26);
  }
};

#endif