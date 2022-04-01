#ifndef SDCOMMS_H
#define SDCOMMS_H

#include "Comms.h"
// #include "SD.h"
#include "SdFat.h"
#include <TimeLib.h>

extern SdFs sd;

class SDComms : public Comms {
private:
    const uint8_t _port;
    String _filename;
    Block<bool>* _writecommand;

    const uint16_t _sending_period_us;
    uint32_t _time_at_last_send;

    void read_packet();
    void send_packet();
    void packetize();
    
public:
    SDComms(uint8_t port = -1);
    void begin(const char* filename);
    const uint8_t get_port();
    void attach_writecommand_block(Block<bool>* writecommand);
};


#endif