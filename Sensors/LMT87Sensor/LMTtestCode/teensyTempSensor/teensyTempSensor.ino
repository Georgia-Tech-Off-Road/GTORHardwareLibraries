#include "LMT87Sensor.h"
#include "TeensyADC.h"
#include "ClockTimer.h"
#define TEENSY_PORT 14

LMT87Sensor temp;
TeensyADC tadc;
ClockTimerf serialTimer(100);
void setup() {
  // put your setup code here, to run once:
  tadc.attach_sensor(temp, TEENSY_PORT);
  Serial.begin(115200);
  delay(100);
  
  

}

void loop() {
  temp.update();
  if(serialTimer.ready(micros())){
    Serial.print("Temperature is: ");
    Serial.print(temp.get_data());
    Serial.println(" degrees celsius");
    
  }

}
