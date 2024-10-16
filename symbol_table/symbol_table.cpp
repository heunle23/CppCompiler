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


}


// این تابع باید اصلاعات بیشتری بگیرد 
// باید info و type را بگیرد
Node* SymbolTable::Connect(string& identifier){
    
    Node* exist = find(identifier);
    if (exist != nullptr) {
        return exist;
    }
    
    return insert(identifier);
};


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





//Horner's Rule
unsigned int SymbolTable::hashfunc(const string& identifier) {
    unsigned int hash_value = 0;
    const int base = 31; // ایا  ۳۱ برای ۱۰۰ خانه بهتر است 

    for (char c : identifier) {
        hash_value = hash_value * base + c;
    }

    return hash_value % 100; 
};




int main(){
    
    string ab = "ab";
    string ba = "ba" ;

    SymbolTable st;
    
    cout << st.Connect(ab) << endl;
    cout << st.Connect(ba) << endl;
  
}












void accepted_char(){
    for (int i = 48; i < 123; ++i) {
        if ((i>=58 && i<=64) || (i>=91 && i<=96)){}
        else{
            char c = (char)i;
            cout << i << ": " << c << std::endl;
            }
        if (i == 95)
        {
            char c = (char)i;
            cout << i << ": " << c << std::endl;
        }
    }
}
