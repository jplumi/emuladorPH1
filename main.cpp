#include <iostream>
#include <fstream>
#include <list>
#include "functions.cpp"

using namespace std;

int main()
{
    list<Data> memory;
    ifstream file;  
    string fileName, fileLine;

    // cout << "Input file: ";
    // cin >> fileName;
    // cout << endl;
    // file.open(fileName);
    // if(!file){
    //     cout << "ERROR: file not found!\n";
    //     return 1;
    // }

    file.open("example.txt");
    int numInstructions=0;

    // lê o arquivo de entrada e coloca as palavras na memory
    while(getline(file, fileLine)){
        if(fileLine == "") {
            continue;
        }
        string addr, value;
        addr.assign(fileLine, 0,2); //vai pegar a string da posicao inicial ate o tamanho definido;
        value.assign(fileLine, 3,2); //vai pegar a partir da posicao 3 de tamanho 2;
        memory.push_back({sHexToDec(addr), sHexToDec(value), false});
    }

    for(auto i : memory){
        cout << i.addr << " " << i.value << endl;
    }
}