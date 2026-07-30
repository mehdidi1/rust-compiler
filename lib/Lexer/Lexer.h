#pragma once
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "Token.h"

class Lexer {
  public:
    Lexer(const std::string &source);
    std::vector<Token> tokenize();

  private:
    char peek();
    char advance();
    bool isAtEnd();
    void skipWhitespace();
    Token scanWord();
    Token scanString();
    Token scanSingleChar(char c, TokenType type);
    Token scanNumber();

    std::string source;
    int pos = 0;
    int line = 1;
    int column = 1;
};
