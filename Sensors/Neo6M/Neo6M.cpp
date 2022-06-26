#include "Neo6M.h"

Neo6M::Neo6M(HardwareSerial& port) : 
    _port(&port),
    _inpacket(0),
    readH(0),
    readL(0),
    _bufind(0) {
    _packlen = 12;
}

void Neo6M::begin(uint32_t baud){
    _port->begin(baud);
    // delay(2000);
    // uint8_t ck1 = 0, ck2 = 0;
    // _port->write(0xB5); 
    // _port->write(0x62);
    // _port->write(0x06); ck1 += 0x06; ck2 += ck1;
    // _port->write(0x08); ck1 += 0x08; ck2 += ck1;
    // uint16_t sen;
    // sen =   6; _port->write((uint8_t*)&sen, 2); // Length
    // ck1 += sen; ck2 += ck1;
    // sen = 200; _port->write((uint8_t*)&sen, 2); // Measurement Rate (ms)
    // ck1 += sen; ck2 += ck1;
    // sen =   5; _port->write((uint8_t*)&sen, 2); // Navigation Rate
    // ck1 += sen; ck2 += ck1;
    // sen =   0; _port->write((uint8_t*)&sen, 2); // Ref Time Alignment
    // ck1 += sen; ck2 += ck2;
    // _port->write(ck1);
    // _port->write(ck2);
}

// void Neo6M::update() {
//     while(!_inpacket && _port->available()) {
//         readL = _port->read();
//         if(readH == 0xB5 && readL == 0x62) {
//             _inpacket = 1;
//             _bufind = 0;
//         } else {
//             readH = readL;
//         }
//     }
//     while (_inpacket && _port->available()) {
//         _buf[_bufind] = _port->read();
//         if(_bufind > 3) {
//             uint16_t readlen = *((uint16_t*) &_buf[2]);
//         }
//         ++_bufind;
//     }
// }

void Neo6M::update() {
    while(!_inpacket && _port->available()) {
        readL = _port->read();
        // Serial.print("readL: "); Serial.println(readL, HEX);
        if(readH == 0xB5 && readL == 0x62) {
            _inpacket = 1;
            _bufind = 0;
            return;
        } else {
            readH = readL;
        }
    }
    while (_inpacket && _port->available()) {
        _buf[_bufind] = _port->read();
        if(_bufind > 1) {
            // Serial.print("_buf[0]: "); Serial.println(_buf[0], HEX);
            // Serial.print("_buf[1]: "); Serial.println(_buf[1], HEX);
            if(!(_buf[0] == NAV && (_buf[1] == SOL))) {
                _inpacket = 0;
                return;
            }
        }
        if(_bufind > 3) {
            _data.length = (uint16_t) *((uint16_t*) &(_buf[2]));
            if(_bufind >= (_data.length + 2)) {
                parse();
                _inpacket = 0;
            }
        }
        ++_bufind;
    }
}

void Neo6M::parse() {
    _data.ecefp[0] = (int32_t) *((int32_t*) &(_buf[16]));
    _data.ecefp[1] = (int32_t) *((int32_t*) &(_buf[20]));
    _data.ecefp[2] = (int32_t) *((int32_t*) &(_buf[24]));
    _data.ecefv[0] = (int32_t) *((int32_t*) &(_buf[32]));
    _data.ecefv[1] = (int32_t) *((int32_t*) &(_buf[36]));
    _data.ecefv[2] = (int32_t) *((int32_t*) &(_buf[40]));
}

void Neo6M::pack(byte* pack){
    float* p = (float*) pack;
    *(p++) = (float) _data.ecefp[0];
    *(p++) = (float) _data.ecefp[1];
    *(p++) = (float) _data.ecefp[2];
}

void Neo6M::unpack(const byte* pack){
    // const float* p = (const float*) pack;
    // (this->_data).gps.latitude = *(p++);
    // (this->_data).gps.longitude = *(p++);
}