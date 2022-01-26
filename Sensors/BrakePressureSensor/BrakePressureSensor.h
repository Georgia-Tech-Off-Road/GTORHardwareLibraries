#ifndef BRAKE_PRESSURE_SENSOR_H
#define BRAKE_PRESSURE_SENSOR_H
#include "AnalogSensor.h"

/**
 * BrakePressureSensor.h
 * A library to work with MLH02KPSB06A sensors and measure the temperature
 * 
 * ------ Constructor ------
 * BrakePressureSensor bp;
 * 
 * where:
 * no input needed
 * 
 * ------ Usage ------
 * adc.attach_sensor(bp, port);
 *      - This will attach the LMT87Sensor to an ADC that it can be read from
 * 
 * int bp_data = bp.get_data();
 *      - This will read the data from the ADC that the BrakePressureSensor is attached to and return it
 * 
 * bp.update();
 *      - This will update the sensor to be used by the communication utility
 */

class AnalogBrakePressure : public AnalogSensor<float> {
    public:
        void set_raw(float raw);
};

#endif