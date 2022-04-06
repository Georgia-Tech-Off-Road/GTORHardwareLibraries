#ifndef IFTHENELSE_H
#define IFTHENELSE_H

#include <functional>

class IfThenElse {
private:
    std::function<bool()> _if;
    std::function<void()> _then;
    std::function<void()> _else;
public:
    void begin(std::function<bool()> if_,std::function<void()> then_,std::function<void()> else_) {
        _if = if_;
        _then = then_;
        _else = else_;
    }

    void update() {
        if(_if){
            if(_if()){ _then(); }
            else { _else(); }
        }
    }
};

#endif