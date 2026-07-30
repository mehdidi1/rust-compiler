#include "Lexer.h"

Lexer::Lexer(const std::string &source) : source(source) {}

char Lexer::peek() {
    if (isAtEnd())
        return '\0';

    return source[pos];
}

char Lexer::advance() {
    if (isAtEnd())
        return '\0';

    char c = source[pos++];

    if (c == '\n') {
        line++;
        column = 1;
    } else {
        column++;
    }

    return c;
}

bool Lexer::isAtEnd() { return pos >= (int)source.size(); }

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
    int startLine = line;
    int startCol = column;
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
    int startLine = line;
    int startCol = column;
    advance(); // skip opening "

    std::string value;
    while (!isAtEnd() && peek() != '"') {
        value += advance();
    }

    advance(); // skip closing "
    return {TokenType::StringLit, value, startLine, startCol};
}

Token Lexer::scanSingleChar(char c, TokenType type) {
    int startLine = line;
    int startCol = column;
    advance();
    return {type, std::string(1, c), startLine, startCol};
}

Token Lexer::scanNumber() {
    int startLine = line;
    int startCol = column;
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
        } else if (c == '-' && pos + 1 < (int)source.size() &&
                   source[pos + 1] == '>') {
            int startLine = line;
            int startCol = column;
            advance(); // skip -
            advance(); // skip >
            tokens.push_back({TokenType::Arrow, "->", startLine, startCol});
        } else if (singleChars.count(c)) {
            tokens.push_back(scanSingleChar(c, singleChars.at(c)));
        } else if (isdigit(c)) {
            tokens.push_back(scanNumber());
        } else {
            std::cerr << "Unexpected character '" << c << "' at line " << line
                      << ", column " << column << std::endl;

            advance();
        }
    }

    tokens.push_back({TokenType::Eof, "", line, column});
    return tokens;
}
