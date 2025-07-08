#ifndef SYMBOL_H
#define SYMBOL_H

#include <cstdint>
#include <string>

namespace nm {

class Symbol {
public:
  Symbol(const std::string &name, uint32_t offset, uint32_t type)
      : _name(name), _offset(offset), _type(type) {}

  Symbol(const std::string &name, uint32_t offset)
      : _name(name), _offset(offset), _type('?') {}

  const std::string &name(void) const { return _name; }
  uint32_t offset(void) const { return _offset; }
  uint8_t type(void) const { return _type; }

private:
  std::string _name;
  uint32_t _offset;
  uint8_t _type;
};

} // namespace nm

#endif // SYMBOL_H
