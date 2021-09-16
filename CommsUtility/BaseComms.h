#ifndef BASECOMMS_H
#define BASECOMMS_H

#include <Arduino.h>
#include <BaseBlock.h>
#include <vector>

struct end_code_t {
    uint8_t code[8];
    end_code_t();
    const byte& operator[] (uint8_t i) const;
};

class BaseComms {
    bool _is_sending_data;
    bool _is_receiving_data;
    std::vector<uint8_t> _packet_receive;
    std::vector<uint8_t> _packet_send;
    const end_code_t _end_code;

    std::vector<BaseBlock*> _input_blocks;
    std::vector<BaseBlock*> _received_blocks;
    std::vector<BaseBlock*> _transmit_blocks;
    std::vector<block_id_t> _detached_blocks;
    std::vector<BaseComms*> _throughput_comms;

    virtual void read_packet() = 0;
    virtual void send_packet() = 0;
    void packetize();
    void unpacketize();

public:
    void update();

    void attach_input_block (BaseBlock &block, block_id_t id);
    void attach_output_block(BaseBlock &block, block_id_t id);

    void attach_throughput_comms(BaseComms &throughput_comms);
    void detach_output_block(block_id_t id);

    uint8_t get_expected_receive_bytes();
    uint8_t get_expected_transmit_bytes();
};

#endif