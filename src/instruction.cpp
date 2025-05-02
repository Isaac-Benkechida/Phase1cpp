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
    } else if(the_opcode == "STORE"){
        opcode = Opcode::STORE; 
    }
    return opcode;
}


uint16_t extract_register_index(int parsed){
    uint16_t index;
    for (int i = 97; i <= 100; i++){ // 97 = "a" in ASCII
        if(parsed == i){
            index = static_cast<uint16_t>(i-97);
            return index;
        }
    }
    std::cerr<< "doesn't correspond to any register name"<<std::endl;
    exit(EXIT_FAILURE); // doesn't correspond to any register
}



void parse_operand(const std::string& instr,Operand* operand, int parameter_position,Opcode opcode){
    std::string op;
    int num_op;
    std::stringstream ss(instr);

    if (parameter_position == 2){ // if it's the first operand
        if(opcode == Opcode::LOAD or opcode == Opcode::STORE){ //They are addresses (always a value)
            operand->type = OperandType::NUMERIC;
            for (int i = 0;i < parameter_position;i++ ){
                ss >> op;
            }

            num_op = std::stoi(op);  
            operand->parsed = static_cast<uint16_t>(num_op);

        }
        else{
            operand->type = OperandType::REGISTER;

            for (int i = 0;i < parameter_position;i++ ){
                ss >> op;
            }
            num_op =  static_cast<int>(op[0]);//transform the string to an int
            operand->parsed = extract_register_index(num_op);
        }
    }
    else if(parameter_position == 3){
        if (opcode == Opcode::SETv or opcode == Opcode::SUBv or opcode == Opcode::ADDv){ // value (not register)
            for (int i = 0;i < parameter_position;i++ ){
                ss >> op;
            }
            num_op = std::stoi(op);  
            operand->parsed = static_cast<uint16_t>(num_op);
            operand->type = OperandType::NUMERIC;
        }
        else{
            for (int i = 0;i < parameter_position;i++ ){
                ss >> op;
            }
            operand->type = OperandType::REGISTER;
            num_op =  static_cast<int>(op[0]);//transform the string to an int
            operand->parsed = extract_register_index(num_op);
        }
        
    }
    

    
}
