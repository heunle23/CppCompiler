#include <iostream>
using namespace std;
const int MAX = 100;
struct Node{
    string name;
    string info; // نیاز به بازنویسی دارد
    

    Node* next;

    Node(string name){
        this->name = name;
        //this->info = info;
        this->next = nullptr;
    }
};

class SymbolTable{

private:
// Node* table[MAX];

public:
    Node* table[100];
    
    
    SymbolTable(){
        for (int i = 0; i < MAX; i++)
        {
            table[i] = nullptr;

        }
        
    };

    Node* Connect(string& identifier);


    unsigned int hashfunc(const string& identifier);

    Node* find(string& identifier) ;

    Node* insert(string& identifier);
 
};