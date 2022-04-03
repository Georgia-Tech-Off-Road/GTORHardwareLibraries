/**
 * File: Comms.cpp
 * Author: Akash Harapanahalli
 * 
 * See Comms.h for prototype and specific details.
 */

#include "Comms.h"

/**
 * end_code_t implementation
 */

end_code_t::end_code_t() {
    for(uint8_t i = 0; i < 7; ++i) code[i] = 0xFF;
    code[7] = 0xF0;
}

const uint8_t& end_code_t::operator[] (uint8_t i) const {
    return code[i];
}


/**
 * Comms implementation
 */

/*
 * Constructor
 */
Comms::Comms() : 
    _is_sending_data(0),
    _is_reading_data(0),
    _unpacketize_attempts(0) { }


/**
 * Comms::update()
 * 
 * Updates the Comms class. 
 * Need to define read_packet and send_packet in derived class.
 */
void Comms::update(){
    read_packet();
    send_packet();
}

void Comms::update_output_blocks(){
    for(auto it = _output_blocks.begin(); it != _output_blocks.end(); it++){
        (*it)->update();
    }
}

/**
 * Comms::unpacketize()
 * 
 * This function takes a received packet in _packet_read and decodes information.
 */

void Comms::unpacketize() {
    // check ack byte --> [000000] & is_sending_data & is_reading_data
    // ^ this is with respect to the sender.
    // if 0x03, then parse data     and send data.
    // if 0x02, then parse data     but send settings.
    // if 0x01, then parse settings and send data.
    // if 0x00, then parse settings and send settings.

    // ACK is the first byte of the received packet.
    const uint8_t ack = _packet_read[0];

    // ACK IS NOT STANDARD! CHANGE TO DO SOMETHING ELSE??
    if(ack > 0x03) return; 

    const bool sender_is_sending_data = ack & 0x02; 
    const bool sender_is_reading_data = ack & 0x01;

    // Send data itself only when "sender" is receiving data correctly.
    _is_sending_data = sender_is_reading_data;

    // RECEIVING DATA
    if(sender_is_sending_data) { 
        if(get_expected_receive_bytes() == _packet_read.size()) { // packet lengths good
            // Skip ACK byte.
            const uint8_t *packet_loc = _packet_read.data() + 1;
            for(auto it = _received_blocks.begin(); it != _received_blocks.end(); it++){
                // Unpack each received block, and move pointer to the next block.
                (*it)->unpack(packet_loc);
                packet_loc += (*it)->get_packlen();
            }
        } else { // packet length not good
            // Wait for 10 packet length misses before requesting new settings.
            if(++_unpacketize_attempts > 10){
                _is_reading_data = 0;
                _unpacketize_attempts = 0;
            }
        }
    } 
    // RECEIVING SETTINGS 
    else { 
        for(auto rs = _received_blocks.begin(); rs != _received_blocks.end(); rs++){
            bool match = 0;
            for(auto is = _input_blocks.begin(); (is != _input_blocks.end() && !match); is++){
                if((*rs)->get_id() == (*is)->get_id()) match = 1;
            }
            if(!match) delete (*rs);
        }

        _received_blocks.clear();

        // Skip ACK byte.
        const uint8_t *packet_loc = _packet_read.data() + 1; 
        // Skip end code.
        const uint8_t * const packet_end = _packet_read.data() + _packet_read.size() - 9;

        while (packet_loc < packet_end) {
            // Piece together ID using first two bytes.
            uint8_t id_lsb = *((uint8_t *) packet_loc);
            uint8_t id_msb = *((uint8_t *) (packet_loc + 1));
            uint16_t id = ((uint16_t) id_msb << 8) | (uint16_t) id_lsb;
            // Pack bytes for block using last byte.
            uint8_t pack_bytes = *((uint8_t *) (packet_loc + 2));

            // Check if Block is in list of input blocks.
            BaseBlock *existing_input_block = 0;
            for (auto it = _input_blocks.begin(); it != _input_blocks.end(); it++){
                if((*it)->get_id() == id) existing_input_block = *it;
            }
            if(existing_input_block != 0) _received_blocks.push_back(existing_input_block);
            else _received_blocks.push_back(new DynamicBlock((block_id_t) id, pack_bytes));

            packet_loc += 3;
        }
        _is_reading_data = 1;
    }


    // ^ those will activate flags inside object.
    
    // on receive settings, rebuild _received_blocks from scratch.
    // make sure to connect to existing _input_blocks, otherwise DynamicBlock.
    // WILL BE ORDERED!!

    // on receive data, check that length of packet is good
    // populate data into blocks using unpack(byte*)
}

/**
 * Comms::packetize()
 * 
 * This function encodes information into a packet in _packet_send .
 */

void Comms::packetize() {
    uint8_t ack = (0x02 & (_is_sending_data << 1)) | (0x01 & (_is_reading_data));
    _packet_send.push_back(ack);
    if(_is_sending_data){
        // ack should be 0x03 or 0x02
        for(auto it = _output_blocks.begin(); it != _output_blocks.end(); it++){
            uint8_t *pack = new byte[(*it)->get_packlen()];
            (*it)->pack(pack);
            for(int i = 0; i < (*it)->get_packlen(); ++i) _packet_send.push_back(pack[i]);
            delete pack;
        }
        for(auto tp = _throughput_comms.begin(); tp != _throughput_comms.end(); tp++){
            for(auto it = (*tp)->_received_blocks.begin(); it != (*tp)->_received_blocks.end(); it++){
                block_id_t id = (*it)->get_id();
                bool detached = 0;
                for(auto ds = _detached_blocks.begin(); (ds != _detached_blocks.end() && !detached); ds++){
                    if((*ds) == id) detached = 1;
                }
                if(!detached){
                    uint8_t *pack = new byte[(*it)->get_packlen()];
                    (*it)->pack(pack);
                    for(int i = 0; i < (*it)->get_packlen(); ++i) _packet_send.push_back(pack[i]);
                    delete pack;
                }
            }
        }
    } else {
        // ack should be 0x01 or 0x00
        for(auto it = _output_blocks.begin(); it != _output_blocks.end(); it++){
            uint16_t id = (*it)->get_id();
            uint8_t id_byte_1 = *((uint8_t *)(&id));
            uint8_t id_byte_2 = *((uint8_t *)(&id) + 1);
            uint8_t pack_bytes = (*it)->get_packlen();
            _packet_send.push_back(id_byte_1);
            _packet_send.push_back(id_byte_2);
            _packet_send.push_back(pack_bytes);
        }
        for(auto tp = _throughput_comms.begin(); tp != _throughput_comms.end(); tp++){
            for(auto it = (*tp)->_received_blocks.begin(); it != (*tp)->_received_blocks.end(); it++){
                bool detached = 0;
                uint16_t id = (*it)->get_id();
                for(auto ds = _detached_blocks.begin(); (ds != _detached_blocks.end() && !detached); ds++){
                    if((*ds) == id) detached = 1;
                }
                if(!detached){
                    uint8_t id_byte_1 = *((uint8_t *)(&id));
                    uint8_t id_byte_2 = *((uint8_t *)(&id) + 1);
                    uint8_t pack_bytes = (*it)->get_packlen();
                    _packet_send.push_back(id_byte_1);
                    _packet_send.push_back(id_byte_2);
                    _packet_send.push_back(pack_bytes);
                }
            }
        }
    }
    for(int i = 0; i < 8; ++i) _packet_send.push_back(_end_code[i]);

    // if need to send settings:
    // settings will be a list of id/byte_length pair.
    // ack is 0x01 or 0x00, depending on checks from unpacketize.
    // 2 uint8_t id, 1 uint8_t byte_length

    // if need to send data:
    // ack is 0x03 or 0x02, depending on checks from unpacketize.
    // packetize
}

uint8_t Comms::get_expected_receive_bytes() {
    uint8_t bytes = 0;
    for(auto it = _received_blocks.begin(); it != _received_blocks.end(); it++) bytes += (*it)->get_packlen();
    return (9 + bytes);
}

uint8_t Comms::get_expected_transmit_bytes() {
    uint8_t bytes = 0;
    for(auto it = _output_blocks.begin(); it != _output_blocks.end(); it++) bytes += (*it)->get_packlen();
    for(auto tp = _throughput_comms.begin(); tp != _throughput_comms.end(); tp++){
        for(auto it = (*tp)->_received_blocks.begin(); it != (*tp)->_received_blocks.end(); it++){
            bool detached = 0;
            uint16_t id = (*it)->get_id();
            for(auto ds = _detached_blocks.begin(); (ds != _detached_blocks.end() && !detached); ds++){
                if((*ds) == id) detached = 1;
            }
            if(!detached) bytes += (*it)->get_packlen();
        }
    }

    return (9 + bytes);
}

/*
 * @brief Attaches a non-DynamicBlock to recieve data from to be used in the main code
 * 
 * @param block A pointer to a block object (derived from Block class)
 * @param id The ID of the block being attached from BlockList
 */
void Comms::attach_input_block(BaseBlock &block, block_id_t id) {
    // Check to see if it is already attached. If so, do nothing
    for (auto it = _input_blocks.begin(); it != _input_blocks.end(); it++){
        if((*it)->get_id() == id)
            return;
    }
    // Attach the block
    block.set_id(id);
    _input_blocks.push_back(&block);
    // Check to see if the block ID is in received blocks, if so, replace generic block with actual block
    for (auto it = _received_blocks.begin(); it != _received_blocks.end(); it++){
        if((*it)->get_id() == id) {
            BaseBlock *old_block = (*it);
            *it = &block;
            delete old_block;
        }
    }
}

/*
 * @brief Attaches a non-DynamicBlock to send data through the comm port
 * 
 * @param block A pointer to a block object (derived from Block class)
 * @param id The ID of the block being attached from BlockList
 */
void Comms::attach_output_block(BaseBlock &block, block_id_t id){
    // Check to see if it is detached. If so, remove it from the detached list
    for (auto ds = _detached_blocks.begin(); ds != _detached_blocks.end(); ds++){
        if((*ds) == id)
            _detached_blocks.erase(ds);
    }
    // Check to see if it is already attached. If so, do nothing
    for (auto it = _output_blocks.begin(); it != _output_blocks.end(); it++){
        if((*it)->get_id() == id)
            return;
    }
    // Attach the block
    block.set_id(id);
    _output_blocks.push_back(&block);
}

/*
 * @brief Attaches a Comms object. It will send all its recieved data to be sent out
 *        out of the ports attached to it.
 * 
 * @param throughput_comms A pointer to a Comms object to sent its data to
 */
void Comms::attach_throughput_comms(Comms &throughput_comms){
    // Check to see if it is already attached. If so, do nothing
    for (auto it = _throughput_comms.begin(); it != _throughput_comms.end(); it++){
        // TODO: Fix logic??
        // if((*it)->get_port() == throughput_comms.get_port())
        if((*it) == &throughput_comms)
            return;
    }
    // Attach the comm port
    _throughput_comms.push_back(&throughput_comms);
}

/*
 * @brief Detaches a block so it won't send it's data out of this port
 * 
 * @param id The ID of the block being attached from BlockList
 */
void Comms::detach_output_block(block_id_t id){
    // Check to see if it is already attached. If so, remove it
    for (auto it = _output_blocks.begin(); it != _output_blocks.end(); it++){
        if((*it)->get_id() == id)
            _output_blocks.erase(it);
    }
    // Check to see if it is already detached. If so, do nothing
    for (auto it = _detached_blocks.begin(); it != _detached_blocks.end(); it++){
        if(*it == id)
            return;
    }
    // Detach the block
    _detached_blocks.push_back(id);
}

// void Comms::multiple_attach_output_block(BaseBlock &block, block_id_t id, std::vector<Comms*> comms){
//     for(auto it = comms.begin(); it != comms.end(); comms++){
//         (*it).attach_output_block(block, id);
//     }
// }

