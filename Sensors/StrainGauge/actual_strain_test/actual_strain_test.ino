#include "StrainGauge.h"
#include "TeensyADC.h"
#include "ClockTimer.h"
#define TEENSY_PORT A0 //was A2
StrainGauge strain;
TeensyADC tadc;
ClockTimerf serialTimer(100);
float offset;
uint64_t youngs_modulus = 70000000000; //youngs modulus of aluminum;
float length = 0.0127;
float width = 0.002;
float area = width * length; //cross sectional area of material that gauge is on;
float force;
float strain_value;
float no_ym;

void setup() {
  // put your setup code here, to run once:
  tadc.attach_sensor(strain, TEENSY_PORT);
  Serial.begin(115200);
  strain.update();
  offset = strain.get_data();
  // offset = 0;

  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  strain.update();

  if(serialTimer.ready(micros())){
    //Serial.printf("Force is: %.10f\n", strain.get_data());
    strain_value = strain.get_data();
    strain_value = strain_value - offset;
    force = (strain_value * area * youngs_modulus)/4.448;
    no_ym = strain_value * area;
    Serial.printf("strain is: %.10f\n", strain_value);
    Serial.printf("Force is: %.10f\n", force);
    Serial.printf("no_ym is: %.10f\n", no_ym);
  }

}
