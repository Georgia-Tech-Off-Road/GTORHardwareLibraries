#include "DigitalOutput.h"
#include "ClockTimer.h"

#define BAUD 230400
#define SEND_MS 100
#define WINDOW_LEN 20

void setup() {
  Serial.begin(BAUD);
  Serial1.begin(BAUD);
}

std::vector<uint8_t> packet;
std::vector<uint8_t> window;
double window_sum = 0.0;
uint32_t last_rx = 0;
uint32_t last_tx = 0;
uint8_t inc = 0;

void loop() {
  uint32_t now = millis();
  if (Serial1.available()) {
    packet.push_back(Serial1.read());

    for (size_t i = packet.size() - 8; i < packet.size() - 1; ++i) {
      if (packet[i] != 0xff) {
        return;
      }
    }
    if (packet[packet.size() - 1] == 0xf0) {
      window.push_back(now - last_rx);
      window_sum += now - last_rx;
      if (packet.size() > WINDOW_LEN) {
        window_sum -= window[0];
        window.erase(window.begin());
      }
      Serial.print(packet[1]);
      Serial.print(' ');
      Serial.print(window_sum / window.size());
      Serial.println();
      packet.clear();
      last_rx = now;
    }
  }
  if (now - last_tx > SEND_MS) {
    uint8_t packet_send[] = {
      0x02,
      inc, inc, inc, inc, inc, inc, inc, inc, inc, inc,
      0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0
    };
    Serial1.write(packet_send, sizeof(packet_send) / sizeof(packet_send[0]));
    inc++;
    last_tx = now;
  }
}
