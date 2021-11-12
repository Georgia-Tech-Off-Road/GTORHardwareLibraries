#include "SpeedSensor.h"
#include "SerialComms.h"

SerialComms serial(Serial);
SpeedSensor speed_sensor(30, 16, 255);

uint32_t temp = 0;
bool led_on = 0;

void setup() {
  // put your setup code here, to run once:
  serial.begin(115200);
  serial.attach_output_block(speed_sensor, 205);
  
  pinMode(13, OUTPUT);
  delay(100);
}

void loop() {
  speed_sensor.update();
//  serial.update_monitor();
  
  uint32_t t = micros();
  if((t - temp) > 50000) {
    led_on = !led_on;
    temp = t;
    digitalWrite(13, led_on);
//    Serial.println(speed_sensor.get_speed());
//    Serial.print("\t");
    Serial.println(speed_sensor.get_data().position);
  }
  
}
