#include "Lexer/Lexer.h"
#include "Lexer/Token.h"
#include <catch2/catch_test_macros.hpp>
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
