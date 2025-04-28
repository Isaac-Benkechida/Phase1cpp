#include "../header/utils.h"
#include <variant>


/*------------------------------------Parse Related Functions and Structures----------------------------------------------------*/
/*used to store the parsed element of the instruction*/
typedef struct {
    std::variant<std::string,uint16_t,uint8_t>the_data; //type safe union
    bool is_a_value = false;
}Parameter;

bool is_register_name(const std::string& parameter); //checks if the parameter is a register name
std::string parse_opcode(const std::string& instr);
Parameter parse_operand(const std::string& instr);
Parameter parse_into_variant(std::string operand);

/*-------------------------------------Register/memory manipulation Functions-------------------------------------------*/
uint16_t set_and_sub(std::map<std::string,uint16_t> registers,std::string opcode,std::string register1,uint16_t param3_value);
uint16_t read(uint8_t address); // reads uint16_t data at a given address
void write(uint8_t address, uint16_t value);// writes uint16_t data at a given address

/*------------------------------------------Main execution function----------------------------------------------------*/
void exec(const std::string& program_path);
