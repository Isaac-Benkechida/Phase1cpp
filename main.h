#include <iostream>
#include <cstdint> // uint16_t
#include <algorithm> // to access min and max methodes (better than using macros -> name conflicts)
#include <string>
#include <fstream> //opening files
#include <sstream> // for string parsing
#include <map> // to easily manipulate registers
#include <string>
#include <typeinfo>
int register_val;


int saturate_int(int value);
std::string parse_opcode(const std::string& instr);
uint16_t parse_operand(const std::string& instr);
void exec(const std::string& program_path);