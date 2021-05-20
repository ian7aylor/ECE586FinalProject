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

// user prototype functions
string get_input_file();
string hex_decoder(string hex_addr);
string instructions_decoder(string binary_addr,int Register[], int Memory[], int counter[], int register_change[], int memory_change[]);
void register_change_list(string binary_addr, int register_change[], bool if_imm);

/*/////////////////////////////////////////////////////
Instruction class with declared functions + definitions
*//////////////////////////////////////////////////////
class instructions_exe {

public:

    int two_complement(string bin_16b) {
        
        for (int i = 0; i < bin_16b.length(); i++) {
            if (bin_16b[i] == '1') {
                bin_16b[i] == '0';
            }
            else {
                bin_16b[i] == '1';
            }
        }

        int dec_16b_1comp = stoi(bin_16b, nullptr, 2);
        int dec_16b_2comp = dec_16b_1comp + 1;

        return dec_16b_2comp;
    }

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
    void sub_func(string binary_addr, int Register[], int Memory[]) {

        //Get instruction decoder
        string rs_bin = binary_addr.substr(6, 5);
        string rt_bin = binary_addr.substr(11, 5);
        string rd_bin = binary_addr.substr(16, 5);

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);
        int rt = stoi(rt_bin, nullptr, 2);
        int rd = stoi(rd_bin, nullptr, 2);

        //Set the value to the register, [rd] = [rs] - [rt]
        cout << rd << ": " << Register[rd] << "    " << rs << ": " << Register[rs] << "   " << rt << ": " << Register[rt] << endl;
        Register[rd] = Register[rs] - Register[rt];

        cout << rd << ": " << Register[rd] << endl;
    }
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
        cout << rd << ": " << Register[rd] << "    " << rs << ": " << Register[rs] << "   " << rt << ": " << Register[rt] << endl;
        Register[rd] = Register[rs] * Register[rt];

        cout << rd << ": " << Register[rd] << endl;
    }
    void addi_func(string binary_addr, int Register[], int Memory[]) {
        
        //Get instruction decoder
        string rs_bin = binary_addr.substr(6, 5);
        string rt_bin = binary_addr.substr(11, 5);
        string Imm_bin = binary_addr.substr(16, 16);
        int Imm = 0;

        if (Imm_bin.substr(0, 1) == "1") {
            cout << "Negative number... Need to use 2s' complement" << endl;
            int dec_2comp = two_complement(Imm_bin);
            Imm = dec_2comp * (-1);
        }
        else {
            Imm = stoi(Imm_bin, nullptr, 2);
        }

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);
        int rt = stoi(rt_bin, nullptr, 2);
        
        //Set the value to the register, [rt] = [rs] + Imm
        cout << "rt: " << Register[rt] << "; rs: " << Register[rs] << "; Imm: " << Imm << endl;
        Register[rt] = Register[rs] + Imm;

        cout << rt << ": " << Register[rt] << endl;
        
    }

    void subi_func(string binary_addr, int Register[], int Memory[]) {

        //Get instruction decoder
        string rs_bin = binary_addr.substr(6, 5);
        string rt_bin = binary_addr.substr(11, 5);
        string Imm_bin = binary_addr.substr(16, 16);
        int Imm = 0;

        if (Imm_bin.substr(0, 1) == "1") {
            cout << "Negative number... Need to use 2s' complement" << endl;
            int dec_2comp = two_complement(Imm_bin);
            Imm = dec_2comp * (-1);
        }
        else {
            Imm = stoi(Imm_bin, nullptr, 2);
        }

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);
        int rt = stoi(rt_bin, nullptr, 2);

        //Set the value to the register, [rt] = [rs] - Imm
        cout << "rt: " << Register[rt] << "; rs: " << Register[rs] << "; Imm: " << Imm << endl;
        Register[rt] = Register[rs] - Imm;
        cout << rt << ": " << Register[rt] << endl;

    }

    void muli_func(string binary_addr, int Register[], int Memory[]) {

        //Get instruction decoder
        string rs_bin = binary_addr.substr(6, 5);
        string rt_bin = binary_addr.substr(11, 5);
        string Imm_bin = binary_addr.substr(16, 16);
        int Imm = 0;

        if (Imm_bin.substr(0, 1) == "1") {
            cout << "Negative number... Need to use 2s' complement" << endl;
            int dec_2comp = two_complement(Imm_bin);
            Imm = dec_2comp * (-1);
        }
        else {
            Imm = stoi(Imm_bin, nullptr, 2);
        }

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);
        int rt = stoi(rt_bin, nullptr, 2);

        //Set the value to the register, [rt] = [rs] * Imm
        cout << "rt: " << Register[rt] << "; rs: " << Register[rs] << "; Imm: " << Imm << endl;
        Register[rt] = Register[rs] * Imm;

        cout << rt << ": " << Register[rt] << endl;

    }
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
    int register_change[32];
    int memory_change[32768];

    //initialize register array
    for (int i = 0; i < 32; i++) {
        Register[i] = 0;
        register_change[i] = -999;
    }

    //initialize memory array
    for (int i = 0; i < 32768; i++) {
        Memory[i] = 0;
        memory_change[i] = -999;
    }

    //initialize counter array
    for (int i = 0; i < 5; i++) {
        counter[i] = 0;
    }

    user_test_file = get_input_file();	//user input file
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

        string result = instructions_decoder(binary_code, Register, Memory, counter, register_change, memory_change);

        // Save register change list and memory change list

    }

    cout << "\n**** Register Summary ****" << endl;
    for (int i = 0; i < 32; i++) {
        if (register_change[i] != -999) {
            cout << "R" << register_change[i] << ": " << Register[register_change[i]] << endl;
        }
        else {
            break;
        }
    }

    cout << "\n**** Instructions count summary ****" << endl;
    cout << "Total number of instructions: " << counter[0] << endl;
    cout << "Total number of arithmetic instructions: " << counter[1] << endl;
    cout << "Total number of logical instructions: " << counter[2] << endl;
    cout << "Total number of memory instructions: " << counter[3] << endl;
    cout << "Total number of control transfer instructions: " << counter[4] << endl;
}
/*////////////////////////////////////////////////////
//Get user input file and check if the file is valid
*/////////////////////////////////////////////////////
string get_input_file() {
    string input_file;


    cout << "Please enter a valid test file:\n";
    //cin >> input_file;
    input_file = "C:/Users/taipham/source/repos/ECE586_FinalProject/sample_memory_image.txt";
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
string instructions_decoder(string binary_addr, int Register[], int Memory[], int counter[], int register_change[], int memory_change[]) {
    instructions_exe function;		//instruction object
    string result;
    bool if_imm_flag = false;
	
	//Checking if instruction is valid before proceeding
    if (binary_addr != "00000000000000000000000000000000") {
        string opcode = binary_addr.substr(0, 6);

        if (opcode == "000000") {
            cout << "call ADD function..." << endl;
            counter[1] = counter[1] + 1;
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
            counter[1] = counter[1] + 1;
            function.addi_func(binary_addr, Register, Memory);

            if_imm_flag = true;
            register_change_list(binary_addr, register_change, if_imm_flag);
        }
        else if (opcode == "000011") {

            cout << "call SUBI function..." << endl;
            counter[1] = counter[1] + 1;
            function.subi_func(binary_addr, Register, Memory);

            if_imm_flag = true;
            register_change_list(binary_addr, register_change, if_imm_flag);
        }
        else if (opcode == "000101") {

            cout << "call MULI function..." << endl;
            counter[1] = counter[1] + 1;
            function.muli_func(binary_addr, Register, Memory);

            if_imm_flag = true;
            register_change_list(binary_addr, register_change, if_imm_flag);
        }
    }
    
    else {
        cout << "0x00000000 input... skip!" << endl;
    }
    

    return result;
}

//Keep track of the change of register
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