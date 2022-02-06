#include "SDComms.h"

SdFs sd;

static time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}

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
    // if(_port == -1){
    sd.begin(SdioConfig(FIFO_SDIO));
    // } else {
    // }

    if(filename == NULL){
        setSyncProvider(getTeensy3Time);
        // "YYYY-MM-DD_HH-MM-SS.bin"
        char s[30];
        sprintf(s, "%04d-%02d-%02d_%02d-%02d-%02d.bin", year(), month(), day(), hour(), minute(), second());

        _filename = String(s);
    } else {
        _filename = String(filename);
    }

}

void SDComms::read_packet() {
    // Do nothing. SDComms only sends packets.
}

void SDComms::send_packet() {
    // if time_interval < passed time, continue
    uint32_t time_current = micros();
    if(abs(time_current - _time_at_last_send) >= _sending_period_us){
        packetize();
        // File datafile = SD.open(_filename.c_str(), FILE_WRITE);
        // File datafile = SD.open("bruh.bin", FILE_WRITE);
        // FsFile datafile = SD.sdfs.open(_filename.c_str(), O_WRITE | O_CREAT);

        FsFile datafile;
        datafile.open(_filename.c_str(), O_WRITE | O_CREAT | O_APPEND);
        datafile.write(_packet_send.data(), _packet_send.size());
        datafile.close();

        _time_at_last_send = time_current;
        _packet_send.clear();
    }
}

void SDComms::packetize() {
    uint8_t ack = (0x02 & (_is_sending_data << 1)) | (0x01 & (0));
    _packet_send.push_back(ack);
    if(_is_sending_data){
        // ack or 0x02
        for(auto it = _output_blocks.begin(); it != _output_blocks.end(); it++){
            uint8_t *pack = new byte[(*it)->get_packlen()];
            (*it)->pack(pack);
            for(int i = 0; i < (*it)->get_packlen(); ++i) _packet_send.push_back(pack[i]);
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
                    for(int i = 0; i < (*it)->get_packlen(); ++i) _packet_send.push_back(pack[i]);
                    delete pack;
                }
            }
        }
    } else {
        // ack should be 0x01 or 0x00
        for(auto it = _output_blocks.begin(); it != _output_blocks.end(); it++){
            uint16_t id = (*it)->get_id();
            uint8_t id_byte_1 = *((uint8_t *)(&id));
            uint8_t id_byte_2 = *((uint8_t *)(&id) + 1);
            uint8_t pack_bytes = (*it)->get_packlen();
            _packet_send.push_back(id_byte_1);
            _packet_send.push_back(id_byte_2);
            _packet_send.push_back(pack_bytes);
        }
        for(auto tp = _throughput_comms.begin(); tp != _throughput_comms.end(); tp++){
            for(auto it = (*tp)->_received_blocks.begin(); it != (*tp)->_received_blocks.end(); it++){
                bool detached = 0;
                uint16_t id = (*it)->get_id();
                for(auto ds = _detached_blocks.begin(); (ds != _detached_blocks.end() && !detached); ds++){
                    if((*ds) == id) detached = 1;
                }
                if(!detached){
                    uint8_t id_byte_1 = *((uint8_t *)(&id));
                    uint8_t id_byte_2 = *((uint8_t *)(&id) + 1);
                    uint8_t pack_bytes = (*it)->get_packlen();
                    _packet_send.push_back(id_byte_1);
                    _packet_send.push_back(id_byte_2);
                    _packet_send.push_back(pack_bytes);
                }
            }
        }
        // Always set this flag... Write Settings once and then write data.
        _is_sending_data = 1;
    }
    for(int i = 0; i < 8; ++i) _packet_send.push_back(_end_code[i]);

    // if need to send settings:
    // settings will be a list of id/byte_length pair.
    // ack is 0x01 or 0x00, depending on checks from unpacketize.
    // 2 uint8_t id, 1 uint8_t byte_length

    // if need to send data:
    // ack is 0x03 or 0x02, depending on checks from unpacketize.
    // packetize
}

const uint8_t SDComms::get_port() {
    return _port;
}

