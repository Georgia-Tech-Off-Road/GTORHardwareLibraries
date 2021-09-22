#ifndef SDWRITE_H
#define SDWRITE_H

#include "BaseComms.h"
#include <SD.h>

class SDWrite : public BaseComms {
private:
    const uint8_t _port;
    String _filename;

    const uint16_t _sending_period_us;
    uint32_t _time_at_last_send;

    void read_packet();
    void send_packet();
    
public:
    SDWrite(uint8_t port);
    void begin(const char* filename);
    const uint8_t get_port();
};


#endif