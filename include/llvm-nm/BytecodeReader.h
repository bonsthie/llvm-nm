#ifndef NM_BYTECODE_READER_H
#define NM_BYTECODE_READER_H

#include <llvm-nm/MemoryBuffer.h>
#include <llvm-nm/Symbol.h>
#include <memory>
#include <optional>
#include <string>

namespace nm {

class BytecodeReader {
public:
  BytecodeReader() = default;
  explicit BytecodeReader(MemoryBuffer buf) : _buff(std::move(buf)) {}

  virtual ~BytecodeReader() = default;

  virtual std::string formatName() const = 0;
  virtual std::string formatIdentifier() const = 0;

  virtual bool isValidFormat(const MemoryBuffer &buffer) const {
    return buffer.view().starts_with(formatIdentifier());
  }

  virtual Symbol nextSymbol(const std::string &path) = 0;

private:
  std::optional<const MemoryBuffer> _buff;
};

std::unique_ptr<BytecodeReader> getBytecodeReader(MemoryBuffer &buffer);

} // namespace nm
#endif // NM_BYTECODE_READER_H
