#include "main.hpp"
#include "memory.hpp"
uint8_t memory[1<<B];
uint16_t stack_pointer = 0;


//returns the saturated version of the value
uint16_t saturate_int(int value){
    int upper = 65535; 
    int saturated = std::min(std::max(value,0),upper); // saturates the int
    return static_cast<uint16_t>(saturated); // cast to the right type(avoids warnings and unexpected behaviour)
}


bool is_register_name(const std::string& parameter) {
    return (parameter == "a" ||parameter == "b" ||parameter == "c" ||parameter == "d") ;
}


//Extracts the Instruction to execute
std::string parse_opcode(const std::string& instr){
    std::string opcode;
    std::stringstream ss(instr);
    ss >> opcode;
    return opcode;
}


Parameter parse_into_variant(std::string operand){
    Parameter the_parameter;
    the_parameter.the_data = operand;
    if (is_register_name(operand)){ //if it is a register name
        the_parameter.the_data.emplace<std::string>(operand); //active type = string
        the_parameter.is_a_value = false;
    }
    else{ //it might be a value
        try {
            uint16_t value = std::stoul(operand); // try to convert it to an uint16_t 
            the_parameter.the_data.emplace<uint16_t>(value); //active type = uint16_t
            the_parameter.is_a_value = true;
        }
        catch(...){ //not a register name, nor a value -> invalid instruction
            std::cerr<<"Invalid instruction"<<std::endl;
        }
    }
    return the_parameter;
}



//extracts the operand that follows an instruction
Parameter parse_operand(const std::string& instr,int parameter_position){
    std::string parameter;

    //parse the line to access the third parameter
    std::stringstream ss(instr);
    for (int i = 0;i < parameter_position;i++){
        ss >> parameter;
    }
    
    return parse_into_variant(parameter);
}


//initialises a map associating each register name to a value
std::map<std::string,uint16_t> build_map(){
    std::map<std::string,uint16_t> registers;
    registers["a"] = 0;
    registers["b"] = 0;
    registers["c"] = 0;
    registers["d"] = 0;
    return registers;
}


uint16_t set_and_sub(std::map<std::string,uint16_t> registers,std::string opcode,std::string register1,uint16_t param3_value){
    uint16_t result;
    if (opcode == "SET"){
        result = param3_value;
    }
    else if (opcode == "ADD"){
        result = saturate_int(registers[register1] + param3_value);
    }
    else if (opcode == "SUB"){
        result = saturate_int(registers[register1] - param3_value);
    }
    return result;
}


// Executes le program in the file named 'program_path'
void exec(const std::string& program_path){

    //generate a map with the 4 registers
    std::map<std::string,uint16_t> registers = build_map();

    std::fstream file;
    file.open(program_path); //open file
    if(!file){              //if inexistant path or open() failed
        std::cerr<<"open() failed\n";
        exit(EXIT_FAILURE);
    }

    std::string opcode;

    Parameter second_parameter,third_parameter;
    std::string register1,register2;
    uint16_t param2_value,param3_value;
    uint8_t address;
    
    bool ignore = false; //for IFNZ operator
    std::string line;

    while(getline(file, line)){
        if(!ignore){
            opcode = parse_opcode(line);
            second_parameter = parse_operand(line,2);
            if (!second_parameter.is_a_value){ //it's a register name
                register1 = std::get<std::string>(second_parameter.the_data); //retrieve register name from variant
                param2_value = registers[register1]; //value in the register

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
                    registers[register1] = pop();                    
                }

                else if(opcode == "SET" || opcode == "ADD" || opcode == "SUB" ){
                    third_parameter = parse_operand(line,3);
                    if(!third_parameter.is_a_value){ //if it's a register name
                        register2 = std::get<std::string>(third_parameter.the_data);
                        param3_value = registers[register2];  
                    }
                    else{ //it's just a value
                        param3_value = std::get<uint16_t>(third_parameter.the_data);
                    }

                    registers[register1] = set_and_sub(registers,opcode,register1,param3_value);
                        
                }
            }
            else {
                address = std::get<uint16_t>(second_parameter.the_data);
                third_parameter = parse_operand(line,3);

                if (!third_parameter.is_a_value){ //register name
                    register2 = std::get<std::string>(third_parameter.the_data);
                    param3_value = registers[register2];

                    if (opcode == "STORE"){
                        write(address,param3_value);
                    }

                    else if (opcode == "LOAD"){
                        registers[register2] = read(address);
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