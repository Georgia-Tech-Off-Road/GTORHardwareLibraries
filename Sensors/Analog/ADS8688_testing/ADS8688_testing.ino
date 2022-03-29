
#include <SPI.h>
#include <Arduino.h>

uint16_t port_voltage = 0;
uint16_t write_message = 0b1100000000000000;
uint8_t NCSPIN = 10;
    
void setup() {
  SPI.begin();
  pinMode(NCSPIN, OUTPUT);


}

void loop() {
    
    SPI.beginTransaction(SPISettings(17000000, MSBFIRST, SPI_MODE0)); // Might be mode 1
    digitalWrite(NCSPIN, LOW);
    SPI.transfer16(write_message);
    port_voltage = SPI.transfer16(0);
    digitalWrite(NCSPIN, HIGH);
    SPI.endTransaction();
    Serial.print(port_voltage,BIN);

}
