#ifndef VOLTAGESENSOR_H
#define VOLTAGESENSOR_H

/**
 * VoltageSensor.h
 * A library to work with Voltage sensors
 * 
 * ------ Constructor ------
 * VoltageSensor<DataType> voltSensor();
 * 
 * where:
 * DataType         -> Either uint8_t, int8_t, or float
 *      - In most cases, float
 * 
 * ------ Usage ------
 * adc.attach_sensor(voltSensor, port);
 *      - This will attach the VoltageSensor to an ADC that it can be read from
 * 
 * DataType voltSensor_data = voltSensor.get_data();
 *      - This will read the data from the ADC that the voltage sensor is attached to and return it
 * 
 * voltSensor.update();
 *      - This will update the sensor to be used by the communication utility
 */

#include "AnalogSensor.h"

template <typename DataType>
class VoltageSensor : public AnalogSensor<DataType> {
public:
    void set_raw(float raw);
};

template class VoltageSensor<uint8_t>;
template class VoltageSensor<int8_t>;
template class VoltageSensor<float>;

#endif
