#ifndef BYTEREADER_H
#define BYTEREADER_H

#include <cstddef>
#include <cstdint>
#include <unistd.h>
#include <vector>

namespace nm {

class ByteReader {
    uint8_t *_data;

    /// size of the data buffer
    size_t _size;

    /// current possition in the buffer
    size_t  _index = 0;
    uint8_t _indexBits = 0;

  public:
    ByteReader(void *data, size_t size) : _data(static_cast<uint8_t *>(data)), _size(size) {}

    /// read bytes by bytes in the buffer of max 64
    /// return the number of byte read default is LSB
    size_t readBits(size_t n, uint64_t &ret) { return readBitsLSB(n, ret); }
    size_t readBits(size_t n, uint8_t &ret);

    size_t readBitsLSB(size_t n, uint64_t &ret);
    size_t readBitsMSB(size_t n, uint64_t &ret);

    uint8_t              readByte();
    std::vector<uint8_t> readBytes(size_t n);

    /// tell you if n bytes is style in the buffer
    bool isOverflowBits(size_t n) const;

    size_t byteRemaining() const;
    size_t bitsRemaining() const;
    size_t bitsRemainingUntilRounding(size_t rounding) const;

  private:
    void _advanceOfBits(size_t n);
};

} // namespace nm

#endif // BYTEREADER_H
