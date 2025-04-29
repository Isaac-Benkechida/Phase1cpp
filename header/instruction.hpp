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


struct Instruction {
    const Opcode opcode;
    const Operand* operands[2];


    Instruction(const std::string& raw): opcode(determine_opcode(raw)), operands{nullptr,nullptr} { 
        Operand* operand1 = new Operand;
        parse_operand(raw,operand1,2,opcode);
        
        Operand* operand2 = new Operand;
        parse_operand(raw,operand1,3,opcode);

        operands[0] = operand1;
        operands[1] = operand2;

        std::cout<< "Operands built successfully!\n";


    };

    inline ~Instruction(){
        for (int i = 0;i < 2;i++){
            delete operands[i];
            operands[i] = nullptr;
        }
    };    
};