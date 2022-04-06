#include "VoltageSensor.h"
#include "TeensyADC.h"
#include "ClockTimer.h"
#define TEENSY_PORT A0

VoltageSensor<float> volt;
TeensyADC tadc;
ClockTimerf serialTimer(100);
void setup() {
  // put your setup code here, to run once:
  tadc.attach_sensor(volt, TEENSY_PORT);
  Serial.begin(115200);
  delay(100);
  
  

}

void loop() {
  volt.update();
  if(serialTimer.ready(micros())){
    Serial.print("Temperature is: ");
    Serial.print(volt.get_data());
    Serial.println(" degrees celsius");
  }

}
