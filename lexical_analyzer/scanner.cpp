#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <array>


enum class TokenType {
    KEYWORD,
    IDENTIFIER,
    INTEGER_LITERAL,
    FLOAT_LITERAL,
    OPERATOR,
    PUNCTUATOR,
    UNKNOWN
};

// Struct to represent a token with its type and value
struct Token {
    TokenType type;
    string value;
    int line;

    Token(TokenType t, const string& v ,int l)
        : type(t), value(v), line(l) {}
};











class LexicalAnalyzer {
private:
    array<char, 100>  buffer;
    vector<char> temp;
    int line = 0;

    bool is_sign(char c){
        return c == '+' || c == '-' ;
    }

    bool is_addop(char c){
        return c == '+' || c == '-' ;
    };





    
    bool isWhitespace(char c) {
        return c == ' ' || c == '\t'  || c == '\r';
    }

    bool is_relop(char c){
        return c == '=' || c == '<>' || c == '=' || c == '=' || c == '=' ;
    }

    bool isAlpha(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

    bool isDigit(char c) {
        return c >= '0' && c <= '9';
    }

    bool isAlphaNumeric(char c) {
        return isAlpha(c) || isDigit(c);
    }

    bool is_start_relop(char c){
        return c == '<' || c == '>' ;
    }
    
    bool is_equl(char c){
        return c == '=';
    }


    void retract(){
        temp.pop_back();
    }

    bool is_delimiter(char c){
        // ali : we check if '\n' is used , we increase the line int .
        if (c == '\n'){
            line++;
        }
        return c == ' ' || c == '\t'  || c == '\r' || c == '\n';
    }

    void tokenize(array<char, 100>& buffer){
        int i=0;

        // ali : label_1 
        // سعی میشود هر بار که حلقه پایین شروع میشود وکتور خالی باشد
        // ولی با توجه به بافر ها بعضی وقت ها این موضوع شدنی نیست.
       
        while ( i<100 ) {

            if (is_delimiter(buffer[i])){
                // ali : label_1 
                if (temp.size() == 0){
                    i++;
                    continue;
                }
                else{
                    i++;
                    // ali : (NEEDS TO BE IMPLEMENTED) clean the vector  and making the identifier or keyword or 2 characters relop token
                    continue;
                }
            }
            

            if (isAlpha(buffer[i])){
                temp.emplace_back(buffer[i]);
                do {
                    i++;
                    if (i<100){
                        temp.emplace_back(buffer[i]);  
                    }
                    else{
                        // ali : if the program comes to this else , the vector for next loop wont be empty!
                        // we break the loop because the (i == 100) is true
                        break; 
                    }
                }
                while (! is_delimiter(buffer[i]) && isAlphaNumeric(buffer[i]) );
                retract();
                // ali : (NEEDS TO BE IMPLEMENTED) clean the vector  and making the identifier or keyword token
                    }


            else if (isDigit(buffer[i])){
                temp.emplace_back(buffer[i]);
                do {
                    i++;
                    if (i<100){
                        temp.emplace_back(buffer[i]);   
                    }
                    else{
                        // ali : if the program comes to this else the vector for next loop wont be empty!
                        break;
                    }
                }
                while (! is_delimiter(buffer[i]) || isAlphaNumeric(buffer[i]) );
                retract();
                // ali : (NEEDS TO BE IMPLEMENTED) clean the vector  and making the int or float token
                }
                
            



            /*
            else if (isWhitespace(buffer[i])){
                temp.pop_back();
                i++;
                continue;
            }
            */

            else if (is_addop(buffer[i])) {
                // ali : create addop token 
                i++;
                continue;
            }
            else if (is_equl(buffer[i])) {
                // ali : create relop tokeen
                i++;
                continue;
            }
            else if (is_start_relop(buffer[i])){
                temp.emplace_back(buffer[i]);
                i++;
                if (i<100){
                    if ()
                }
                else{

                }
                
                continue;
            }





        };
        
    };
        
        






    void fill_buffer(ifstream& file,array<char, 100>& buffer) {

        file.read(buffer.data(), buffer.size());

        if (file.gcount() < buffer.size()) {
            // If fewer than 100 characters were read, fill the rest with null chars
            fill(buffer.begin() + file.gcount(), buffer.end(), '\0');
            }
    };

    void processFile(const string& filename) {
        ifstream file(filename);  // Open the file
        if (!file.is_open()) {
            cerr << "Error: Unable to open file " << filename << endl;
            return;
        }

        // 
        while (!file.eof()) {
            fill_buffer(file, buffer);
            tokenize(buffer);
            
        }

        file.close();  // Close the file
    };


    



};





int main() {
    
}