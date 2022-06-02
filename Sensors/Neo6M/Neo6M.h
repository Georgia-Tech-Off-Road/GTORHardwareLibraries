#ifndef NEO6M_H
#define NEO6M_H

#include "Block.h"

#define NAV 0x01

class Neo6M : public Block<Neo6M_data_t> {
private:
    HardwareSerial * _port;
    uint8_t _buf[100];
    bool _inpacket;
    uint8_t readH, readL;
    uint8_t _bufind;
    // uint16_t _readlen;
public:
    typedef enum {
        POSLLH = 0x02,
        SVINFO = 0x30,
        VELNED = 0x12,
        POSECEF = 0x01,
        VELECEF = 0x11,
        SOL = 0x06,
    } nav_id_t;

    Neo6M(HardwareSerial& port);
    void begin(uint32_t baud);
    void update();
    void parse();

    void pack  (uint8_t* pack);
    void unpack(const uint8_t* pack);
};

#endif