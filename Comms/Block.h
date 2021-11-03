#ifndef BLOCK_H
#define BLOCK_H

#include <Arduino.h>
#include <vector>

typedef uint16_t block_id_t;

/**
 * BaseBlock is the unit of all communications.
 * DO NOT extend this class directly! Use Sensor or Generic...
 * All communications over the protocol will use this base type.
 * All blocks are assumed to have write and read capabilities.
 */

class BaseBlock {
protected:
	block_id_t _id;
    uint8_t    _packlen;

public:
    BaseBlock(block_id_t id, uint8_t packlen);

    virtual block_id_t get_id();
    virtual void set_id(block_id_t id);
    virtual uint8_t get_packlen();
    virtual void set_packlen(uint8_t packlen);

    /**
     * VERY IMPORTANT FUNCTIONS!!! Must be defined for use anywhere in Comms.
     */

    /**
     * pack <==> write
     * pack will write its data to an inputted uint8_t (byte) buffer.
     * All comms blocks need to send data in byte array format.
     */
    virtual void pack   (uint8_t* pack) = 0;

    /**
     * unpack <==> read
     * unpack will take data from an inputted uint8_t (byte) buffer.
     * All comms blocks need to read data in byte array format.
     */
    virtual void unpack (const uint8_t* pack) = 0;

    virtual void update () = 0;
};

template <typename DataType>
class Block : public BaseBlock {
protected:
    DataType _data;

public:
    Block();

    /**
     * DANGEROUS!! ONLY USE FOR DIRECT BLOCK USAGE! USE UPDATE FOR MOST CASES
     */
    virtual void  set_data(const DataType& data);
    virtual const DataType& get_data();

    virtual void pack   (uint8_t* pack);
    virtual void unpack (const uint8_t* pack);
    virtual void update ();
};

class DynamicBlock : public Block<std::vector<uint8_t>> {
public:
    DynamicBlock (block_id_t id, uint8_t packlen);
    void pack   (uint8_t* pack);
    void unpack (const uint8_t* pack);
};

#include "BlockTypes.h"

#endif
