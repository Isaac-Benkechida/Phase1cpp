#include "main.hpp"
#include "memory.hpp"


//returns the saturated version of the value
int saturate_int(int value){
    int upper = 65535; 
    int saturated = std::min(std::max(value,0),upper); // saturates the int
    return saturated; // cast to the right type(avoids warnings and unexpected behaviour)
}


bool is_register_name(std::string third_parameter,std::map<std::string,int>& registers){
    registers.find(third_parameter) != registers.end();
}


//Extracts the Instruction to execute
std::string parse_opcode(const std::string& instr){
    std::string opcode;
    std::stringstream ss(instr);
    ss >> opcode;
    return opcode;
}


//extracts the operand that follows an instruction
std::string parse_operand(const std::string& instr){
    std::string operand;
    std::stringstream ss(instr);
    ss >> operand;
    ss >> operand;
    
    return operand;
}



//extracts the operand that follows an instruction
uint16_t parse_value(const std::string& instr, std::map<std::string,int>& registers){
    std::string third_parameter;

    //parse the line to access the third parameter
    std::stringstream ss(instr);
    ss >> third_parameter;
    ss >> third_parameter;
    ss >> third_parameter; //access third parameter of the line

    if (is_register_name(third_parameter,registers)) {
        // It's a register name, return its value
        return registers[third_parameter];
    }
    else{
        int value;
        //convert it to uint16_t
        if ((value = std::stoi(third_parameter)) == -1){
            std::cerr<<"stoi() failed\n";
            exit(-1);
        }
        return value;
    }
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
    std::string param1;
    uint16_t third_parameter;

    bool ignore = false; //for IFNZ operator
    std::string line;

    while(getline(file, line)){
        if(!ignore){
            opcode = parse_opcode(line); //get instruction
            param1 = parse_operand(line); //parse reg on which operation will be exec on

            //print
            if(opcode == "PRINT"){
                std::cout << registers[param1] <<std::endl;
            }

            //ignore next instruction if null value in register
            else if(opcode == "IFNZ" ){
                if (registers[param1] == 0){
                    ignore = true;
                }
            }
            

            else {
                third_parameter = parse_value(line,registers);
                
                //assignement
                if(opcode == "SET"){
                    registers[param1] = saturate_int(third_parameter);
                    
                }

                //addition
                else if(opcode == "ADD"){
                    registers[param1] = saturate_int(registers[param1] + third_parameter);
                    
                }

                //subtraction
                else if(opcode == "SUB"){
                    registers[param1] = saturate_int(registers[param1] - third_parameter);
                    
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