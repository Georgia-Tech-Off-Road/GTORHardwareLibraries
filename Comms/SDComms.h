#ifndef SDCOMMS_H
#define SDCOMMS_H

#include "Comms.h"
#include <SD.h>

class SDComms : public Comms {
private:
    const uint8_t _port;
    String _filename;

    const uint16_t _sending_period_us;
    uint32_t _time_at_last_send;

    void read_packet();
    void send_packet();
    
public:
    SDComms(uint8_t port);
    void begin(const char* filename);
    const uint8_t get_port();
};


#endif