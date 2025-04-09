#include "main.hpp"
#include "memory.hpp"
uint8_t memory[1<<B];
uint16_t stack_pointer = 0;


//returns the saturated version of the value
int saturate_int(int value){
    int upper = 65535; 
    int saturated = std::min(std::max(value,0),upper); // saturates the int
    return saturated; // cast to the right type(avoids warnings and unexpected behaviour)
}


bool is_register_name(std::string parameter,std::map<std::string,int>& registers){
    return registers.find(parameter) != registers.end();
}


//Extracts the Instruction to execute
std::string parse_opcode(const std::string& instr){
    std::string opcode;
    std::stringstream ss(instr);
    ss >> opcode;
    return opcode;
}


//extracts the operand that follows an instruction
Parameter parse_operand(const std::string& instr,std::map<std::string,int>& registers){
    Parameter second_parameter;
    std::string operand;
    std::stringstream ss(instr);
    ss >> operand;
    ss >> operand;
    second_parameter.the_data = operand;
    if (!is_register_name(operand,registers)){ //if it is not a register name
        second_parameter.is_a_value = true;
    }
    
    return second_parameter;
}



//extracts the operand that follows an instruction
Parameter parse_value(const std::string& instr, std::map<std::string,int>& registers){
    Parameter third_parameter;
    std::string parameter;

    //parse the line to access the third parameter
    std::stringstream ss(instr);
    ss >> parameter;
    ss >> parameter;
    ss >> parameter; //access third parameter of the line
    third_parameter.the_data;
    if (!is_register_name(parameter,registers)){ //if it is not a register name
        third_parameter.is_a_value = true;
    }
    return third_parameter;
}


//initialises a map associating each register name to a value
std::map<std::string,int> build_map(){
    std::map<std::string,int> registers;
    registers["a"] = 0;
    registers["b"] = 0;
    registers["c"] = 0;
    registers["d"] = 0;
    return registers;
}


uint16_t value_in_register(std::string the_register,std::map<std::string,int>& registers){
    return registers[the_register];
}


// Executes le program in the file named 'program_path'
void exec(const std::string& program_path){

    //initialise a map with the 4 registers
    std::map<std::string,int> registers = build_map();

    std::fstream file;
    file.open(program_path); //open file
    if(!file){ //if inexistant path or open failed
        std::cerr<<"open() failed\n";
        exit(EXIT_FAILURE);
    }

    std::string opcode;

    Parameter second_parameter;
    std::string reg1;
    uint16_t param2_value;

    Parameter third_parameter;
    std::string reg2;
    uint16_t param3_value;

    uint8_t address;
    
    bool ignore = false; //for IFNZ operator
    std::string line;

    while(getline(file, line)){
        if(!ignore){
            opcode = parse_opcode(line);
            second_parameter = parse_operand(line,registers);
            if (!second_parameter.is_a_value){//if it's a register name
                reg1 = std::get<std::string>(second_parameter.the_data);
                param2_value = registers[reg1];
                if (opcode == "PRINT"){
                    std::cout << param2_value<<std::endl;
                }
                else if (opcode == "IFNZ"){
                    if (param2_value == 0){
                        ignore = true;
                    }
                }
                else if (opcode == "PUSH"){
                    push(param2_value);
                }
                else if (opcode == "POP"){
                    registers[reg1] = pop();                    
                }
                else if(opcode == "SET" || opcode == "ADD" || opcode == "SUB" ){
                    third_parameter = parse_value(line,registers);
                    if(!third_parameter.is_a_value){ //if it's a reg name
                        reg2 = std::get<std::string>(third_parameter.the_data);
                        param3_value = registers[reg2];  
                    }
                    else{
                        param3_value = std::get<uint16_t>(third_parameter.the_data);
                    }

                    if (opcode == "SET"){
                        registers[reg1] = param3_value;
                    }
                    else if (opcode == "ADD"){
                        registers[reg1] = saturate_int(registers[reg1] + param3_value);
                    }
                    else if (opcode == "SUB"){
                        registers[reg1] = saturate_int(registers[reg1] - param3_value);
                    }
                    
                }
            }
            else {
                address = std::get<uint8_t>(third_parameter.the_data);
                third_parameter = parse_value(line,registers);
                if (!third_parameter.is_a_value){//reg name
                    reg2 = std::get<std::string>(third_parameter.the_data);
                    param3_value = registers[reg2];
                    if (opcode == "STORE"){
                        write(address,param3_value);
                    }
                    else if (opcode == "LOAD"){
                        registers[reg2] = read(address);
                    }
                }
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