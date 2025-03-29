#include "main.h"


//returns the saturated version of the value
int saturate_int(int value){
    int saturated = std::min(std::max(value,0),65535); // saturates the int
    return saturated; // cast to the right type(avoids warnings and unexpected behaviour)
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
    operand = value_in_register(operand);
    return operand;
}


// determine what value the operand needs to store
uint16_t value_in_register(auto operand){
    uint16_t value;
    if (operand == "a"){
        value = a;
    }else if(operand == "b"){
        value = b;
    }else if(operand == "c"){
        value = c;
    }else if(operand == "d"){
        value = d;
    }else{
        return operand;
    }
    return value;
}


// Executes le program in the file named 'program_path'
void exec(const std::string& program_path){

    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;

    std::vector<registers> registers;
    registers.emplace_back(a,b,c,d);
    
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
            //print
            if(opcode == "PRINT"){
                std::cout << register_val<<std::endl;
            }
            //ignore next instruction if null value in register
            else if(opcode == "IFNZ" && register_val == 0){
                ignore = true;
            }

            else{
                operand = parse_operand(line);
                //assignement
                if(opcode == "SET"){
                    register_val = saturate_int(operand);
                    
                }
                //addition
                else if(opcode == "ADD"){
                    register_val = saturate_int(register_val + operand);
                    
                }
                //subtraction
                else if(opcode == "SUB"){
                    register_val = saturate_int(register_val - operand);
                    
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
    //in case the file path was not provided
    if (argc < 2){
        std::cerr << "Please provide the file path\n";
        exit(EXIT_FAILURE);
    }
    
    char* filepath = argv[1];
    exec(filepath);
    return 0;
}