#include <iostream>
#include "functions.cpp"

using namespace std;

// struct Data {
//     int addr;   
//     int value;
//     bool modified;
// };

int main()
{
    FILE* file;
    char fileName[256];
    cout << "Input file: ";
    cin >> fileName;
    cout << endl;

    file = fopen(fileName, "r");
    if(!file){
        cout << "ERROR: File not found\n";
        return 1;
    }

    // file = fopen("example.txt", "r");

    int memory[256];
    // lê o arquivo de entrada e coloca as palavras na memory
    while(!feof(file)){
        int addr, value;
        fscanf(file, "%x %x", &addr, &value);
        memory[addr] = value;
    }
    fclose(file);

    int pc, ac=0, numInstructions=0;
    for(pc=0; pc<255; pc++){
        if(memory[pc] == 16){ // LDR
            pc++;
            int addr = memory[pc];
            ac = memory[addr];
            cout << "LDR " << hex << addr << " ; AC <- MEM[" << hex << addr << "]\n";
            numInstructions++;
            continue;
        }
        if(memory[pc] == 32){ // STR
            pc++;
            int addr = memory[pc];
            memory[addr] = ac;
            cout << "STR " << hex << addr << " ; MEM[" << addr << "] <- AC\n";
            numInstructions++;
            continue;
        }
        if(memory[pc] == 48){ // ADD
            pc++;
            int addr = memory[pc];
            ac += memory[addr];
            cout << "ADD " << hex << addr << " ; AC <- AC + MEM[" << hex << addr << "]\n";
            numInstructions++;
            continue;
        }
        if(memory[pc] == 64){ // SUB
            pc++;
            int addr = memory[pc];
            ac -= memory[addr];
            cout << "sub ac: " << ac << endl;
            cout << "SUB " << hex << addr << " ; AC <- AC - MEM[" << hex << addr << "]\n";
            numInstructions++;
            continue;
        }
        if(memory[pc] == 80){ // MUL
            pc++;
            int addr = memory[pc];
            ac *= memory[addr];
            cout << "MUL " << hex << addr << " ; AC <- AC * MEM[" << hex << addr << "]\n";
            numInstructions++;
            continue;
        }
        if(memory[pc] == 96){ // DIV
            pc++;
            int addr = memory[pc];
            ac /= memory[addr];
            cout << "DIV " << hex << addr << " ; AC <- AC / MEM[" << hex << addr << "]\n";
            numInstructions++;
            continue;
        }
        if(memory[pc] == 112){ // NOT
            ac = ~ac;
            cout << "NOT    ; AC <- !AC\n";
            numInstructions++;
            continue;
        }
        if(memory[pc] == 128){ // AND
            pc++;
            int addr = memory[pc];
            ac = ac & memory[addr];
            cout << "AND " << hex << addr << " ; AC <- AC & MEM[" << hex << addr << "]\n";
            numInstructions++;
            continue;
        }
        if(memory[pc] == 144){ // OR
            pc++;
            int addr = memory[pc];
            ac = ac | memory[addr];
            cout << "OR  " << hex << addr << " ; AC <- AC | MEM[" << hex << addr << "]\n";
            numInstructions++;
            continue;
        }
        if(memory[pc] == 160){ // XOR
            pc++;
            int addr = memory[pc];
            ac = ac ^ memory[addr];
            cout << "XOR " << hex << addr << " ; AC <- AC ^ MEM[" << hex << addr << "]\n";
            numInstructions++;
            continue;
        }
        if(memory[pc] == 176){ // JMP
            pc++;
            int addr = memory[pc];
            pc = addr-1;
            cout << "JMP " << hex << addr << " ; PC <- " << hex << addr << endl;
            numInstructions++;
            continue;
        }
        if(memory[pc] == 192){ // JEQ
            pc++;
            int addr = memory[pc];
            if(ac == 0){
                pc = addr-1;
            }
            cout << "JEQ " << hex << addr << " ; Se AC==0 então PC <- " << hex << addr << endl;
            numInstructions++;
            continue;
        }
        if(memory[pc] == 208){ // JG
            pc++;
            int addr = memory[pc];
            if(ac > 0){
                pc = addr-1;
            }
            cout << "JG  " << hex << addr << " ; Se AC>0 então PC <- " << hex << addr << endl;
            numInstructions++;
            continue;
        }
        if(memory[pc] == 224){ // JL TODO funcao nao ta funcionando
            pc++;
            int addr = memory[pc];
            if(ac < 0){
                pc = addr-1;
            }
            cout << "JL  " << hex << addr << " ; Se AC<0 então PC <- " << hex << addr << endl;
            numInstructions++;
            continue;
        }
        if(memory[pc] == 240){
            pc++;
            cout << "HTL\n";
            numInstructions++;
            break;
        }
    }

    cout << endl << numInstructions << " instructions executed\n\n";

    cout << "Registers:\n"
        << "AC " << hex << ac << endl
        << "PC " << hex <<  pc << endl;

    cout << "MEMORY: " << memory[128] << endl;

    return 0;
}