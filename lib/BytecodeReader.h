#include "elfBytecodeReader.h"
#include "llvmBytecodeReader.h"

namespace nm {

enum target {
#define NM_TARGET(x) x ## _target,
#include "nmTarget.def"
};

} // namespace nm
