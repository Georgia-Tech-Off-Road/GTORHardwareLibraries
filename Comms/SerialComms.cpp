#include "SerialComms.h"

/*
 * Constructor
 */
SerialComms::SerialComms(usb_serial_class &port) : 
    _port(&port),
    _sending_period_us(10000),
    _settings_period_us(500000),
    _time_at_last_send(0),
    _time_at_last_read(0),
    _monitor_timer(200) { }

/*
 * @brief Initializes the hardware for the Serial Port
 */
void SerialComms::begin(uint32_t baud=230400){
    _baud = baud;
    _port->begin(_baud);
}

void SerialComms::read_packet() {
    // RESET _is_reading_data WHEN TIME SINCE LAST BYTE RECEIVED IS LARGE
    if(_port->available()){
        // Serial.print("p");
        while(_port->available()) _packet_read.push_back(_port->read());
        _time_at_last_read = micros();

        if(_packet_read.size() >= 8) {
            bool is_end_of_packet = 1;
            int packet_size = _packet_read.size();
            for (int i = 0; (i < 8 && is_end_of_packet); ++i){
                if(_packet_read[packet_size - 8 + i] != _end_code[i]) is_end_of_packet = 0;
            }
            if(is_end_of_packet){
                unpacketize();
                _packet_read.clear();
            }
        }
    } else if ((micros() - _time_at_last_read) > 1000000) {
        _is_reading_data = 0; // If you haven't gotten a packet for longer than 1 second, assume you've lost connection
    }
}

void SerialComms::send_packet() {
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

usb_serial_class *SerialComms::get_port() {
    return _port;
}

void SerialComms::update_monitor() {
    read_packet();

    if(_monitor_timer.ready(micros())){
        _port->println("===============SerialComms::update_monitor()===============");
        for(auto it = _output_blocks.begin(); it != _output_blocks.end(); it++){
            uint8_t *pack = new byte[(*it)->get_packlen()];
            (*it)->pack(pack);
            _port->print((*it)->get_id());
            _port->print(": ");
            uint32_t print = 0;
            for(uint8_t i = 0; i < (*it)->get_packlen(); ++i){
                print = print << 8;
                print = print | pack[(*it)->get_packlen() - i - 1];
            }
            _port->print(print, DEC);
            _port->println();
            delete pack;
        }
        for(auto tp = _throughput_comms.begin(); tp != _throughput_comms.end(); tp++){
            for(auto it = (*tp)->_received_blocks.begin(); it != (*tp)->_received_blocks.end(); it++){
                block_id_t id = (*it)->get_id();
                bool detached = 0;
                for(auto ds = _detached_blocks.begin(); (ds != _detached_blocks.end() && !detached); ds++){
                    if((*ds) == id) detached = 1;
                }
                if(!detached){
                    uint8_t *pack = new byte[(*it)->get_packlen()];
                    (*it)->pack(pack);
                    _port->print((*it)->get_id());
                    _port->print(": ");
                    uint32_t print = 0;
                    for(uint8_t i = 0; i < (*it)->get_packlen(); ++i){
                        print = print << 8;
                        print = print | pack[(*it)->get_packlen() - i - 1];
                    }
                    _port->print(print, DEC);
                    _port->println();
                    delete pack;
                }
            }
        }

        _port->println();
        _port->println();
    }
}

// void SerialComms::update_plotter() {
//     read_packet();

//     if(_monitor_timer.ready(micros())){
//         for(auto it = _output_blocks.begin(); it != _output_blocks.end(); it++){
//             _port->print((*it)->get_id());
//             _port->print(":");
//             _port->print((*it)->get_data());
//             _port->print("\t");
//         }

//         _port->println();
//     }
// }
