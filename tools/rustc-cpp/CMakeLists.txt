add_executable(rustc-cpp main.cpp)
target_link_libraries(rustc-cpp PRIVATE Lexer)