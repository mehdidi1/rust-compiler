#pragma once
#include <string>
#include <unordered_map>

/// The kind of a token. Keywords and punctuation each have their own kind;
/// identifiers and literals share one kind per category and carry their
/// spelling in Token::text.
enum class TokenType {
    Ident,          // identifier
    Fn,             // fn
    Let,            // let
    Bool,           // true or false; Token::text tells which

    StringLit,      // "..." string literal
    IntLit,         // decimal integer literal

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

    Eof,            // end of input; always the last token
};

/// Words that lex as keywords instead of identifiers. A word not listed here
/// becomes an Ident token.
const std::unordered_map<std::string, TokenType> keywords = {
    {"fn",    TokenType::Fn},
    {"let",   TokenType::Let},
    {"true",  TokenType::Bool},
    {"false", TokenType::Bool},
};

/// Punctuation and operators made of a single character. Multi-character
/// operators such as "->" are not listed here; Lexer::tokenize() recognizes
/// them before consulting this table.
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

/// Returns the enumerator's name, e.g. "Arrow" for TokenType::Arrow, for use
/// in debug output.
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

/// One token produced by the lexer.
struct Token {
    TokenType type;
    /// The token's spelling as written in the source, except for StringLit,
    /// where it is the contents without the surrounding quotes, and Eof,
    /// where it is empty.
    std::string text;
    /// 1-based line of the token's first character.
    int line;
    /// 1-based column of the token's first character, counted in bytes.
    int column;
};