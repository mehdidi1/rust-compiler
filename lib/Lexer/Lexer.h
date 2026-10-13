#pragma once
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "Token.h"

/// Hand-written, single-pass lexer that turns Rust source text into tokens.
///
/// The lexer works on bytes, not Unicode characters: line and column numbers
/// are 1-based and count bytes, so a tab or one byte of a multi-byte UTF-8
/// character each advance the column by one.
///
/// Errors are not fatal. An unrecognized character is reported to std::cerr
/// and skipped, and lexing continues with the next character.
class Lexer {
  public:
    /// Creates a lexer over a copy of \p source.
    Lexer(const std::string &source);

    /// Lexes the whole source and returns its tokens in order.
    ///
    /// The result always ends with exactly one Eof token, positioned just
    /// past the last character of the input. Whitespace is skipped and
    /// produces no tokens; comments are not recognized.
    ///
    /// Meant to be called once: the lexer does not rewind, so a second call
    /// returns only an Eof token.
    std::vector<Token> tokenize();

  private:
    /// Returns the current character without consuming it, or '\0' at the
    /// end of input.
    char peek();

    /// Consumes and returns the current character, updating the line and
    /// column: a '\n' moves to column 1 of the next line, any other
    /// character moves one column right. At the end of input, returns '\0'
    /// and changes nothing.
    char advance();

    /// Returns true once every character of the source has been consumed.
    bool isAtEnd();

    /// Consumes spaces, tabs, '\n' and '\r' up to the next other character.
    void skipWhitespace();

    /// Scans an identifier or keyword: a letter or '_' followed by letters,
    /// digits and '_'. Returns a keyword token if the word is in `keywords`,
    /// otherwise an Ident token.
    ///
    /// Precondition: the current character is a letter or '_'.
    Token scanWord();

    /// Scans a double-quoted string literal. The token's text is the
    /// contents between the quotes, without the quotes.
    ///
    /// Escape sequences are not interpreted: a backslash is kept as-is and
    /// does not escape a following quote. If the closing quote is missing,
    /// the literal runs to the end of input and no error is reported.
    ///
    /// Precondition: the current character is '"'.
    Token scanString();

    /// Consumes one character and returns a token of \p type whose text is
    /// \p c.
    ///
    /// Precondition: \p c is the current character.
    Token scanSingleChar(char c, TokenType type);

    /// Scans a decimal integer literal made only of the digits 0-9. Digit
    /// separators ('_'), prefixes such as 0x, type suffixes and fractional
    /// parts are not recognized.
    ///
    /// Precondition: the current character is a digit.
    Token scanNumber();

    /// The text being lexed.
    std::string source_;
    /// Index of the next character to consume in source_.
    size_t pos_ = 0;
    /// Line of the next character to consume, starting at 1.
    int line_ = 1;
    /// Column of the next character to consume, starting at 1.
    int column_ = 1;
};
