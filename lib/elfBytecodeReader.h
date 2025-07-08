#ifndef ELF_BYTECODE_READER
#define ELF_BYTECODE_READER

#include <llvm-nm/BytecodeReader.h>
#include <string>

namespace nm::elf {

class BytecodeReader : public nm::BytecodeReader {
public:
  using ::nm::BytecodeReader::BytecodeReader;

  std::string formatName() const override { return "ELF"; }

  std::string formatIdentifier() const override {
    // 0x7F 'E' 'L' 'F'
    return std::string("\x7f"
                       "ELF",
                       4);
  }

  Symbol nextSymbol(const std::string &path) override {
    return Symbol("none", 0);
  }
};

} // namespace nm::elf

#endif // ELF_BYTECODE_READER
