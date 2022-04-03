#ifndef EDGE_DETECTOR_H
#define EDGE_DETECTOR_H

#include <vector>
#include <functional>
#include "Block.h"

enum edge_type_t {
    EDGE_RISING, EDGE_FALLING, EDGE_RISING_OR_FALLING
};

struct Edge {
    Block<bool>* block;
    edge_type_t type;
    bool state;
    Edge(Block<bool>* block_, edge_type_t type_, bool state_ = 0) : block(block_), type(type_), state(state_) {}
};

class EdgeDetector {
private:
    std::function<void()> _cb;
    std::vector<Edge*> _edges;
public:
    void set_cb (std::function<void()> cb){ _cb = cb; }
    void attach_input_block(Block<bool>& block, edge_type_t type){
        _edges.push_back(new Edge(&block, type, block.get_data()));
    }
    bool update() {
        bool edge_detected = 0;
        for(auto it = _edges.begin(); it != _edges.end(); it++){
            bool new_state = (*it)->block->get_data();

            // RISING,  0 --> 1
            if(((*it)->type == EDGE_RISING  || (*it)->type == EDGE_RISING_OR_FALLING) &&
                !(*it)->state && new_state) {
                edge_detected = 1;
            }
            // FALLING, 1 --> 0
            if(((*it)->type == EDGE_FALLING || (*it)->type == EDGE_RISING_OR_FALLING) &&
                (*it)->state && !new_state) {
                edge_detected = 1;
            }

            (*it)->state = new_state;
        }
        if(edge_detected && _cb){
            _cb();
        }
        return edge_detected;
    }
};

#endif