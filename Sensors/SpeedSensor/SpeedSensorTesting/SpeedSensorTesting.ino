#include "SpeedSensor.h"

SpeedSensor he_sensor_1(600, 10000, 2);

uint32_t temp = 0;
bool led_on = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  he_sensor_1.begin(22);

  delay(100);
}

void loop() {  
  he_sensor_1.update();
  uint32_t t = micros();
  if((t - temp) > 50000) {
    led_on = !led_on;
    temp = t;
    digitalWrite(13, led_on);
    Serial.print(he_sensor_1.get_speed());
    Serial.print("\t");
    Serial.print(he_sensor_1.get_position());
    Serial.print("\t");
    Serial.println(micros());
  }
  
}
