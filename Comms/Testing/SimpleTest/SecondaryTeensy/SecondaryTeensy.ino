#include "UARTComms.h"
#include "SerialComms.h"
#include "TeensyADC.h"
#include "Potentiometer.h"
#include "ClockTimer.h"
#include "TimeSensor.h"

// DIFF

UARTComms uart1(Serial1);
SerialComms serial(Serial);

TeensyADC tadc;
Potentiometer<uint32_t> active_pot(270);
Potentiometer<uint32_t> passive_pot(270);

TimeSensor ts_dash;
TimeSensor ts_auxdaq;
TimeSensor ts_diff; // TIME_DIFF_US

void setup() {
  serial.begin(115200);
  uart1.begin(115200);
  
  tadc.attach_sensor(active_pot, A2);
  uart1.attach_output_block(active_pot, 91);
  uart1.attach_output_block(ts_diff, TIME_DIFF_US);
  uart1.attach_input_block(passive_pot, 90);
  uart1.attach_input_block(ts_dash, TIME_DASH_US);

  serial.attach_output_block(active_pot, 91);
  serial.attach_output_block(passive_pot, 90);
  serial.attach_output_block(ts_dash, TIME_DASH_US);
  serial.attach_output_block(ts_auxdaq, TIME_AUXDAQ_US);
  serial.attach_output_block(ts_diff, TIME_DIFF_US);
}

void loop() {
  static ClockTimerf print_timer(100);
  
  tadc.update_sensors();
  ts_diff.update();
  
  uart1.update();
  serial.update_monitor();
  
//  uint32_t t = micros();
//  if (print_timer.ready(t)) {
//    Serial.print("active_pot:");
//    Serial.print(active_pot.get_data());
//    Serial.print("\tpassive_pot:");
//    Serial.println(passive_pot.get_data());
//  }
}
