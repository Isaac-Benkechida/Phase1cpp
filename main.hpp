#include <iostream>
#include <cstdint> // uint16_t
#include <algorithm> // to access min and max methodes (better than using macros -> name conflicts)
#include <string>
#include <fstream> //opening files
#include <sstream> // for string parsing
#include <map> // to easily manipulate registers
#include <string>
#include <typeinfo>

uint16_t stack_pointer = 0;


int saturate_int(int value);
std::string parse_opcode(const std::string& instr);
std::string parse_operand(const std::string& instr);
void exec(const std::string& program_path);
uint16_t read(uint8_t address);
void write(uint8_t address, uint16_t value);