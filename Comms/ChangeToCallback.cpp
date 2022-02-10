#include "ChangeToCallback.h"


/**
 * CommandBlock Definitions
 */

template <class DataType>
check_t<DataType>::check_t(std::function<DataType()> check, 
                           std::function<void(DataType)> callback) : 
    _old_data(),
    _has_changed(false),
    _check(check),
    _callback(callback) { }

CommandBlock::CommandBlock() { }

template <class DataType>
Check CommandBlock::attach_check_to_callback(std::function<DataType()> check, 
											std::function<void(DataType)> callback) {
    if (!check) return;
	_checks.push_back(std::make_unique<check_t>(check, callback));
    return 
}


template <class DataType>
CommandBlock<DataType>::CommandBlock() : _has_changed(0) { };

template <class DataType>
void CommandBlock<DataType>::attach_callback(std::function<void(DataType)> onchange_callback) {
    _onchange_callback = onchange_callback;
}

template <class DataType>
void CommandBlock<DataType>::unpack (const uint8_t* pack){
    memcpy((uint8_t*) &this->_data, pack, this->_packlen);
}

template <class DataType>
void CommandBlock<DataType>::update() {
    if(_prev_data != this->_data) {
        _has_changed = 1;
        if(_onchange_callback) _onchange_callback(this->_data);
    }
    _prev_data = this->_data;
}

template <class DataType>
bool CommandBlock<DataType>::has_changed () {
    if(_has_changed) {
        _has_changed = 0;
        return 1;
    } else {
        return 0;
    }
}