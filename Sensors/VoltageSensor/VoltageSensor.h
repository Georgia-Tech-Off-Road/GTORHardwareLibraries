#ifndef VOLTAGESENSOR_H
#define VOLTAGESENSOR_H

/**
 * Potentiometer.h
 * A library to work with potentiometer sensors and measures the angular position
 * 
 * ------ Constructor ------
 * Potentiometer<DataType> pot(full_scale_range, is_reversed);
 * 
 * where:
 * DataType         -> Either uint8_t, uint16_t, uint32_t, or float
 *      - In most cases, uint16 is probably fine since a lot of our potentiometers are 270 degrees
 * 
 * full_scale_range -> The full scale range in degrees of the potentiometer being used
 * is_reversed      -> If the potentiometer is increasing clockwise then setting is_reversed will make
 *                     it increase counterclockwise
 * 
 * ------ Usage ------
 * adc.attach_sensor(pot, port);
 *      - This will attach the potentiometer sensor to an ADC that it can be read from
 * 
 * DataType pot_data = pot.get_data();
 *      - This will read the data from the ADC that the potentiometer is attached to and return it
 * 
 * pot.update();
 *      - This will update the sensor to be used by the communication utility
 */

#include "AnalogSensor.h"

template <typename DataType>
class VoltageSensor : public AnalogSensor<DataType> {
private:
    uint16_t _full_scale_range;

public:
    /**
     * Constructor for the VoltageSensor sensor
     */
    VoltageSensor(uint16_t full_scale_range);
    void set_raw(float raw);

};

template class VoltageSensor<uint8_t>;
template class VoltageSensor<uint16_t>;
template class VoltageSensor<uint32_t>;
template class VoltageSensor<float>;
template class VoltageSensor<double>;

#endif
