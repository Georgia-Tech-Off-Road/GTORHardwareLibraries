#ifndef UARTCOMMS_H
#define UARTCOMMS_H

#include "Comms.h"

class UARTComms : public Comms {
private:
    HardwareSerial * const _port;
    const uint32_t _baud;

    const uint32_t _sending_period_us;
    const uint32_t _settings_period_us;
    uint32_t _time_at_last_send;
    uint32_t _time_at_last_receive;

    void read_packet();
    void send_packet();
    
public:
    UARTComms(uint32_t baud, HardwareSerial &port);
    void begin();
    HardwareSerial *get_port();
};

#endif