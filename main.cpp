#include <iostream>
#include <string>
#include <vector>

#include "compiler.h"
#include "lexer.h"
#include "parser.h"
#include "vm.h"

int main() {
  // A script to test our entire pipeline!
  // It should calculate 2 + 12, print 14, then check if 14 > 10 and print 1
  // (true)
  std::string sourceCode =
      "let score = 2 + 3 * 4; print score; print score > 10;";

  std::cout << "--- CVM++ Execution Engine --- \n";

  // 1. Front-End: Read text and build the Tree
  Lexer lexer(sourceCode);
  std::vector<Token> tokens = lexer.scanTokens();

  Parser parser(tokens);
  std::vector<std::unique_ptr<Stmt>> statements = parser.parse();

  // 2. Back-End: Flatten the Tree and run it!
  Compiler compiler;
  Chunk chunk = compiler.compile(statements);

  VM vm;
  vm.interpret(&chunk);

  return 0;
}