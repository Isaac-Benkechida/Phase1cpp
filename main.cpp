#include <iostream>
#include <cstdint>
#include <algorithm> // to access MIN and MAX methodes
#include <string>
#include <fstream
>

uint16_t saturate_int(int value);
std::string parse_opcode(const std::string& instr);
uint16_t parse_operand(const std::string& instr);
void exec(const std::string& program_path);



//returns the saturated version of the value
uint16_t saturate_int(int value){
    int max_val = 65535;
    uint16_t saturated = std::min(std::max(value,0),max_val); // saturates the int
    return static_cast<uint16_t>(saturated); // cast to the right type(avoids warnings and unexpected behaviour)
}


std::string parse_opcode(const std::string& instr){
    std::string opcode;
    std::stringstream ss(line);
    ss >> opcode;
    return opcode;
}



int main(){
    uint16_t register_val = 0; //initialised to 0
    fstream file;
    char* filepath = argv[1]
    file.open(filepath,ios::in); //open file in read mode
    if(!file){ //if iniexistant path or open failed
        exit(EXIT_FAILURE);
    }

    char* line;
    std::string opcode;
    while(std::getline(instr)){
        opcode = parse_opcode(const std::string& instr);
        

    }


    return 0;
}