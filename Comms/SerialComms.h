#ifndef SERIALCOMMS_H
#define SERIALCOMMS_H

#include "Comms.h"

class SerialComms : public Comms {
private:
    usb_serial_class * const _port;
    const uint32_t _baud;

    const uint32_t _sending_period_us;
    const uint32_t _settings_period_us;
    uint32_t _time_at_last_send;
    uint32_t _time_at_last_receive;

    void read_packet();
    void send_packet();
    
public:
    SerialComms(uint32_t baud, usb_serial_class &port);
    void begin();
    usb_serial_class *get_port();
};

#endif