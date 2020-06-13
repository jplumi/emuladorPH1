#include <iostream>
#include <fstream>
#include "functions.cpp"

using namespace std;

int main()
{

   ifstream file;
    int memory[256]; // dados de memória do PH1
    string fileName, line;
    
    cout << "Input file: ";
    cin >> fileName;
    cout << endl;

    file.open(fileName);
    if(!file){
        cout << "ERROR: File not found\n";
        return 1;
    }

    // file = fopen("example.txt", "r");
    int addr, value;
    while(file >> hex >> addr){
        file >> hex >> value;
        memory[addr] = value;
    }
    file.close();

    addr=0;
    int pc, ac=0, numInstructions=0;
    bool verifica = false;
    for(pc=0; pc<255; pc++){

        switch (memory[pc])
        {
            case 16: //ldr
                pc++;
                addr = memory[pc];
                ac = memory[addr];
                cout << "LDR " << hex << addr << " ; AC <- MEM[" << hex << addr << "]\n";
                numInstructions++;
                break;
            
            case 32: //str
                pc++;
                addr = memory[pc];
                memory[addr] = ac;
                cout << "STR " << hex << addr << " ; MEM[" << addr << "] <- AC\n";
                numInstructions++;
                break;
            
            case 48: //add
                pc++;
                addr = memory[pc];
                ac += memory[addr];
                cout << "ADD " << hex << addr << " ; AC <- AC + MEM[" << hex << addr << "]\n";
                numInstructions++;
                break;
            
            case 64: //sub
                pc++;
                addr = memory[pc];
                ac -= memory[addr];
                cout << "sub ac: " << ac << endl;
                cout << "SUB " << hex << addr << " ; AC <- AC - MEM[" << hex << addr << "]\n";
                numInstructions++;
                break;

            case 80: //mul
                pc++;
                addr = memory[pc];
                ac *= memory[addr];
                cout << "MUL " << hex << addr << " ; AC <- AC * MEM[" << hex << addr << "]\n";
                numInstructions++;
                break;
            
            case 96: //div
                pc++;
                addr = memory[pc];
                ac /= memory[addr];
                cout << "DIV " << hex << addr << " ; AC <- AC / MEM[" << hex << addr << "]\n";
                numInstructions++;
                break;

            case 112: //not
                ac = ~ac;
                cout << "NOT    ; AC <- !AC\n";
                numInstructions++;
                break;
            
            case 128: //and
                pc++;
                addr = memory[pc];
                ac = ac & memory[addr];
                cout << "AND " << hex << addr << " ; AC <- AC & MEM[" << hex << addr << "]\n";
                numInstructions++;
                break;

            case 144: //or
                pc++;
                addr = memory[pc];
                ac = ac | memory[addr];
                cout << "OR  " << hex << addr << " ; AC <- AC | MEM[" << hex << addr << "]\n";
                numInstructions++;
                break;
            
            case 160: //xor
                pc++;
                addr = memory[pc];
                ac = ac ^ memory[addr];
                cout << "XOR " << hex << addr << " ; AC <- AC ^ MEM[" << hex << addr << "]\n";
                numInstructions++;
                break;
            
            case 176: //jmp
                pc++;
                addr = memory[pc];
                pc = addr-1;
                cout << "JMP " << hex << addr << " ; PC <- " << hex << addr << endl;
                numInstructions++;
                break;

            case 192: //jeq
                pc++;
                addr = memory[pc];
                if(ac == 0){
                    pc = addr-1;
                }
                cout << "JEQ " << hex << addr << " ; Se AC==0 então PC <- " << hex << addr << endl;
                numInstructions++;
                break;

            case 208: //jg
                pc++;
                addr = memory[pc];
                if(ac > 0){
                    pc = addr-1;
                }
                cout << "JG  " << hex << addr << " ; Se AC>0 então PC <- " << hex << addr << endl;
                numInstructions++;
                break;

            case 224:
                pc++;
                addr = memory[pc];
                if(ac < 0){
                    pc = addr-1;
                }
                cout << "JL  " << hex << addr << " ; Se AC<0 então PC <- " << hex << addr << endl;
                numInstructions++;
                break;

            case 240: //hlt
                pc++;
                cout << "HTL\n";
                numInstructions++;
                verifica = true;
                break; 
        }

        if(verifica)
        {
            break;
        }
    }

    cout << endl << numInstructions << " instructions executed\n\n";

    cout << "Registers:\n"
        << "AC " << hex << ac << endl
        << "PC " << hex <<  pc << endl;

    // cout << "MEMORY: " << memory[128] << endl;

    return 0;
}