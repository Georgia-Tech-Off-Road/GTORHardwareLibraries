#include "TLC5952.h"
// parameteres: c, d, l
TLC5952 testR(3, 2, 4);
TLC5952 testL(12, 11, 10);

void setup() {
  // put your setup code here, to run once:
//  Serial.begin(115200);
  testR.begin();
  pinMode(17, INPUT);
  testL.begin();
//  Serial.println("I got here 1");
  testR.set_control_data(127, 127, 127, 0);
  testL.set_control_data(127, 127, 127, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  testL.set_on_off_data(0b111111111111111111111111);
  Serial.println(digitalRead(17));
  testR.set_on_off_data(0b111111111111111111111111);
  Serial.println("I got here 2");
  testR.write();
  testL.write();
}
