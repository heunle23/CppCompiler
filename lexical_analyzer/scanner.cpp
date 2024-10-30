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
    UNKNOWN,
    ENDOFBUFFER,
};

// Struct to represent a token with its type and value
struct Token {
    TokenType type;
    string value;
    int line;

    Token(TokenType t, const string& v ,int l)
        : type(t), value(v), line(l) {}
};


class Tools {
    public:
    array<char, 100>  buffer;
    vector<char> temp;
    int line = 0;
    int i=0;
    ifstream file;
    Token token;

    bool is_sign(char c){
        return c == '+' || c == '-' ;
    }

    bool is_addop(char c){
        return c == '+' || c == '-' ;
    }

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
    };

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


};








class LexicalAnalyzer : public Tools{
public:
        LexicalAnalyzer()
        

        ;
private:
    
    bool fill_buffer(ifstream& file,array<char, 100>& buffer) {

        if (file.eof()){
            file.close();
            return false;
        }


        file.read(buffer.data(), buffer.size());

        if (file.gcount() < buffer.size()) {
            // If fewer than 100 characters were read, fill the rest with null chars
            fill(buffer.begin() + file.gcount(), buffer.end(), '\0');
            }

        return true;

    };

    void open_file(const string& filename) {
        ifstream file(filename);  // Open the file
        if (!file.is_open()) {
            cerr << "Error: Unable to open file " << filename << endl;
        }
    };



    Token touch(){
        // ali : a function for parser to comunicate with our scanner
        // each time this func is called , one token will be returned (exept when eof is true)
        
        token = tokenize();
        
        if (token.type == TokenType::ENDOFBUFFER){
            i = 0;
            bool feasible = fill_buffer(file,buffer);
            if (feasible == false) {
                //ali : (NEEDS TO BE IMPLEMENTED) scanner cant make token anymore , because eof is true 
            }else{
                token = tokenize();
            }
        
        }
        
        return token;
        

    }



    Token tokenize(){

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
                        // ali : (NEEDS TO BE IMPLEMENTED) if the program comes to this else , the vector for next loop wont be empty!
                        // we break the loop because the (i == 100) is true
                        // time to refill the buffer 
                        return Token(TokenType::ENDOFBUFFER,"0",0); 
                    }
                }
                while (! is_delimiter(buffer[i]) && isAlphaNumeric(buffer[i]) );
                
                if  ( is_delimiter(buffer[i]) ){
                    retract();
                }
                else if (!isAlphaNumeric(buffer[i]))
                {
                    /*ali : raise lexical error  (NEEDS TO BE IMPLEMENTED) */  
                }
            
                // ali : (NEEDS TO BE IMPLEMENTED) clean the vector  and making the identifier or keyword  or  multop token 
                    }


            else if (isDigit(buffer[i])){
                if (temp.size() == 0){
                    temp.emplace_back(buffer[i]);
                    do {
                        i++;
                        if (i<100){
                            temp.emplace_back(buffer[i]);   
                        }
                        else{
                            // ali : if the program comes to this else the vector for next loop wont be empty!
                            return Token(TokenType::ENDOFBUFFER,"0",0);
                        }
                    }
                    while (! is_delimiter(buffer[i]) || isDigit(buffer[i]) );
                    
                    if  ( is_delimiter(buffer[i]) ){
                        retract();
                    }
                    else if (!isDigit(buffer[i]))
                    {
                        /* raise lexical error */
                    }
                    // ali : (NEEDS TO BE IMPLEMENTED) clean the vector  and making the int or float token
                }
                else{
                    // ali :this digit might be part of a identifier
                    int j = 0;
                    while ( j < temp.size() ){
                        if (isAlpha(temp[j])){
                            // ali :if we find one alpha so this was ofc a identifier
                            temp.emplace_back(buffer[i]);
                    do {
                        i++;
                        if (i<100){
                            temp.emplace_back(buffer[i]);  
                        }
                        else{
                            // ali : (NEEDS TO BE IMPLEMENTED) if the program comes to this else , the vector for next loop wont be empty!
                            // we break the loop because the (i == 100) is true
                            // time to refill the buffer 
                            return Token(TokenType::ENDOFBUFFER,"0",0); 
                        }
                    }
                    while (! is_delimiter(buffer[i]) && isAlphaNumeric(buffer[i]) );
                    
                    if  ( is_delimiter(buffer[i]) ){
                        retract();
                    }
                    else if (!isAlphaNumeric(buffer[i]))
                    {
                        /*ali : raise lexical error  (NEEDS TO BE IMPLEMENTED) */  
                    }
                
                    // ali : (NEEDS TO BE IMPLEMENTED) clean the vector  and making the identifier or keyword  or  multop token
                                



                            }
                        j++;
                    }




                }

                
                }
                
            



            

            else if (is_addop(buffer[i])) {
                if (temp.size() == 0){
                    // ali : create addop token (NEEDS TO BE IMPLEMENTED)
                    i++;
                    //  return  token
                }
                else{
                    // ali : error , the '+' and '-' cant have any chat befor them .
                }
                
                // ali : create addop token (NEEDS TO BE IMPLEMENTED)
                i++;
                continue;
            }

            else if (is_equl(buffer[i])) {
                // ali : create relop token (NEEDS TO BE IMPLEMENTED)
                i++;
                continue;
            }

            else if (is_start_relop(buffer[i])){
                temp.emplace_back(buffer[i]);
                i++;
                
                if (i<100){
                    if (buffer[i] == '>' || buffer[i] == '=' ){
                        // ali : check if the two character relop is valid
                        // for example : '<<' is not valid
                        // (NEEDS TO BE IMPLEMENTED)
                        // create two char realop token
                        i++;
                    }
                    else if (is_delimiter(buffer[i])){
                        //ali : (NEEDS TO BE IMPLEMENTED)
                        // create one char realop token
                        i++;
                    }
                    else{
                        //ali : (NEEDS TO BE IMPLEMENTED)
                        // lexical error 
                    }
                }
                
                else{
                    return Token(TokenType::ENDOFBUFFER,"0",0);
                }
                
                
            }





        };
        return Token(TokenType::ENDOFBUFFER,"0",0); 



        
    };
        
        






    


    


    



};





int main() {
    
}