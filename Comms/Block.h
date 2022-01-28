/**
 * File: Block.h
 * Author: Akash Harapanahalli
 * 
 * Blocks are the base unit of all communications under DAQCP.
 * For more information about DAQCP, check the DAQCP documentation.
 * 
 * At their core, Blocks are very simple and do the following:
 *  - store data of any type (primitive or user-defined)
 *  - "pack" its data into a byte array to send over Comms
 *  - "unpack" byte arrays from Comms to set its data (not an active Block)
 *  - "update" its data through some user-defined sequence (active Block)
 * 
 * Active Blocks are being actively set by the host microcontroller.
 * Passive Blocks are not, instead having their values received over Comms.
 * 
 * All instances of Block have their own unique ID. See BlockId.h
 * 
 * See Block.cpp for implementation details.
 */

#ifndef BLOCK_H
#define BLOCK_H

#include <Arduino.h>
#include <vector>
#include "BlockId.h"

/**
 * BaseBlock
 * 
 * BaseBlock is an Abstract Class that implements all of Block except for the data.
 * They are separated because templated classes cannot have polymorphic references.
 * Instead, we have polymorphic references to BaseBlock.
 * 
 * DO NOT extend BaseBlock class directly! Use Block or some extension of Block.
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


/**
 * Block
 * 
 * Extend Block when you need to communicate over DAQCP.
 */

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
