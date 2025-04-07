#include "utils.h"
#include <variant>


typedef struct {
    std::variant<std::string,uint16_t> the_data;
    bool is_a_value = false;
}SecondParameter;


int saturate_int(int value);
std::string parse_opcode(const std::string& instr);
std::string parse_operand(const std::string& instr);
void exec(const std::string& program_path);
uint16_t read(uint8_t address);
void write(uint8_t address, uint16_t value);