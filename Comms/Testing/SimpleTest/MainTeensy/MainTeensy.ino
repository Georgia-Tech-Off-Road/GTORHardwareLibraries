#include "UARTComms.h"
#include "SerialComms.h"
#include "WirelessComms.h"
#include "TeensyADC.h"
#include "Potentiometer.h"
#include "ClockTimer.h"

SerialComms serial(Serial);
UARTComms uart1(Serial1);
WirelessComms wireless(Serial2);

TeensyADC tadc;
Potentiometer<uint32_t> active_pot(270);
Potentiometer<uint32_t> passive_pot(270);

void setup() {
  serial.begin(115200);
  uart1.begin(115200);
  wireless.begin(115200);
  
  tadc.attach_sensor(active_pot, A2);
  
  uart1.attach_output_block(active_pot, 90);
  uart1.attach_input_block(passive_pot, 91);
  
  serial.attach_output_block(active_pot, 90);
  serial.attach_throughput_comms(uart1);

  wireless.attach_output_block(active_pot, 90);
  wireless.attach_throughput_comms(uart1);
}

void loop() {
  static ClockTimerf print_timer(100);
  
  tadc.update_sensors();
  
  uart1.update();
  serial.update();
  wireless.update();
  
//  uint32_t t = micros();
//  if (print_timer.ready(t)) {
//    Serial.print("active_pot:");
//    Serial.print(active_pot.get_data());
//    Serial.print("\tpassive_pot:");
//    Serial.println(passive_pot.get_data());
//  }
}
