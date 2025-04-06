#include "memory.hpp"



uint16_t read(uint8_t address){
    if(address + DATA_SIZE > 255){ //the memory was exceeded
        std::cerr<<"Invalid address(memory overflow)\n";
        exit(EXIT_FAILURE);
    }
    uint16_t value;
    uint8_t most_significant_bits = memory[address]; //the msb = left side of data
    uint8_t least_significant_bits = memory[address+1]; 
    value = decode_value(most_significant_bits,least_significant_bits);
    return value;
}


void write(uint8_t address, uint16_t value){
    if(address + DATA_SIZE > 255){ //the memory was exceeded
        std::cerr<<"Invalid address(memory overflow)\n";
        exit(EXIT_FAILURE);
    }

    MsbAndLsb pair = divide_to_encode(value);
    memory[address] = pair.msb;
    memory[address+1] = pair.lsb;    
}


// Ajoute une valeur au sommet du stack
void push(uint16_t value){
    //avoid stack overflow
    if (stack_pointer > STACK_LAST_ADDRESS){
        std::cerr<<"Invalid address(stack overflow)\n";
        exit(EXIT_FAILURE);
    }
    write(stack_pointer,value);
    stack_pointer += 2;
}


// Retire la valeur au sommet du stack et retourne cette valeur
uint16_t pop(){
    uint16_t popped_value;
    stack_pointer -= 2; //retrive the latest value stored
    popped_value = read(stack_pointer);
    return popped_value;
}
