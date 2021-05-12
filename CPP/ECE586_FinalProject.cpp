// ECE586_FinalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h> 
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
#include <string.h>

using namespace std;



string get_input_file();
string hex_decoder(string hex_addr);
string instructions_decoder(string binary_addr,int Register[], int Memory[], int counter[]);


class instructions_exe {

public:

    void add_func() {

    }
    void sub_func() {

    }
    void mul_func() {

    }
    void addi_func(string binary_addr, int Register[], int Memory[]) {
        
        //Get instruction decoder
        string rs_bin = binary_addr.substr(6, 5);
        string rt_bin = binary_addr.substr(11, 5);
        string Imm_bin = binary_addr.substr(16, 16);

        //Convert the binary value to dec
        int rs = stoi(rs_bin, nullptr, 2);
        int rt = stoi(rt_bin, nullptr, 2);
        int Imm = stoi(Imm_bin, nullptr, 2);
        
        //Set the value to the register, [rt] = [rs] + Imm
        Register[rt] = Register[rs] + Imm;

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

    //initialize register array
    for (int i = 0; i < 32; i++) {
        Register[i] = 0;
    }

    //initialize memory array
    for (int i = 0; i < 32768; i++) {
        Memory[i] = 0;
    }

    //initialize counter array
    for (int i = 0; i < 5; i++) {
        counter[i] = 0;
    }

    user_test_file = get_input_file();
    inFile.open(user_test_file);

    while (!inFile.eof()) {
        inFile >> test_line;

        binary_code = hex_decoder(test_line);
        cout << binary_code << endl;

        //Get the total number of instructions counter[0]
        //Get the total number of arithmetic instructions counter[1]
        //Get the total number of logical instructions counter[2]
        //Get the total number of memory instructions counter[3]
        //Get the total number of control transfer instructions counter[4]

        counter[0] = counter[0] + 1;

        string result = instructions_decoder(binary_code, Register, Memory, counter);
    }


    cout << "\n**** Instructions count summary ****" << endl;
    cout << "Total number of instructions: " << counter[0] << endl;
    cout << "Total number of arithmetic instructions: " << counter[1] << endl;
    cout << "Total number of logical instructions: " << counter[2] << endl;
    cout << "Total number of memory instructions: " << counter[3] << endl;
    cout << "Total number of control transfer instructions: " << counter[4] << endl;
}

//Get user input file and check if the file is valid
string get_input_file() {
    string input_file;


    cout << "Please enter a valid test file:\n";
    //cin >> input_file;
    input_file = "C:/Users/taipham/source/repos/ECE586_FinalProject/sample_memory_image.txt";

    //input C:\Users\taipham\source\repos\ECE586_FinalProject\sample_memory_image.txt
    cout << "Input file: " << input_file << endl;
    //Get the input file

    bool file_flag = true;

    while (file_flag) {
        ifstream f(input_file.c_str());
        if (!(f.good())) {
            cout << "Test file is not valid. Please enter a valid test file:\n";
            cin >> input_file;
            cout << "Input file: " << input_file << endl;
        }
        else {
            file_flag = false;
        }
    }
    return input_file;
}

//Convert hex to binary
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
        address = address.append(temp_address);
        // cout << address << endl;
        i++;
    }
    return address;
}

//Instruction decoder
string instructions_decoder(string binary_addr, int Register[], int Memory[], int counter[]) {
    instructions_exe function;
    string result;    

    if (binary_addr != "00000000000000000000000000000000") {
        string opcode = binary_addr.substr(0, 6);

        if (opcode == "000000") {
            cout << "call ADD function..." << endl;
            counter[1] = counter[1] + 1;
        }
        else if (opcode == "000010") {

            cout << "call SUB function..." << endl;
            counter[1] = counter[1] + 1;
        }
        else if (opcode == "000100") {

            cout << "call MUL function..." << endl;
            counter[1] = counter[1] + 1;
        }
        else if (opcode == "000001") {

            cout << "call ADDI function..." << endl;
            counter[1] = counter[1] + 1;
            function.addi_func(binary_addr, Register, Memory);
        }
        else if (opcode == "000011") {

            cout << "call SUBI function..." << endl;
            counter[1] = counter[1] + 1;
        }
        else if (opcode == "000101") {

            cout << "call MULI function..." << endl;
            counter[1] = counter[1] + 1;
        }
    }
    
    else {
        cout << "0x00000000 input... skip!" << endl;
    }
    

    return result;
}