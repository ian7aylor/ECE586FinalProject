// ECE586_FinalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
​
#include <stdio.h> 		
#include <iostream>		//input-output stream
#include <fstream>		//file stream
#include <string>		//string classes like string, wstring etc.
#include <sstream>		//string stream functionality
#include <filesystem>	//Retrieve information about paths, files, directories
#include <string.h>		//allows for strcpy, strlen functions
​
using namespace std;
​/*
Function Prototypes
​*//////////////////////////////////////////////////////
string get_input_file();
string hex_decoder(string hex_addr);
string instructions_decoder(string binary_addr);
​///////////////////////////////////////////////////////

/*/////////////////////////////////////////////////////
Instruction class with declared functions, not yet defined
*//////////////////////////////////////////////////////
class instructions_exe {
​
public:
​
    void add_func() {
​
    }
    void sub_func() {
​
    }
    void mul_func() {
​
    }
    void addi_func() {
​
    }
};
​
//Create an Register Array Reg[32] to store R0-R31 register
//Create an Memorry Array Mem[32768] to store all address content
​
int main()
{
    string test_line;
    string user_test_file = get_input_file();
    ifstream inFile;
    string binary_code;
​
    inFile.open(user_test_file);		//opens user test file found in get_input_file function
​
	//While not at end of line 
    while (!inFile.eof()) {
        inFile >> test_line;
​
        binary_code = hex_decoder(test_line);		//turns binary to hex
        cout << binary_code << endl;
​
        string result = instructions_decoder(binary_code);		//decodes binary into their proper instructions
​
    }
}
​
/*//////////////////////////////////////////////////
Get user input file and check if the file is valid
*///////////////////////////////////////////////////
string get_input_file() {
    string input_file;
​
​
    cout << "Please enter a valid test file:\n";
    cin >> input_file;
​
    //input C:\Users\taipham\source\repos\ECE586_FinalProject\sample_memory_image.txt
    cout << "Input file: " << input_file << endl;
    //Get the input file
​
    bool file_flag = true;		//Set to true to enter loop
​
    while (file_flag) {
        ifstream f(input_file.c_str());		//turns input_file to a c string and reads from file, file "f"
        //checks whether there were errors reading the file, if no errors set file_flag to false
		if (!(f.good())) {
            cout << "Test file is not valid. Please enter a valid test file:\n";
            cin >> input_file;
            cout << "Input file: " << input_file << endl;
        }
        else {
            file_flag = false;
        }
    }
    return input_file;		//returns the file string to main
}
​
/*/////////////////////////////////////////
Converts hex to binary
*//////////////////////////////////////////
string hex_decoder(string hex_addr) {
​
    long int i = 0;
    string address = "";		
    string temp_address = "";
​
    while (hex_addr[i]) {
​
        switch (hex_addr[i]) {
​
        case '0':
​
            temp_address = "0000";
            break;
​
        case '1':
            temp_address = "0001";
            break;
​
        case '2':
            temp_address = "0010";
            break;
​
        case '3':
            temp_address = "0011";
            break;
​
        case '4':
            temp_address = "0100";
            break;
​
        case '5':
            temp_address = "0101";
            break;
​
        case '6':
            temp_address = "0110";
            break;
​
        case '7':
            temp_address = "0111";
            break;
​
        case '8':
            temp_address = "1000";
            break;
​
        case '9':
            temp_address = "1001";
            break;
​
        case 'A':
            temp_address = "1010";
            break;
​
        case 'B':
            temp_address = "1011";
            break;
​
        case 'C':
            temp_address = "1100";
            break;
​
        case 'D':
            temp_address = "1101";
            break;
​
        case 'E':
            temp_address = "1110";
            break;
​
        case 'F':
            temp_address = "1111";
            break;
​
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
​
/*////////////////////////////////////////////////
Instruction decoder
*/////////////////////////////////////////////////
string instructions_decoder(string binary_addr) {
    instructions_exe function;
    string result;
​
    if (binary_addr != "00000000000000000000000000000000") {
        string opcode = binary_addr.substr(0, 6);
​
        if (opcode == "000000") {
            cout << "call ADD function..." << endl;
        }
        else if (opcode == "000010") {
​
            cout << "call SUB function..." << endl;
        }
        else if (opcode == "000100") {
​
            cout << "call MUL function..." << endl;
        }
        else if (opcode == "000001") {
​
            cout << "call ADDI function..." << endl;
        }
        else if (opcode == "000011") {
​
            cout << "call SUBI function..." << endl;
        }
        else if (opcode == "000101") {
​
            cout << "call MULI function..." << endl;
        }
    }
    
    else {
        cout << "0x00000000 input... skip!" << endl;
    }
    
    return result;
}