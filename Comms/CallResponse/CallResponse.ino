#include "DigitalOutput.h"
#include "ClockTimer.h"

#define BAUD 230400

#define TIMEOUT 5000

void setup() {
  Serial.begin(BAUD);
  Serial1.begin(BAUD);
}

std::vector<uint8_t> packet;

uint8_t inc = 0;

uint32_t last_rx = -TIMEOUT;

void print_packet() {
  for (uint8_t i : packet) {
    Serial.print(String(i, HEX));
    Serial.print(' ');
  }
  Serial.print(millis() - last_rx);
  Serial.println();
}

void send_packet() {
  std::vector<uint8_t> packet_send;
  packet_send.push_back(0x02);
  for (int i = 0; i < 57; ++i) {
    packet_send.push_back(inc);
  }
  for (int i = 0; i < 7; ++i) {
    packet_send.push_back(0xff);
  }
  packet_send.push_back(0xf0);
  Serial1.write(packet_send.data(), 10);
  packet.clear();
  last_rx = millis();
}

void loop() {
  if (Serial1.available()) {
    packet.push_back(Serial1.read());

    for (int i = packet.size() - 8; i < packet.size() - 1; ++i) {
      if (packet[i] != 0xff) {
        return;
      }
    }
    if (packet[packet.size() - 1] == 0xf0) {
      print_packet();
      inc = (inc + 1) % 256;
      send_packet();
    }
  }
  if (millis() - last_rx >= TIMEOUT) {
    Serial.println("TIMEOUT --- RESENDING PACKET");
    send_packet();
  }
}
