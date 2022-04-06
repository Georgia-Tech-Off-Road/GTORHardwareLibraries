/**
 * File: Comms.h
 * Author: Akash Harapanahalli
 * 
 * Comms is the implementation of DAQCP.
 * For more information about DAQCP, check the DAQCP documentation.
 * 
 * Comms does the following:
 *  - Manage dynamic additions and removal of blocks (input or output)
 *  - "packetize" all blocks into settings and data packets
 *  - "send_packet" to the other side (done in derived classes)
 *  - "unpacketize" settings and data packets and set received blocks
 *  - "read_packet" from the other side (done in derived classes)
 * 
 * See Block.cpp for implementation details.
 */

#ifndef COMMS_H
#define COMMS_H

#include "Block.h"

/**
 * end_code_t
 * 
 * Creates the end code (0xFFFFFFFFFFFFF0)
 * Is a struct so we can make it a constant object and treat it like its
 *      not a pesky C++ array :)
 */

struct end_code_t {
    uint8_t code[8];
    end_code_t();
    const uint8_t& operator[] (uint8_t i) const;
};

/**
 * Comms
 * 
 * The class where all the magic happens
 */

class Comms {
protected:
    /**
     * Flags for two-way communication
     */
    bool _is_sending_data;
    bool _is_reading_data;

    /**
     * Buffers for the packets, both received and transmitted.
     */
    std::vector<uint8_t> _packet_read;
    std::vector<uint8_t> _packet_send;
    const end_code_t _end_code;

    /**
     * Dynamic data structures of objects.
     */

    // Blocks that are attached as inputs to be read.
    std::vector<BaseBlock*> _input_blocks;

    // All blocks that are received from the sender.
    std::vector<BaseBlock*> _received_blocks;

    // Blocks that are attached as outputs to be sent.
    std::vector<BaseBlock*> _output_blocks;

    // Blocks that are specifically not sent out.
    std::vector<block_id_t> _detached_blocks;

    // Other Comms objects to throughput through this object.
    std::vector<Comms*> _throughput_comms;

    virtual void packetize();
    virtual void unpacketize();

    /**
     * Pure virtual functions to handle reading and sending packets.
     * Actual implementation details are handled in derived classes.
     */
    virtual void read_packet() = 0;
    virtual void send_packet() = 0;

    // Logs the amount of packet size misses. Requests settings when high
    uint16_t _unpacketize_attempts;

public:
    Comms();

    void update();
    void update_output_blocks();

    void attach_input_block (BaseBlock &block, block_id_t id);
    void attach_output_block(BaseBlock &block, block_id_t id);

    void attach_throughput_comms(Comms &throughput_comms);
    void detach_output_block(block_id_t id);

    uint8_t get_expected_receive_bytes();
    uint8_t get_expected_transmit_bytes();

    static void multiple_attach_output_block(BaseBlock &block, block_id_t id, std::vector<Comms*> comms);

    friend class SDComms;
    friend class SerialComms;
};

#endif