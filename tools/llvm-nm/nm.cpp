#include "llvm-nm/BytecodeReader.h"

int main(int argc, char** argv) {
	if (argc != 2)
		return 1;
    nm::BytecodeReader(argv[1]);
    return 0;
}
