
#include <SPI.h>
#include <Arduino.h>
#include <ADS8688.h>
#include <LDS.h>

ADS8688 ads(35);
LDS<uint16_t> lds(100);
    
void setup() {
  ads.attach_sensor(lds,22); //22 is pin on teensy
  SPI.begin();
  ads.begin(34); //34 is chip select for ADC


}

void loop() {
    lds.update();
    if(serialTimer.ready(micros())){
      Serial.print(lds.get_data());
    
    }

}

}
