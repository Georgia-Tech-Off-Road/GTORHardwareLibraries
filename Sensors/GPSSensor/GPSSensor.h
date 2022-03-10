#ifndef GPSSENSOR_H
#define GPSSENSOR_H

#include "Block.h"
#include "TinyGPS.h"

struct gps_data_t {
    int32_t  latitude;
    int32_t  longitude;
    uint32_t date;
    uint32_t time;
    int32_t  altitude;
    uint32_t course;
    uint32_t speed;
    uint32_t satellites;
    uint32_t hdop;
};

#define GPS_COMMS_LATITUDE   0b0000000001
#define GPS_COMMS_LONGITUDE  0b0000000010
#define GPS_COMMS_DATE       0b0000000100
#define GPS_COMMS_TIME       0b0000001000
#define GPS_COMMS_ALTITUDE   0b0000010000
#define GPS_COMMS_COURSE     0b0000100000
#define GPS_COMMS_SPEED      0b0001000000
#define GPS_COMMS_SATELLITES 0b0010000000
#define GPS_COMMS_HDOP       0b0100000000

#define GPS_COMMS_DEFAULT    (GPS_COMMS_LATITUDE | GPS_COMMS_LONGITUDE)

class GPSSensor : public Block<gps_data_t> {
public:
    GPSSensor(HardwareSerial& port);
    void begin();
    void set_comms_flag  (uint16_t comms_addr, bool comms_flag);
    void set_comms_flags (uint16_t comms_flags);
    void update();
    void pack   (uint8_t* pack);
    void unpack (const uint8_t* pack);
private:
    TinyGPS _gps;
    HardwareSerial& _port;
    uint16_t _comms_flags;
    void reset_packlen();
};

#endif