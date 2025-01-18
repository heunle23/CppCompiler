#include <iostream>
using namespace std;

const int MAX = 100;


struct Node{
    string name;
    string info; // نیاز به بازنویسی دارد
    

    Node* next;

    Node(string name){
        this->name = name;
        this->next = nullptr;
    }
};

class SymbolTable{

public:
    Node* table[MAX] = {nullptr};
    
    
    SymbolTable(){};

    // تابعی اصلی برای ارتباط برقرار کردن با جدول نماد ها
    //
    Node* SymbolTable::Connect(string& identifier){
    
        Node* exist = find(identifier);
        if (exist != nullptr) {
            return exist;
        }
        
        return insert(identifier);
        }



    //Horner's Rule 
    unsigned int SymbolTable::hashfunc(const string& identifier) {
        unsigned int hash_value = 0;
        const int base = 31; // عدد اول استفاده شده در قانون هورنر

        for (char c : identifier) {
            hash_value = hash_value * base + c;
        }

        return hash_value % MAX; 
        };


    //تابعی که وجود متغیر را در حدول نماد ها
    // از قبل میسنجد
    //
    Node* SymbolTable::find(string& identifier){
        int adress = hashfunc(identifier);
        Node* temp_node = table[adress];
        

        if (temp_node == nullptr){
            return nullptr;
        }
        
        while (temp_node != nullptr){
            if (temp_node->name == identifier){
                return temp_node;
            }
            temp_node = temp_node->next;
        }
        return nullptr;
        };   

    // تابعی که متغیر را در حدول نماد ها نصب میکند
    //
    Node* SymbolTable::insert(string& identifier){
        int adress = hashfunc(identifier);
        Node* temp = table[adress];

        if (temp == nullptr) {
            table[adress] = new Node(identifier);
            return table[adress];
        }

        while (temp->next != nullptr){
            temp = temp->next;
        }
        Node* p = new Node(identifier);
        temp->next = p;

        return temp->next;
        };
 
};


///////

