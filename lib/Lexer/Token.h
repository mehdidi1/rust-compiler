#pragma once
#include <string>
#include <unordered_map>

enum class TokenType {
    Ident,          // identity
    Fn,             // fn
    Let,            // let
    Bool,           // true or false

    StringLit,      // quoted string
    IntLit,        // num

    LParen,         // (
    RParen,         // )
    LBrace,         // {
    RBrace,         // }
    Semicolon,      // ;

    Bang,           // !
    Eq,             // =
    Plus,           // +
    Minus,          // -
    Star,           // *
    Slash,          // /
    Arrow,          // ->

    Eof,
};

const std::unordered_map<std::string, TokenType> keywords = {
    {"fn",    TokenType::Fn},
    {"let",   TokenType::Let},
    {"true",  TokenType::Bool},
    {"false", TokenType::Bool},
};

const std::unordered_map<char, TokenType> singleChars = {
    {'(', TokenType::LParen},
    {')', TokenType::RParen},
    {'{', TokenType::LBrace},
    {'}', TokenType::RBrace},
    {';', TokenType::Semicolon},
    {'!', TokenType::Bang},
    {'=', TokenType::Eq},
    {'+', TokenType::Plus},
    {'-', TokenType::Minus},
    {'*', TokenType::Star},
    {'/', TokenType::Slash},
};

inline std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::Ident:      return "Ident";
        case TokenType::Fn:         return "Fn";
        case TokenType::Let:        return "Let";
        case TokenType::Bool:       return "Bool";

        case TokenType::StringLit:  return "StringLit";
        case TokenType::IntLit:     return "IntLit";

        case TokenType::LParen:     return "LParen";
        case TokenType::RParen:     return "RParen";
        case TokenType::LBrace:     return "LBrace";
        case TokenType::RBrace:     return "RBrace";
        case TokenType::Semicolon:  return "Semicolon";

        case TokenType::Bang:       return "Bang";
        case TokenType::Eq:         return "Eq";
        case TokenType::Plus:       return "Plus";
        case TokenType::Minus:      return "Minus";
        case TokenType::Star:       return "Star";
        case TokenType::Slash:      return "Slash";
        case TokenType::Arrow:      return "Arrow";
        
        case TokenType::Eof:        return "Eof";

    }
    return "Unknown";
}

struct Token {
    TokenType type;
    std::string text;
    int line;
    int column;
};