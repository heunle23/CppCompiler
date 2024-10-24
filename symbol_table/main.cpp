#include "symbol_table.h"
#include <iostream>

using namespace std;

int main(){
    
    string ab = "ab";
    string ba = "ba" ;

    SymbolTable st;
    
    cout << st.Connect(ab) << endl;
    cout << st.Connect(ba) << endl;
  
}