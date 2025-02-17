#include <iostream>
#include <cstdint>
#include <algorithm> // to access MIN and MAX methodes



//returns the saturated version of the value
uint16_t saturate_int(int value){
    int max_val = 65535;
    uint16_t saturated = std::min(std::max(value,0),max_val); // saturates the int
    return static_cast<uint16_t>(saturated); // cast to the right type(avoids warnings and unexpected behaviour)
}




int main(){
    uint16_t register_val = 0; //initialised to 0
    register_val = saturate_int(register_val);
    std::cout << register_val<<std::endl;
    return 0;
}