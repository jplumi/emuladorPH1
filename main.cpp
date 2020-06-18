#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>

using namespace std;

int main()
{
    ifstream file;
    int memory[256]; // dados de memória do PH1
    list<int> modaddr; // lista para identificar dados da memory modificados
    string fileName, line;
    
    cout << "Input file: ";
    cin >> fileName;
    cout << endl;

    file.open(fileName);
    if(!file){
        cout << "ERROR: File not found!!\n";
        return 1;
    }

    int addr, value;
    while(file >> hex >> addr){
        file >> hex >> value;
        memory[addr] = value;
    }
    file.close();

    addr=0;
    int pc;
    int ac=0, numInstructions=0;
    bool hlt = false;
    for(pc=0; pc<255; pc++){

        switch (memory[pc]){
            case  0: // NOP
                cout << "NOP\n";
                numInstructions++;
                break;

            case 16: // LDR
                pc++;
                addr = memory[pc];
                ac = memory[addr];
                cout << "LDR " << setw(2) << setfill('0') << hex << addr << " ; AC <- MEM[" << setw(2) << setfill('0') << hex << addr << "]\n";
                numInstructions++;
                break;
            
            case 32: // STR
                pc++;
                addr = memory[pc];
                memory[addr] = ac;
                cout << "STR " << setw(2) << setfill('0') << hex << addr << " ; MEM[" << setw(2) << setfill('0') << hex << addr << "] <- AC\n";
                modaddr.push_back(addr);
                numInstructions++;
                break;
            
            case 48: // ADD
                pc++;
                addr = memory[pc];
                ac += memory[addr];
                cout << "ADD " << setw(2) << setfill('0') << hex << addr << " ; AC <- AC + MEM[" << setw(2) << setfill('0') << hex << addr << "]\n";
                numInstructions++;
                break;
            
            case 64: // SUB
                pc++;
                addr = memory[pc];
                ac -= memory[addr];
                cout << "SUB " << setw(2) << setfill('0') << hex << addr << " ; AC <- AC - MEM[" << setw(2) << setfill('0') << hex << addr << "]\n";
                numInstructions++;
                break;

            case 80: // MUL
                pc++;
                addr = memory[pc];
                ac *= memory[addr];
                cout << "MUL " << setw(2) << setfill('0') << hex << addr << " ; AC <- AC * MEM[" << setw(2) << setfill('0') << hex << addr << "]\n";
                numInstructions++;
                break;
            
            case 96: // DIV
                pc++;
                addr = memory[pc];
                ac /= memory[addr];
                cout << "DIV " << setw(2) << setfill('0') << hex << addr << " ; AC <- AC / MEM[" << setw(2) << setfill('0') << hex << addr << "]\n";
                numInstructions++;
                break;

            case 112: // NOT
                ac = ~ac;
                cout << "NOT    ; AC <- !AC\n";
                numInstructions++;
                break;
            
            case 128: // AND
                pc++;
                addr = memory[pc];
                ac = ac & memory[addr];
                cout << "AND " << setw(2) << setfill('0') << hex << addr << " ; AC <- AC & MEM[" << setw(2) << setfill('0') << hex << addr << "]\n";
                numInstructions++;
                break;

            case 144: // OR
                pc++;
                addr = memory[pc];
                ac = ac | memory[addr];
                cout << "OR  " << setw(2) << setfill('0') << hex << addr << " ; AC <- AC | MEM[" << setw(2) << setfill('0') << hex << addr << "]\n";
                numInstructions++;
                break;
            
            case 160: // XOR
                pc++;
                addr = memory[pc];
                ac = ac ^ memory[addr];
                cout << "XOR " << setw(2) << setfill('0') << hex << addr << " ; AC <- AC ^ MEM[" << setw(2) << setfill('0') << hex << addr << "]\n";
                numInstructions++;
                break;
            
            case 176: // JMP
                pc++;
                addr = memory[pc];
                pc = addr-1;
                cout << "JMP " << setw(2) << setfill('0') << hex << addr << " ; PC <- " << setw(2) << setfill('0') << hex << addr << endl;
                numInstructions++;
                break;

            case 192: // JEQ
                pc++;
                addr = memory[pc];
                if(ac == 0){
                    pc = addr-1;
                }
                cout << "JEQ " << setw(2) << setfill('0') << hex << addr << " ; Se AC==0 então PC <- " << setw(2) << setfill('0') << hex << addr << endl;
                numInstructions++;
                break;

            case 208: // JG
                pc++;
                addr = memory[pc];
                if(ac > 0){
                    pc = addr-1;
                }
                cout << "JG  " << hex << addr << " ; Se AC>0 então PC <- " << setw(2) << setfill('0') << hex << addr << endl;
                numInstructions++;
                break;

            case 224: // JL
                pc++;
                addr = memory[pc];
                if(ac < 0){
                    pc = addr-1;
                }
                cout << "JL  " << setw(2) << setfill('0') << hex << addr << " ; Se AC<0 então PC <- " << setw(2) << setfill('0') << hex << addr << endl;
                numInstructions++;
                break;

            case 240: // HLT
                pc++;
                cout << "HLT\n";
                numInstructions++;
                hlt = true;
                break;
            
            default:
                cout << "ERROR: " << " failed to identify \'" << memory[pc] << "\' at address " << pc << endl;
                return 1;
        }

        if(hlt){
            break;
        }
    }

    cout << endl << numInstructions << " instructions executed\n\n";

    cout << "Registers:\n";
    cout << "AC " << setw(2) << setfill('0') << hex << ac << endl;
    cout << "PC " << setw(2) << setfill('0') << hex << pc << endl; 

    cout << "\nMemory:\n";
    if(!modaddr.empty()){
        for(int i : modaddr){
            cout << i << " " << setw(2) << setfill('0') << memory[i] << endl;
        }
    }
    else{
        cout << "No changes\n";
    }

    return 0;
}