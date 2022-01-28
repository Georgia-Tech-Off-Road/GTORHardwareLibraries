/**
 * StrainGauge.h
 * A library to work with strain gauges and measures strain. This library is only to be used with strain gauges
 * that are amplified using a custom circuit and measured using an ADC.
 * 
 * ------ Constructor ------
 * StrainGauge strain_gauge;
 * 
 * 
 * ------ Usage ------
 * strain_gauge.tare();
 *      - This will zero the strain gauge
 * 
 * strain_gauge.set_scale(float scale);
 *      - This will add a multiplier for whatever value the strain gauge is reading
 *          - The strain_gauge will by default read just the voltage if the scale is 1 and the offset is 0
 * 
 * float scale = strain_gauge.get_scale();
 *      - Gets the scale 
 * 
 * adc.attach_sensor(strain_gauge, port);
 *      - This will attach the strain gauge sensor to an ADC that it can be read from
 * 
 * float strain_gauge_data = strain_gauge.get_data();
 *      - This will read the data from the ADC that the strain gauge is attached to and return the strain that it measures
 * 
 * strain_gauge.update();
 *      - This will update the sensor to be used by the communication utility
 */

#ifndef STRAINGAUGE_H
#define STRAINGAUGE_H

#include "LoadCell.h"

using StrainGauge = LoadCell;

#endif