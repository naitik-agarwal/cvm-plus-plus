#ifndef CHUNK_H
#define CHUNK_H

#include <cstdint>
#include <string>
#include <vector>

enum class OpCode : uint8_t {
  OP_CONSTANT,
  OP_ADD,
  OP_SUBTRACT,
  OP_MULTIPLY,
  OP_DIVIDE,
  OP_EQUAL,
  OP_LESS,
  OP_GREATER,
  OP_PRINT,
  OP_RETURN,
  // NEW: Variable Commands
  OP_DEFINE_GLOBAL,
  OP_GET_GLOBAL
};

struct Chunk {
  std::vector<uint8_t> code;
  std::vector<double> constants;
  std::vector<std::string> stringConstants;  // NEW: Vault for variable names

  void write(uint8_t byte) { code.push_back(byte); }

  int addConstant(double value) {
    constants.push_back(value);
    return constants.size() - 1;
  }

  // NEW: Save string and get its index
  int addStringConstant(const std::string& str) {
    stringConstants.push_back(str);
    return stringConstants.size() - 1;
  }
};

#endif