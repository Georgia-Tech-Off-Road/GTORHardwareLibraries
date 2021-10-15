#ifndef LDS_H
#define LDS_H


/**
 * LDS.h
 * A library to work with LDS sensors and measures the linear position
 * 
 * ------ Constructor ------
 * LDS<DataType> lds(full_scale_range, is_reversed);
 * 
 * where:
 * DataType         -> Either uint8_t, uint16_t, uint32_t, or float
 *      - In most cases, uint8_t is probably fine since our LDS sensors are usually less than 255mm in stroke length anyways
 * 
 * full_scale_range -> The range of the LDS in mm
 * is_reversed      -> If the position is increasing when the LDS is being retracted, then setting is_reversed will make the
 *                     position increase when the LDS is being extended
 * 
 * ------ Usage ------
 * adc.attach_sensor(lds, port);
 *      - This will attach the LDS sensor to an ADC that it can be read from
 * 
 * DataType lds_data = lds.get_data();
 *      - This will read the data from the ADC that the LDS is attached to and return it
 * 
 * lds.update();
 *      - This will update the sensor to be used by the communication utility
 */

#include "Potentiometer.h"

typedef Potentiometer LDS;

#endif