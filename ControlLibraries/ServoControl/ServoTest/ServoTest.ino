#include <ServoControl.h>

ServoControl servoR(9, 270);
ServoControl servoL(5, 270);

void setup() {
  servoR.begin();
  servoL.begin();
}

uint8_t prev_count = 0;
uint8_t dialnum = 127;

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 270; i++) {
    servoR.writeDeg(i);
    servoL.writeDeg(i);
    delay(10);
  }
  for (int i = 269; i > 0; i--) {
    servoR.writeDeg(i);
    servoL.writeDeg(i);
    delay(10);
  }
}
