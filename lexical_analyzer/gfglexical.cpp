#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "../symbol_table/symbol_table.h"
using namespace std;

// Enum class to define different types of tokens
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

    Token(TokenType t, const string& v)
        : type(t), value(v) {}
};

// Class that implements the lexical analyzer
class LexicalAnalyzer {
private:
    string input;
    size_t position;
    unordered_map<string, TokenType> keywords;

    void initKeywords() {
        keywords["int"] = TokenType::KEYWORD;
        keywords["float"] = TokenType::KEYWORD;
        keywords["if"] = TokenType::KEYWORD;
        keywords["else"] = TokenType::KEYWORD;
        keywords["while"] = TokenType::KEYWORD;
        keywords["return"] = TokenType::KEYWORD;
    }

    bool isWhitespace(char c) {
        return c == ' ' || c == '\t' || c == '\n' || c == '\r';
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

    string getNextWord() {
        size_t start = position;
        while (position < input.length() && isAlphaNumeric(input[position])) {
            position++;
        }
        return input.substr(start, position - start);
    }

    string getNextNumber() {
        size_t start = position;
        bool hasDecimal = false;
        while (position < input.length() && (isDigit(input[position]) || input[position] == '.')) {
            if (input[position] == '.') {
                if (hasDecimal) break;
                hasDecimal = true;
            }
            position++;
        }
        return input.substr(start, position - start);
    }

public:
    LexicalAnalyzer() : position(0) {
        initKeywords();
    }

    // Set the input for the lexical analyzer to process
    void setInput(const string& source) {
        input = source;
        position = 0;
    }

    // Tokenize the input string
    vector<Token> tokenize() {
        vector<Token> tokens;

        while (position < input.length()) {
            char currentChar = input[position];

            if (isWhitespace(currentChar)) {
                position++;
                continue;
            }

            if (isAlpha(currentChar)) {
                string word = getNextWord();
                if (keywords.find(word) != keywords.end()) {
                    tokens.emplace_back(TokenType::KEYWORD, word);
                } else {
                    tokens.emplace_back(TokenType::IDENTIFIER, word);
                }
            } else if (isDigit(currentChar)) {
                string number = getNextNumber();
                if (number.find('.') != string::npos) {
                    tokens.emplace_back(TokenType::FLOAT_LITERAL, number);
                } else {
                    tokens.emplace_back(TokenType::INTEGER_LITERAL, number);
                }
            } else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') {
                tokens.emplace_back(TokenType::OPERATOR, string(1, currentChar));
                position++;
            } else if (currentChar == '(' || currentChar == ')' || currentChar == '{' || currentChar == '}' || currentChar == ';') {
                tokens.emplace_back(TokenType::PUNCTUATOR, string(1, currentChar));
                position++;
            } else {
                tokens.emplace_back(TokenType::UNKNOWN, string(1, currentChar));
                position++;
            }
        }

        return tokens;
    }
};

// Function to convert TokenType to string for printing
string getTokenTypeName(TokenType type) {
    switch (type) {
        case TokenType::KEYWORD: return "KEYWORD";
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::INTEGER_LITERAL: return "INTEGER_LITERAL";
        case TokenType::FLOAT_LITERAL: return "FLOAT_LITERAL";
        case TokenType::OPERATOR: return "OPERATOR";
        case TokenType::PUNCTUATOR: return "PUNCTUATOR";
        case TokenType::UNKNOWN: return "UNKNOWN";
        default: return "UNDEFINED";
    }
}

// Function to read and return a chunk of source code from the file
string readSourceFromFile(ifstream& file, size_t bufferSize) {
    char* buffer = new char[bufferSize];    // Allocate a buffer
    file.read(buffer, bufferSize);          // Read from file into the buffer
    string chunk(buffer, file.gcount());    // Create a string from the buffer
    delete[] buffer;                       // Free the buffer memory
    return chunk;                           // Return the read chunk
}

// Function to process the file chunk by chunk using a buffer
void processFile(const string& filename, size_t bufferSize) {
    ifstream file(filename);  // Open the file
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    LexicalAnalyzer lexer;  // Create a lexical analyzer

    // Read the file chunk by chunk until the end of the file
    while (!file.eof()) {
        string chunk = readSourceFromFile(file, bufferSize);
        lexer.setInput(chunk);  // Set the current chunk as input for the lexer
        vector<Token> tokens = lexer.tokenize();  // Tokenize the current chunk

        // Print the tokens for the current chunk
        for (const auto& token : tokens) {
            cout << "Type: " << getTokenTypeName(token.type)
                 << ", Value: " << token.value << endl;
        }
    }

    file.close();  // Close the file
}

// Driver code
int main() {
    string filename = "source_code.txt";  // Name of the file to process
    size_t bufferSize = 512;  // Buffer size to read in chunks

    processFile(filename, bufferSize);  // Process the file with the buffer

    cout << endl;
    string ab = "ab";
    string ba = "ba" ;

    SymbolTable st;
    
    cout << st.Connect(ab) << endl;
    cout << st.Connect(ba) << endl;

}



