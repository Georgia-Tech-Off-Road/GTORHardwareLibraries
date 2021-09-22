#include <ServoControl.h>

ServoControl servo1(5, 270);

void setup() {
  servo1.begin();
}

uint8_t prev_count = 0;
uint8_t dialnum = 127;

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 270; i++) {
    servo1.writeDeg(i);
    delay(10);
  }
  for (int i = 269; i > 0; i--) {
    servo1.writeDeg(i);
    delay(10);
  }
}
