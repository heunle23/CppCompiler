#include "../lexical_analyzer/scanner.cpp"

enum class TokenType {
    KEYWORD,
    IDENTIFIER,
    INTEGER,
    OPERATOR,
    PUNCTUATOR,
    ENDOFBUFFER,
    ADD_SIGN,
    MINUS_SIGN,
    RELATION_OPERATOR,
    MULTOP
};



// Recursive Descent First half of the grammer
class RDFH{
    
    Token lexitem;
    LexicalAnalyzer lexianalyzer;
    int error = 0;

    void scanner(){
        lexitem = lexianalyzer.touch(); 
        }

    






    void ParseProgram(){
        scanner(); // تنها باری که اسکنر صدا زده میشود ولی قبلش مقایسه رخ نداده

        if ( !(lexitem.type == TokenType::KEYWORD && lexitem.value == "PROGRAM")){
            error +=1 ;
            cerr << "error at line = " << lexitem.line << endl << "should use PROGRAM keyword first " << endl;
        }
        scanner();
        
        if ( !(lexitem.type == TokenType::IDENTIFIER )){
            error +=1 ;
            cerr << "error at line = " << lexitem.line << endl << "should use IDENTIFIER " << endl;
        }

        scanner();

        if ( !(lexitem.type == TokenType::PUNCTUATOR && lexitem.value == ";" )){
            error +=1;
            cerr << "error at line = " << lexitem.line << endl << "should use semicolon " << endl;
        }

        scanner();

        ParseBlock();

        if ( !(lexitem.type == TokenType::PUNCTUATOR && lexitem.value == "." )){
            error +=1;
            cerr << "error at line = " << lexitem.line << endl << "should use period " << endl;
        }


        if (error == 0){
            // accpted 
        }
        else{
            cout << "the grammer dosnt accept the code !" ;
        }


    }

    void ParseBlock(){

        


    }




};