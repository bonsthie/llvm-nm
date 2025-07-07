
#include "llvm-nm/BytecodeReader.h"
#include <iostream>

namespace nm {
    void readBytecode(const std::string &path) {
        std::cout << "Reading bytecode from " << path << std::endl;

#define NM_TARGET(x ,y) y(path);
		#include "nmTarget.def"
    }
}
