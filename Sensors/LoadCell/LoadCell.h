/**
 * LoadCell.h
 * A library to work with load cells and measures force. This library is only to be used with load cells
 * that are amplified using a custom circuit and measured using an ADC. For load cells that are measured
 * using the Sparkfun QwiicScale or with an HX711, use those respective libraries for getting data from
 * a load cell.
 * 
 * ------ Constructor ------
 * LoadCell load_cell;
 * 
 * 
 * ------ Usage ------
 * load_cell.tare();
 *      - This will zero the load cell
 * 
 * load_cell.set_scale(float scale);
 *      - This will add a multiplier for whatever value the load cell is reading
 *          - The load_cell will by default read just the voltage if the scale is 1 and the offset is 0
 * 
 * float scale = load_cell.get_scale();
 *      - Gets the scale 
 * 
 * adc.attach_sensor(load_cell, port);
 *      - This will attach the load cell sensor to an ADC that it can be read from
 * 
 * float load_cell_data = load_cell.get_data();
 *      - This will read the data from the ADC that the load cell is attached to and return the force that it measures
 * 
 * load_cell.update();
 *      - This will update the sensor to be used by the communication utility
 */

#ifndef LOADCELL_H
#define LOADCELL_H

#include "AnalogSensor.h"

class LoadCell : public AnalogSensor<float> {
    private:
        float _offset;
        float _scale;
    public:
        void update_data();
        void tare();
        void set_scale(float scale);
        float get_scale();
};

#endif