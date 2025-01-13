using namespace std;
#include <unordered_map>
#include <string>
#include <vector>
#include "../lexical_analyzer/scanner.cpp"
#include <algorithm>




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


enum class Node_Type {
    TOKEN,
    HELPER,

};



struct Node {

    string name;
    Node_Type type;

    Node* child1;
    Node* child2;
    Node* child3;
    Node* child4;
    Node* child5;

    Node(string data ,Node_Type t ) : name(data) , type(t)
    {
        
        child1 = nullptr; 
        child2 = nullptr; 
        child3 = nullptr; 
        child4 = nullptr; 
        child5 = nullptr; 
    }
};






// Simple Precedence Second Half of the grammer
class SPSH {
public:

    unordered_map<string, unordered_map<string,char> > SP_table;
    
    LexicalAnalyzer& analyzer; 
    vector<Node> stack;

    unordered_map<string, vector<string>> Grammer_Second_Half;

    


    SPSH(LexicalAnalyzer& object) : analyzer(object){
        

        Grammer_Second_Half["exp"].push_back("sim");
        Grammer_Second_Half["exp"].push_back("sim rel SSF");
        
        Grammer_Second_Half["rel"].push_back("=");
        Grammer_Second_Half["rel"].push_back("<>");
        Grammer_Second_Half["rel"].push_back("<");
        Grammer_Second_Half["rel"].push_back(">");
        Grammer_Second_Half["rel"].push_back("<=");
        Grammer_Second_Half["rel"].push_back(">=");

        Grammer_Second_Half["sim"].push_back("opr");
        Grammer_Second_Half["sim"].push_back("sig SSF2");
        Grammer_Second_Half["sim"].push_back("sim add SSF2");

        Grammer_Second_Half["sig"].push_back("+");
        Grammer_Second_Half["sig"].push_back("-");

        Grammer_Second_Half["add"].push_back("+");
        Grammer_Second_Half["add"].push_back("-");

        Grammer_Second_Half["opr"].push_back("fac");
        Grammer_Second_Half["opr"].push_back("opr mul fac");

        Grammer_Second_Half["mul"].push_back("*");
        Grammer_Second_Half["mul"].push_back("/");
        Grammer_Second_Half["mul"].push_back("DIV");
        Grammer_Second_Half["mul"].push_back("MOD");

        Grammer_Second_Half["fac"].push_back("id");
        Grammer_Second_Half["fac"].push_back("con");
        Grammer_Second_Half["fac"].push_back("( exp )");
        Grammer_Second_Half["fac"].push_back("id ( exp )");
        Grammer_Second_Half["fac"].push_back("id ( exp SRF)");

        Grammer_Second_Half["SSF"].push_back("sim");

        Grammer_Second_Half["SSF2"].push_back("opr");

        Grammer_Second_Half["TF"].push_back(", exp TF");
        Grammer_Second_Half["TF"].push_back(", exp");

        Grammer_Second_Half["SRF"].push_back("TF");






        stack.push_back(Node("#",Node_Type::HELPER));


        

        SP_table["#"]["sim"] = '<';
        SP_table["#"]["sig"] = '<';
        SP_table["#"]["opr"] = '<';
        SP_table["#"]["fac"] = '<';
        SP_table["#"][" +S"] = '<';
        SP_table["#"]["-S"] = '<';
        SP_table["#"]["id"] = '<';
        SP_table["#"]["con"] = '<';
        SP_table["#"]["("] = '<';
        SP_table["exp"][")"] = '>';
        SP_table["exp"][","] = '<';
        SP_table["exp"]["TF"] = ' =';
        SP_table["exp"]["SRF"] = ' =';
        SP_table["rel"]["sim"] = '<';
        SP_table["rel"]["sig"] = '<';
        SP_table["rel"]["opr"] = '<';
        SP_table["rel"]["fac"] = '<';
        SP_table["rel"]["ssf"] = ' =';
        SP_table["rel"][" +S"] = '<';
        SP_table["rel"]["-S"] = '<';
        SP_table["rel"]["id"] = '<';
        SP_table["rel"]["con"] = '<';
        SP_table["rel"]["("] = '<';
        SP_table["sim"]["#"] = '>';
        SP_table["sim"]["rel"] = ' =';
        SP_table["sim"]["add"] = ' =';
        SP_table["sim"][" ="] = '<';
        SP_table["sim"]["<>"] = '<';
        SP_table["sim"]["<"] = '<';
        SP_table["sim"][">"] = '<';
        SP_table["sim"]["<="] = '<';
        SP_table["sim"][">="] = '<';
        SP_table["sim"][" +a"] = '<';
        SP_table["sim"]["-a"] = '<';
        SP_table["sim"][")"] = '>';
        SP_table["sim"][","] = '>';
        SP_table["sig"]["opr"] = '<';
        SP_table["sig"]["fac"] = '<';
        SP_table["sig"]["ssf2"] = ' =';
        SP_table["sig"]["id"] = '<';
        SP_table["sig"]["con"] = '<';
        SP_table["sig"]["("] = '<';
        SP_table["add"]["opr"] = '<';
        SP_table["add"]["fac"] = '<';
        SP_table["add"]["ssf2"] = ' =';
        SP_table["add"]["id"] = '<';
        SP_table["add"]["con"] = '<';
        SP_table["add"]["("] = '<';
        SP_table["opr"]["#"] = '>';
        SP_table["opr"]["mul"] = ' =';
        SP_table["opr"][" ="] = '>';
        SP_table["opr"]["<>"] = '>';
        SP_table["opr"]["<"] = '>';
        SP_table["opr"][">"] = '>';
        SP_table["opr"]["<="] = '>';
        SP_table["opr"][">="] = '>';
        SP_table["opr"][" +a"] = '>';
        SP_table["opr"]["-a"] = '>';
        SP_table["opr"]["*"] = '<';
        SP_table["opr"]["/"] = '<';
        SP_table["opr"]["div"] = '<';
        SP_table["opr"]["mod"] = '<';
        SP_table["opr"][")"] = '>';
        SP_table["opr"][","] = '>';
        SP_table["mul"]["fac"] = ' =';
        SP_table["mul"]["id"] = '<';
        SP_table["mul"]["con"] = '<';
        SP_table["mul"]["("] = '<';
        SP_table["fac"]["#"] = '>';
        SP_table["fac"][" ="] = '>';
        SP_table["fac"]["<>"] = '>';
        SP_table["fac"]["<"] = '>';
        SP_table["fac"][">"] = '>';
        SP_table["fac"]["<="] = '>';
        SP_table["fac"][">="] = '>';
        SP_table["fac"][" +a"] = '>';
        SP_table["fac"]["-a"] = '>';
        SP_table["fac"]["*"] = '>';
        SP_table["fac"]["/"] = '>';
        SP_table["fac"]["div"] = '>';
        SP_table["fac"]["mod"] = '>';
        SP_table["fac"][")"] = '>';
        SP_table["fac"][","] = '>';
        SP_table["ssf"]["#"] = '>';
        SP_table["ssf"][")"] = '>';
        SP_table["ssf"][","] = '>';
        SP_table["ssf2"]["#"] = '>';
        SP_table["ssf2"][" ="] = '>';
        SP_table["ssf2"]["<>"] = '>';
        SP_table["ssf2"]["<"] = '>';
        SP_table["ssf2"][">"] = '>';
        SP_table["ssf2"]["<="] = '>';
        SP_table["ssf2"][">="] = '>';
        SP_table["ssf2"][" +a"] = '>';
        SP_table["ssf2"]["-a"] = '>';
        SP_table["ssf2"][")"] = '>';
        SP_table["ssf2"][","] = '>';
        SP_table[" ="]["sim"] = '>';
        SP_table[" ="]["sig"] = '>';
        SP_table[" ="]["opr"] = '>';
        SP_table[" ="]["fac"] = '>';
        SP_table[" ="][" +S"] = '>';
        SP_table[" ="]["-S"] = '>';
        SP_table[" ="]["id"] = '>';
        SP_table[" ="]["con"] = '>';
        SP_table[" ="]["("] = '>';
        SP_table["<>"]["sim"] = '>';
        SP_table["<>"]["sig"] = '>';
        SP_table["<>"]["opr"] = '>';
        SP_table["<>"]["fac"] = '>';
        SP_table["<>"][" +S"] = '>';
        SP_table["<>"]["-S"] = '>';
        SP_table["<>"]["id"] = '>';
        SP_table["<>"]["con"] = '>';
        SP_table["<>"]["("] = '>';
        SP_table["<"]["sim"] = '>';
        SP_table["<"]["sig"] = '>';
        SP_table["<"]["opr"] = '>';
        SP_table["<"]["fac"] = '>';
        SP_table["<"][" +S"] = '>';
        SP_table["<"]["-S"] = '>';
        SP_table["<"]["id"] = '>';
        SP_table["<"]["con"] = '>';
        SP_table["<"]["("] = '>';
        SP_table[">"]["sim"] = '>';
        SP_table[">"]["sig"] = '>';
        SP_table[">"]["opr"] = '>';
        SP_table[">"]["fac"] = '>';
        SP_table[">"][" +S"] = '>';
        SP_table[">"]["-S"] = '>';
        SP_table[">"]["id"] = '>';
        SP_table[">"]["con"] = '>';
        SP_table[">"]["("] = '>';
        SP_table["<="]["sim"] = '>';
        SP_table["<="]["sig"] = '>';
        SP_table["<="]["opr"] = '>';
        SP_table["<="]["fac"] = '>';
        SP_table["<="][" +S"] = '>';
        SP_table["<="]["-S"] = '>';
        SP_table["<="]["id"] = '>';
        SP_table["<="]["con"] = '>';
        SP_table["<="]["("] = '>';
        SP_table[">="]["sim"] = '>';
        SP_table[">="]["sig"] = '>';
        SP_table[">="]["opr"] = '>';
        SP_table[">="]["fac"] = '>';
        SP_table[">="][" +S"] = '>';
        SP_table[">="]["-S"] = '>';
        SP_table[">="]["id"] = '>';
        SP_table[">="]["con"] = '>';
        SP_table[">="]["("] = '>';
        SP_table[" +S"]["opr"] = '>';
        SP_table[" +S"]["fac"] = '>';
        SP_table[" +S"]["id"] = '>';
        SP_table[" +S"]["con"] = '>';
        SP_table[" +S"]["("] = '>';
        SP_table["-s"]["opr"] = '>';
        SP_table["-s"]["fac"] = '>';
        SP_table["-s"]["id"] = '>';
        SP_table["-s"]["con"] = '>';
        SP_table["-s"]["("] = '>';
        SP_table[" +a"]["opr"] = '>';
        SP_table[" +a"]["fac"] = '>';
        SP_table[" +a"]["id"] = '>';
        SP_table[" +a"]["con"] = '>';
        SP_table[" +a"]["("] = '>';
        SP_table["-a"]["opr"] = '>';
        SP_table["-a"]["fac"] = '>';
        SP_table["-a"]["id"] = '>';
        SP_table["-a"]["con"] = '>';
        SP_table["-a"]["("] = '>';
        SP_table["*"]["id"] = '>';
        SP_table["*"]["con"] = '>';
        SP_table["*"]["("] = '>';
        SP_table["/"]["id"] = '>';
        SP_table["/"]["con"] = '>';
        SP_table["/"]["("] = '>';
        SP_table["div"]["id"] = '>';
        SP_table["div"]["con"] = '>';
        SP_table["div"]["("] = '>';
        SP_table["mod"]["id"] = '>';
        SP_table["mod"]["con"] = '>';
        SP_table["mod"]["("] = '>';
        SP_table["id"]["#"] = '>';
        SP_table["id"][" ="] = '>';
        SP_table["id"]["<>"] = '>';
        SP_table["id"]["<"] = '>';
        SP_table["id"][">"] = '>';
        SP_table["id"]["<="] = '>';
        SP_table["id"][">="] = '>';
        SP_table["id"][" +a"] = '>';
        SP_table["id"]["-a"] = '>';
        SP_table["id"]["*"] = '>';
        SP_table["id"]["/"] = '>';
        SP_table["id"]["div"] = '>';
        SP_table["id"]["mod"] = '>';
        SP_table["id"]["("] = ' =';
        SP_table["id"][")"] = '>';
        SP_table["id"][","] = '>';
        SP_table["con"]["#"] = '>';
        SP_table["con"][" ="] = '>';
        SP_table["con"]["<>"] = '>';
        SP_table["con"]["<"] = '>';
        SP_table["con"][">"] = '>';
        SP_table["con"]["<="] = '>';
        SP_table["con"][">="] = '>';
        SP_table["con"][" +a"] = '>';
        SP_table["con"]["-a"] = '>';
        SP_table["con"]["*"] = '>';
        SP_table["con"]["/"] = '>';
        SP_table["con"]["div"] = '>';
        SP_table["con"]["mod"] = '>';
        SP_table["con"][")"] = '>';
        SP_table["con"][","] = '>';
        SP_table["("]["exp"] = ' =';
        SP_table["("]["sim"] = '<';
        SP_table["("]["sig"] = '<';
        SP_table["("]["opr"] = '<';
        SP_table["("]["fac"] = '<';
        SP_table["("][" +S"] = '<';
        SP_table["("]["-S"] = '<';
        SP_table["("]["id"] = '<';
        SP_table["("]["con"] = '<';
        SP_table["("]["("] = '<';
        SP_table[")"]["#"] = '>';
        SP_table[")"][" ="] = '>';
        SP_table[")"]["<>"] = '>';
        SP_table[")"]["<"] = '>';
        SP_table[")"][">"] = '>';
        SP_table[")"]["<="] = '>';
        SP_table[")"][">="] = '>';
        SP_table[")"][" +a"] = '>';
        SP_table[")"]["-a"] = '>';
        SP_table[")"]["*"] = '>';
        SP_table[")"]["/"] = '>';
        SP_table[")"]["div"] = '>';
        SP_table[")"]["mod"] = '>';
        SP_table[")"][")"] = '>';
        SP_table[")"][","] = '>';
        SP_table[","]["exp"] = ' =';
        SP_table["TF"][")"] = '>';
        SP_table["SRF"][")"] = ' =';
    
    
    }
        
    void scanner(){
        Token lexitem = analyzer.touch(); 
        }


    // the topmost non terminal or terminal in the stack
    string topmost_NT_or_T(){
        for(int i =stack.size() -1  ; i>-1 ; i--)
            if (stack[i].type == Node_Type::TOKEN){
                return stack[i].name ;
            }

        return "#" ;
    }



    string search_grammer(string handle){

        for (const auto& pair : Grammer_Second_Half) {
                    for(int j=0 ; j < pair.second.size()  ; j++)
                        if (pair.second[j] == handle){
                            string left = pair.first;
                            return left;
                        }


                }

    }



    void ParseExpression(Token lexitem){

        while(true){

            string row = topmost_NT_or_T() ;
            string coloumn = lexitem.value ;
            char result = SP_table[row][coloumn];

            if (result == '=' || result == '<' ) {    // shift
                stack.push_back(Node(string (1,result),Node_Type::HELPER)); 
                scanner();



            }else if (result == '>'){ // reduce
                stack.push_back(Node(string (1,result),Node_Type::HELPER)); 
                
                string handle = "";

                do
                {
                    
                    Node node = stack.back();
                    stack.pop_back();

                    if (node.type == Node_Type::TOKEN){
                        handle += node.name;

                    }


                } while (stack.back().name != "<");
                

                reverse(handle.begin(), handle.end()); 

                
                string left = search_grammer(handle);


                string row = topmost_NT_or_T() ;
                string coloumn = left;
                char result2 = SP_table[row][coloumn];

                if (result2 == '<' || result2 == '='){

                    // children making and parent making needs to be implemented (ali)

                    stack.push_back(Node(string (1,result2),Node_Type::HELPER)); 
                    stack.push_back(Node(left,Node_Type::TOKEN)); 


                }else if (result2 == '>'){
                    // needs more information to implement
                    // جزوه صفحه ۱۱۵ توضیحی نداده است



                }
            } 
        }
    };
};


