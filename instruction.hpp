#include "utils.h"

enum class Opcode{

};
struct Operand{

};

struct Instruction {
    const Opcode opcode;
    const Operand* operands[2];
    Instruction(const std::string& raw);
    inline ~Instruction(){
        delete operands;
        *operands = nullptr;
    };
};