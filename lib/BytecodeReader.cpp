
#include "llvm-nm/BytecodeReader.h"
#include "BytecodeReader.h"
#include <iostream>

namespace nm {
void BytecodeReader(const std::string &path) {
  std::cout << "Reading bytecode from " << path << std::endl;

#define NM_TARGET(x) x::BytecodeReader(path);
#include "nmTarget.def"
}
} // namespace nm
