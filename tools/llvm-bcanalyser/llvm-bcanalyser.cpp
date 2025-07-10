#include "llvm-nm/BytecodeReader.h"
#include "llvm-nm/MemoryBuffer.h"
#include <iostream>
#include <ostream>
#include <stdexcept>

using namespace nm;

int main(int argc, char **argv) {
  if (argc != 2)
    return 1;

  try {
    MemoryBuffer buffer(argv[1]);

    auto reader = getBytecodeReader(buffer);
    if (reader) {
      std::cout << "file format : " << reader->formatName() << std::endl;
    } else {
      std::cout << "invalid file format" << std::endl;
    }
  } catch (std::runtime_error &e) {
    std::cout << e.what() << std::endl;
    return 1;
  }

  return 0;

} // namespace nm
