#include <iostream>
using namespace std;

const int MAX = 100;


struct Node{
    int data;
    Node* next;

};


class SymbolTable{

private:
// Node* table[MAX];

public:
    Node* table[MAX];
    
    
    SymbolTable(){
        for (int i = 0; i < MAX; i++)
        {
            table[i] = nullptr;

        }
        
    }
    
};



int main(){

    SymbolTable st;

    

}