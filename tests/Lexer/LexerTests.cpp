#include "Lexer/Lexer.h"
#include "Lexer/Token.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <string>

TEST_CASE("empty input produces only Eof", "[lexer]") {
    // Arrange
    std::string text = "";
    Lexer lexer(text);

    // Act
    std::vector<Token> tokens{lexer.tokenize()};

    // Assert
    REQUIRE(tokens.size() == 1);
    REQUIRE(tokens[0].type == TokenType::Eof);
}

TEST_CASE("a single keyword or symbol lexes to exactly one token", "[lexer]") {
    auto [input, expected] = GENERATE(table<std::string, TokenType>({
        {"let", TokenType::Let},
        {"fn", TokenType::Fn},
        {"(", TokenType::LParen},
        {")", TokenType::RParen},
        {"{", TokenType::LBrace},
        {"}", TokenType::RBrace},
        {";", TokenType::Semicolon},
        {"!", TokenType::Bang},
        {"=", TokenType::Eq},
        {"+", TokenType::Plus},
        {"-", TokenType::Minus},
        {"*", TokenType::Star},
        {"/", TokenType::Slash},
        {"->", TokenType::Arrow},
        {"true", TokenType::Bool},
        {"false", TokenType::Bool},
    }));
    CAPTURE(input); // on failure, prints which row failed
    Lexer lexer(input);
    std::vector<Token> tokens{lexer.tokenize()};

    REQUIRE(tokens.size() == 2);
    REQUIRE(tokens[0].text == input);
    REQUIRE(tokens[0].type == expected);
    REQUIRE(tokens[1].type == TokenType::Eof);
}
