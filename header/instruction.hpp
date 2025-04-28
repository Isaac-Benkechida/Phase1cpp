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
    Operand(OperandType t , uint16_t p) : type(t), parsed(p) {};
};


Opcode determine_opcode(const std::string& instr);
void parse_operand(const std::string& instr,unsigned int parameter_position,Opcode opcode,const Operand* operands[]);


struct Instruction {
    const Opcode opcode;
    const Operand* operands[2];


    Instruction(const std::string& raw): opcode(determine_opcode(raw)), operands{nullptr, nullptr} {
        parse_operand(raw,1,opcode,operands);
        if (!(opcode == Opcode::PRINT or opcode == Opcode::IFNZ or opcode == Opcode::PUSH or opcode == Opcode::POP) ){ 
            parse_operand(raw,2,opcode,operands);
        }
    };

    inline ~Instruction(){
        for (int i = 0;i < 2;i++){
            delete operands[i];
            operands[i] = nullptr;
        }
    };    
};