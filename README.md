# CVM++

**A Turing-Complete, Stack-Based Virtual Machine and Bytecode Compiler written from scratch in C++17.**

CVM++ is a custom, dynamically-typed programming language. It features a complete end-to-end compilation pipeline: reading raw source code, generating an Abstract Syntax Tree (AST) via a Recursive Descent Parser, flattening it into Bytecode, and executing it on a custom high-performance Virtual Machine.

## The Architecture Pipeline

Unlike tree-walking interpreters, CVM++ is designed for pure execution speed by separating the translation phase from the execution phase.

1. **Lexical Analysis (`lexer.cpp`):** Scans raw text and converts it into a structured vocabulary of `Tokens` (handling keywords, operators, and dynamic numbers/strings).
2. **Recursive Descent Parser (`parser.cpp`):** Reads the tokens and enforces grammar and Order of Operations (BODMAS), structuring the code into an **Abstract Syntax Tree (AST)** using C++ smart pointers (`std::unique_ptr`).
3. **Bytecode Compiler (`compiler.cpp`):** Performs a post-order traversal of the 3D AST, flattening the complex tree into a 1D array of highly optimized, 1-byte machine instructions (`OpCodes`).
4. **Stack-Based Virtual Machine (`vm.cpp`):** The execution engine. It utilizes an Instruction Pointer (`ip`) to blindly and rapidly execute the bytecode array against a C++ `std::vector` data stack.

## Language Features

- **Dynamic Variables & Memory State:** Stored securely in a C++ Hash Map (`std::unordered_map`).
- **Arithmetic & Boolean Logic:** Complete support for `+`, `-`, `*`, `/`, `==`, `<`, `>`.
- **Turing-Complete Control Flow:** `if`/`else` statements and `while` loops implemented entirely via **Bytecode Backpatching** and dynamic `ip` jump offsets.

## Code Example

CVM++ executing a classic while-loop countdown with conditional branching:

```javascript
let countdown = 3;

if (countdown > 0) {
    print 999;
} else {
    print 0;
}

while (countdown > 0) {
    print countdown;
    let countdown = countdown - 1;
}
```
