#include <iostream>

using namespace std;

struct Node{
    int data;
    Node* next;

};

class SymbolTable{


public:
    Node* table;
    SymbolTable() {
        table = new Node[100];
        


};
};



int main(){

    SymbolTable st;



}