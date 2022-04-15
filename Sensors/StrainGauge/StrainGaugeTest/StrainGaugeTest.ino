#include <SerialComms.h>
#include <TeensyADC.h>
#include <StrainGauge.h>
#include <ClockTimer.h>
#include <Block.h>
#include <BlockId.h>


SerialComms serial(Serial);

TeensyADC tadc;
StrainGauge strain;
ClockTimerf serialTimer(100);

#define LED_PIN 13


void setup() {
  tadc.attach_sensor(strain, A0);
  strain.set_scale(0.6);
  Serial.begin(115200);
  strain.update();
  strain.tare();
  serial.attach_output_block(strain, 311);

  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  strain.update();
  serial.update(); 
  if (serialTimer.ready(micros())) {
   Serial.print("strain_gauge:");
   Serial.print(strain.get_data());
  }
  
}
