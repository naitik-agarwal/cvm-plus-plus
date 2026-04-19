#include "compiler.h"

#include <string>

// ==========================================
// BYTECODE WRITERS
// ==========================================
void Compiler::emitByte(uint8_t byte) { chunk.write(byte); }

void Compiler::emitConstant(double value) {
  emitByte(static_cast<uint8_t>(OpCode::OP_CONSTANT));  // Instruction
  int constantIndex = chunk.addConstant(value);  // Save the massive number
  emitByte(static_cast<uint8_t>(
      constantIndex));  // Tell the instruction where to find it
}

// ==========================================
// THE MAIN COMPILER LOOP
// ==========================================
Chunk Compiler::compile(const std::vector<std::unique_ptr<Stmt>>& statements) {
  for (const auto& stmt : statements) {
    if (stmt != nullptr) {
      compileStmt(stmt.get());
    }
  }
  emitByte(static_cast<uint8_t>(OpCode::OP_RETURN));  // Tell the VM to stop
  return chunk;
}

// ==========================================
// STATEMENT COMPILATION
// ==========================================
void Compiler::compileStmt(Stmt* stmt) {
  if (auto printStmt = dynamic_cast<PrintStmt*>(stmt)) {
    compileExpr(printStmt->expression.get());
    emitByte(static_cast<uint8_t>(OpCode::OP_PRINT));
  } else if (auto varStmt = dynamic_cast<VarStmt*>(stmt)) {
    // Compile the math first (puts result on stack)
    compileExpr(varStmt->initializer.get());

    // Save the variable name and emit the define instruction
    uint8_t nameIdx = chunk.addStringConstant(varStmt->name.lexeme);
    emitByte(static_cast<uint8_t>(OpCode::OP_DEFINE_GLOBAL));
    emitByte(nameIdx);
  }
}

// ==========================================
// EXPRESSION COMPILATION
// ==========================================
void Compiler::compileExpr(Expr* expr) {
  if (auto literal = dynamic_cast<LiteralExpr*>(expr)) {
    double val = std::stod(literal->value.lexeme);
    emitConstant(val);
  } else if (auto varExpr = dynamic_cast<VariableExpr*>(expr)) {
    // NEW: Handle reading variables!
    uint8_t nameIdx = chunk.addStringConstant(varExpr->name.lexeme);
    emitByte(static_cast<uint8_t>(OpCode::OP_GET_GLOBAL));
    emitByte(nameIdx);
  } else if (auto binary = dynamic_cast<BinaryExpr*>(expr)) {
    compileExpr(binary->left.get());
    compileExpr(binary->right.get());

    switch (binary->op.type) {
      case TokenType::PLUS:
        emitByte(static_cast<uint8_t>(OpCode::OP_ADD));
        break;
      case TokenType::MINUS:
        emitByte(static_cast<uint8_t>(OpCode::OP_SUBTRACT));
        break;
      case TokenType::STAR:
        emitByte(static_cast<uint8_t>(OpCode::OP_MULTIPLY));
        break;
      case TokenType::SLASH:
        emitByte(static_cast<uint8_t>(OpCode::OP_DIVIDE));
        break;
      case TokenType::EQUAL_EQUAL:
        emitByte(static_cast<uint8_t>(OpCode::OP_EQUAL));
        break;
      case TokenType::LESS:
        emitByte(static_cast<uint8_t>(OpCode::OP_LESS));
        break;
      case TokenType::GREATER:
        emitByte(static_cast<uint8_t>(OpCode::OP_GREATER));
        break;
      default:
        break;
    }
  }
}