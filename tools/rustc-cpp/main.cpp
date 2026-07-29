#include <iostream>
#include <fstream>
#include <sstream>
#include "Lexer/Lexer.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: rustc-cpp <file.rs>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cout << "Error: cannot open file " << argv[1] << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();
    
    Lexer lexer(source);
    std::vector<Token> tokens = lexer.tokenize();

    for (const auto& token : tokens) {
        std::cout << "Token { type: " << tokenTypeToString(token.type)
                  << ", lexeme: \"" << token.text
                  << "\", line: " << token.line
                  << ", col: " << token.column << " }" << std::endl;
    }

    return 0;
}