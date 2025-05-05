#include "../header/memory.hpp"


// check if memory manipulation doesn't go out of bounds
void Memory::memory_overflow(uint8_t address){
    int last_heap_address = 1 << nbits;
    if(address + DATA_SIZE > last_heap_address){
        std::cerr<<"Invalid address(memory overflow)\n";
        exit(EXIT_FAILURE);
    }
}


// Ajoute une valeur au sommet du stack
void Memory::push(uint16_t value){
    
    //avoid stack overflow
    if (stack_pointer > STACK_LAST_ADDRESS){
        std::cerr<<"Invalid address(stack overflow)\n";
        exit(EXIT_FAILURE);
    }

    uint8_t address = static_cast<uint8_t>(stack_pointer); //explicitly convert to an uint8_t address
    (*this)[address] = value;
    stack_pointer += 2;
    
}


// Removes the value at the top of the stack + returns it
uint16_t Memory::pop(){
    uint16_t popped_value;
    stack_pointer -= 2; //retrieve the latest value stored

    uint8_t address = static_cast<uint8_t>(stack_pointer); //explicitely convert to an uint8_t address
    popped_value = (*this)[address]; //use overloaded []
    return popped_value;
}