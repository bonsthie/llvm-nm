
#include "llvm-nm/BytecodeReader.h"
#include "elfBytecodeReader.h"
#include "llvmBytecodeReader.h"
#include <iostream>
#include <memory>

namespace nm {

std::unique_ptr<BytecodeReader> getBytecodeReader(MemoryBuffer &buffer) {
  std::cout << "selecting BytecodeReader" << std::endl;

#define NM_TARGET(x)                                                           \
  if (x ::BytecodeReader{}.isValidFormat(buffer))                              \
    return std::make_unique<x ::BytecodeReader>(std::move(buffer));
#include <nmTarget.def>
  return nullptr;
}

} // namespace nm
