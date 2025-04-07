#include "utils.h"

#define B 8 //size of address in bits
#define DATA_SIZE 2 //bytes that an element occupies
#define STACK_LAST_ADDRESS 15

extern uint8_t memory[1<<B];
extern uint16_t stack_pointer;     
/*I have decided that in memory, the data will be stored using big endian boutism*/

//used to divide a uint16_t to 2 uint8_t values
struct MsbAndLsb{
    uint8_t lsb;
    uint8_t msb;
};


MsbAndLsb divide_to_encode(uint16_t value);
uint16_t decode_value(uint8_t most_significant_bits,uint8_t least_significant_bits);
uint16_t read(uint8_t address);
void write(uint8_t address, uint16_t value);
void push(uint16_t value);
uint16_t pop();




