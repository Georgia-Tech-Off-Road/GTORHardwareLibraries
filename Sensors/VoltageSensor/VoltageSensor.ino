#include "VoltageSensor.h"
#include "ADS8688.h"
#include "ClockTimer.h"
#define TEENSY_PORT A2

VoltageSensor<float> volt;
ADS8688 adc(10);
ClockTimerf serialTimer(100);
void setup() {
  // put your setup code here, to run once:
  adc.attach_sensor(volt, TEENSY_PORT);
  adc.set_port_vrange(0,ADS8688::VOLTAGE_RANGE::SIGNED_5V12);
  Serial.begin(115200);
  delay(100);
  
  

}

void loop() {
  volt.update();
  if(serialTimer.ready(micros())){
    Serial.print("Voltage is: ");
    Serial.print(volt.get_data());
    Serial.println(" Volts");
    
  }

}
