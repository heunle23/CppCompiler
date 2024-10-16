// C++ Program to Demonstrate the Functioning of Enumerators 
// with an example of Gender 
#include <bits/stdc++.h> 
using namespace std; 

int main() 
{ 
	// Defining enum Gender 
	enum Gender { Male, Female }; 

	// Creating Gender type variable 
	Gender gender = Male; 

    int i = 0;
    int j = Male;

    if (i==j){
        cout << "yes" << endl;
    }


	switch (gender) { 
	case Male: 
		cout << "Gender is Male" << gender << endl; 
		break; 
	case Female: 
		cout << "Gender is Female"<< gender << endl; 
		break; 
	default: 
		cout << "Value can be Male or Female"<< gender << endl; 
	} 
	return 0; 
}
