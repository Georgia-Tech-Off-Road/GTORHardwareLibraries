#ifndef LMT87SENSOR_H
#define LMT87ENSOR_H
/**
 * LMT87Sensor.h
 * A library to work with LMT87 sensors and measures the temperature
 * 
 * ------ Constructor ------
 * LMT87Sensor temp();
 * 
 * where:
 * no input needed
 * 
 * ------ Usage ------
 * adc.attach_sensor(temp, port);
 *      - This will attach the LMT87Sensor to an ADC that it can be read from
 * 
 * int temp_data = temp.get_data();
 *      - This will read the data from the ADC that the LMT87Sensor is attached to and return it
 * 
 * temp.update();
 *      - This will update the sensor to be used by the communication utility
 */


#include "AnalogSensor.h"

class LMT87Sensor : public AnalogSensor<float> {


public:
    /**
     * Constructor for the temperature sensor
     */
    void set_raw(float raw);

};



#endif
