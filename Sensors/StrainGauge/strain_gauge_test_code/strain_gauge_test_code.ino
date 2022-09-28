#include "StrainGauge.h"
#include "TeensyADC.h"
#include "ADS8688.h"
#include "ClockTimer.h"
#define TEENSY_PORT A3

StrainGauge strain;
ADS8688 tadc(35);
ClockTimerf serialTimer(1000);


void setup() {
  // put your setup code here, to run once:
  SPI.begin();
  tadc.begin();
  tadc.attach_sensor(strain, 0);
  strain.set_scale(1);
  //strain.tare();
  
  Serial.begin(115200);
  strain.update();
  delay(100); 

}

void loop() {
  strain.update();
  if(serialTimer.ready(micros())){
    Serial.println(strain.get_data());
  }


}
