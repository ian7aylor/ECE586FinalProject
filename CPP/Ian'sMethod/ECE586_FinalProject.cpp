// ECE586_FinalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h> 
#include <iostream> 	//input-output stream
#include <fstream>		//file stream
#include <string>		//string classes like string, wstring etc.
#include <sstream>		//string stream functionality
#include <filesystem>	//Retrieve information about paths, files, directories
#include <string.h>		//allows for strcpy, strlen functions
using namespace std;


/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Function Prototypes
*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string get_input_file();
string hex_decoder(string hex_addr);
int instructions_decoder(string binary_addr,int Register[], int Memory[], int counter[], int register_change[], int memory_change[], uint8_t special, int PC);
void print_result(int counter[], int Register[], int Memory[],int register_change[], int memory_change[], uint8_t special, int PC);
void register_change_list(string binary_addr, int register_change[], bool if_imm);
void memory_change_list(string binary_addr,int Register[], int register_change[]);
void pipe_check(void);

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Instruction class with declared functions + definitions
Contains the following functions:
    Arithmetic
        Add, ADDI
        SUB, SUBI
        MUL, MULI
    Logical
        OR, ORI
        AND, ANDI
        XOR, XORI
    Memory
        LDW
        STW
    Control
        BEZ,
        BNEZ,
        BEQ,
        JR
        HALT
*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class instructions_exe {

public:

    /*/////////////////////////////////////////////////////////////
    If the binary value is negative (leading 1), take the one's complement
    Add 1 to the resulting value and return the result
    *//////////////////////////////////////////////////////////////
    int two_complement(string bin_16b) {

        for (int i = 0; i < bin_16b.length(); i++) {
            if (bin_16b[i] == '1') {
                bin_16b[i] = '0';
            }
            else {
                bin_16b[i] = '1';
            }
        }

        int dec_16b_1comp = stoi(bin_16b, nullptr, 2);
        int dec_16b_2comp = dec_16b_1comp + 1;

        return dec_16b_2comp;
    }


    /*/////////////////////////////////////////////////////////////
    Addition function of values in two registers
    Stores in target register
    *//////////////////////////////////////////////////////////////
    void add_func(string binary_addr, int Register[], int Memory[]) {

        //Get instruction decoder
        string rs_bin = binary_addr.substr(6, 5);		//Gets rs binary string from binary instruction
        string rt_bin = binary_addr.substr(11, 5);		//Gets rt binary string from binary instruction
        string rd_bin = binary_addr.substr(16, 5);		//Gets rd binary string from binary instruction

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);          //takes binary string and turns to an integer
        int rt = stoi(rt_bin, nullptr, 2);          //takes binary string and turns to an integer
        int rd = stoi(rd_bin, nullptr, 2);          //takes binary string and turns to an integer

        //Set the value to the register, [rd] = [rs] + [rt]
        //register 0 must remain a value of 0. It cannot be changed in MIPS
        if (rd != 0) {
            Register[rd] = Register[rs] + Register[rt];
        }
        //Print operands and result
        cout << "rd: " << Register[rd] << "; rs: " << Register[rs] << "; rt: " << Register[rt] << endl;
    }
    /*/////////////////////////////////////////////////////////////
    Subtraction function of values in two registers
    Stores in target register
    *//////////////////////////////////////////////////////////////
    void sub_func(string binary_addr, int Register[], int Memory[]) {
        //Get instruction decoder
        string rs_bin = binary_addr.substr(6, 5);		//Gets rs binary string from binary instruction
        string rt_bin = binary_addr.substr(11, 5);		//Gets rt binary string from binary instruction
        string rd_bin = binary_addr.substr(16, 5);		//Gets rd binary string from binary instruction

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);          //takes binary string and turns to an integer
        int rt = stoi(rt_bin, nullptr, 2);          //takes binary string and turns to an integer
        int rd = stoi(rd_bin, nullptr, 2);          //takes binary string and turns to an integer

        //Set the value to the register, [rd] = [rs] - [rt]
        //register 0 must remain a value of 0. It cannot be changed in MIPS
        if (rd != 0) {
            Register[rd] = Register[rs] - Register[rt];
        }
        //Print operands and result
        cout << "rd: " << Register[rd] << "; rs: " << Register[rs] << "; rt: " << Register[rt] << endl;
    }
    /*/////////////////////////////////////////////////////////////
    Multiplication function of values in two registers
    Stores in target register
    *//////////////////////////////////////////////////////////////
    void mul_func(string binary_addr, int Register[], int Memory[]) {
        //Get instruction decoder
        string rs_bin = binary_addr.substr(6, 5);		//Gets rs binary string from binary instruction
        string rt_bin = binary_addr.substr(11, 5);		//Gets rt binary string from binary instruction
        string rd_bin = binary_addr.substr(16, 5);		//Gets rd binary string from binary instruction

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);           //takes binary string and turns to an integer
        int rt = stoi(rt_bin, nullptr, 2);          //takes binary string and turns to an integer
        int rd = stoi(rd_bin, nullptr, 2);          //takes binary string and turns to an integer

        //Set the value to the register, [rd] = [rs] * [rt]      
        //register 0 must remain a value of 0. It cannot be changed in MIPS       
        if (rd != 0) {
            Register[rd] = Register[rs] * Register[rt];
        }
        //Print operands and result
        cout << "rd: " << Register[rd] << "; rs: " << Register[rs] << "; rt: " << Register[rt] << endl;
    }
    /*/////////////////////////////////////////////////////////////
    Add Immediate function. Adds value in one register with an immediate value
    Stores in target register
    *//////////////////////////////////////////////////////////////	
    void addi_func(string binary_addr, int Register[], int Memory[]) {

        //Get instruction decoder
        string rs_bin = binary_addr.substr(6, 5);		//Gets rs binary string from binary instruction		
        string rt_bin = binary_addr.substr(11, 5);		//Gets rt binary string from binary instruction
        string Imm_bin = binary_addr.substr(16, 16);		//Gets Imm binary string from binary instruction
        int Imm = 0;

        if (Imm_bin.substr(0, 1) == "1") {
            cout << "Negative number... Need to use 2s' complement" << endl;
            int dec_2comp = two_complement(Imm_bin);
            Imm = dec_2comp * (-1);      //Sets integer to negative value
        }
        else {
            Imm = stoi(Imm_bin, nullptr, 2);      //takes binary string and turns to an integer
        }

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);          //takes binary string and turns to an integer
        int rt = stoi(rt_bin, nullptr, 2);          //takes binary string and turns to an integer

        //Set the value to the register, [rt] = [rs] + Imm
        //register 0 must remain a value of 0. It cannot be changed in MIPS
        if (rt != 0) {
            Register[rt] = Register[rs] + Imm;
        }
        //Print operands and results
        cout << "rt: " << Register[rt] << "; rs: " << Register[rs] << "; Imm: " << Imm << endl;

    }
    /*/////////////////////////////////////////////////////////////
    Subtract Immediate function. Adds value in one register with an immediate value
    Stores in target register
    *//////////////////////////////////////////////////////////////	
    void subi_func(string binary_addr, int Register[], int Memory[]) {

        //Get instruction decoder
        string rs_bin = binary_addr.substr(6, 5);		//Gets rs binary string from binary instruction
        string rt_bin = binary_addr.substr(11, 5);		//Gets rt binary string from binary instruction
        string Imm_bin = binary_addr.substr(16, 16);		//Gets Imm binary string from binary instruction

        int Imm = 0;
        if (Imm_bin.substr(0, 1) == "1") {
            cout << "Negative number... Need to use 2s' complement" << endl;
            int dec_2comp = two_complement(Imm_bin);
            Imm = dec_2comp * (-1);      //Sets integer to negative value
        }
        else {
            Imm = stoi(Imm_bin, nullptr, 2);      //takes binary string and turns to an integer
        }

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);      //takes binary string and turns to an integer
        int rt = stoi(rt_bin, nullptr, 2);      //takes binary string and turns to an integer

        //Set the value to the register, [rt] = [rs] - Imm
        //register 0 must remain a value of 0. It cannot be changed in MIPS
        if (rt != 0) {
            Register[rt] = Register[rs] - Imm;
        }

        //Print operands and results
        cout << "rt: " << Register[rt] << "; rs: " << Register[rs] << "; Imm: " << Imm << endl;

    }
    /*/////////////////////////////////////////////////////////////
    Multiply Immediate function. Adds value in one register with an immediate value
    Stores in target register
    *//////////////////////////////////////////////////////////////	
    void muli_func(string binary_addr, int Register[], int Memory[]) {

        //Get instruction decoder
        string rs_bin = binary_addr.substr(6, 5);		//Gets rs binary string from binary instruction
        string rt_bin = binary_addr.substr(11, 5);		//Gets rt binary string from binary instruction
        string Imm_bin = binary_addr.substr(16, 16);		//Gets Imm binary string from binary instruction

        int Imm = 0;
        if (Imm_bin.substr(0, 1) == "1") {
            cout << "Negative number... Need to use 2s' complement" << endl;
            int dec_2comp = two_complement(Imm_bin);
            Imm = dec_2comp * (-1);      //Sets integer to negative value
        }
        else {
            Imm = stoi(Imm_bin, nullptr, 2);      //takes binary string and turns to an integer
        }

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);      //takes binary string and turns to an integer
        int rt = stoi(rt_bin, nullptr, 2);      //takes binary string and turns to an integer

        //Set the value to the register, [rt] = [rs] * Imm
        //register 0 must remain a value of 0. It cannot be changed in MIPS
        if (rt != 0) {
            Register[rt] = Register[rs] * Imm;
        }

        //Print operands and results
        cout << "rt: " << Register[rt] << "; rs: " << Register[rs] << "; Imm: " << Imm << endl;

    }

    /*/////////////////////////////////////////////////////////////
    Logical functions:
    - OR
    - OR Immediate
    - AND
    - AND Immediate
    - XOR
    - XOR Immediate
    *//////////////////////////////////////////////////////////////	
    /*/////////////////////////////////////////////////////////////
    OR function. ORs values of in 2 registers
    Stores in target register
    *//////////////////////////////////////////////////////////////	
    void OR_func(string binary_addr, int Register[], int Memory[]) {

        //Decode the instruction
        string rs_bin = binary_addr.substr(6, 5);		//Gets rs binary string from binary instruction
        string rt_bin = binary_addr.substr(11, 5);		//Gets rt binary string from binary instruction
        string rd_bin = binary_addr.substr(16, 5);		//Gets rd binary string from binary instruction

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);      //takes binary string and turns to an integer
        int rt = stoi(rt_bin, nullptr, 2);      //takes binary string and turns to an integer
        int rd = stoi(rd_bin, nullptr, 2);      //takes binary string and turns to an integer

        //Set the value to the register, [rd] = [rs] | [rt]
        //register 0 must remain a value of 0. It cannot be changed in MIPS
        if (rd != 0) {
            Register[rd] = Register[rs] | Register[rt];
        }

        //Print operands and result
        cout << "rd: " << Register[rd] << "; rs: " << Register[rs] << "; rt: " << Register[rt] << endl;
    }
    /*/////////////////////////////////////////////////////////////
    OR Immediate function. ORs value in one register with an immediate value
    Stores in target register
    *//////////////////////////////////////////////////////////////	
    void ORI_func(string binary_addr, int Register[], int Memory[]) {

        //Get instruction decoder
        string rs_bin = binary_addr.substr(6, 5);		//Gets rs binary string from binary instruction
        string rt_bin = binary_addr.substr(11, 5);		//Gets rt binary string from binary instruction
        string Imm_bin = binary_addr.substr(16, 16);		//Gets Imm binary string from binary instruction

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);          //takes binary string and turns to an integer
        int rt = stoi(rt_bin, nullptr, 2);          //takes binary string and turns to an integer
        int Imm = stoi(Imm_bin, nullptr, 2);        //takes binary string and turns to an integer

        //Set the value to the register, [rt] = [rs] | Imm
        //register 0 must remain a value of 0. It cannot be changed in MIPS
        if (rt != 0) {
            Register[rt] = Register[rs] | Imm;
        }

        //Print operands and results
        cout << "rt: " << Register[rt] << "; rs: " << Register[rs] << "; Imm: " << Imm << endl;
    }
    /*/////////////////////////////////////////////////////////////
    AND function. ANDs values of in 2 registers
    Stores in target register
    *//////////////////////////////////////////////////////////////	
    void AND_func(string binary_addr, int Register[], int Memory[]) {
        //Decode the instruction
        string rs_bin = binary_addr.substr(6, 5);		//Gets rs binary string from binary instruction
        string rt_bin = binary_addr.substr(11, 5);		//Gets rt binary string from binary instruction
        string rd_bin = binary_addr.substr(16, 5);		//Gets rd binary string from binary instruction

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);          //takes binary string and turns to an integer
        int rt = stoi(rt_bin, nullptr, 2);          //takes binary string and turns to an integer
        int rd = stoi(rd_bin, nullptr, 2);          //takes binary string and turns to an integer

        //Set the value to the register, [rd] = [rs] & [rt]
       //register 0 must remain a value of 0. It cannot be changed in MIPS
        if (rd != 0) {
            Register[rd] = Register[rs] & Register[rt];
        }

        //Print operands and result
        cout << "rd: " << Register[rd] << "; rs: " << Register[rs] << "; rt: " << Register[rt] << endl;
    }
    /*/////////////////////////////////////////////////////////////
    AND Immediate function. ORs value in one register with an immediate value
    Stores in target register
    *//////////////////////////////////////////////////////////////	
    void ANDI_func(string binary_addr, int Register[], int Memory[]) {
        //Get instruction decoder
        string rs_bin = binary_addr.substr(6, 5);		//Gets rs binary string from binary instruction
        string rt_bin = binary_addr.substr(11, 5);		//Gets rt binary string from binary instruction
        string Imm_bin = binary_addr.substr(16, 16);		//Gets Imm binary string from binary instruction

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);          //takes binary string and turns to an integer
        int rt = stoi(rt_bin, nullptr, 2);          //takes binary string and turns to an integer
        int Imm = stoi(Imm_bin, nullptr, 2);          //takes binary string and turns to an integer

        //Set the value to the register, [rt] = [rs] & Imm
        //register 0 must remain a value of 0. It cannot be changed in MIPS
        if (rt != 0) {
            Register[rt] = Register[rs] & Imm;
        }

        //Print operands and result
        cout << "rt: " << Register[rt] << "; rs: " << Register[rs] << "; Imm: " << Imm << endl;
    }
    /*/////////////////////////////////////////////////////////////
    XOR function. XORs values of in 2 registers
    Stores in target register
    *//////////////////////////////////////////////////////////////	
    void XOR_func(string binary_addr, int Register[], int Memory[]) {
        //Decode the instruction
        string rs_bin = binary_addr.substr(6, 5);		//Gets rs binary string from binary instruction
        string rt_bin = binary_addr.substr(11, 5);		//Gets rt binary string from binary instruction
        string rd_bin = binary_addr.substr(16, 5);		//Gets rd binary string from binary instruction

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);          //takes binary string and turns to an integer
        int rt = stoi(rt_bin, nullptr, 2);          //takes binary string and turns to an integer
        int rd = stoi(rd_bin, nullptr, 2);          //takes binary string and turns to an integer

        //Set the value to the register, [rd] = [rs] ^ [rt]
       //register 0 must remain a value of 0. It cannot be changed in MIPS
        if (rd != 0) {
            Register[rd] = Register[rs] ^ Register[rt];
        }

        //Print operands and result
        cout << "rd: " << Register[rd] << "; rs: " << Register[rs] << "; rt: " << Register[rt] << endl;
    }
    /*/////////////////////////////////////////////////////////////
    XOR Immediate function. ORs value in one register with an immediate value
    Stores in target register
    *//////////////////////////////////////////////////////////////	
    void XORI_func(string binary_addr, int Register[], int Memory[]) {
        //Get instruction decoder
        string rs_bin = binary_addr.substr(6, 5);		//Gets rs binary string from binary instruction 
        string rt_bin = binary_addr.substr(11, 5);		//Gets rt binary string from binary instruction
        string Imm_bin = binary_addr.substr(16, 16);		//Gets Imm binary string from binary instruction

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);          //takes binary string and turns to an integer
        int rt = stoi(rt_bin, nullptr, 2);          //takes binary string and turns to an integer
        int Imm = stoi(Imm_bin, nullptr, 2);          //takes binary string and turns to an integer

        //register 0 must remain a value of 0. It cannot be changed in MIPS       
        if (rt != 0) {
            //Set the value to the register, [rt] = [rs] & Imm
            Register[rt] = Register[rs] ^ Imm;
        }

        //Print operands and result
        cout << "rt: " << Register[rt] << "; rs: " << Register[rs] << "; Imm: " << Imm << endl;
    }

    /*//////////////////////////////////////////////////////////////
    Memory Access Instructions
    - LDW
    - STW
    *///////////////////////////////////////////////////////////////
    /*/////////////////////////////////////////////////////////////
    LDW function. Reads value from memory address (that is stored in register)
    and writes value to a register
    *//////////////////////////////////////////////////////////////	
    void LDW_func(string binary_addr, int Register[], int Memory[]) {
        //Get instruction decoder
        string rs_bin = binary_addr.substr(6, 5);		//Gets rs binary string from binary instruction
        string rt_bin = binary_addr.substr(11, 5);		//Gets rt binary string from binary instruction
        string Imm_bin = binary_addr.substr(16, 16);		//Gets Imm binary string from binary instruction

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2); 		    //Gets rs binary string from binary instruction
        int rt = stoi(rt_bin, nullptr, 2);          //takes binary string and turns to an integer
        int Imm = stoi(Imm_bin, nullptr, 2);          //takes binary string and turns to an integer

       //register 0 must remain a value of 0. It cannot be changed in MIPS
        if (rt != 0) {
            //Set the value to the register, [rt] = Mem[[rs] + Imm]
            Register[rt] = Memory[Register[rs] + Imm];
        }

        //Print operands and result
        cout << "R" << rt << ": " << Register[rt] << ";LW from Mem Address: " << Memory[Register[rs] + Imm] << endl;
    }
    /*/////////////////////////////////////////////////////////////
    STW function. Writes value in one register to the memory address
    that is stored in another register
    *//////////////////////////////////////////////////////////////	
    void STW_func(string binary_addr, int Register[], int Memory[]) {
        //Get instruction decoder
        string rs_bin = binary_addr.substr(6, 5);		//Gets rs binary string from binary instruction
        string rt_bin = binary_addr.substr(11, 5);		//Gets rt binary string from binary instruction
        string Imm_bin = binary_addr.substr(16, 16);		//Gets Imm binary string from binary instruction

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);          //takes binary string and turns to an integer
        int rt = stoi(rt_bin, nullptr, 2);          //takes binary string and turns to an integer
        int Imm = stoi(Imm_bin, nullptr, 2);          //takes binary string and turns to an integer

        //Set the value to the register, Mem[[rs] + Imm] = [rt]
        Memory[Register[rs] + Imm] = Register[rt];

        //Print operands and result
        cout << "SW in Mem Address: " << Register[rs] + Imm << ";Data: " << Register[rt] << endl;
    }
    /*//////////////////////////////////////////////////////////////
    Control Flow Instructions
    - BZ
    - BEQ
    - JR
    -Halt --> Handled in instruction decoder since it just calls on pr
    inting results
    *///////////////////////////////////////////////////////////////
    /*/////////////////////////////////////////////////////////////
        STW function. Writes value in one register to the memory address
        that is stored in another register
        *//////////////////////////////////////////////////////////////	
    int BZ_func(string binary_addr, int Register[], int PC){
        //Get instruction decoder
        string rs_bin = binary_addr.substr(6, 5);		//Gets rs binary string from binary instruction
        string Imm_bin = binary_addr.substr(16, 16);		//Gets Imm binary string from binary instruction

        int Imm = 0;
        if (Imm_bin.substr(0, 1) == "1") {
            cout << "Negative number... Need to use 2s' complement" << endl;
            int dec_2comp = two_complement(Imm_bin);
            Imm = dec_2comp * (-1);      //Sets integer to negative value
        }
        else {
            Imm = stoi(Imm_bin, nullptr, 2);      //takes binary string and turns to an integer
        }
        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);          //takes binary string and turns to an integer

        //If contents of rs equal 0, update the PC with the immediate value
        if (Register[rs] == 0) {
            PC += Imm;
            cout << "R[" << rs << "]: " << Register[rs];               //should say 0
            cout << " New PC: " << PC << endl;           //New program counter based on the immediate value + PC
        }
        else {
            cout << "R[" << rs << "]!= 0;";               //should say 0
            cout << " PC: " << PC << endl;;           //New program counter based on the immediate value + PC
        }
        return PC;
    }
    /*/////////////////////////////////////////////////////////////
        STW function. Writes value in one register to the memory address
        that is stored in another register
        *//////////////////////////////////////////////////////////////	
    int BEQ_func(string binary_addr, int Register[], int PC) {
        //Get instruction decoder
        string rs_bin = binary_addr.substr(6, 5);		//Gets rs binary string from binary instruction
        string rt_bin = binary_addr.substr(11, 5);		//Gets rt binary string from binary instruction
        string Imm_bin = binary_addr.substr(16, 16);		//Gets Imm binary string from binary instruction
       
        int Imm = 0;
        if (Imm_bin.substr(0, 1) == "1") {
            cout << "Negative number... Need to use 2s' complement" << endl;
            int dec_2comp = two_complement(Imm_bin);
            Imm = dec_2comp * (-1);      //Sets integer to negative value
        }
        else {
            Imm = stoi(Imm_bin, nullptr, 2);      //takes binary string and turns to an integer
        }
        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);          //takes binary string and turns to an integer
        int rt = stoi(rt_bin, nullptr, 2);          //takes binary string and turns to an integer

        //If contents of rs equal contents of rt, update the PC with the immediate value
        if (Register[rs] == Register[rt]) {
            PC += Imm;
            cout << "R[" << rs << "]" << "equals R[" << rt << "] = " << Register[rs];
            cout << " New PC: " << PC << endl;;
        }
        else {
            cout << "R[" << rs << "]" << "!= R[" << rt << "];";
            cout << " PC: " << PC << endl;
        }
        return PC;
    }
    /*/////////////////////////////////////////////////////////////
        STW function. Writes value in one register to the memory address
        that is stored in another register
        *//////////////////////////////////////////////////////////////	
    int JR_func(string binary_addr, int Register[], int PC) {
        //Get instruction decoder
        string rs_bin = binary_addr.substr(6, 5);		//Gets rs binary string from binary instruction

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);          //takes binary string and turns to an integer

        PC = Register[rs];
        cout << "New PC: " << PC << endl;;
        return PC;
    }
};

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Create an Register Array Reg[32] to store R0-R31 register
//Create an Memorry Array Mem[32768] to store all address content
Main Function:

*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){
    //#pragma comment(linker, "/STACK:8000000")
    string test_line;
    string user_test_file;
    ifstream inFile;
    ofstream test, PCprint, MemImageOutput;
    string binary_code;
    int Register [32];          //Holds register values, register 0 cannot be written to
    int Memory[32768];          //Holds memory values  
    int register_change[32];
    int memory_change[32768];
    int counter[5];             //Keeps track of type of instructions
    int CC, stall;              //Keeps
    uint8_t special = 0;        //tells print whether it is a halt or not. Initialize to 0
    
    //PC 
    string *DynamicPCArray;      //Points to a address which holds string data.
    int PC = -1;                 //Initializes program counter
    int ProgramEnd;             //Integer that holds total length of PC

    //initialize register array to values of 0
    for (int i = 0; i < 32; i++) {
        Register[i] = 0;                //initialize all registers to a value of 0
        register_change[i] = -999;      //just sets register_change for all 32 registers to a randomly chosen number, -999
    }

    //initialize memory array to values of 0
    for (int i = 0; i < 32768; i++) {
        Memory[i] = 0;          //Sets all memory address spaces to a value of 0
        memory_change[i] = -999;        //Sets all memory change spaces to a value of 0.
    }

    //initialize counter array to values of 0
    for (int i = 0; i < 5; i++) {
        counter[i] = 0;         //initialize all instruction type counters to 0
    }

    /*/////////////////////////////////////////////////////////////
    This section is where the program grabs the list of instructions
    And stores the instructions in a instruction memory array
    It also determines:
    - range of instruction addresses (PC)
    - Total instruction memory space
    *//////////////////////////////////////////////////////////////	
    user_test_file = get_input_file();	//user input file - gets user test file
    inFile.open(user_test_file);		//opens user test file
	
    //This gets the length of the program in single integer values
    //true PC is PC * 4
    while (!inFile.eof()){
        inFile >> test_line;
        if (!inFile.eof()) {
            if (PC >= 0) {
                PC = PC + 1;
            }
            else if (PC < 0) {
                PC = 0;
            }
        }
    }
    ProgramEnd = PC;            //We count 0 as the PC start. Subtract 1 because the above while loop adds 1 more and if it does not get a line then ends. Need to remove the last read.
    cout << "Address seen as single bits: 0 to " << ProgramEnd << endl;  //Prints the total array address spce. This is the range used to access
    cout << "Total Program Addresses:0 to " << ProgramEnd*4 << endl;     //Print the total program end from 0 - Program End
    cout << "Total Program Memory Space is:0 to" << (ProgramEnd + 1) * 4 << endl;       //Shows total memory space.
    /*/////////////////////////////////////////////////////////////
    Create the new array given the total length of the program
      This will allow us to go back and forth in the program when
      branching
    *///////////////////////////////////////////////////////////
    DynamicPCArray = new string[ProgramEnd];
   
    /*////////////////////////////////////
    //Debugging
   for (PC = 0; PC <= ProgramEnd; PC++) {
        cout << PC << endl;
    }
    *////////////////////////////////////

    //sets file back to the start to prepare for reading into our new array
    inFile.clear();
    inFile.seekg(0);
    
    test.open("test.txt");
    PCprint.open("PCTest.txt");
    //Reading strings into 
    for (PC = 0; PC <= ProgramEnd; PC++) {
        inFile >> test_line;
        if(!inFile.eof()){
            DynamicPCArray[PC] = test_line;
            test << DynamicPCArray[PC] << endl;
        }
        PCprint << PC << endl;
    }
    //Close File
    inFile.close();

    //start at beginning of the program and read in the values
    for (PC = 0; PC <= ProgramEnd; PC++) {
        binary_code = hex_decoder(DynamicPCArray[PC]);		//Calls on hex_decoder and returns the binary code for that line
        cout << binary_code << endl;		//Prints the binary code for that line

        //Get the total number of instructions counter[0]
        //Get the total number of arithmetic instructions counter[1]
        //Get the total number of logical instructions counter[2]
        //Get the total number of memory instructions counter[3]
        //Get the total number of control transfer instructions counter[4] 
        counter[0] = counter[0] + 1;	//Keeps track of total instructions

       PC = instructions_decoder(binary_code, Register, Memory, counter, register_change, memory_change, special, PC);
    }
    print_result(counter, Register, Memory, register_change, memory_change, special, PC);
}

/*////////////////////////////////////////////////////
Prints the final results of the pipeline
*/////////////////////////////////////////////////////
void print_result(int counter[], int Register[], int Memory[],int register_change[], int memory_change[], uint8_t special, int PC) {
    ofstream Memory_Image;
    string text;        //what to write to conole and txt file

    Memory_Image.open("Memory_Image.txt");      //open .txt file

    //1st line
    text = "\n ****Instructions count summary ****";
    cout << text << endl;
    Memory_Image << text << endl;
    //second line
    text = "Total number of instructions: ";
    cout << text << counter[0] << endl;
    Memory_Image << text << counter[0] << endl;

    //3rd line
    text = "Total number of arithmetic instructions: ";
    cout << text << counter[1] << endl;
    Memory_Image << text << counter[1] << endl;
    
    //4th line
    text = "Total number of logical instructions : ";
    cout << text << counter[2] << endl;
    Memory_Image << text << counter[2] << endl;

    //5th line
    text = "Total number of memory instructions: ";
    cout << text << counter[3] << endl;
    Memory_Image << text << counter[3] << endl;

    //6th line
    text = "Total number of control transfer instructions: ";
    cout << text << counter[4] << endl;
    Memory_Image << text << counter[4] << endl;

    //Print Final Register Contents
    text = "\nFinal Register State:";
    cout << text << endl;
    Memory_Image << text << endl;

    //Print Program Counter
    text = "Program counter: ";
    cout << text << PC << endl;
    Memory_Image << text << PC << endl;
    
    for (int i = 0; i < 32; i++) {
        if (register_change[i] != -999){
            cout << "R" << i << ": " << Register[i] << endl;                //prints to console
            Memory_Image << "R" << i << ": " << Register[i] << endl;        //prints to .txt file
        }
    }


    text = "\nFinal Memory State: ";
    cout << text << endl;
    Memory_Image << text << endl;
    for (int i = 0; i < 32768; i++) {
        if (memory_change[i] != -999) {
            cout << "Address: " << i << " ,Contents: " << Memory[i] << endl;
            Memory_Image << "Address: " << i << " ,Contents: " << Memory[i] << endl;
        }
    }
    //Print Timing Simulator
    text = "\nTiming Simulator:";
    cout << text << endl;
    Memory_Image << text << endl;

    text = "Without Forwarding:";
    cout << text << endl;
    Memory_Image << text << endl;
    //Print stalls
    text = "Total stalls: ";
    cout << text << endl;
    Memory_Image << text << endl;
    //Print clock cycles
    text = "Total number of clock cycles: ";
    cout << text << endl;
    Memory_Image << text << endl;

    text = "With Forwarding:";
    cout << text << endl;
    Memory_Image << text << endl;
    //Print stalls
    text = "Total stalls: ";
    cout << text << endl;
    Memory_Image << text << endl;
    //Print clock cycles
    text = "Total number of clock cycles: ";
    cout << text << endl;
    Memory_Image << text << endl;

    //If program is halted
    if (special == 1){
        text = "Program was Halted";
        cout << text << endl;
        Memory_Image << text << endl;
    }
    exit(0);

}
/*////////////////////////////////////////////////////
//Get user input file and check if the file is valid
*/////////////////////////////////////////////////////
string get_input_file() {
    string input_file;


    cout << "Please enter a valid test file:\n";
    //cin >> input_file;
    input_file = "C:/Learning/GI_CQ/Spring2021/ECE586_CompArch/ECE586FinalProject/CPP/Ian'sMethod/logic_image.txt";
    //input C:\Users\taipham\source\repos\ECE586_FinalProject\sample_memory_image.txt
    cout << "Input file: " << input_file << endl;     //Write out the input file


    bool file_flag = true;		//Set a flag
	
	//Check if file has valid data, if valid set file_flag to false and ask for valid file location
    while (file_flag) {
        ifstream f(input_file.c_str());		//Read from this file
        if (!(f.good())) {
            cout << "Test file is not valid. Please enter a valid test file:\n";
            cin >> input_file;
            cout << "Input file: " << input_file << endl;
        }
        else {
            file_flag = false;
        }
    }
    return input_file;		//returns input file to main
}

/*//////////////////////////////////////////////
Function that Converts hex to binary
*///////////////////////////////////////////////
string hex_decoder(string hex_addr) {

    long int i = 0;
    string address = "";
    string temp_address = "";

    while (hex_addr[i]) {

        switch (hex_addr[i]) {

        case '0':

            temp_address = "0000";
            break;

        case '1':
            temp_address = "0001";
            break;

        case '2':
            temp_address = "0010";
            break;

        case '3':
            temp_address = "0011";
            break;

        case '4':
            temp_address = "0100";
            break;

        case '5':
            temp_address = "0101";
            break;

        case '6':
            temp_address = "0110";
            break;

        case '7':
            temp_address = "0111";
            break;

        case '8':
            temp_address = "1000";
            break;

        case '9':
            temp_address = "1001";
            break;

        case 'A':
            temp_address = "1010";
            break;

        case 'B':
            temp_address = "1011";
            break;

        case 'C':
            temp_address = "1100";
            break;

        case 'D':
            temp_address = "1101";
            break;

        case 'E':
            temp_address = "1110";
            break;

        case 'F':
            temp_address = "1111";
            break;

        default:
            cout << "\nInvalid hexadecimal digit. Hex digit must be number of capital letter: A, B, C, D, E, F: "
                << hex_addr[i] << endl;
        }
        address = address.append(temp_address);		//appends binary values to address
        // cout << address << endl;
        i++;
    }
    return address;
}

/*////////////////////////////////////////////////////
Instruction decoder stage
*/////////////////////////////////////////////////////
int instructions_decoder(string binary_addr, int Register[], int Memory[], int counter[],int register_change[], int memory_change[], uint8_t special, int PC) {
    instructions_exe function;		//instruction object
    string result;
    bool if_imm_flag = false;
	
	//Checking if instruction is valid before proceeding
    if (binary_addr != "00000000000000000000000000000000") {
        string opcode = binary_addr.substr(0, 6);
		//Checking if an arithmetic instruction
        if (opcode == "000000") {
            cout << "call ADD function..." << endl;
            counter[1] = counter[1] + 1;    //counts instructions of type arithmetic
            function.add_func(binary_addr, Register, Memory);
            register_change_list(binary_addr, register_change, if_imm_flag);
        }
        else if (opcode == "000010") {

            cout << "call SUB function..." << endl;
            counter[1] = counter[1] + 1;
            function.sub_func(binary_addr, Register, Memory);
            register_change_list(binary_addr, register_change, if_imm_flag);
        }
        else if (opcode == "000100") {

            cout << "call MUL function..." << endl;
            counter[1] = counter[1] + 1;
            function.mul_func(binary_addr, Register, Memory);
            register_change_list(binary_addr, register_change, if_imm_flag);
        }
        else if (opcode == "000001") {

            cout << "call ADDI function..." << endl;
            counter[1] = counter[1] + 1;    //counts instructions of type arithmetic
            function.addi_func(binary_addr, Register, Memory);

            if_imm_flag = true;
            register_change_list(binary_addr, register_change, if_imm_flag);
        }
        else if (opcode == "000011") {

            cout << "call SUBI function..." << endl;
            counter[1] = counter[1] + 1;    //counts instructions of type arithmetic
            function.subi_func(binary_addr, Register, Memory);

            if_imm_flag = true;
            register_change_list(binary_addr, register_change, if_imm_flag);
        }
        else if (opcode == "000101") {

            cout << "call MULI function..." << endl;
            counter[1] = counter[1] + 1;    //counts instructions of type arithmetic
            function.muli_func(binary_addr, Register, Memory);

            if_imm_flag = true;
            register_change_list(binary_addr, register_change, if_imm_flag);
        }
        //Logical Operations
        else if (opcode == "000110") {
            //OR instruction
            cout << "call OR function..." << endl;
            counter[2] = counter[2] + 1;    //counts instructions of type arithmetic
            function.OR_func(binary_addr, Register, Memory);

            if_imm_flag = true;
            register_change_list(binary_addr, register_change, if_imm_flag);
        }
        else if (opcode == "000111") {
            //ORI instruction
            cout << "call OR Immediate function..." << endl;
            counter[2] = counter[2] + 1;    //counts instructions of type arithmetic
            function.ORI_func(binary_addr, Register, Memory);

            if_imm_flag = true;
            register_change_list(binary_addr, register_change, if_imm_flag);
        }
        else if (opcode == "001000") {
            //AND instruction
            cout << "call AND function..." << endl;
            counter[2] = counter[2] + 1;    //counts instructions of type arithmetic
            function.AND_func(binary_addr, Register, Memory);

            if_imm_flag = true;
            register_change_list(binary_addr, register_change, if_imm_flag);
        }
        else if (opcode == "001001") {
            //AND Immediate instruction
            cout << "call AND Immediate function..." << endl;
            counter[2] = counter[2] + 1;    //counts instructions of type arithmetic
            function.ANDI_func(binary_addr, Register, Memory);

            if_imm_flag = true;
            register_change_list(binary_addr, register_change, if_imm_flag);
        }
        else if (opcode == "001010") {
            //XOR instruction
            cout << "call XOR function..." << endl;
            counter[2] = counter[2] + 1;    //counts instructions of type arithmetic
            function.XOR_func(binary_addr, Register, Memory);

            if_imm_flag = true;
            register_change_list(binary_addr, register_change, if_imm_flag);
        }
        else if (opcode == "001011") {
            //XOR Immediate instruction
            cout << "call XOR Immediate function..." << endl;
            counter[2] = counter[2] + 1;    //counts instructions of type arithmetic
            function.XORI_func(binary_addr, Register, Memory);

            if_imm_flag = true;
            register_change_list(binary_addr, register_change, if_imm_flag);
        }
        //Memory Operations
        else if (opcode == "001100") {
            //LDW instruction
            cout << "call LDW function..." << endl;
            counter[3] = counter[3] + 1;    //counts instructions of type arithmetic
            function.LDW_func(binary_addr, Register, Memory);

            if_imm_flag = true;
            register_change_list(binary_addr, register_change, if_imm_flag);
        }
        else if (opcode == "001101") {
            //STW instruction
            cout << "call STW function..." << endl;
            counter[3] = counter[3] + 1;    //counts instructions of type arithmetic
            function.STW_func(binary_addr, Register, Memory);
            
            memory_change_list(binary_addr, Register, memory_change);
        }
        //Control Operations
        else if (opcode == "001110") {
            //BZ instruction
            cout << "Call BZ function..." << endl;
            PC = function.BZ_func(binary_addr, Register, PC);
            counter[4] = counter[4] + 1;    //counts instructions of type arithmetic         
        }
        else if (opcode == "001111") {
            //BEQ instruction
            cout << "Call BEQ function..." << endl;
            PC = function.BEQ_func(binary_addr, Register, PC);
            counter[4] = counter[4] + 1;    //counts instructions of type control
        }
        else if (opcode == "010000") {
            //JR instruction
            cout << "Call JR function..." << endl;
            PC = function.JR_func(binary_addr, Register, PC);
            counter[4] = counter[4] + 1;    //counts instructions of type Control
        }       
        else if (opcode == "010001") {
            //Halt instruction
            cout << "Halting Program..." << endl;
            counter[4] = counter[4] + 1;    //counts instructions of type Control
            special = 1;
            print_result(counter, Register, Memory, register_change, memory_change, special, PC);
        }
    }
    else {
        cout << "0x00000000 input... skip!" << endl;
    }
    return PC;
}

/*//////////////////////////////////////////////////////////////////////////////////
Keeps track of changes in register values
*//////////////////////////////////////////////////////////////////////////////////
void register_change_list(string binary_addr, int register_change[], bool if_imm) {

    bool if_exist_flag = false;
    int r_reg;

    //Get rd register
    if (if_imm == false) {
        r_reg = stoi(binary_addr.substr(16, 5), nullptr, 2);
        
    }

    //Get rt register
    else {
        r_reg = stoi(binary_addr.substr(11, 5), nullptr, 2);
    }

    for (int i = 0; i < 32; i++) {
        //cout << register_change[i] << endl;
        if (r_reg == register_change[i]) {
            if_exist_flag = true;
        }
        if (register_change[i] == -999) {
            break;
        }
    }

    if (if_exist_flag == false) {
        for (int i = 0; i < 32; i++) {
            if (register_change[i] == -999) {
                register_change[i] = r_reg;
                break;
            }
        }
    }
}


/*//////////////////////////////////////////////////////////////////////////////////
Keep track of the change in memory values 
*//////////////////////////////////////////////////////////////////////////////////
void memory_change_list(string binary_addr, int Register[], int memory_change[]) {

    int m_mem, rreg, IMM;
    bool if_exist_flag = false;


    rreg = stoi(binary_addr.substr(6, 5), nullptr, 2);        //get source register
    IMM = stoi(binary_addr.substr(16, 16), nullptr, 2);       //Get immediate value for adding to the source register contents
    

    m_mem = Register[rreg] + IMM;       //Memory address = Target Register contents

    for (int i = 0; i < 32768; i++) {
        if (m_mem == memory_change[i]) {
            if_exist_flag = true;
        }
        if (memory_change[i] == -999) {
            break;
        }
    }

    if (if_exist_flag == false) {
        for (int i = 0; i < 32768; i++) {
            if (memory_change[m_mem] == -999) {
                memory_change[m_mem] = m_mem;
                //cout << m_mem << endl;
                break;
            }
        }
    }
}
/*//////////////////////////////////////////////
This will determine if stalls are required based on the previous instructions that have already entered the pipe
This will check on what type of instruction they are and take appropriate actions based on that.
*//////////////////////////////////////////////
void pipe_check(void) {



}