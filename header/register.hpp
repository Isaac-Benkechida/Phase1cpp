#include "../header/utils.h"


class Register {
    uint16_t register_value = 0;

    public:

    constexpr void operator=(uint16_t value){
        this->register_value = value;
    }
    constexpr void operator+=(uint16_t value){
        this->register_value = saturate_int(this->register_value + value);
    }
    constexpr void operator-=(uint16_t value){
        this->register_value = saturate_int(this->register_value - value);
    }
    constexpr operator uint16_t() const{ // will be interesting when we will assign an uint16_t to the register ^^
        return register_value;
    }
    
};
