#include <iostream>
#include <cstdint> // uint16_t
#include <algorithm> // to access min and max methodes
#include <string>
#include <fstream>
#include <sstream> // for string parsing
int register_val = 0; //initialised to 0

int saturate_int(int value);
std::string parse_opcode(const std::string& instr);
uint16_t parse_operand(const std::string& instr);
void exec(const std::string& program_path);
int subtract(int registerval,uint16_t operand);