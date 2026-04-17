#include <iostream>
#include <string>
#include <vector>

#include "ast.h"
#include "lexer.h"
#include "parser.h"

// ==========================================
// AST PRINTER HELPER (To visualize our tree)
// ==========================================
std::string printExpr(Expr* expr) {
  if (auto e = dynamic_cast<BinaryExpr*>(expr)) {
    return "(" + e->op.lexeme + " " + printExpr(e->left.get()) + " " +
           printExpr(e->right.get()) + ")";
  } else if (auto e = dynamic_cast<LiteralExpr*>(expr)) {
    return e->value.lexeme;
  } else if (auto e = dynamic_cast<VariableExpr*>(expr)) {
    return e->name.lexeme;
  }
  return "?";
}

std::string printStmt(Stmt* stmt) {
  if (auto s = dynamic_cast<VarStmt*>(stmt)) {
    return "(let " + s->name.lexeme + " = " + printExpr(s->initializer.get()) +
           ")";
  } else if (auto s = dynamic_cast<PrintStmt*>(stmt)) {
    return "(print " + printExpr(s->expression.get()) + ")";
  }
  return "?";
}

// ==========================================
// MAIN ENGINE
// ==========================================
int main() {
  // 1. A tricky script to test Order of Operations
  std::string sourceCode = "let score = 2 + 3 * 4; print score;";

  std::cout << "--- CVM++ Compiler Engine --- \n";
  std::cout << "Raw Script: \n" << sourceCode << "\n\n";

  // 2. Lexer: String -> Tokens
  Lexer lexer(sourceCode);
  std::vector<Token> tokens = lexer.scanTokens();

  // 3. Parser: Tokens -> AST (Tree)
  Parser parser(tokens);
  std::vector<std::unique_ptr<Stmt>> statements = parser.parse();

  // 4. Print the generated Abstract Syntax Tree
  std::cout << "Abstract Syntax Tree Generated:\n";
  for (const auto& stmt : statements) {
    if (stmt != nullptr) {
      std::cout << "-> " << printStmt(stmt.get()) << "\n";
    }
  }

  return 0;
}