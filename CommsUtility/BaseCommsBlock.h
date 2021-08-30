
class BaseSensor {
protected:
    sensor_id_t   _id;
    sensor_type_t _type;
    uint8_t  _pack_bytes;

public:
    /**
     * Getters and Setters
     */
    virtual sensor_id_t get_id() = 0;
    virtual void set_id(sensor_id_t id) = 0;
    virtual sensor_type_t get_type() = 0;
    virtual void set_type(sensor_type_t type) = 0;
    virtual uint8_t get_pack_bytes() = 0;
    virtual void set_pack_bytes(uint8_t pack_bytes) = 0;

    /**
     * Member functions
     */
    virtual void pack   (byte *pack) = 0;
    virtual void unpack (const byte *pack) = 0;
};

class BaseCommsBlock {
	block_id_t	
};
