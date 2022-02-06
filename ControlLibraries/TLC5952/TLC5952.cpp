/*!
 *  @file TLC5952.cpp
 *  @mainpage 24-channel PWM/LED driver
 */

#include <TLC5952.h>

/*!
 *    @brief Instantiates a new TLC5952 class
 *    @param  c Arduino pin connected to TLC5952 clock pin
 *    @param  d Arduino pin connected to TLC5952 data pin
 *    @param  l Arduino pin connected to TLC5952 latch pin
 */
TLC5952::TLC5952(uint8_t c, uint8_t d, uint8_t l) {
  _clk = c;
  _dat = d;
  _lat = l;
}

/*!
 *    @brief  Writes data message into the Common Shift Register(CSR) and then latches it into the data latch
 */
void TLC5952::write() {
  // Serial.println("bruh");
  // Serial.println(_data_message, HEX);
  digitalWrite(_lat, LOW);
  delayMicroseconds(10);

  // 25 bits, send MSB first
  for (int8_t b = 24; b >= 0; b--) {
    digitalWrite(_clk, LOW);
    delayMicroseconds(10);

    // If the b-th bit is a 1, make _dat high, else low
    if (_data_message & (1 << b)){
      digitalWrite(_dat, HIGH);
      delayMicroseconds(10);
    }
    else {
      digitalWrite(_dat, LOW);
      delayMicroseconds(10);
    }

    digitalWrite(_clk, HIGH);
    delayMicroseconds(10);
  }

  digitalWrite(_clk, LOW);
  delayMicroseconds(10);

  digitalWrite(_lat, HIGH);
  delayMicroseconds(10);
  digitalWrite(_lat, LOW);
  delayMicroseconds(10);


}

/*!

 */
void TLC5952::set_control_data(uint8_t red_percent, uint8_t green_percent, uint8_t blue_percent, uint8_t error_mode = 0) {

 uint8_t r_value = red_percent;
// if (red_percent > 100){
//   r_value = 127;
// }
// else if (red_percent < 0)
// {
//   r_value = 0;
// }
// else {
//   r_value = red_percent * 127 / 100;
// }

 uint8_t g_value = green_percent;
// if (green_percent > 100){
//   g_value = 127;
// }
// else if (green_percent < 0)
// {
//   g_value = 0;
// }
// else {
//   g_value = green_percent * 127 / 100;
// }

 uint8_t b_value = blue_percent;
// if (blue_percent > 100){
//   b_value = 127;
// }
// else if (blue_percent < 0)
// {
//   b_value = 0;
// }
// else {
//   b_value = blue_percent * 127 / 100;
// }

uint8_t e_mode;
if (error_mode > 7){
  e_mode = 7;
}
else if (error_mode < 0)
{
  e_mode = 0;
}
else {
  e_mode = error_mode;
}

 _data_message = (1 << 24) | (e_mode << 21) | (b_value << 14) | (g_value << 7) | r_value;

 write();

}

/*!

 */
void TLC5952::set_on_off_data(uint32_t LED_positions) {

 _data_message = (0 << 24) | (LED_positions & 0x00FFFFFF);

 write();

}

/*!
 *    @brief  Setups the HW
 *    @return True if initialization was successful, otherwise false.
 */
bool TLC5952::begin() {

  pinMode(_clk, OUTPUT);
  pinMode(_dat, OUTPUT);
  pinMode(_lat, OUTPUT);
  digitalWrite(_lat, LOW);

  set_control_data(100, 100, 100, 0);
  set_on_off_data(0);
 
  return true;
}
