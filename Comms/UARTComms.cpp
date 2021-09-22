#include "UARTComms.h"

/*
 * Constructor
 */
UARTComms::UARTComms(uint32_t baud, HardwareSerial &port) : 
    _port(&port),
    _baud(baud), 
    _sending_period_us(10000),
    _settings_period_us(500000),
    _time_at_last_send(0),
    _time_at_last_receive(0) { }

/*
 * @brief Initializes the hardware for the Serial Port
 */
void UARTComms::begin(){
    _port->begin(_baud);
}

void UARTComms::read_packet() {
    // RESET _IS_RECEIVING_DATA WHEN TIME SINCE LAST BYTE RECEIVED IS LARGE
    if(_port->available()){
        // Serial.print("p");
        while(_port->available()) _packet_receive.push_back(_port->read());
        _time_at_last_receive = micros();

        if(_packet_receive.size() >= 8) {
            bool is_end_of_packet = 1;
            int packet_size = _packet_receive.size();
            for (int i = 0; (i < 8 && is_end_of_packet); ++i){
                if(_packet_receive[packet_size - 8 + i] != _end_code[i]) is_end_of_packet = 0;
            }
            if(is_end_of_packet){
                unpacketize();
                _packet_receive.clear();
            }
        }
    } else if ((micros() - _time_at_last_receive) > 1000000) {
        _is_receiving_data = 0; // If you haven't gotten a packet for longer than 1 second, assume you've lost connection
    }
}

void UARTComms::send_packet() {
    // if time_interval < passed time, continue
    uint32_t time_current = micros();
    if(_is_sending_data){
        if(abs(time_current - _time_at_last_send) >= _sending_period_us){
            packetize();
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

HardwareSerial *UARTComms::get_port() {
    return _port;
}

