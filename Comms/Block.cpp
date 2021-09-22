#include "Block.h"

/**
 * BaseBlock Definitions
 */

BaseBlock::BaseBlock(block_id_t id, uint8_t packlen) : _id(id), _packlen(packlen) { }

block_id_t BaseBlock::get_id(){ 
	return _id; 
}

void BaseBlock::set_id(block_id_t id){
	_id = id;
}

uint8_t BaseBlock::get_packlen(){
	return _packlen;
}

void BaseBlock::set_packlen(uint8_t packlen){
	_packlen = packlen;
}


/**
 * Block Definitions
 */

template <class DataType>
Block<DataType>::Block() : BaseBlock(0, sizeof(DataType)) { }


template <class DataType>
void  Block<DataType>::set_data(const DataType& data) {
	_data = data;
}

template <class DataType>
const DataType& Block<DataType>::get_data() {
	return _data;
}

template <class DataType>
void Block<DataType>::pack (uint8_t* pack) {
	memcpy(pack, (uint8_t*) &_data, _packlen);
}

template <class DataType>
void Block<DataType>::unpack (const uint8_t* pack){
	memcpy((uint8_t*) &_data, pack, _packlen);
}

template <class DataType>
void Block<DataType>::update (){ }


/**
 * DynamicBlock Definitions
 */

DynamicBlock::DynamicBlock (block_id_t id, uint8_t packlen){
    _id = id;
    _packlen = packlen;
    _data.resize(packlen);
}
void DynamicBlock::pack   (byte* pack){
    memcpy(pack, _data.data(), _packlen);
}
void DynamicBlock::unpack (const byte* pack){
    memcpy(_data.data(), pack, _packlen);
}

