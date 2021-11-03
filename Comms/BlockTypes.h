template class Block<uint8_t>;
template class Block<uint16_t>;
template class Block<uint32_t>;
template class Block<float>;
template class Block<double>;

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