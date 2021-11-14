#ifndef LoadCell_H
#define LoadCell_H


/**
 * LoadCell.h
 * A library to work with load cells and measures strain
 * 
 * ------ Constructor ------
 * LoadCell<DataType> load_cell(full_scale_range, is_reversed = false);
 * 
 * where:
 * DataType         -> Either uint8_t, uint16_t, uint32_t, or float
 * 
 * full_scale_range -> The range of the load cell in mm
 * is_reversed      -> If the position is increasing when the load cell is being retracted, then setting is_reversed will make the
 *                     position increase when the load cell is being extended. Defaults to false.
 * 
 * ------ Usage ------
 * adc.attach_sensor(load_cell, port);
 *      - This will attach the load cell sensor to an ADC that it can be read from
 * 
 * DataType load_cell_data = load_cell.get_data();
 *      - This will read the data from the ADC that the load cell is attached to and return it
 * 
 * load_cell.update();
 *      - This will update the sensor to be used by the communication utility
 */

#include "Potentiometer.h"

template<typename T>
using LoadCell = Potentiometer<T>;

#endif