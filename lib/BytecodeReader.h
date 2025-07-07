
namespace nm {

enum target {
#define NM_TARGET(x, y) x
#include "nmTarget.def"
};

} // namespace nm
