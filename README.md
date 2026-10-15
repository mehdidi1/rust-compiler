# rustc-cpp

A compiler for a subset of Rust, written in C++20. Personal project, in progress.

The code is split LLVM-style into libraries under `lib/` (Lexer, Parser, Sema, AST,
IR, CodeGen, Diagnostics, Support) and a `rustc-cpp` driver under `tools/`. Only the
lexer is implemented so far; the other libraries are placeholders.

## Status

- [x] Lexer: `fn` and `let` keywords, identifiers, integer and string literals,
  booleans, and `( ) { } ; ! = + - * / ->`, with line/column tracking and an error
  for each unexpected character
- [ ] Parser and AST
- [ ] Semantic analysis
- [ ] IR and code generation

## Build

Requires CMake 3.20+ and a C++20 compiler.

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

Everything compiles with `-Wall -Wextra -Wpedantic -Wshadow -Wconversion -Werror`.
Debug builds also enable AddressSanitizer and UndefinedBehaviorSanitizer.

## Run

```bash
./build/tools/rustc-cpp/rustc-cpp examples/helloword.rs
```

The driver currently prints the token stream:

```
Token { type: Fn, lexeme: "fn", line: 1, col: 1 }
Token { type: Ident, lexeme: "main", line: 1, col: 4 }
Token { type: LParen, lexeme: "(", line: 1, col: 8 }
...
```

## Tests

Tests use [Catch2](https://github.com/catchorg/Catch2), fetched by CMake. They are
off by default; no test cases are written yet.

```bash
cmake -B build -DRUSTC_BUILD_TESTS=ON
cmake --build build
ctest --test-dir build
```

## License

MIT
