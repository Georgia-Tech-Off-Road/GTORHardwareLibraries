#include "StrainGauge.h"
#include "TeensyADC.h"
#include "ClockTimer.h"
#define TEENSY_PORT A0
StrainGauge strain;
TeensyADC tadc;
ClockTimerf serialTimer(100);
void setup() {
  // put your setup code here, to run once:
  tadc.attach_sensor(strain, TEENSY_PORT);
  Serial.begin(115200);
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  strain.update();
  if(serialTimer.ready(micros())){
    Serial.print("Strain is: ");
    Serial.print(strain.get_data());
  }

}
