#include "GPSSensor.h"

GPSSensor::GPSSensor(HardwareSerial& port) : 
    _comms_flags(GPS_COMMS_DEFAULT),
    _port(port) { 
    reset_packlen();
}

void GPSSensor::begin() {
    _port.begin(9600);
}

void GPSSensor::set_comms_flag (uint16_t comms_addr, bool comms_flag){
    if(comms_flag) _comms_flags |= comms_addr;
    else           _comms_flags &= (~comms_addr);
    reset_packlen();
}

void GPSSensor::set_comms_flags (uint16_t comms_flags) {
    _comms_flags = comms_flags;
    reset_packlen();
}

void GPSSensor::reset_packlen(){
    uint8_t set_bits = 0;
    for(uint8_t i = 0; i < 16; ++i){
        if(_comms_flags & (1 << i)) ++set_bits;
    }
    this->set_packlen(set_bits * 4);
}

void GPSSensor::update() {
    while(_port.available()) {
        char r = _port.read();
        _gps.encode(r);
        if (r == '*') { // End of a transaction, GPS gets updated.
            gps_data_t new_data;
            //_gps.get_position(&new_data.location.lat(), &new_data.location.lng());
            //_gps.get_datetime(&new_data.date, &new_data.time);
            new_data.latitude = _gps.location.lat();
            new_data.longitude = _gps.location.lng();
            new_data.date = _gps.date.value();
            new_data.time = _gps.time.value();
            new_data.altitude = _gps.altitude.meters();
            new_data.course = _gps.course.deg();
            new_data.speed = _gps.speed.mph();
            new_data.satellites = _gps.satellites.value();
            new_data.hdop = _gps.hdop.hdop();
            this->set_data(new_data);
        }
    }
}

uint32_t pack_double(double d) {
  return (int) (d * 1.0e7);
}

double unpack_double(uint32_t i) {
  return i / 1.0e7;
}

void GPSSensor::pack   (uint8_t* pack) {
    uint32_t* pack_ptr = (uint32_t*) pack;
    if(_comms_flags & GPS_COMMS_LATITUDE  ) *(pack_ptr++) = pack_double(this->_data.latitude) ;
    if(_comms_flags & GPS_COMMS_LONGITUDE ) *(pack_ptr++) = pack_double(this->_data.longitude);
    if(_comms_flags & GPS_COMMS_DATE      ) *(pack_ptr++) =             this->_data.date      ;
    if(_comms_flags & GPS_COMMS_TIME      ) *(pack_ptr++) =             this->_data.time      ;
    if(_comms_flags & GPS_COMMS_ALTITUDE  ) *(pack_ptr++) = pack_double(this->_data.altitude );
    if(_comms_flags & GPS_COMMS_COURSE    ) *(pack_ptr++) = pack_double(this->_data.course   );
    if(_comms_flags & GPS_COMMS_SPEED     ) *(pack_ptr++) = pack_double(this->_data.speed    );
    if(_comms_flags & GPS_COMMS_SATELLITES) *(pack_ptr++) =             this->_data.satellites;
    if(_comms_flags & GPS_COMMS_HDOP      ) *(pack_ptr++) = pack_double(this->_data.hdop     );
}

void GPSSensor::unpack (const uint8_t* pack) {
    const uint32_t* pack_ptr = (const uint32_t*) pack;
    if(_comms_flags & GPS_COMMS_LATITUDE  ) this->_data.latitude   = unpack_double(*(pack_ptr++));
    if(_comms_flags & GPS_COMMS_LONGITUDE ) this->_data.longitude  = unpack_double(*(pack_ptr++));
    if(_comms_flags & GPS_COMMS_DATE      ) this->_data.date       =               *(pack_ptr++) ;
    if(_comms_flags & GPS_COMMS_TIME      ) this->_data.time       =               *(pack_ptr++) ;
    if(_comms_flags & GPS_COMMS_ALTITUDE  ) this->_data.altitude   = unpack_double(*(pack_ptr++));
    if(_comms_flags & GPS_COMMS_COURSE    ) this->_data.course     = unpack_double(*(pack_ptr++));
    if(_comms_flags & GPS_COMMS_SPEED     ) this->_data.speed      = unpack_double(*(pack_ptr++));
    if(_comms_flags & GPS_COMMS_SATELLITES) this->_data.satellites =               *(pack_ptr++) ;
    if(_comms_flags & GPS_COMMS_HDOP      ) this->_data.hdop       = unpack_double(*(pack_ptr++));
}
