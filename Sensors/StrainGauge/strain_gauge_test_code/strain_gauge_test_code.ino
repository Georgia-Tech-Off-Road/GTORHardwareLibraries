#include "StrainGauge.h"
#include "TeensyADC.h"
#include "ClockTimer.h"
#define TEENSY_PORT A0

StrainGauge strain;
TeensyADC tadc;
ClockTimerf serialTimer(1000);


void setup() {
  // put your setup code here, to run once:
  tadc.attach_sensor(strain, TEENSY_PORT);
  strain.set_scale(32.33);
  Serial.begin(115200);
  strain.update();
  strain.tare();
  delay(100); 

}

void loop() {
  strain.update();
  if(serialTimer.ready(micros())){
    Serial.println(strain.get_data());
  }


}
