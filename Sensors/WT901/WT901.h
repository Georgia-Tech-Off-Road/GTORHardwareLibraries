#ifndef WT901_H
#include "Block.h"
#include "arm_math.h"

#define ACC_FFT_LEN 256
#define SERIAL_BUF_LEN 11
#define SERIAL_SETTING 0
#define FS 200
#define LEAK 0.98
#define G 9.8
#define MPS_MPH 2.237
#define EPS 0.0

class WT901 : public Block<WT901_data_t> {
public:
    typedef enum {
        TIME    = 0x50,
        ACC     = 0x51,
        ANGV    = 0x52,
        ANG     = 0x53,
        MAG     = 0x54,
        DSTATUS = 0x55,
        ATM     = 0x56,
        GPS     = 0x57,
        GPSV    = 0x58,
        QUAT    = 0x59,
        GPSACC  = 0x5a,
    } output_command_t;

    typedef enum {
        SAVE     = 0x00,
        CALSW    = 0x01,
        RSW      = 0x02,
        RRATE    = 0x03,
        BAUD     = 0x04,
        AXOFFSET = 0x05,
        AYOFFSET = 0x06,
        AZOFFSET = 0x07,
        GXOFFSET = 0x08,
        GYOFFSET = 0x09,
        GZOFFSET = 0x0a,
        HXOFFSET = 0x0b,
        HYOFFSET = 0x0c,
        HZOFFSET = 0x0d,
        D0MODE   = 0x0e,
        D1MODE   = 0x0f,
        D2MODE   = 0x10,
        D3MODE   = 0x11,
        D0PWMH   = 0x12,
        D1PWMH   = 0x13,
        D2PWMH   = 0x14,
        D3PWMH   = 0x15,
        D0PWMT   = 0x16,
        D1PWMT   = 0x17,
        D2PWMT   = 0x18,
        D3PWMT   = 0x19,
        IICADDR  = 0x1a,
        LEDOFF   = 0x1b,
        GPSBAUD  = 0x1c,
    } config_command_t;

    typedef enum {
        HZ0_2  = 0x01,
        HZ0_5  = 0x02,
        HZ1    = 0x03,
        HZ2    = 0x04,
        HZ5    = 0x05,
        HZ10   = 0x06,
        HZ20   = 0x07,
        HZ50   = 0x08,
        HZ100  = 0x09,
        HZ125  = 0x0a,
        HZ200  = 0x0b,
        SINGLE = 0x0c,
        NOT    = 0x0d,
    } return_rate_t;

    typedef enum {
        B4800   = 0x01,
        B9600   = 0x02,
        B19200  = 0x03,
        B38400  = 0x04,
        B57600  = 0x05,
        B115200 = 0x06,
        B230400 = 0x07,
        B460800 = 0x08,
        B921600 = 0x09,
    } baud_rate_t;

    float acc_fft_buf[ACC_FFT_LEN*2];
    float out_fft_buf[ACC_FFT_LEN*2];
    uint16_t acc_fft_loc;
    arm_rfft_fast_instance_f32 acc_fft_inst;

    WT901(HardwareSerial& port);
    void begin(baud_rate_t baud = B9600);
    void update();
    void setup();

    void unlock();
    void set_return_rate(return_rate_t return_rate);
    void set_config(config_command_t command, uint16_t data);
    void set_return(output_command_t command, bool setting);

    void pack  (uint8_t* pack);
    void unpack(const uint8_t* pack);
    void printall();

private:
    HardwareSerial * _port;
    baud_rate_t _baudrate;
    uint32_t _baud;
    uint16_t _returncontent;
};

#endif