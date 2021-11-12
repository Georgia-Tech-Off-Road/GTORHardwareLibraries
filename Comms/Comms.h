#ifndef COMMS_H
#define COMMS_H

#include "Block.h"

struct end_code_t {
    uint8_t code[8];
    end_code_t();
    const uint8_t& operator[] (uint8_t i) const;
};

class Comms {
protected:
    bool _is_sending_data;
    bool _is_receiving_data;
    std::vector<uint8_t> _packet_receive;
    std::vector<uint8_t> _packet_send;
    const end_code_t _end_code;

    std::vector<BaseBlock*> _input_blocks;
    std::vector<BaseBlock*> _received_blocks;
    std::vector<BaseBlock*> _transmit_blocks;
    std::vector<block_id_t> _detached_blocks;
    std::vector<Comms*> _throughput_comms;

    virtual void read_packet() = 0;
    virtual void send_packet() = 0;
    virtual void packetize();
    virtual void unpacketize();

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

    friend class SDComms;
    friend class SerialComms;
};

#endif