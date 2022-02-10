#ifndef CHANGETOCALLBACK_H
#define CHANGETOCALLBACK_H

#include "Block.h"
#include <vector>
#include <functional>
#include <memory>

template <class DataType>
struct check_t {
	DataType _old_data;
	bool _has_changed;
	std::function<DataType()> _check;
	std::function<void(DataType)> _callback;

	check_t(std::function<DataType()> check, std::function<void(DataType)> callback);
};

typedef check_t (&Check);

class ChangeToCallback {
private:
	std::vector<std::unique_ptr<check_t>> _checks;
public:
    ChangeToCallback();

    template <class DataType>
    check_t attach_check_to_callback(std::function<DataType()> check, std::function<void(DataType)> callback);

    void attach_callback(std::function<void(DataType)> onchange_callback);
    void unpack (const uint8_t* pack);
    void update();
    bool has_changed();
};

#endif