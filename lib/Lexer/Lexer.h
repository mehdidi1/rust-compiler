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

    std::string source_;
    size_t pos_ = 0;
    int line_ = 1;
    int column_ = 1;
};
