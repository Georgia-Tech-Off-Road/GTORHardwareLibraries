#include "DigitalOutput.h"
#include "ClockTimer.h"

#define BAUD 230400

#define S1 Serial
#define S2 Serial1

ClockTimerf ct(1);
DigitalOutput led;

void setup() {
  // put your setup code here, to run once:
  S1.begin(BAUD);
  S2.begin(BAUD);
  led.begin(13);
  led.set_flipcb(MAKE_CB(ct.ready()));
}

void loop() {
  // put your main code here, to run repeatedly:
  while(S1.available()) {
    S2.write(S1.read());
  }
  while(S2.available()) {
    S1.write(S2.read());
  }
  led.update();
}