#ifndef ABITCODEREADER_H
#define ABITCODEREADER_H

#include "Symbol.h"
#include <fstream>
#include <string>
#include <vector>

namespace nm {

class ABytecodeReader {
public:
  virtual ~ABytecodeReader() = default;

  virtual const std::string &formatName() const = 0;
  virtual const std::string &formatIdentifier() const = 0;

  virtual bool isValidFormat(std::ifstream &file) const {
    const std::string &expected = formatIdentifier();
    std::vector<char> magic(expected.size());

    file.read(magic.data(), magic.size());
    file.clear();
    file.seekg(0);

    return std::equal(magic.begin(), magic.end(), expected.begin());
  }

  virtual Symbol nextSymbol(const std::string &path) = 0;

private:
  std::ifstream _file;
};

} // namespace nm

#endif // ABITCODEREADER_H
