#include "WirelessComms.h"
#include "SerialComms.h"
#include "Potentiometer.h"

SerialComms serial(Serial);
WirelessComms wireless(Serial1);

Potentiometer<uint32_t> received_pot_90(270);
Potentiometer<uint32_t> received_pot_91(270);

void setup() {
  // put your setup code here, to run once:
  serial.begin(115200);
  wireless.begin(115200);

  serial.attach_throughput_comms(wireless);

  wireless.attach_input_block(received_pot_90, 90);
  wireless.attach_input_block(received_pot_91, 91);
}

void loop() {
  // put your main code here, to run repeatedly:
  wireless.update();
  serial.update();
}
