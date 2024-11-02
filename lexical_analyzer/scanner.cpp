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
    INTEGER_LITERAL,
    FLOAT_LITERAL,
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
            


            if (is_delimiter((current_buff)[i])){
                // ali : label_1 
                if (temp.size() == 0){
                    fp++;
                    bp = fp;
                    continue;
                }
                else{
                    i++;
                    // ali : (NEEDS TO BE IMPLEMENTED) clean the vector  and making the identifier or keyword or one characters relop token
                    continue;
                }
            }
            
            // identifier or keyword
            if (isAlpha((current_buff)[fp])){
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
                while (!is_delimiter((current_buff)[fp]) && isAlphaNumeric((current_buff)[fp]) );
                
                if  ( is_delimiter((current_buff)[fp]) ){
                    retract();
                }
                else if (!isAlphaNumeric((current_buff)[fp]))
                {
                    /*ali : raise lexical error  (NEEDS TO BE IMPLEMENTED) */  
                }
            
                // ali : (NEEDS TO BE IMPLEMENTED) clean the vector  and making the identifier or keyword  or  multop token 
                string word = "";
                previous_buff[bp]
                
                if (keywords.find(word) != keywords.end()) {
                    
                }
                else{

                }
                
                is_token_seperated = false;
                    }


            else if (isDigit((*buffer)[fp])){
                if (temp.size() == 0){
                    temp.emplace_back((*buffer)[fp]);
                    do {
                        i++;
                        if (i<100){
                            temp.emplace_back((*buffer)[fp]);   
                        }
                        else{
                            // ali : if the program comes to this else the vector for next loop wont be empty!
                            return Token(TokenType::ENDOFBUFFER,"0",0);
                        }
                    }
                    while (! is_delimiter((*buffer)[fp]) || isDigit((*buffer)[fp]) );
                    
                    if  ( is_delimiter((*buffer)[fp]) ){
                        retract();
                    }
                    else if (!isDigit((*buffer)[fp]))
                    {
                        /* raise lexical error */
                    }
                    // ali : (NEEDS TO BE IMPLEMENTED) clean the vector  and making the int or float token
                }
                else{
                    // ali :this digit might be part of a identifier

                    // ali : we dont need while , if temp is an identifier the first char is alpha 
                    // isAlpha(temp[0]) is true


                    int j = 0;
                    while ( j < temp.size() ){
                        if (isAlpha(temp[j])){
                            // ali :if we find one alpha so this was ofc a identifier
                            temp.emplace_back((*buffer)[fp]);





                    do {
                        i++;
                        if (i < buffer_size){
                            temp.emplace_back((*buffer)[fp]);  
                        }
                        else{
                            // ali : (NEEDS TO BE IMPLEMENTED) if the program comes to this else , the vector for next loop wont be empty!
                            // we break the loop because the (i == 100) is true
                            // time to refill the buffer 
                            return Token(TokenType::ENDOFBUFFER,"0",0); 
                        }
                    }
                    while (! is_delimiter((*buffer)[fp]) && isAlphaNumeric((*buffer)[fp]) );
                    
                    if  ( is_delimiter((*buffer)[fp]) ){
                        retract();
                    }
                    else if (!isAlphaNumeric((*buffer)[fp]))
                    {
                        /*ali : raise lexical error  (NEEDS TO BE IMPLEMENTED) */  
                    }
                
                    // ali : (NEEDS TO BE IMPLEMENTED) clean the vector  and making the identifier or keyword  or  multop token
                                



                            }
                        j++;
                    }




                }

                
                }
                
            



            // ali : couldnt write it 

            else if (is_addop((*buffer)[fp])) {
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

            else if (is_equl((*buffer)[fp])) {
                // ali : create relop token (NEEDS TO BE IMPLEMENTED)
                i++;
                continue;
            }

            else if (is_start_relop((*buffer)[fp])){
                do{
                if (!two_buffer)
                    bp = fp;
                
                if (fp<100){
                    if ((*buffer)[fp] == '>'){
                        fp++;
                        if ((*buffer)[fp] == '='){
                            return Token(TokenType::relop, '>=', line)
                        }
                        return Token(TokenType::relop, '>', line)
                    }
                        
                    if ((*buffer)[fp] == '<'){
                        fp++;
                        if ((*buffer)[fp] == '>'){
                            return Token(TokenType::relop, '<>', line)
                        }
                        if ((*buffer)[fp] = '=')
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
    
