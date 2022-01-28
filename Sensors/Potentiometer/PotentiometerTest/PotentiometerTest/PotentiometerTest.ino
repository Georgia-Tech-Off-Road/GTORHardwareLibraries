#include <SerialComms.h>
#include <TeensyADC.h>
#include <Potentiometer.h>
#include <ClockTimer.h>
#include <Block.h>
#include <BlockId.h>


SerialComms serial(Serial);

TeensyADC tadc;
Potentiometer<uint32_t> active_pot(270);
Potentiometer<uint32_t> passive_pot(270);

#define LED_PIN 13
uint32_t prev_time = micros();
bool led_state = 0;

void setup() {
  serial.begin(115200);
  
  tadc.attach_sensor(active_pot, A2);
  serial.attach_output_block(active_pot, 91);
  serial.attach_output_block(passive_pot, 90);

  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  //static ClockTimerf print_timer(100);  

  active_pot.update();
  
  serial.update();
  
  //uint32_t t = micros();

  if(abs(micros() - prev_time) > 250000){
    led_state = !led_state;
    digitalWrite(LED_PIN, led_state);
    prev_time = micros();
  } 
  
  /*
  if (print_timer.ready(t)) {
  Serial.print("active_pot:");
  Serial.print(active_pot.get_data());
  Serial.print("\tpassive_pot:");
  Serial.println(passive_pot.get_data());
  }
  */
}
