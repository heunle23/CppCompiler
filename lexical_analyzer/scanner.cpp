#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <array>

const int buffer_size = 128;
const char end_of_line = '\n';

enum class TokenType {
    KEYWORD,
    IDENTIFIER,
    INTEGER,
    OPERATOR,
    PUNCTUATOR,
    RELOP,
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
    array<char, buffer_size> current_buff, previous_buff;
    //array<char, buffer_size>
    vector<char> temp;
    int line = 0;
    int i=0;
    bool is_token_seperated = false; // if true our bp is in the previous_buff. and fp in current_buff.
    ifstream file;
    Token token;
    int bp , fp;
    




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
        return c == '<' || c == '>' || '=';
    }
    
    bool is_equl(char c){
        return c == '=';
    };

    void retract(){
        fp--;
    }

    bool is_delimiter(char c){
        // ali : we check if '\n' is used , we increase the line int .
        if (c == end_of_line){
            line++;
        }
        return c == ' ' || c == '\t'  || c == '\r' || c == '\n';
    }


};








class LexicalAnalyzer : public Tools{
public:
        LexicalAnalyzer()
        // ali : (NEEDS TO BE IMPLEMENTED)  
        // call open_file in here 
        // call fill_buffer  

        ;

    unordered_map<string, TokenType> keywords;

    void initKeywords() {
        keywords["PROGRAM"] = TokenType::KEYWORD;
        keywords["BEGIN"] = TokenType::KEYWORD;
        keywords["INTEGER"] = TokenType::KEYWORD;
        keywords["END"] = TokenType::KEYWORD;
        keywords["FUNCTION"] = TokenType::KEYWORD;
        keywords["DIV"] = TokenType::KEYWORD;
        keywords["MOD"] = TokenType::KEYWORD;
    }
    
    bool fill_buffer(ifstream& file,array<char, buffer_size>& buffer) {

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
                // if temp.size() != 0 { error }
                //ali : (NEEDS TO BE IMPLEMENTED) scanner cant make token anymore , because eof is true 
            }else{
                token = tokenize();
            }
        
        }
        
        return token;
        

    };


    void switch_buffer(){
        array<char, buffer_size> new_buffer; 
        fill_buffer(file,new_buffer);

        previous_buff = current_buff;
        current_buff = new_buffer;
        fp = 0;
    }




    Token tokenize(){

        // ali : label_1 
        // سعی میشود هر بار که حلقه پایین شروع میشود وکتور خالی باشد
        // ولی با توجه به بافر ها بعضی وقت ها این موضوع شدنی نیست.
       
        while ( fp < buffer_size ) {
            


            if (is_delimiter(current_buff[fp])){
                // ali : label_1 
                fp++;
            }
            
            // identifier or keyword
            if (isAlpha(current_buff[fp])){
                bp = fp;
                do {
                    if (fp != buffer_size-1){
                        fp++;  
                    }
                    else{
                        switch_buffer();
                        if( !is_token_seperated ){
                            is_token_seperated = true;
                        }
                        else{
                            //  lexical error // message : the lenght of token cant be more than 256
                        }
                        
                    }
                }
                while (!is_delimiter(current_buff[fp]) && isAlphaNumeric(current_buff[fp]) );
                
                if  ( is_delimiter(current_buff[fp]) ){
                    retract();
                }
                else if (!isAlphaNumeric(current_buff[fp]))
                {
                    /*ali : raise lexical error  (NEEDS TO BE IMPLEMENTED) */  
                }
            
                // ali : (NEEDS TO BE IMPLEMENTED) clean the vector  and making the identifier or keyword  or  multop token 
                string word = "";
                if (is_token_seperated){
                    for (int i = bp; bp < 128; bp++){
                        word += previous_buff[i];}
                    for (int i = 0; i <= fp; bp++){
                        word += current_buff[i];
                    }
                }
                else{
                    for (i = bp; i <= fp; i++){
                        word += current_buff[i];
                    }
                }

                
                if (keywords.find(word) != keywords.end()) {
                    return Token(TokenType::KEYWORD, word, line);
                    
                }
                else{
                    return Token(TokenType::IDENTIFIER, word, line);

                }
                
                is_token_seperated = false;
                    }


            else if (isDigit(current_buff[fp])){
                bp = fp;
                do {
                    
                    if (fp < buffer_size - 1){
                        fp++;   
                    }
                    else{
                        switch_buffer();
                        if( !is_token_seperated ){
                            is_token_seperated = true;
                        }
                        else{
                            //  lexical error // message : the lenght of token cant be more than 256
                        }
                    }
                }
                while (!is_delimiter(current_buff[fp]) && isDigit(current_buff[fp]) );
                
                if  ( is_delimiter(current_buff[fp]) ){
                    retract();
                }
                else if (!isDigit(current_buff[fp]))
                {
                    /* raise lexical error -> start with digit but alpha after that */
                }
                // ali : (NEEDS TO BE IMPLEMENTED) clean the vector  and making the int or float token

                string num = "";
                if (is_token_seperated){
                    for (int i = bp; bp < 128; bp++){
                        num += previous_buff[i];}
                    for (int i = 0; i <= fp; bp++){
                        num += current_buff[i];
                    }
                }
                else{
                    for (i = bp; i <= fp; i++){
                        num += current_buff[i];
                    }
                }

                
                is_token_seperated = false;
                return Token(TokenType::INTEGER, num, line);
                    }
                

            
            
                

                
                
                
            



            // ali : couldnt write it 

            else if (is_addop(current_buff[fp])) {
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

            else if (is_equl(current_buff[fp])) {
                // ali : create relop token (NEEDS TO BE IMPLEMENTED)
                i++;
                continue;
            }

            else if (is_start_relop(current_buff[fp])){
                do{
                
                if (fp<100){
                    if (current_buff[fp] == '>'){
                        fp++;
                        if (current_buff[fp] == '='){
                            return Token(TokenType::relop, '>=', line)
                        }
                        return Token(TokenType::relop, '>', line)
                    }
                        
                    if (current_buff[fp] == '<'){
                        fp++;
                        if (current_buff[fp] == '>'){
                            return Token(TokenType::relop, '<>', line)
                        }
                        if (current_buff[fp] = '=')
                        {
                            return Token(TokenType::relop, '<=', line)
                        }
                        return Token(TokenType::relop, '<', line)    
                    }
                    return Token(TokenType::relop, '=', line)
                }
                
                else{
                    fill_buffer(ifstream& file,array<char, buffer_size>& buffer_new)
                    buffer = &buffer_new;
                    two_buffer = true;
                    continue;
                }
                }while (true);
                
                
            }





        };
        return Token(TokenType::ENDOFBUFFER,"0",0); 



        
    };
        
        








    


    



};





int main() {
    
}
    
