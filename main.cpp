#include <iostream>
#include <fstream>
#include <iomanip>
#include "functions.cpp"

using namespace std;

int main()  
{

    ifstream file;
    int memory[256]; // dados de memória do PH1
    int valmod[256], posmod[256]; //faz uma copia dos valores p memory
    string fileName, line;
    
    cout << "Input file: ";
    cin >> fileName;
    cout << endl;

    file.open(fileName);
    if(!file){
        cout << "ERROR: File not found\n";
        return 1;
    }

    int addr, value;
    while(file >> hex >> addr){
        file >> hex >> value;
        memory[addr] = value;
    }
    file.close();

    addr=0;
    int pc, ac=0, numInstructions=0, i = 0;
    bool verifica = false, modificou = false;
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
                i++;
                modificou = true;
                pc++;
                addr = memory[pc];
                posmod[i] = addr;
                memory[addr] = ac;
                valmod[addr] = ac;
                cout << "Testando valmod: " << posmod[i] << " " << setfill('0') << setw(2) << valmod[addr] << endl;
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
         << "AC " << hex << setfill('0') << setw(2) << ac << endl
         << "PC " << hex << setfill('0') << setw(2) << pc << endl;
    
    
    if(modificou)
    {
        cout << "MEMORY: " << endl;
        //nao ta entrando no for
        for(i = 0; i > 255; i++)
        {   
            cout << "entrou no for" << endl;
            addr = memory[i];
            cout << posmod[i] << "" << valmod[addr] << endl;
        }
    }    
    else
    {
        cout << "MEMORY : Não foi modificado" << endl;
    } 
    

    return 0;
}