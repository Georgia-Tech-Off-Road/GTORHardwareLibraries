#ifndef WIRELESSCOMMS_H
#define WIRELESSCOMMS_H

#include "Comms.h"

class WirelessComms : public Comms {
private:
    HardwareSerial * const _port;
    uint32_t _baud;

    const uint32_t _sending_period_us;
    const uint32_t _settings_period_us;
    uint32_t _time_at_last_send;
    uint32_t _time_at_last_read;

    void read_packet();
    void send_packet();
    
public:
    WirelessComms(HardwareSerial &port);
    void begin(uint32_t baud);
    HardwareSerial *get_port();
};

#endif