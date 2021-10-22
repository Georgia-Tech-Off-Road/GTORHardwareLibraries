#include "UARTComms.h"
#include "TeensyADC.h"
#include "Potentiometer.h"
#include "ClockTimer.h"

UARTComms uart1(Serial1);

TeensyADC tadc;
Potentiometer<uint32_t> active_pot(270);
Potentiometer<uint32_t> passive_pot(270);

void setup() {
  Serial.begin(115200);
  uart1.begin(115200);
  
  tadc.attach_sensor(active_pot, A2);
  uart1.attach_output_block(active_pot, 91);
  uart1.attach_input_block(passive_pot, 90);
}

void loop() {
  static ClockTimerf print_timer(100);
  
  tadc.update_sensors();
  uart1.update();
  
  uint32_t t = micros();
  if (print_timer.ready(t)) {
    Serial.print("active_pot:");
    Serial.print(active_pot.get_data());
    Serial.print("\tpassive_pot:");
    Serial.println(passive_pot.get_data());
  }
}
