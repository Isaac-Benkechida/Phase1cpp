#include <iostream>
#include <bitset>
#include <cstdint>
#include "main.h"
#define B 8 //size of address in bits
uint8_t memory[2^B];

int main() {
    uint16_t value = 256|1;
    std::cout<<value<<std::endl;

}