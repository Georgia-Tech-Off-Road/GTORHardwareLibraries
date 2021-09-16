#ifndef SENSOR_H
#define SENSOR_H

#include <vector>
#include "./SensorId.h"

enum sensor_type_t : uint8_t {
    PASSIVE, ACTIVE
};

template <class DataType>
class Sensor : public BaseSensor {
protected:
    DataType _data;

public:
    Sensor(){
        _id = DEFAULT_NO_SENSOR;
        _type = ACTIVE;
        _pack_bytes = sizeof(DataType);
    }

    /**
     * Getters and Setters
     */
    virtual const DataType& get_data() {
        return _data;
    }
    virtual const DataType& update_internal() {
        if(_type == ACTIVE){
            return update();
        }
        return _data;
    }
    virtual const DataType& update() = 0;

    virtual sensor_id_t get_id(){
        return _id;
    }
    virtual void set_id(sensor_id_t id){
        _id = id;
    }
    virtual sensor_type_t get_type(){
        return _type;
    }
    virtual void set_type(sensor_type_t type){
        _type = type;
    }
    virtual uint8_t get_pack_bytes(){
        return _pack_bytes;
    }
    virtual void set_pack_bytes(uint8_t pack_bytes){
        _pack_bytes = pack_bytes;
    }

    /**
     * Member functions
     */
    virtual void pack   (byte *pack) {
        memcpy(((DataType*)pack), &_data, sizeof(DataType));
        *((DataType*)pack) = _data;
    }
    virtual void unpack (const  byte *pack) {
        _data = *((DataType*)pack);
    }
};

class GenericSensor : public Sensor<std::vector<byte>> {
public:
    GenericSensor (sensor_id_t id, uint8_t pack_bytes){
        _id = id;
        _pack_bytes = pack_bytes;
        _type = PASSIVE;
        _data.resize(pack_bytes);
    }
    void pack   (byte* pack){
        memcpy(pack, _data.data(), _pack_bytes);
    }
    void unpack (const byte* pack){
        memcpy(_data.data(), pack, _pack_bytes);
    }
    const std::vector<byte>& get_data(){
        return _data;
    }
};


// Sending states.
// Default (initial) state will be 0
template<typename StateType>
class StateSensor : public Sensor<StateType> {
public:
    StateSensor(){
        _pack_bytes = sizeof(StateType);
    }
    void pack(byte* pack){
        *((StateType*)pack) = _data;
    }
    void unpack (const byte* pack){
        _data = *((StateType*)pack);
    }
    void set_state(StateType state){
        _data = state;
    }
    StateType get_state(){
        return get_data();
    }
    const StateType& get_data(){
        return _data;
    }
};


#include "../LDS/LDS.h"
#include "../TimeSensor/TimeSensor.h"
#include "../BrakePressureTransducer/BrakePressureTransducer.h"
#include "../SpeedSensor/SpeedSensor.h"
#include "../SparkFun_Qwiic_Scale_NAU7802_Arduino_Library-master/src/SparkFun_Qwiic_Scale_NAU7802_Arduino_Library.h"
//#include "../RTCSensor/RTCSensor.h"
#include "./DerivedSensors/ADCSensor.h"
#include "./DerivedSensors/ButtonSensor.h"

#endif
