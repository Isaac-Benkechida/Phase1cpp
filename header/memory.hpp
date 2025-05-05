#include "../header/utils.h"

#define B 8 //memory cell size
#define DATA_SIZE 2 //bytes that an element occupies
#define FIST_ADDRESS 0
#define STACK_LAST_ADDRESS 15

/* I have decided that in memory, the data will be stored using big endian boutism */
extern uint16_t stack_pointer; // points to the top of the stack



/*---------------------------------------Memory Manipulation functions-------------------------------------------------*/
class Memory {
    private:
        uint8_t* MEM ;  //initialisation of memory
        uint8_t nbits;

    public:
        inline Memory(uint8_t nbits){ // nbits = address size .
            int memory_size = 1 << nbits; //determine the size of the memory with nbits .
            MEM = new uint8_t[memory_size];
            this->nbits = nbits;
        };
        inline ~Memory(){ delete[] MEM; };

        struct MsbAndLsb{
            // references of memory slots
            uint8_t& lsb; 
            uint8_t& msb;
            
            operator uint16_t() const{ //transforms struct to its uint16_t equivalent (uint16_t value = MEM[address])
                return static_cast<uint16_t>((msb << B) | lsb ); 
            }

            MsbAndLsb& operator=(uint16_t value){ // stores the value at the address as an MsbAndLsb
                lsb = static_cast<uint8_t>(value & 0xFF); //mask the msb
                msb = static_cast<uint8_t>((value >> B) & 0xFF); // most significant bits (shift to right + masking)
                return *this;
            }

        };


        MsbAndLsb operator[](uint8_t address){ // to modify the contents of memory (write)
            memory_overflow(address); // check if the address is in bounds
            return {MEM[address],MEM[address+1]}; // take both memory cells and ref them in the struct
        }


        void memory_overflow(uint8_t address);
        uint16_t pop();
        void push(uint16_t value);
};



