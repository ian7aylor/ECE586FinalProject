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


/*/////////////////////////////////////////////////////
Function Prototypes
?*//////////////////////////////////////////////////////
string get_input_file();
string hex_decoder(string hex_addr);
string instructions_decoder(string binary_addr,int Register[], int Memory[], int counter[], uint8_t special);
int print_result(int counter[], int Register[], int Memory[], uint8_t special);
int pipeline_sim(int rs[], int rt[], int rd[]);
/*/////////////////////////////////////////////////////
Instruction class with declared functions + definitions
*//////////////////////////////////////////////////////
class instructions_exe {

public:
	/*/////////////////////////////////////////////////////////////
	Addition function of values in two registers
	Stores in target register
	*//////////////////////////////////////////////////////////////
    void add_func(string binary_addr, int Register[], int Memory[]) {
        
        //Get instruction decoder
        string rs_bin = binary_addr.substr(6, 5);
        string rt_bin = binary_addr.substr(11, 5);
        string rd_bin = binary_addr.substr(16, 5);

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);
        int rt = stoi(rt_bin, nullptr, 2);
        int rd = stoi(rd_bin, nullptr, 2);

        //Set the value to the register, [rd] = [rs] + [rt]
        cout << rd << ": "<< Register[rd] << "    " << rs << ": "<< Register[rs] << "   " << rt <<": " << Register[rt] << endl;
        Register[rd] = Register[rs] + Register[rt];

        cout << rd << ": " << Register[rd] << endl;
    }
	/*/////////////////////////////////////////////////////////////
	Subtraction function of values in two registers
	Stores in target register
	*//////////////////////////////////////////////////////////////
    void sub_func(string binary_addr, int Register[], int Memory[]) {
        //Get instruction decoder
        string rs_bin = binary_addr.substr(6, 5);
        string rt_bin = binary_addr.substr(11, 5);
        string rd_bin = binary_addr.substr(16, 5);

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);
        int rt = stoi(rt_bin, nullptr, 2);
        int rd = stoi(rd_bin, nullptr, 2);

        //Set the value to the register, [rd] = [rs] + [rt]
        cout << rd << ": "<< Register[rd] << "    " << rs << ": "<< Register[rs] << "   " << rt <<": " << Register[rt] << endl;
        Register[rd] = Register[rs] - Register[rt];

        cout << rd << ": " << Register[rd] << endl;
    }
	/*/////////////////////////////////////////////////////////////
	Multiplication function of values in two registers
	Stores in target register
	*//////////////////////////////////////////////////////////////
    void mul_func(string binary_addr, int Register[], int Memory[]) {
        //Get instruction decoder
        string rs_bin = binary_addr.substr(6, 5);
        string rt_bin = binary_addr.substr(11, 5);
        string rd_bin = binary_addr.substr(16, 5);

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);
        int rt = stoi(rt_bin, nullptr, 2);
        int rd = stoi(rd_bin, nullptr, 2);

        //Set the value to the register, [rd] = [rs] * [rt]
        cout << rd << ": "<< Register[rd] << "    " << rs << ": "<< Register[rs] << "   " << rt <<": " << Register[rt] << endl;
        Register[rd] = Register[rs] * Register[rt];

        cout << rd << ": " << Register[rd] << endl;
    }
	/*/////////////////////////////////////////////////////////////
	Add Immediate function. Adds value in one register with an immediate value
	Stores in target register
	*//////////////////////////////////////////////////////////////	
    void addi_func(string binary_addr, int Register[], int Memory[]) {
        
        //Get instruction decoder
        string rs_bin = binary_addr.substr(6, 5);		//
        string rt_bin = binary_addr.substr(11, 5);
        string Imm_bin = binary_addr.substr(16, 16);

        if (Imm_bin.substr(0, 1) == "1") {
            cout << "Negative number... Need to use 2s' complement" << endl;
        }

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);
        int rt = stoi(rt_bin, nullptr, 2);
        int Imm = stoi(Imm_bin, nullptr, 2);
        
        //Set the value to the register, [rt] = [rs] + Imm
        Register[rt] = Register[rs] + Imm;

        cout << rt << ": " << Register[rt] << endl;
        
    }
	/*/////////////////////////////////////////////////////////////
	Subtract Immediate function. Adds value in one register with an immediate value
	Stores in target register
	*//////////////////////////////////////////////////////////////	
    void subi_func(string binary_addr, int Register[], int Memory[]) {

        //Get instruction decoder
        string rs_bin = binary_addr.substr(6, 5);		//Gets binary value for 
        string rt_bin = binary_addr.substr(11, 5);
        string Imm_bin = binary_addr.substr(16, 16);

        if (Imm_bin.substr(0, 1) == "1") {
            cout << "Negative number... Need to use 2s' complement" << endl;
        }

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);
        int rt = stoi(rt_bin, nullptr, 2);
        int Imm = stoi(Imm_bin, nullptr, 2);

        //Set the value to the register, [rt] = [rs] - Imm
        Register[rt] = Register[rs] - Imm;

        cout << rt << ": " << Register[rt] << endl;

    }
	/*/////////////////////////////////////////////////////////////
	Multiply Immediate function. Adds value in one register with an immediate value
	Stores in target register
	*//////////////////////////////////////////////////////////////	
    void muli_func(string binary_addr, int Register[], int Memory[]) {

        //Get instruction decoder
        string rs_bin = binary_addr.substr(6, 5);
        string rt_bin = binary_addr.substr(11, 5);
        string Imm_bin = binary_addr.substr(16, 16);

        if (Imm_bin.substr(0, 1) == "1") {
            cout << "Negative number... Need to use 2s' complement" << endl;
        }

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);
        int rt = stoi(rt_bin, nullptr, 2);
        int Imm = stoi(Imm_bin, nullptr, 2);

        //Set the value to the register, [rt] = [rs] * Imm
        Register[rt] = Register[rs] * Imm;

        cout << rt << ": " << Register[rt] << endl;

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
    void OR_func(string binary_addr, int Register[], int Memory[]){
        
        //Decode the instruction
        string rs_bin = binary_addr.substr(6, 5);
        string rt_bin = binary_addr.substr(11, 5);
        string rd_bin = binary_addr.substr(16, 5);

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);
        int rt = stoi(rt_bin, nullptr, 2);
        int rd = stoi(rd_bin, nullptr, 2);

        //Set the value to the register, [rd] = [rs] | [rt]
        Register[rd] = Register[rs] | Register[rt];
        cout << rd << ": "<< Register[rd] << "    " << rs << ": "<< Register[rs] << "   " << rt <<": " << Register[rt] << endl;
    }

    void ORI_func(string binary_addr, int Register[], int Memory[]){
        
        //Get instruction decoder
        string rs_bin = binary_addr.substr(6, 5);		//Gets binary value for 
        string rt_bin = binary_addr.substr(11, 5);
        string Imm_bin = binary_addr.substr(16, 16);

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);
        int rt = stoi(rt_bin, nullptr, 2);
        int Imm = stoi(Imm_bin, nullptr, 2);

        //Set the value to the register, [rt] = [rs] | Imm
        Register[rt] = Register[rs] | Imm;

        cout << rt << ": " << Register[rt] << endl;
    }

    void AND_func(string binary_addr, int Register[], int Memory[] ){
        //Decode the instruction
        string rs_bin = binary_addr.substr(6, 5);
        string rt_bin = binary_addr.substr(11, 5);
        string rd_bin = binary_addr.substr(16, 5);

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);
        int rt = stoi(rt_bin, nullptr, 2);
        int rd = stoi(rd_bin, nullptr, 2);

        //Set the value to the register, [rd] = [rs] & [rt]
        Register[rd] = Register[rs] & Register[rt];
        cout << rd << ": "<< Register[rd] << "    " << rs << ": "<< Register[rs] << "   " << rt <<": " << Register[rt] << endl;
    }

    void ANDI_func(string binary_addr, int Register[], int Memory[]){
        //Get instruction decoder
        string rs_bin = binary_addr.substr(6, 5);		//Gets binary value for 
        string rt_bin = binary_addr.substr(11, 5);
        string Imm_bin = binary_addr.substr(16, 16);

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);
        int rt = stoi(rt_bin, nullptr, 2);
        int Imm = stoi(Imm_bin, nullptr, 2);

        //Set the value to the register, [rt] = [rs] & Imm
        Register[rt] = Register[rs] & Imm;

        cout << rt << ": " << Register[rt] << endl; 
    }

    void XOR_func(string binary_addr, int Register[], int Memory[]){
        //Decode the instruction
        string rs_bin = binary_addr.substr(6, 5);
        string rt_bin = binary_addr.substr(11, 5);
        string rd_bin = binary_addr.substr(16, 5);

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);
        int rt = stoi(rt_bin, nullptr, 2);
        int rd = stoi(rd_bin, nullptr, 2);

        //Set the value to the register, [rd] = [rs] ^ [rt]
        Register[rd] = Register[rs] ^ Register[rt];
        cout << rd << ": "<< Register[rd] << "    " << rs << ": "<< Register[rs] << "   " << rt <<": " << Register[rt] << endl;
    }

    void XORI_func(string binary_addr, int Register[], int Memory[]){
        //Get instruction decoder
        string rs_bin = binary_addr.substr(6, 5);		//Gets binary value for 
        string rt_bin = binary_addr.substr(11, 5);
        string Imm_bin = binary_addr.substr(16, 16);

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);
        int rt = stoi(rt_bin, nullptr, 2);
        int Imm = stoi(Imm_bin, nullptr, 2);

        //Set the value to the register, [rt] = [rs] & Imm
        Register[rt] = Register[rs] ^ Imm;

        cout << rt << ": " << Register[rt] << endl;     
    }

    /*//////////////////////////////////////////////////////////////
    Memory Access Instructions
    - LDW
    - STW
    *///////////////////////////////////////////////////////////////
    void LDW_func(string binary_addr, int Register[], int Memory[]){
        //Get instruction decoder
        string rs_bin = binary_addr.substr(6, 5);		//Gets binary value for 
        string rt_bin = binary_addr.substr(11, 5);
        string Imm_bin = binary_addr.substr(16, 16);

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);
        int rt = stoi(rt_bin, nullptr, 2);
        int Imm = stoi(Imm_bin, nullptr, 2);

        //Set the value to the register, [rt] = Mem[[rs] + Imm]
        Register[rt] = Memory[Register[rs] + Imm];

        cout << "R" << rt << ": " << Register[rt] << endl;     
    }
    void STW_func(string binary_addr, int Register[], int Memory[]){
        //Get instruction decoder
        string rs_bin = binary_addr.substr(6, 5);		//Gets binary value for 
        string rt_bin = binary_addr.substr(11, 5);
        string Imm_bin = binary_addr.substr(16, 16);

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);
        int rt = stoi(rt_bin, nullptr, 2);
        int Imm = stoi(Imm_bin, nullptr, 2);

        //Set the value to the register, Mem[[rs] + Imm] = [rt]
        Memory[Register[rs] + Imm] = Register[rt];

        cout << "Memory Address: "<< Register[rs] + Imm << "--> Data: " << Register[rt] << endl;     
    }
    /*//////////////////////////////////////////////////////////////
    Control Flow Instructions
    - BZ
    - BEQ
    - JR
    *///////////////////////////////////////////////////////////////
};

//Create an Register Array Reg[32] to store R0-R31 register
//Create an Memorry Array Mem[32768] to store all address content

int main()
{
    string test_line;
    string user_test_file;
    ifstream inFile;		
    string binary_code;
    int Register [32];
    int Memory[32768];
    int counter[5];
    uint8_t special = 0;        //tells print whether it is a halt or not. Initialize to 0

    //initialize register array to values of 0
    for (int i = 0; i < 32; i++) {
        Register[i] = 0;
    }

    //initialize memory array to values of 0
    for (int i = 0; i < 32768; i++) {
        Memory[i] = 0;
    }

    //initialize counter array to values of 0
    for (int i = 0; i < 5; i++) {
        counter[i] = 0;
    }

    user_test_file = get_input_file();	//user input file - gets user test file
    inFile.open(user_test_file);		//opens user test file
	
	//While not at the end of the file
    while (!inFile.eof()) {
        inFile >> test_line;		//inFile reads in strings 1 by 1 (delimiter is a space)
        binary_code = hex_decoder(test_line);		//Calls on hex_decoder and returns the binary code for that line
        cout << binary_code << endl;		//Prints the binary code for that line

        //Get the total number of instructions counter[0]
        //Get the total number of arithmetic instructions counter[1]
        //Get the total number of logical instructions counter[2]
        //Get the total number of memory instructions counter[3]
        //Get the total number of control transfer instructions counter[4]

        counter[0] = counter[0] + 1;	//Keeps track of total instructions

        string result = instructions_decoder(binary_code, Register, Memory, counter, special);
    }
    print_result(counter, Register, Memory, special);
}

/*////////////////////////////////////////////////////
Prints the final results of the pipeline
*/////////////////////////////////////////////////////
int print_result(int counter[], int Register[], int Memory[], uint8_t special) {

    cout << "\n**** Instructions count summary ****" << endl;
    cout << "Total number of instructions: " << counter[0] << endl;
    cout << "Total number of arithmetic instructions: " << counter[1] << endl;
    cout << "Total number of logical instructions: " << counter[2] << endl;
    cout << "Total number of memory instructions: " << counter[3] << endl;
    cout << "Total number of control transfer instructions: " << counter[4] << endl;

    //Print Final Register Contents    
    cout << "Final Register State:" << endl;

    cout <<"Program counter: " << endl;
    for (int i = 0; i < 32; i++) {
        if (Register[i] != 0){
            cout << "R" << i << ": " << Register[i] << endl; 
        }
    }
    cout << "Total stalls: " << endl;
    cout << "Final Memory State: " << endl;
     for (int i = 0; i < 32768; i++) {
        if (Memory[i] != 0) {
            cout << "Address: " << i << " ,Contents: " << Memory[i] << endl;
        }
    }
    cout << "Timing Simulator:" << endl;

    cout << "Total number of clock cycles" << endl;
    if (special == 1){
        cout << "Program Halted" << endl;
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
Convert hex to binary
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
Instruction decoder
*/////////////////////////////////////////////////////
string instructions_decoder(string binary_addr, int Register[], int Memory[], int counter[], uint8_t special) {
    instructions_exe function;		//instruction object
    string result;    	            			
	int instruction_type[2];

	//Checking if instruction is valid before proceeding
    if (binary_addr != "00000000000000000000000000000000") {
        string opcode = binary_addr.substr(0, 6);
		//Checking if an arithmetic instruction
        if (opcode == "000000") {
            cout << "call ADD function..." << endl;
            counter[1] = counter[1] + 1;    //counts instructions of type arithmetic
            function.add_func(binary_addr, Register, Memory);

        }
        else if (opcode == "000010") {

            cout << "call SUB function..." << endl;
            counter[1] = counter[1] + 1;    //counts instructions of type arithmetic
        }
        else if (opcode == "000100") {

            cout << "call MUL function..." << endl;
            counter[1] = counter[1] + 1;    //counts instructions of type arithmetic
        }
        else if (opcode == "000001") {

            cout << "call ADDI function..." << endl;
            counter[1] = counter[1] + 1;    //counts instructions of type arithmetic
            function.addi_func(binary_addr, Register, Memory);
        }
        else if (opcode == "000011") {

            cout << "call SUBI function..." << endl;
            counter[1] = counter[1] + 1;    //counts instructions of type arithmetic
            function.subi_func(binary_addr, Register, Memory);
        }
        else if (opcode == "000101") {

            cout << "call MULI function..." << endl;
            counter[1] = counter[1] + 1;    //counts instructions of type arithmetic
            function.muli_func(binary_addr, Register, Memory);
        }
        else if (opcode == "000110") {
            cout << "call OR function..." << endl;
            counter[2] = counter[2] + 1;    //counts instructions of type logic
            function.OR_func(binary_addr, Register, Memory);
        }
        else if (opcode == "000111") {
            cout << "call OR Immediate function..." << endl;
            counter[2] = counter[2] + 1;    //counts instructions of type logic
            function.ORI_func(binary_addr, Register, Memory);
        }
        else if (opcode == "001000") {
            cout << "call AND function..." << endl;
            counter[2] = counter[2] + 1;    //counts instructions of type logic
            function.AND_func(binary_addr, Register, Memory);
        }
        else if (opcode == "001001") {
            cout << "call AND Immediate function..." << endl;
            counter[2] = counter[2] + 1;    //counts instructions of type logic
            function.ANDI_func(binary_addr, Register, Memory);
        }    
        else if (opcode == "001010") {
            cout << "call XOR function..." << endl;
            counter[2] = counter[2] + 1;    //counts instructions of type logic
            function.XOR_func(binary_addr, Register, Memory);
        }  
        else if (opcode == "001011") {
            cout << "call XOR Immediate function..." << endl;
            counter[2] = counter[2] + 1;    //counts instructions of type logic
            function.XORI_func(binary_addr, Register, Memory);
        }     
        else if (opcode == "001100") {
            cout << "call STW Immediate function..." << endl;
            counter[3] = counter[3] + 1;    //counts instructions of type memory
            function.LDW_func(binary_addr, Register, Memory);
        }  
        else if (opcode == "001101") {
            cout << "call STW Immediate function..." << endl;
            counter[3] = counter[3] + 1;
            function.STW_func(binary_addr, Register, Memory);
        }
        else if (opcode == "010001") {
            cout << "Halting the program" << endl;
            special = 1;
            print_result(counter, Register, Memory, special);
        }
    }
    
    else {
        cout << "0x00000000 input... skip!" << endl;
    }

    return result;
}
/*//////////////////////////////////////////////
This is a pipeline that looks at previous instructions
And looks for RAW and WAR hazards and whether or not there is a stall on the pipeline.
Need to look at timing for both forwarding and non-forwarding pipeline structures
//Needs work
*//////////////////////////////////////////////
int pipeline_sim(int rs[], int rt[], int rd[], int PC[], string[]){


return 0;
}