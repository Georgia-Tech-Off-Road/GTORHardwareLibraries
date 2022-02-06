/*!
 *  @file TLC5952.h
 */

#ifndef TLC5952_H
#define TLC5952_H

#include <Arduino.h>

/*!
 *    @brief  Class that stores state and functions for interacting with
 *            TLC5947 24-channel PWM/LED driver
 */

class TLC5952 {
public:
  TLC5952(uint8_t c, uint8_t d, uint8_t l);

  bool begin(void);
  void write();

  // In progress functions
  void set_control_data(uint8_t red_percent, uint8_t green_percent, uint8_t blue_percent, uint8_t error_mode = 0);
  void set_on_off_data(uint32_t LED_positions);

private:
  uint32_t _data_message;
  uint8_t _clk, _dat, _lat;
};

#endif
