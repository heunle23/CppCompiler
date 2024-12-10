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
    int error_count  = 0;

    void scanner(){
        lexitem = lexianalyzer.touch(); 
        }

    






    void ParseProgram(){
        scanner(); // تنها باری که اسکنر صدا زده میشود ولی قبلش مقایسه رخ نداده

        if ( !(lexitem.type == TokenType::KEYWORD && lexitem.value == "PROGRAM")){
            error_count +=1 ;
            cerr << "error at line = " << lexitem.line << endl << "should use PROGRAM keyword first " << endl;
        }
        scanner();
        
        if ( !(lexitem.type == TokenType::IDENTIFIER )){
            error_count +=1 ;
            cerr << "error at line = " << lexitem.line << endl << "should use IDENTIFIER " << endl;
        }

        scanner();

        if ( !(lexitem.type == TokenType::PUNCTUATOR && lexitem.value == ";" )){
            error_count +=1;
            cerr << "error at line = " << lexitem.line << endl << "should use semicolon " << endl;
        }

        scanner();

        ParseBlock();

        if ( !(lexitem.type == TokenType::PUNCTUATOR && lexitem.value == "." )){
            error_count +=1;
            cerr << "error at line = " << lexitem.line << endl << "should use period " << endl;
        }


        if (error_count == 0){
            // accpted 
        }
        else{
            cout << "the grammer dosnt accept the code !" ;
        }


    }

    void ParseBlock(){

        if (lexitem.type == TokenType::KEYWORD && lexitem.value == "VAR"){
            scanner;
            ParseVarList();
        }
        while (lexitem.type == TokenType::KEYWORD && lexitem.value == "FUNCTION")
        {
            scanner;
            ParseFunctionDefinition();
        }
        if ( !(lexitem.type == TokenType::KEYWORD && lexitem.value == "BEGIN ")){
            error_count +=1;
            cerr << "error at line = " << lexitem.line << endl << "should use BEGIN " << endl;
        }
        ParseFunctionBody();

    }

    void ParseVarList(){
        ParseDataDefinition();

        while (lexitem.type == TokenType::IDENTIFIER){
            scanner;
            ParseDataDefinition();
        }


    }

    void ParseDataDefinition(){
        ParseIdentifierList();

        if ( !(lexitem.type == TokenType::PUNCTUATOR && lexitem.value == ":" )){
            error_count +=1;
            cerr << "error at line = " << lexitem.line << endl << "should use colon " << endl;
        }
        scanner();

        if ( !(lexitem.type == TokenType::KEYWORD && lexitem.value == "INTEGER" )){
            error_count +=1;
            cerr << "error at line = " << lexitem.line << endl << "should use INTEGER keyword " << endl;
        }
        scanner();


        if ( !(lexitem.type == TokenType::PUNCTUATOR && lexitem.value == ";" )){
            error_count +=1;
            cerr << "error at line = " << lexitem.line << endl << "should use semicolon " << endl;
        }
        scanner();


    }

    void ParseIdentifierList(){

        if ( !(lexitem.type == TokenType::IDENTIFIER )){
            error_count +=1 ;
            cerr << "error at line = " << lexitem.line << endl << "should use IDENTIFIER " << endl;
        }
        scanner();

        // below code needs to be tested
        // اگر منطق پایین اوک بود بقیه حلقه ها هم همین طوری شوند
        while (lexitem.value.length() == 1){
            
            if ( lexitem.type == TokenType::PUNCTUATOR && lexitem.value == ","){
            error_count +=1 ;
            cerr << "error at line = " << lexitem.line << endl << "should use IDENTIFIER " << endl;
            }
    
            scanner();

            if ( !(lexitem.type == TokenType::IDENTIFIER )){
            error_count +=1 ;
            cerr << "error at line = " << lexitem.line << endl << "should use IDENTIFIER " << endl;

            }
            scanner();

        }



    }


    void ParseFunctionDefinition(){
        ParseHeading();

        if ( !(lexitem.type == TokenType::PUNCTUATOR && lexitem.value == ";" )){
            error_count +=1;
            cerr << "error at line = " << lexitem.line << endl << "should use semicolon " << endl;
        }
        scanner();

        ParseBlock();

        if ( !(lexitem.type == TokenType::PUNCTUATOR && lexitem.value == ";" )){
            error_count +=1;
            cerr << "error at line = " << lexitem.line << endl << "should use semicolon " << endl;
        }
        scanner();



    }

    void ParseHeading(){
        if ( !(lexitem.type == TokenType::KEYWORD && lexitem.value == "FUNCTION" )){
            error_count +=1;
            cerr << "error at line = " << lexitem.line << endl << "should use FUNCTION keyword " << endl;
        }
        scanner();

        if ( !(lexitem.type == TokenType::IDENTIFIER )){
            error_count +=1;
            cerr << "error at line = " << lexitem.line << endl << "should use identifier " << endl;
        }
        scanner();


        if (lexitem.type == TokenType::PUNCTUATOR && lexitem.value == "(" ){
            ParseParameterList();
        }

        if ( !(lexitem.type == TokenType::PUNCTUATOR && lexitem.value == ":" )){
            error_count +=1;
            cerr << "error at line = " << lexitem.line << endl << "should use semicolon " << endl;
        }
        scanner();

        if ( !(lexitem.type == TokenType::KEYWORD && lexitem.value == "INTEGER" )){
            error_count +=1;
            cerr << "error at line = " << lexitem.line << endl << "should use INTEGER keyword " << endl;
        }
        scanner();



    }
    
    void ParseParameterList(){




    }

    void ParseFunctionBody(){}

    
    



};