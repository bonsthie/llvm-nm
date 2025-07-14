#include "llvm/MemoryBuffer.h"
#include <iostream>
#include <ostream>
#include <stdexcept>

using namespace nm;

int main(int argc, char **argv) {
  if (argc != 2)
    return 1;

  try {
    MemoryBuffer buffer(argv[1]);

  } catch (std::runtime_error &e) {
    std::cout << e.what() << std::endl;
    return 1;
  }

  return 0;

} // namespace nm
