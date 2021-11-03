#include "SDComms.h"

/*
 * Constructor
 */
SDComms::SDComms(uint8_t port) : 
    _port(port),
    _sending_period_us(10000),
    _time_at_last_send(0) { }

/*
 * @brief Initializes the hardware for the Serial Port
 */
void SDComms::begin(const char* filename){
    SD.begin(_port);
    _filename = String(filename);
}

void SDComms::read_packet() {
    // Do nothing. SDComms only sends packets.
}

void SDComms::send_packet() {
    // if time_interval < passed time, continue
    uint32_t time_current = micros();
    if(abs(time_current - _time_at_last_send) >= _sending_period_us){
        packetize();
        File datafile = SD.open(_filename.c_str(), FILE_WRITE);
        datafile.write(_packet_send.data(), _packet_send.size());
        datafile.close();
        // Serial.println("Wrote data");
        _time_at_last_send = time_current;
        _packet_send.clear();
    }
}

const uint8_t SDComms::get_port() {
    return _port;
}

