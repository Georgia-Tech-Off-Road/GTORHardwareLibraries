#include <Arduino.h>
#include <ADS8688.h>
#include <LDS.h>

ADS8688 ads(10);
LDS<uint16_t> lds(160);

void setup() {
  ads.begin();
  ads.attach_sensor(lds, 0);
}

void loop() {
  ads.update_sensors();
  Serial.println(lds.get_data());
}
