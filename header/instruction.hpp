#include "../header/utils.h"

enum class Opcode{
    SETv,
    SETr,
    ADDv,
    ADDr,
    SUBv,
    SUBr,
    LOAD,
    PUSH,
    POP,
    PRINT,
    IFNZ,
    STORE
};


enum class OperandType{
    NUMERIC,
    REGISTER
};


struct Operand{
    OperandType type;
    uint16_t parsed;
};


Opcode determine_opcode(const std::string& instr);
void parse_operand(const std::string& instr,Operand* operand,int parameter_position,Opcode opcode);
uint16_t extract_register_index(int parsed);

struct Instruction {
    const Opcode opcode;
    const Operand* operands[2];


    Instruction(const std::string& raw): opcode(determine_opcode(raw)){ 
        Operand* operand1 = new Operand;
        Operand* operand2 = new Operand;

        parse_operand(raw,operand1,2,opcode);
        operands[0] = operand1;

        if (opcode != Opcode::IFNZ && opcode != Opcode::PRINT && opcode != Opcode::PUSH && opcode != Opcode::POP){
            parse_operand(raw,operand2,3,opcode);
            operands[1] = operand2;
        } else {
            delete operand2; //avoid memory leak 
            operands[1] = nullptr;
        }
        
    }; 
    ~Instruction() {
        delete operands[0];
        if (opcode != Opcode::IFNZ && opcode != Opcode::PRINT && opcode != Opcode::PUSH && opcode != Opcode::POP) {
            delete operands[1];
        }
    }
    

};