#include <iostream>
#include <math.h>

using namespace std;


struct Data {
    int addr;   
    int value;
    bool modified;
};

/**
 * Traduz o primeiro caractere de uma string em uma instrução
 */
// string getInstruction(string value){
//     char opcode = value[0];
//     string result;
//     switch (opcode){
//         case '0':
//             result = "NOP";break; 0
//         case '1':
//             result = "LDR";break; 16
//         case '2':
//             result = "STR";break; 32
//         case '3':
//             result = "ADD";break; 48
//         case '4':
//             result = "SUB";break; 64
//         case '5':
//             result = "MUL";break; 80
//         case '6':
//             result = "DIV";break; 96
//         case '7':
//             result = "NOT";break; 112
//         case '8':
//             result = "AND";break; 128
//         case '9':
//             result = "OR";break; 144
//         case 'A':
//             result = "XOR";break; 160
//         case 'B':
//             result = "JMP";break; 176
//         case 'C':
//             result = "JEQ";break; 192
//         case 'D':
//             result = "JG";break; 208
//         case 'E':
//             result = "JL";break; 224
//         case 'F':
//             result = "HLT";break; 240
//         default:
//             cout << "ERROR: \"" << opcode << "\" is not a valid opcode." << endl;
//             break;
//     }
//     return result;
// }

// Transforma uma string que representa um numero hexadecimal em um int decimal
int sHexToDec(string value){
    int sum=0;
    for(int i=0, j=value.length()-1;i<=value.length()-1; i++, j--){
        string alg;
        alg.assign(value, i,1);
        if(alg == "A") alg = "10";
        else if(alg == "B") alg = "11";
        else if(alg == "C") alg = "12";
        else if(alg == "D") alg = "13";
        else if(alg == "E") alg = "14";
        else if(alg == "F") alg = "15";
        
        int n = pow(16, j), algInt = stoi(alg);
        sum += algInt * n;
    }
    return sum;
}

