#include "WirelessComms.h"

/*
 * Constructor
 */
WirelessComms::WirelessComms(HardwareSerial &port) : 
    _port(&port),
    _sending_period_us(100000),
    _settings_period_us(1000000),
    _time_at_last_send(0),
    _time_at_last_read(0) { }

/*
 * @brief Initializes the hardware for the Serial Port
 */
void WirelessComms::begin(uint32_t baud){
    _baud = baud;
    _port->begin(_baud);
}

void WirelessComms::read_packet() {
    // RESET _is_reading_data WHEN TIME SINCE LAST BYTE RECEIVED IS LARGE
    if(_port->available()){
        // Serial.print("p");
        while(_port->available()) {
        	// Serial.print("r");
        	_packet_read.push_back(_port->read());
        }
        _time_at_last_read = micros();

        if(_packet_read.size() >= 2) {
            bool is_end_of_packet = 1;
            int packet_size = _packet_read.size();
            for (int i = 0; (i < 2 && is_end_of_packet); ++i){
                if(_packet_read[packet_size - 2 + i] != _end_code[i]) is_end_of_packet = 0;
            }
            if(is_end_of_packet){
		        // Serial.write(&_packet_read[0], _packet_read.size());
                unpacketize();
                _packet_read.clear();
            }
        }
    } else if ((micros() - _time_at_last_read) > 5000000) {
        _is_reading_data = 0; // If you haven't gotten a packet for longer than 5 second, assume you've lost connection
        // Serial.println("no data");
    }
    // Serial.println("b");
  //     while(_port->available()){
  //   Serial.println(_port->read(), HEX);
  // }
}

void WirelessComms::send_packet() {
    // if time_interval < passed time, continue
    uint32_t time_current = micros();
    if(_is_sending_data){
        if(abs(time_current - _time_at_last_send) >= _sending_period_us){
            packetize();
            // Serial.println(_packet_send[0], HEX);
            _port->write(_packet_send.data(), _packet_send.size());
            _time_at_last_send = time_current;
            _packet_send.clear();
        }
    } else {
        if(abs(time_current - _time_at_last_send) >= _settings_period_us){
            packetize();
            _port->write(_packet_send.data(), _packet_send.size());
            _time_at_last_send = time_current;
            _packet_send.clear();
        }
    }
}

HardwareSerial *WirelessComms::get_port() {
    return _port;
}

