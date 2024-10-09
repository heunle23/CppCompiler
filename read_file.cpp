#include <fstream>
#include <iostream>

using namespace std;

bool create_file(string file_name){
    ofstream file;
    file.open(file_name);
    if (!file.is_open())
        {
            cout << "Error in creating file." << endl;
            return 0;
        }
    cout << "File created successfully." << endl;

    // بستن فایل برای خالی کردن حافظه
    file.close();
    return 1;
}

bool append_file(string data, string file_name){
    ofstream file;
    // با استفاده از ios::app به اخر فایل اضافه میکنیم
    file.open(file_name, ios::app);
    if (!file)
        return 0;
    file << endl << data;
    return 1;
}

bool read_file(string file_name){
    ifstream file;
    file.open(file_name);
    if (!file)
        return 0;
    else {
        char c;
        while (1){
            c = file.get();
            if (file.eof())
                break;
            cout << c;
        }
        
    }
    file.close();
    return 1;
}

int main(){
    
    
}
