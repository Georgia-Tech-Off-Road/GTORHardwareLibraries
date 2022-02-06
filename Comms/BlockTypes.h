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

typedef struct {
    uint32_t position;
    uint16_t speed;
} speed_sensor_data_t;

template class Block<speed_sensor_data_t>;

#endif