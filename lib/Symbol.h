#ifndef SYMBOL_H
#define SYMBOL_H

#include <cstdint>
#include <string>

namespace nm {

class Symbol {
public:
  Symbol(std::string name, uint32_t offset, uint32_t type);

private:
  std::string _name;
  uint32_t _offset;
  uint32_t _type;
};

} // namespace nm

#endif // SYMBOL_H
