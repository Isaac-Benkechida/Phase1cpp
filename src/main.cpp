#include "../header/main.hpp"
#include "../header/memory.hpp"
#include "../header/register.hpp"
#include "../header/instruction.hpp"

uint8_t memory[1 << B];
uint16_t stack_pointer = 0;


//returns the saturated version of the value
constexpr uint16_t saturate_int(int value){
    int upper = 65535; 
    int saturated = std::min(std::max(value,0),upper); // saturates the int
    return static_cast<uint16_t>(saturated); // cast to the right type(avoids warnings and unexpected behaviour)
}


bool is_register_name(const std::string& parameter) {
    return (parameter == "a" ||parameter == "b" ||parameter == "c" ||parameter == "d") ;
}


// Executes le program in the file named 'program_path'
void exec(const std::string& program_path){

    //generate 4 registers
    Register a,b,c,d;
    Register registers[4] = {a, b, c, d};

    std::fstream file;
    file.open(program_path); //open file
    if(!file){ //if inexistant path or open() failed
        std::cerr<<"open() failed\n";
        exit(EXIT_FAILURE);
    }

    bool ignore = false; //for IFNZ operator
    std::string line;
    int operation_result;
    uint8_t address; //for LOAD and STORE instruction
    uint16_t val1,val2;


    while(getline(file, line)){
        if(!ignore){

            Instruction instruction(line); // build the instruction structure
            Opcode opcode = instruction.opcode;

            if(opcode == Opcode::LOAD or opcode == Opcode::STORE){ //first operand is an address 
                address = static_cast<uint8_t>(instruction.operands[0]->parsed); //no implicit conversions (avoid warnings)
                val2 = instruction.operands[1]->parsed ;

            } else if(opcode == Opcode::PRINT or opcode == Opcode::IFNZ or opcode == Opcode::POP or opcode == Opcode::PUSH){
                val1 =  instruction.operands[0]->parsed;

            } else{
                val1 =  instruction.operands[0]->parsed;
                val2 = instruction.operands[1]->parsed ;
            }

            switch (opcode){
                case Opcode::SETv:
                    registers[val1] = val2;
                    break;
                case Opcode::SETr:
                    registers[val1] = registers[val2];
                    break;
                case Opcode::SUBv:
                    operation_result = registers[val1] - val2 ;
                    registers[val1] = saturate_int(operation_result);
                    break;
                case Opcode::SUBr:
                    operation_result = registers[val1] - registers[val2];
                    registers[val1] = saturate_int(operation_result);
                    break;

                case Opcode::ADDv:
                    operation_result = registers[val1] + val2;
                    registers[val1] = saturate_int(operation_result);
                    break;

                case Opcode::ADDr:
                    operation_result = registers[val1] + registers[val2];
                    registers[val1] = saturate_int(operation_result);
                    break;

                case Opcode::PRINT:
                    std::cout<< registers[val1 ] <<std::endl;
                    break;

                case Opcode::IFNZ:
                    if(registers[val1] == 0){
                       ignore = true; 
                    }
                    
                    break;

                case Opcode::POP:
                    registers[val1] = pop();
                    
                    break;

                case Opcode::PUSH:
                    push(registers[val1]);
                    break;

                case Opcode::LOAD:
                    registers[val2] = read(address);
                    break;

                case Opcode::STORE:
                    write(address,registers[val2]);
                    break;

                }  

        }
        else {
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