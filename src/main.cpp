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


unsigned int extract_register_index(uint16_t parsed){
    unsigned int index = 0;
    for (int i = 97; i <= 100; i++){ // 97 = "a" in ASCII
        if(parsed == i){
            return index;
        }
        index++;
    }
    return -1; // doesn't correspond to any register
}


// Executes le program in the file named 'program_path'
void exec(const std::string& program_path){

    //generate 4 registers
    Register a,b,c,d;
    Register registers[4] = {a, b, c, d};

    std::fstream file;
    file.open(program_path); //open file
    if(!file){              //if inexistant path or open() failed
        std::cerr<<"open() failed\n";
        exit(EXIT_FAILURE);
    }

    bool ignore = false; //for IFNZ operator
    std::string line;
    int reg_ind[2];
    uint16_t values[2];
    uint8_t address;
    uint16_t value_in_reg;


    while(getline(file, line)){
        if(!ignore){
            Instruction instruction(line); // build the instruction structure

            for (int i = 0; i < 2;i++){ // get the index of the used registers
                if (!instruction.operands[i]) continue;
                if(instruction.operands[i]->type == OperandType::REGISTER){
                    reg_ind[i] = extract_register_index(instruction.operands[i]->parsed);
                    std::cout<<"reg_ind[i]: "<<reg_ind[i];
                } 
                else{
                    values[i] = instruction.operands[i]->parsed;
                }  
            }

            switch(instruction.opcode){

                case Opcode::IFNZ:
                    ignore = true;
                    break;

                case Opcode::PRINT:
                    value_in_reg = static_cast<uint16_t>(registers[reg_ind[0]]);// get the val of the register
                    std::cout << value_in_reg << std::endl;
                    break;


                case Opcode::SETv:
                    registers[reg_ind[0]] = values[1];
                    break;

                case Opcode::ADDv:
                    registers[reg_ind[0]] = saturate_int(registers[reg_ind[0]] + values[1]);
                    break;

                case Opcode::SUBv:
                    registers[reg_ind[0]] = saturate_int(registers[reg_ind[0]] - values[1]);
                    break;


                case Opcode::SETr:
                    registers[reg_ind[0]] = registers[reg_ind[1]];
                    break;
                case Opcode::ADDr:
                    registers[reg_ind[0]] = saturate_int(registers[reg_ind[0]] + registers[reg_ind[1]]);
                    break;

                case Opcode::SUBr:
                    registers[reg_ind[0]] = saturate_int(registers[reg_ind[0]] - registers[reg_ind[1]]);
                    break;


                case Opcode::POP:
                    registers[reg_ind[0]] = pop();
                    break;
                
                case Opcode::PUSH:
                    push(registers[reg_ind[0]]);
                    break;

                case Opcode::STORE:
                    address = static_cast<uint8_t>(values[0]);
                    write(address,registers[reg_ind[1]]);
                    break;
                
                case Opcode::LOAD:
                    address = static_cast<uint8_t>(values[0]);
                    read(address);
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