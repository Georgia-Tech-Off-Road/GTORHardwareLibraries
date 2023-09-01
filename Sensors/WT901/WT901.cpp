#include "WT901.h"

WT901::WT901(HardwareSerial& port) :
    _port(&port),
    _baudrate(B9600),
    _baud(9600) { 
    _packlen = 40;
    arm_rfft_fast_init_f32(&acc_fft_inst, ACC_FFT_LEN);
    for(int i = 0; i < ACC_FFT_LEN; ++i) {
        acc_fft_buf[i] = 0;
        out_fft_buf[i] = 0;
    }
}

void WT901::begin(baud_rate_t baudrate) {
    _port->begin(_baud);
    // _port->begin(_baud);
    _baudrate = baudrate;
    // switch(baudrate) {
    //     case B4800  : _baud =   4800; break;
    //     default:
    //     case B9600  : _baud =   9600; break;
    //     case B19200 : _baud =  19200; break;
    //     case B38400 : _baud =  38400; break;
    //     case B57600 : _baud =  57600; break;
    //     case B115200: _baud = 115200; break;
    //     case B230400: _baud = 230400; break;
    //     case B460800: _baud = 460800; break;
    //     case B921600: _baud = 921600; break;
    // }
    // unlock();
    // set_config(BAUD, _baudrate);
    // set_config(SAVE, 0);
    // _port->write(0xFF);
    // _port->write(0xAA);
    // _port->write(0x04);
    // _port->write(0x01);
    // _port->write(0x00);
    // delayMicroseconds(10000);
    // _port->flush();
    // delayMicroseconds(10000);
    // _port->end();
    // delayMicroseconds(10000);
    // _port->begin(_baud);
    // delayMicroseconds(10000);
}

void WT901::update() {
    static uint32_t timer;
    while(_port->available() > SERIAL_BUF_LEN){
        if(_port->read() == 0x55) { // Start of packet command
            output_command_t command = (output_command_t) _port->read();
            uint8_t* out_buf;
            switch (command) { 
                default:
                case TIME   : out_buf = (uint8_t*) &(this->_data.time);    break;
                case ACC    : out_buf = (uint8_t*) &(this->_data.acc);     break;
                case ANGV   : out_buf = (uint8_t*) &(this->_data.angv);    break;
                case ANG    : out_buf = (uint8_t*) &(this->_data.ang);     break;
                case MAG    : out_buf = (uint8_t*) &(this->_data.mag);     break;
                case DSTATUS: out_buf = (uint8_t*) &(this->_data.dstatus); break;
                case ATM    : out_buf = (uint8_t*) &(this->_data.atm);     break;
                case GPS    : out_buf = (uint8_t*) &(this->_data.gps);     break;
                case GPSV   : out_buf = (uint8_t*) &(this->_data.gpsv);    break;
                case QUAT   : out_buf = (uint8_t*) &(this->_data.quat);    break;
                case GPSACC : out_buf = (uint8_t*) &(this->_data.gpsacc);  break;
            }
            for(uint8_t i = 0; i < 8; ++i){
                out_buf[i] = _port->read();
            }
            if (command == ACC) {
                // Serial.print("TIMEDIFF: "); Serial.println(micros() - timer);
                timer = micros();
                float accx = (float) _data.acc.a[0] * 16 * G / (32768);
                float accy = (float) _data.acc.a[1] * 16 * G / (32768);
                float accz = (float) _data.acc.a[2] * 16 * G / (32768);
                // Serial.print("accx: "); Serial.println(accx);
                // Serial.print("accy: "); Serial.println(accy);
                // Serial.print("accz: "); Serial.println(accz);
                _data.acc_mag = sqrt(accx*accx + accy*accy + accz*accz);
                // q15_t acc_mag = (q15_t) sqrt(_data.acc.a[0]*_data.acc.a[0] +
                //                              _data.acc.a[1]*_data.acc.a[1] +
                //                              _data.acc.a[2]*_data.acc.a[2] ); // may need to >> 1
                // Serial.print("acc_mag: "); Serial.println(_data.acc_mag);

                if(++acc_fft_loc > ACC_FFT_LEN) acc_fft_loc = 0;
                acc_fft_buf[acc_fft_loc] = _data.acc_mag;
                acc_fft_buf[acc_fft_loc + ACC_FFT_LEN] = _data.acc_mag;
                arm_rfft_fast_f32(&acc_fft_inst, &(acc_fft_buf[acc_fft_loc + 1]), out_fft_buf, 0);
                // Serial.print("DC: "); Serial.println(out_fft_buf[0]);
                // Serial.print("DC+1: "); Serial.println(out_fft_buf[1]);
                
                float multiplier = accy;//_data.acc_mag;// - G;
                // if (multiplier < EPS) multiplier = 0;
                _data.speed = LEAK*_data.speed + multiplier/FS;
                // Serial.print("multiplier: "); Serial.println(multiplier);
                // Serial.print("SPEED: "); Serial.println(_data.speed * MPS_MPH);
                // Serial.println();
            }
            _port->read(); // Checksum (not checking)
        }
    }
}

void WT901::unlock() {
    _port->write(0xFF);
    _port->write(0xAA);
    _port->write(0x69);
    _port->write(0x88);
    _port->write(0xB5);
}

void WT901::set_return_rate(return_rate_t return_rate) {
    // unlock();
    // set_config(RRATE, return_rate);
    // set_config(SAVE, 0);
    _port->write(0xFF);
    _port->write(0xAA);
    _port->write(0x69);
    _port->write(0x88);
    _port->write(0xB5);
    _port->write(0xFF);
    _port->write(0xAA);
    _port->write(0x03);
    _port->write(0x07);
    _port->write(0x00);
    _port->write(0xFF);
    _port->write(0xAA);
    _port->write(0x00);
    _port->write(0x00);
    _port->write(0x00);
}

void WT901::set_config(config_command_t command, uint16_t data) {
    _port->write(0xFF);
    _port->write(0xAA);
    _port->write((uint8_t) command);
    _port->write((uint8_t) data);
    _port->write((uint8_t) (data >> 8));
}

void WT901::set_return(output_command_t command, bool setting){
    uint8_t index;
    switch (command) { 
        default:
        case TIME   : index =  0; break;
        case ACC    : index =  1; break;
        case ANGV   : index =  2; break;
        case ANG    : index =  3; break;
        case MAG    : index =  4; break;
        case DSTATUS: index =  5; break;
        case ATM    : index =  6; break;
        case GPS    : index =  7; break;
        case GPSV   : index =  8; break;
        case QUAT   : index =  9; break;
        case GPSACC : index = 10; break;
    }
    _returncontent = (_returncontent & ~(1 << index)) | (setting << index);
    set_config(RSW, _returncontent);
}

void WT901::pack(byte* pack){
    float* p = (float*) pack;
    *(p++) = (float) _data.acc.a[0] * 16 * G / (32768);
    *(p++) = (float) _data.acc.a[1] * 16 * G / (32768);
    *(p++) = (float) _data.acc.a[2] * 16 * G / (32768);
    *(p++) = (float) _data.ang.rpy[0] * 180 / (32768);
    *(p++) = (float) _data.ang.rpy[1] * 180 / (32768);
    *(p++) = (float) _data.ang.rpy[2] * 180 / (32768);
    *(p++) = (float) _data.quat.q[0] / (32768);
    *(p++) = (float) _data.quat.q[1] / (32768);
    *(p++) = (float) _data.quat.q[2] / (32768);
    *(p++) = (float) _data.quat.q[3] / (32768);
}
void WT901::unpack(const byte* pack){
    const float* p = (const float*) pack;
    (this->_data).acc.a[0] = (int16_t) (*(p++) * 32768 / G / 16);
    (this->_data).acc.a[1] = (int16_t) (*(p++) * 32768 / G / 16);
    (this->_data).acc.a[2] = (int16_t) (*(p++) * 32768 / G / 16);
    (this->_data).acc.a[0] = (int16_t) (*(p++) * 32768 / 180);
    (this->_data).acc.a[1] = (int16_t) (*(p++) * 32768 / 180);
    (this->_data).acc.a[2] = (int16_t) (*(p++) * 32768 / 180);
    (this->_data).quat.q[0] = (int16_t) (*(p++) * 32768);
    (this->_data).quat.q[1] = (int16_t) (*(p++) * 32768);
    (this->_data).quat.q[2] = (int16_t) (*(p++) * 32768);
    (this->_data).quat.q[3] = (int16_t) (*(p++) * 32768);
}

void WT901::printall() {
    Serial.printf("acc(%d, %d, %d) ", _data.acc.a[0], _data.acc.a[1], _data.acc.a[2]);
    Serial.printf("ang(%d, %d, %d) ", _data.ang.rpy[0], _data.ang.rpy[1], _data.ang.rpy[2]);
    Serial.printf("quat(%d, %d, %d, %d)", _data.quat.q[0], _data.quat.q[1], _data.quat.q[2], _data.quat.q[3]);
}