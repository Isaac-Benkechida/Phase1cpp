#include "../header/instruction.hpp"
#include "../header/utils.h"


//Extracts the Instruction to execute
std::string parse_opcode(const std::string& instr){
    std::string opcode;
    std::stringstream ss(instr);
    ss >> opcode;
    return opcode;
}


Opcode determine_opcode(const std::string& instr){
    std::string the_opcode = parse_opcode(instr);
    Opcode opcode;
    if (the_opcode == "SETv"){
        opcode = Opcode::SETv;
    } else if(the_opcode == "SETr"){
        opcode = Opcode::SETr;
    } else if(the_opcode == "ADDv"){
        opcode = Opcode::ADDv;
    }  else if(the_opcode == "ADDr"){
        opcode = Opcode::ADDr;
    }  else if(the_opcode == "SUBv"){
        opcode = Opcode::SUBv;
    }  else if(the_opcode == "SUBr"){
        opcode = Opcode::SUBr;
    }  else if(the_opcode == "LOAD"){
        opcode = Opcode::LOAD;
    }  else if(the_opcode == "PUSH"){
        opcode = Opcode::PUSH;
    }  else if(the_opcode == "POP"){
        opcode = Opcode::POP;
    } else if(the_opcode == "PRINT"){
        opcode = Opcode::PRINT;
    } else if(the_opcode == "IFNZ"){
        opcode = Opcode::IFNZ;
    }
    return opcode;
}


void parse_operand(const std::string& instr,unsigned int parameter_position,Opcode opcode,const Operand* operands[2]){
    
}
