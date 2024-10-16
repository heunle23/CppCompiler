#include <iostream>
#include <string>


using namespace std;

const int MAX = 100;


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

unsigned int hashfunc(const string& identifier) {
    unsigned int hash_value = 0;
    const int base = 31; // Prime number for better distribution

    for (char c : identifier) {
        hash_value = hash_value * base + c;
    }

    return hash_value % 100; // Modulo 100 to fit within the array size
}



int main() {
    accepted_char();
    
    
   
    
    
    }

    

