add_executable(LexerTests LexerTests.cpp)
target_link_libraries(LexerTests PRIVATE Lexer Catch2::Catch2WithMain)
catch_discover_tests(LexerTests)
