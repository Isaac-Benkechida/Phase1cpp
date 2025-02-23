#include "main.h"

//Apply a subtraction on the register value
int subtract(uint16_t operand){

    if(register_val < operand){
        return 0;
    }
    else{
        return saturate_int(register_val -= operand);
    }
}


//returns the saturated version of the value
int saturate_int(int value){
    int saturated = std::min(std::max(value,0),65535); 
    return saturated;
}


//Extracts the Instruction to execute
std::string parse_opcode(const std::string& instr){
    std::string opcode;
    std::stringstream ss(instr);
    ss >> opcode;
    return opcode;
}


//extracts the operand that follows an instruction
uint16_t parse_operand(const std::string& instr){
    std::string opcode;
    uint16_t operand;
    std::stringstream ss(instr);
    ss >> opcode;
    ss >> operand;

    return operand;
}


// Executes the program int the file named 'program_path'
void exec(const std::string& program_path){
    std::fstream file;
    file.open(program_path); //open file in reading mode
    if(!file){ //if inexistant path or open failed
        std::cerr<<"open() failed\n";
        exit(EXIT_FAILURE);
    }

    std::string line;
    std::string opcode;
    uint16_t operand;
    bool ignore = false; //for IFNZ operator

    while(getline(file, line)){

        if(!ignore){

            opcode = parse_opcode(line);
            if(opcode == "PRINT"){
                std::cout << register_val<<std::endl;
            }

            else if(opcode == "IFNZ" && register_val == 0){
                ignore = true;
            }

            else{
                operand = parse_operand(line);

                if(opcode == "SET"){
                    register_val = saturate_int(operand);
                    
                }

                else if(opcode == "ADD"){
                    register_val = saturate_int(register_val += operand);
                    
                }

                else if(opcode == "SUB"){

                    register_val = subtract(operand);
                    
                }

                
            }
            
        }
        else{
            ignore = false; //reset ignore flag
        }
        
    }
    file.close();

}


int main(int argc, char* argv[]){
    if (argc < 2){
        std::cerr << "Please provide the file path\n";
        exit(EXIT_FAILURE);
    }
    char* filepath = argv[1];
    exec(filepath);
    return 0;
}