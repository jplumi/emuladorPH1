#include <iostream>
#include <list>
#include "functions.cpp"

using namespace std;

struct Data {
    int addr;   
    int value;
    bool modified;
};

int main()
{
    list<Data> memory;
    FILE* file;

    file = fopen("example.txt", "r");
    int numInstructions=0;

    // lê o arquivo de entrada e coloca as palavras na memory
    while(!feof(file)){
        int addr, value;
        fscanf(file, "%x %x", &addr, &value);
        memory.push_back({addr, value, false});
    }

    fclose(file);

    for(auto i : memory){
        cout << i.addr << " " << i.value << endl;
    }
}