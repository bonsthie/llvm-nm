#ifndef LLVM_BYTECODE_READER
#define LLVM_BYTECODE_READER

#include <llvm-nm/BytecodeReader.h>

namespace nm::llvm {

class BytecodeReader : public nm::BytecodeReader {
  using ::nm::BytecodeReader::BytecodeReader;

  std::string formatName() const override { return "LLVM BC"; }

  std::string formatIdentifier() const override {
    return std::string("\x42\x43\xC0\xDE", 4);
  }

  Symbol nextSymbol(const std::string &path) override {
    return Symbol("none", 0);
  }
};

}

#endif // LLVM_BYTECODE_READER
