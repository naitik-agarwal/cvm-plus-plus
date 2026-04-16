#include <iostream>
#include <vector>

#include "lexer.h"

// A quick helper function to print the token names clearly
std::string tokenTypeToString(TokenType type) {
  switch (type) {
    case TokenType::LEFT_PAREN:
      return "LEFT_PAREN";
    case TokenType::RIGHT_PAREN:
      return "RIGHT_PAREN";
    case TokenType::LEFT_BRACE:
      return "LEFT_BRACE";
    case TokenType::RIGHT_BRACE:
      return "RIGHT_BRACE";
    case TokenType::SEMICOLON:
      return "SEMICOLON";
    case TokenType::PLUS:
      return "PLUS";
    case TokenType::MINUS:
      return "MINUS";
    case TokenType::STAR:
      return "STAR";
    case TokenType::SLASH:
      return "SLASH";
    case TokenType::EQUAL:
      return "EQUAL";
    case TokenType::EQUAL_EQUAL:
      return "EQUAL_EQUAL";
    case TokenType::LESS:
      return "LESS";
    case TokenType::LESS_EQUAL:
      return "LESS_EQUAL";
    case TokenType::GREATER:
      return "GREATER";
    case TokenType::GREATER_EQUAL:
      return "GREATER_EQUAL";
    case TokenType::IDENTIFIER:
      return "IDENTIFIER";
    case TokenType::NUMBER:
      return "NUMBER";
    case TokenType::LET:
      return "LET";
    case TokenType::PRINT:
      return "PRINT";
    case TokenType::IF:
      return "IF";
    case TokenType::ELSE:
      return "ELSE";
    case TokenType::WHILE:
      return "WHILE";
    case TokenType::TRUE_TOKEN:
      return "TRUE_TOKEN";
    case TokenType::FALSE_TOKEN:
      return "FALSE_TOKEN";
    case TokenType::TOKEN_EOF:
      return "EOF";
    default:
      return "UNKNOWN";
  }
}

int main() {
  // 1. The custom script we want to run
  std::string sourceCode =
      "let score = 100; \n if (score >= 90) { print score; }";

  std::cout << "--- CVM++ Lexer Booting Up --- \n";
  std::cout << "Scanning Script: \n" << sourceCode << "\n\n";

  // 2. Feed the script to our engine
  Lexer lexer(sourceCode);
  std::vector<Token> tokens = lexer.scanTokens();

  // 3. Print out the generated tokens
  for (const Token& token : tokens) {
    std::cout << "[Line " << token.line
              << "] Token: " << tokenTypeToString(token.type) << " | Lexeme: '"
              << token.lexeme << "'\n";
  }

  return 0;
}