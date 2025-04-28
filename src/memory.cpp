#include "../header/memory.hpp"


// check if memory manipulation doesn't go out of bounds
void memory_overflow(uint8_t address){
    if(address + DATA_SIZE > LAST_HEAP_ADDRESS){
        std::cerr<<"Invalid address(memory overflow)\n";
        exit(EXIT_FAILURE);
    }
}



uint16_t read(uint8_t address){
    memory_overflow(address);

    uint16_t value;
    uint8_t most_significant_bits = memory[address]; //the msb = left side of data
    uint8_t least_significant_bits = memory[address+1]; 

    value = decode_value(most_significant_bits,least_significant_bits);
    return value;
}


void write(uint8_t address, uint16_t value){
    memory_overflow(address);

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
    uint8_t address = static_cast<uint8_t>(stack_pointer); //explicitly convert to an uint8_t address
    write(address,value);
    stack_pointer += 2;
}


// Removes the value at the top of the stack + returns it
uint16_t pop(){
    uint16_t popped_value;
    stack_pointer -= 2; //retrieve the latest value stored
    uint8_t address = static_cast<uint8_t>(stack_pointer); //explicitly convert to an uint8_t address
    popped_value = read(address);
    return popped_value;
}

/*-----------------------------------------Auxillary Functions------------------------------------------------------*/

//used to write data in memory 
MsbAndLsb divide_to_encode(uint16_t value){
    MsbAndLsb pair;
    pair.lsb = static_cast<uint8_t>( value & 0xFF); //Apply mask (remove msb)
    pair.msb = static_cast<uint8_t>(value >> B); //remove lsb
    return pair;
}


//rebuilds the value that was stored in memory
uint16_t decode_value(uint8_t most_significant_bits,uint8_t least_significant_bits){
    int decoded_value = (most_significant_bits << B) | least_significant_bits;
    return static_cast<uint16_t>(decoded_value);
}


