/**
 * File: BlockTypes.h
 * Author: Akash Harapanahalli
 * 
 * Whenever you want a new data type for Block to use, add it here.
 * 
 * This file is a quick fix to a stupid problem.
 * All template types need to be known when Block.cpp is compiled.
 * The reason is because the compiler needs to make different versions
 *      of each Block function for each different template type.
 * Since things are compiled in units, Block may not be in the same 
 *      unit as where each template type is. Therefore, the system
 *      would not know to make versions for those types.
 * To avoid this problem, all possible Block types are listed here.
 */

#ifndef BLOCKTYPES_H
#define BLOCKTYPES_H

/**
 * Primitive and Basic Types
 */

template class Block<uint8_t>;
template class Block<uint16_t>;
template class Block<uint32_t>;
template class Block<int8_t>;
template class Block<int16_t>;
template class Block<int32_t>;
template class Block<float>;
template class Block<double>;
template class Block<bool>;

template class Block<std::vector<uint8_t>>;

/**
 * User Defined Types
 */

struct float_3d_t {
    float x;
    float y;
    float z;
};
struct imu_data_t {
    float_3d_t acceleration;
    float_3d_t gyro;
    float temperature;
};
template class Block<imu_data_t>;
struct WT901_data_t {
    struct {
        uint8_t ymdhms[6];
        uint16_t millisecond;
    } time;
    struct {
        int16_t a[3];
        int16_t temp;
    } acc;
    struct {
        uint16_t w[3];
        uint16_t temp;
    } angv;
    struct {
        uint16_t rpy[3];
        uint16_t version;
    } ang;
    struct {
        uint16_t H[3];
        uint16_t temp;
    } mag;
    struct {
        uint16_t d[4];
    } dstatus;
    struct {
        uint32_t pressure;
        uint32_t altitude;
    } atm;
    struct {
        uint32_t longitude;
        uint32_t latitude;
    } gps;
    struct {
        uint16_t height;
        uint16_t yaw;
        uint32_t velocity;
    } gpsv;
    struct {
        int16_t q[4];
    } quat;
    struct {
        uint16_t satquan;
        uint16_t locaccu;
        uint16_t horaccu;
        uint16_t veraccu;
    } gpsacc;

    float acc_mag;
    float speed;
};
template class Block<WT901_data_t>;

struct Neo6M_data_t {
    // int32_t lon;
    // int32_t lat;
    int32_t ecefp[3];
    int32_t ecefv[3];
    uint16_t length;
};
template class Block<Neo6M_data_t>;

typedef struct {
    int32_t position;
    uint16_t speed;
} speed_sensor_data_t;

template class Block<speed_sensor_data_t>;

struct gps_data_t {
    double  latitude;
    double  longitude;
    uint32_t date;
    uint32_t time;
    double  altitude;
    double course;
    double speed;
    uint32_t satellites;
    double hdop;
};

template class Block<gps_data_t>;

#endif