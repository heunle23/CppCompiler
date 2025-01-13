#include "../lexical_analyzer/scanner.cpp"
#include "./parser_part2.cpp"




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



// Recursive Descent First Half of the grammer
class RDFH{
    
    LexicalAnalyzer analyzer; 
    Token lexitem = analyzer.touch(); 
    int error_count  = 0;
    SPSH* pointer_to_SHSP;


    RDFH() {
        pointer_to_SHSP = new SPSH(analyzer);
    };


    void scanner(){
        lexitem = analyzer.touch(); 
        }

    






    void ParseProgram(){
        

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
        while ( lexitem.value.length() == 1 && !(lexitem.value == ":")){
            
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

        if ( !(lexitem.type == TokenType::PUNCTUATOR && lexitem.value == "(" )){
            error_count +=1;
            cerr << "error at line = " << lexitem.line << endl << "should use opening parenthesis " << endl;
        }
        scanner();

        ParseIdentifierList();

        if ( !(lexitem.type == TokenType::PUNCTUATOR && lexitem.value == ":" )){
            error_count +=1;
            cerr << "error at line = " << lexitem.line << endl << "should use opening parenthesis " << endl;
        }
        scanner();

        if ( !(lexitem.type == TokenType::KEYWORD && lexitem.value == "INTEGER" )){
            error_count +=1;
            cerr << "error at line = " << lexitem.line << endl << "should use INTEGER keyword " << endl;
        }
        scanner();

        if ( !(lexitem.type == TokenType::PUNCTUATOR && lexitem.value == ")" )){
            error_count +=1;
            cerr << "error at line = " << lexitem.line << endl << "should use closing parenthesis " << endl;
        }
        scanner();



    }

    void ParseFunctionBody(){
        if ( !(lexitem.type == TokenType::KEYWORD && lexitem.value == "BEGIN ")){
            error_count +=1;
            cerr << "error at line = " << lexitem.line << endl << "should use BEGIN keyword" << endl;
        }
        scanner();

        ParseStatementSequence();

        if ( !(lexitem.type == TokenType::KEYWORD && lexitem.value == "END ")){
            error_count +=1;
            cerr << "error at line = " << lexitem.line << endl << "should use END keyword " << endl;
        }
        scanner();


    }

    
    void ParseStatementSequence(){
        ParseStatment();

        while (lexitem.value.length() == 1 ){
            
            if ( lexitem.type == TokenType::PUNCTUATOR && lexitem.value == ";"){
            error_count +=1 ;
            cerr << "error at line = " << lexitem.line << endl << "should use semicolon " << endl;
            }
            scanner();

            ParseStatment();

            

        }




    }

    void ParseStatment()
    {

        if (lexitem.type == TokenType:: KEYWORD)
        {
            if (lexitem.value == "BEGIN")
            {
                scanner();
                ParseStatementSequence();

                if ( !(lexitem.type == TokenType::KEYWORD && lexitem.value == "END "))
                {
                    error_count +=1;
                    cerr << "error at line = " << lexitem.line << endl << "should use END keyword " << endl;
                }
                scanner();

            }
            else if (lexitem.value == "IF")
            {
                scanner();
                ParseExpression(lexitem);

                if ( !(lexitem.type == TokenType::KEYWORD && lexitem.value == "THEN "))
                {
                    error_count +=1;
                    cerr << "error at line = " << lexitem.line << endl << "should use THEN keyword " << endl;
                }
                scanner();

                ParseStatment();

                if (lexitem.type == TokenType::KEYWORD && lexitem.value == "ELSE ")
                {
                    scanner();
                    ParseStatment();
                    
                }
                


            }
            
            else if(lexitem.value == "WHILE")
            {
                scanner();
                ParseExpression(lexitem);

                if ( !(lexitem.type == TokenType::KEYWORD && lexitem.value == "DO "))
                {
                    error_count +=1;
                    cerr << "error at line = " << lexitem.line << endl << "should use DO keyword " << endl;
                }
                scanner();
                ParseStatment();


            }
            else if(lexitem.value == "FOR")
            {
                scanner();

                if ( !(lexitem.type == TokenType::IDENTIFIER ))
                {
                    error_count +=1;
                    cerr << "error at line = " << lexitem.line << endl << "should use identifier " << endl;
                }
                scanner();

                if ( lexitem.type == TokenType::PUNCTUATOR && lexitem.value == ":=")
                {
                    error_count +=1 ;
                    cerr << "error at line = " << lexitem.line << endl << "should use semicolon " << endl;
                }
                scanner();
                ParseExpression(lexitem);

                if ( lexitem.type == TokenType::KEYWORD && (lexitem.value == "TO" || lexitem.value == "DOWN TO" ))
                {
                    error_count +=1 ;
                    cerr << "error at line = " << lexitem.line << endl << "should use DOWN or  DOWN TO " << endl;
                }
                scanner();
                ParseExpression(lexitem);

                if ( !(lexitem.type == TokenType::KEYWORD && lexitem.value == "DO "))
                {
                    error_count +=1;
                    cerr << "error at line = " << lexitem.line << endl << "should use DO keyword " << endl;
                }
                scanner();
                ParseStatment();




            }

        }






    }


    void ParseExpression(Token a){
        
        pointer_to_SHSP->ParseExpression(a);
    };

};