/**
 * BrakePressureSensor.h
 * A library to work with MLH02KPSB06A sensors and measure the brake pressure in PSI
 * 
 * ------ Constructor ------
 * BrakePressureSensor bp;
 * 
 * where:
 * no input needed
 * 
 * ------ Usage ------
 * adc.attach_sensor(bp, port);
 *      - This will attach the BrakePressureSensor to an ADC that it can be read from
 * 
 * float bp_data = bp.get_data();
 *      - This will read the data from the ADC that the BrakePressureSensor is attached to and return it
 * 
 * bp.update();
 *      - This will update the sensor to be used by the communication utility
 */

#ifndef BRAKE_PRESSURE_SENSOR_H
#define BRAKE_PRESSURE_SENSOR_H

#include "AnalogSensor.h"

class BrakePressureSensor : public AnalogSensor<float> {
    public:
        void update_data();
};

#endif