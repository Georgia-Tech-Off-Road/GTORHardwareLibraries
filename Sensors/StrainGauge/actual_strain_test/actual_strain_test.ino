#include "StrainGauge.h"
#include "TeensyADC.h"
#include "ClockTimer.h"
#define TEENSY_PORT A2 //was A0
StrainGauge strain;
TeensyADC tadc;
ClockTimerf serialTimer(100);
float area = 12.5 * 1.45 * 0.000001; //cross sectional area of whatever the strain gauge is on
float youngModulus = 70000000000; //determined by the material (aluminum for testing), multiplied by 10^10

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
    Serial.print("Force is: ");
    Serial.println(strain.get_data() * area * youngModulus);
  }

}
