#include "Lexer.h"

Lexer::Lexer(const std::string &source) : source_(source) {}

char Lexer::peek() {
    if (isAtEnd())
        return '\0';

    return source_[pos_];
}

char Lexer::advance() {
    if (isAtEnd())
        return '\0';

    char c = source_[pos_++];

    if (c == '\n') {
        line_++;
        column_ = 1;
    } else {
        column_++;
    }

    return c;
}

bool Lexer::isAtEnd() { return pos_ >= source_.size(); }

void Lexer::skipWhitespace() {
    while (!isAtEnd()) {
        char c = peek();
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
            advance();
        } else {
            break;
        }
    }
}

Token Lexer::scanWord() {
    int startLine = line_;
    int startCol = column_;
    std::string word;

    while (!isAtEnd() && (isalnum(peek()) || peek() == '_')) {
        word += advance();
    }

    if (keywords.count(word)) {
        return {keywords.at(word), word, startLine, startCol};
    }

    return {TokenType::Ident, word, startLine, startCol};
}

Token Lexer::scanString() {
    int startLine = line_;
    int startCol = column_;
    advance(); // skip opening "

    std::string value;
    while (!isAtEnd() && peek() != '"') {
        value += advance();
    }

    advance(); // skip closing "
    return {TokenType::StringLit, value, startLine, startCol};
}

Token Lexer::scanSingleChar(char c, TokenType type) {
    int startLine = line_;
    int startCol = column_;
    advance();
    return {type, std::string(1, c), startLine, startCol};
}

Token Lexer::scanNumber() {
    int startLine = line_;
    int startCol = column_;
    std::string num;

    while (!isAtEnd() && isdigit(peek())) {
        num += advance();
    }

    return {TokenType::IntLit, num, startLine, startCol};
}

std::vector<Token> Lexer::tokenize() {

    std::vector<Token> tokens;

    while (!isAtEnd()) {
        skipWhitespace();
        if (isAtEnd())
            break;

        char c = peek();

        if (isalpha(c) || c == '_') {
            tokens.push_back(scanWord());
        } else if (c == '"') {
            tokens.push_back(scanString());
        } else if (c == '-' && pos_ + 1 < source_.size() &&
                   source_[pos_ + 1] == '>') {
            int startLine = line_;
            int startCol = column_;
            advance(); // skip -
            advance(); // skip >
            tokens.push_back({TokenType::Arrow, "->", startLine, startCol});
        } else if (singleChars.count(c)) {
            tokens.push_back(scanSingleChar(c, singleChars.at(c)));
        } else if (isdigit(c)) {
            tokens.push_back(scanNumber());
        } else {
            std::cerr << "Unexpected character '" << c << "' at line " << line_
                      << ", column " << column_ << std::endl;

            advance();
        }
    }

    tokens.push_back({TokenType::Eof, "", line_, column_});
    return tokens;
}
